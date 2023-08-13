#include "uefi_structures.h"
#include "uefi_lib.h"
#include "linux.h"

static void
start_kernel(
    VOID *kernel,
    const struct boot_params *boot_params,
    struct gdt_ptr_struct *gdt_ptr,
    UINTN realModeCodeSize, EFI_SYSTEM_TABLE *SystemTable, EFI_HANDLE ImageHandle);
    
EFI_STATUS
EFIAPI
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;
    EFI_INPUT_KEY Key;

    printIntroduction(SystemTable);
    clearKeyboardBuffer(SystemTable); // clear keyboard buffer
    do
    {
        Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key);

        if (Key.UnicodeChar == L'r' || Key.UnicodeChar == L'R')
        {
            COLD_REBOOT(SystemTable);
        }
        else if (Key.UnicodeChar == L'b' || Key.UnicodeChar == L'B')
        {
        }
        else if (Key.UnicodeChar == L's' || Key.UnicodeChar == L'S')
        {
            SHUTDOWN(SystemTable);
        }

    } while (Status == EFI_NOT_READY || !(Key.UnicodeChar == L'r' || Key.UnicodeChar == L'R' || Key.UnicodeChar == L'b' || Key.UnicodeChar == L'B'));

    EFI_FILE_PROTOCOL *Volume = GetVolume(SystemTable, ImageHandle);   // Open EFI FAT32 filesystem
    EFI_FILE_PROTOCOL *file = checkForConfigFile(SystemTable, Volume); // Check if 'simple.cfg' exists and if so points to it
    VOID *FileContents = NULL;                                         // Points to memory where file contents are stored
    UINTN fileSize = GetFileSize(file);                                // Stores size of file contents

    if (file != NULL)
    {
        Status = SystemTable->BootServices->AllocatePool(EfiLoaderData, fileSize, (VOID **)&FileContents); // Allocate memory for file content buffer
        Status = file->Read(file, &fileSize, FileContents);                                                // Store file content in buffer
        file->Close(file);
    }

    CHAR16 **names = parseConfigFile(SystemTable, FileContents, fileSize); // parse simple.cfg

    VOID *kernelBuffer = loadKernel(SystemTable, Volume, names[0]);

    checkKernelMagicNumber(SystemTable, kernelBuffer); // validate kernel image magic number/signature

    UINTN setupCodeSize = getSetupCodeSize(SystemTable, kernelBuffer); // get size of setup code from kernel image
    UINTN realModeCodeSize = 512 + setupCodeSize;

    struct boot_params *boot_params;
    SystemTable->BootServices->AllocatePool(EfiLoaderData, sizeof(struct boot_params), (VOID **)&boot_params); // Allocate memory for boot_params
    SystemTable->BootServices->SetMem(boot_params, sizeof(struct boot_params), 0);                             // Initialise to all zero

    struct setup_header *setup_header = &boot_params->hdr;

    UINTN setupHeaderEnd = getSetupHeaderEnd(SystemTable, kernelBuffer);
    extractLoadSetupHeader(SystemTable, kernelBuffer, boot_params, setupHeaderEnd);

    printBootProtocolVersion(SystemTable, setup_header);
    validateBootSector(SystemTable, setup_header);

    CHAR8 *cmdline; // Will specify the kernel command line parameter in cmdline, can be used to customise kernel booting options
    SystemTable->BootServices->AllocatePool(EfiLoaderData, sizeof("root=/dev/sdb"), (VOID **)&cmdline);
    SystemTable->BootServices->CopyMem(cmdline, "root=/dev/sdb", sizeof("root=/dev/sdb"));

    setup_header->cmd_line_ptr = (UINT32)(uintptr_t)cmdline; // Setting command line paramters in boot_params setup_header (hdr field)
    setup_header->vid_mode = 0xffff;                         // set vid_mode of kernel to 'normal mode'
    setup_header->type_of_loader = 0xff;                     // Used to indicate the bootloaded that loaded the kernel, set to unique value so kernel can identify bootloader

    VOID *initrdBuffer = loadInitrd(SystemTable, Volume, names[1], setup_header);

    struct screen_info *screen_info = &boot_params->screen_info;
    videoSetup(SystemTable, screen_info);

    // final paragraph

    struct gdt_entry_struct gdt[4]; // 0 is null descriptor, 1 is null descriptor, 2 is __BOOT_CS(0x10), 3 is __BOOT_DS(0X18)
    

    // base_low, base_middle and base_high must be set to 0, since we are using flat memory model 
    // where every segments base address starts at 0

    gdt[0].limit_low    = 0;           
    gdt[0].base_low     = 0;           
    gdt[0].base_middle  = 0;      // Setting NULL descriptor at gdt[0]
    gdt[0].access       = 0;              
    gdt[0].granularity  = 0;
    gdt[0].base_high    = 0;

    gdt[1].limit_low    = 0;           
    gdt[1].base_low     = 0;           
    gdt[1].base_middle  = 0;      // Setting NULL descriptor at gdt[1]
    gdt[1].access       = 0;              
    gdt[1].granularity  = 0;
    gdt[1].base_high    = 0;


    gdt[2].limit_low    = 0xFFFF; // Setting __BOOT_CS(0x10) descriptor at gdt[2]
    gdt[2].base_low     = 0;      // Because segment selector 0x10 in 16 bit binary looks like:     
    gdt[2].base_middle  = 0;      // Index           TI   RPL
                                  // 0000000000010   0    00
    gdt[2].access       = 0x9A;   // __BOOT_CS(0x10) has execute/read           
    gdt[2].granularity  = 0xCF;
    gdt[2].base_high    = 0;


    gdt[3].limit_low    = 0xFFFF; // Setting __BOOT_DS(0x18) descriptor at gdt[3]          
    gdt[3].base_low     = 0;      // Because segment selector 0x18 in 16 bit binary looks like:     
    gdt[3].base_middle  = 0;      // Index           TI  RPL
                                  // 0000000000011   0   00
    gdt[3].access       = 0x92;   // __BOOT_DS(0x18) has read/write           
    gdt[3].granularity  = 0xCF;
    gdt[3].base_high    = 0;

    struct gdt_ptr_struct gdt_ptr;
    
    gdt_ptr.limit = sizeof(gdt) - 1;
    gdt_ptr.base  = (UINT64) gdt;

    ACPIsetup(SystemTable, boot_params);

    start_kernel(kernelBuffer, boot_params, &gdt_ptr, realModeCodeSize, SystemTable, ImageHandle);
  
    Delay(SystemTable, 60);

    return 0;
}

static void
start_kernel(
    VOID *kernel,
    const struct boot_params *boot_params,
    struct gdt_ptr_struct *gdt_ptr,
    UINTN realModeCodeSize, EFI_SYSTEM_TABLE *SystemTable, EFI_HANDLE ImageHandle)
{

    EFI_PHYSICAL_ADDRESS JumpAddr = (EFI_PHYSICAL_ADDRESS)(kernel + realModeCodeSize + 0x200);    // Address to jump to, in order to start kernel
    
    UINTN MemoryMapSize = 0;
    EFI_MEMORY_DESCRIPTOR *MemoryMap = NULL;
    UINTN MapKey;
    UINTN DescriptorSize;
    UINT32 DescriptorVersion;

    obtainMemoryMap(SystemTable, &MemoryMapSize, &MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);

    setTextPosition(SystemTable, 4, 12);
    Print(SystemTable, L"Jumping to kernel entry point...\n");
    Delay(SystemTable, 1);

    SystemTable->BootServices->ExitBootServices(ImageHandle, MapKey);

    /*
    __asm__ volatile("cli" ::: "memory");                  // Disable interrupts
    __asm__ volatile("movq %0, %%rsi" ::"r"(boot_params)); // Load boot_params base address into $rsi
    __asm__ volatile("lgdt %0" :: "m"(gdt_ptr));           // Use lgdt instruction to load gdt   

    __asm__ volatile("mov $0x18, %ax");  // move __BOOT_DS value into ax register
    __asm__ volatile("mov %ax, %ds");    // set Data Segment register
    __asm__ volatile("mov %ax, %es");    // set Extra Segment register
    __asm__ volatile("mov %ax, %ss");    // set Stack Segment register

    // Load __BOOT_CS(0x10) into CS segment register

    __asm__ volatile("mov %0, %%rbx" :: "m" (JumpAddr));
    __asm__ volatile("pushq $0x10");
    __asm__ volatile("pushq %rbx");
    __asm__ volatile("lretq");
    */

    __asm__ volatile (
        "cli;"                       // Disable interrupts
        "lgdt %[gdt_ptr];"           // Load GDT
        "mov $0x18, %%ax;"           // Load __BOOT_DS value into ax
        "mov %%ax, %%ds;"            // Set Data Segment register
        "mov %%ax, %%es;"            // Set Extra Segment register
        "mov %%ax, %%ss;"            // Set Stack Segment register
        "mov %[boot_params], %%rsi;" // Load boot_params base address into rsi
        "pushq $0x10;"               // Push __BOOT_CS(0x10)
        "pushq %[jump_addr];"        // Push JumpAddr directly
        "lretq"                      // Far return
        :
        : [boot_params] "m" (boot_params), [gdt_ptr] "m" (gdt_ptr), [jump_addr] "m" (JumpAddr)
        : "memory", "rax", "cc"
    );
}