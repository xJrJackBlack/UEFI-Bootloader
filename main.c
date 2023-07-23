#include "uefi_structures.h"
#include "uefi_lib.h"
#include "linux.h"

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
    UINTN fileSize = GetFileSize(file);                       // Stores size of file contents

    if (file != NULL)
    {
        Status = SystemTable->BootServices->AllocatePool(EfiLoaderData, fileSize, (VOID **)&FileContents); // Allocate memory for file content buffer
        Status = file->Read(file, &fileSize, FileContents);                                                // Store file content in buffer
        file->Close(file);
    }

    CHAR16 **names = parseConfigFile(SystemTable, FileContents, fileSize); // parse simple.cfg

    VOID *kernelBuffer = loadKernel(SystemTable, Volume, names[0]);

    checkKernelMagicNumber(SystemTable, kernelBuffer); // validate kernel image magic number/signature

    UINTN setupCodeSize = getSetupCodeSize(SystemTable,kernelBuffer); // get size of setup code from kernel image
    UINTN realModeCodeSize = 512 + setupCodeSize; 

    struct boot_params *boot_params;
    SystemTable->BootServices->AllocatePool(EfiLoaderData, sizeof(struct boot_params), (VOID **)&boot_params); // Allocate memory for boot_params
    SystemTable->BootServices->SetMem(boot_params, sizeof(struct boot_params), 0); // Initialise to all zero

    struct setup_header *setup_header = &boot_params->hdr;

    UINTN setupHeaderEnd = getSetupHeaderEnd(SystemTable, kernelBuffer);
    extractLoadSetupHeader(SystemTable, kernelBuffer, boot_params, setupHeaderEnd);

    printBootProtocolVersion(SystemTable, setup_header);
    validateBootSector(SystemTable, setup_header);

    CHAR8 *cmdline;  // Will specify the kernel command line parameter in cmdline, can be used to customise kernel booting options 
    SystemTable->BootServices->AllocatePool(EfiLoaderData, sizeof("root=/dev/sdb"), (VOID**) &cmdline);
    SystemTable->BootServices->CopyMem(cmdline, "root=/dev/sdb", sizeof("root=/dev/sdb"));

    setup_header->cmd_line_ptr = (UINT32)(uintptr_t)cmdline;    // Setting command line paramters in boot_params setup_header (hdr field)
    setup_header->vid_mode = 0xffff;     // set vid_mode of kernel to 'normal mode'
    setup_header->type_of_loader = 0xff; // Used to indicate the bootloaded that loaded the kernel, set to unique value so kernel can identify bootloader

    VOID *initrdBuffer = loadInitrd(SystemTable, Volume, names[1], setup_header);

    struct screen_info *screen_info = &boot_params->screen_info;
    videoSetup(SystemTable, screen_info);
    
    jumpToEntry(SystemTable, ImageHandle, realModeCodeSize);

    __asm__("movl %edx, %eax\n\t"
        "addl $2, %eax\n\t");

    Delay(SystemTable, 5);

    return 0;
}