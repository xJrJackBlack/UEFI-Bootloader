BITS 16       ; Generate 16 bit code, will be used within the 16 bit mode
ORG 0x7C00    ; Set program origin at address 0x7C00

setup:      

xor ax, ax        ; Set ax, ds and ss registers to 0         
mov ds, ax 
mov ss, ax
mov sp, 0x7C00    ; Move stack pointer to program origin


mov si, msg       ; Move the string 'msg' isnt the si register
call print
hlt

print:

mov al, [si]      ; Dereference si and store first byte in al register
inc si            ; Increment si register
test al, al       ; Perform bitwise AND on al register to test if the current byte is 0 aka null-terminator
jz print_end      ; If so end the print function
mov ah, 0x0E      ; Load 0x0E value into ah register for TeleType Output 
int 0x10          ; Issue 0x10 interrupt
jmp print         

print_end:
ret


msg db "Hello World!", 0  ; Define null-terminated string

times 510-($-$$) db 0     ; Fill up remaining bootloader 512 byte area, up to the 510th byte with 0's 
dw 0xAA55                 ; Write the 2-byte boot-signature / magic-number to end of 512 byte bootloader memory area 
