;
; Boot sector to read sectors from boot disk.
;
[org 0x7c00]

mov [BOOT_DRIVE], dl    ; BIOS stores our boot drive in dl.

mov bp, 0x8000          ; We set our stack safely away.
mov sp, bp

mov bx, 0x9000          ; Load 5 sectors to 0x0000 (es):0x9000(bx)
mov dh, 5               
mov dl, [BOOT_DRIVE]    ; From boot disk.
call disk_load

mov dx, [0x9000]        ; Print out the first loaded word, which we expect to 
call print_hex          ; be 0xdada, stored at 0x9000.

mov dx, [0x9000 + 512]  ; Print second word from the 2nd loaded sector. Should 
call print_hex           ; be 0xface

jmp $



%include "print_string.asm"
%include "print_hex.asm"
%include "disk_load.asm"

BOOT_DRIVE:
 db 0


; Boot sector padding
times 510-($-$$) db 0
dw 0xaa55


; We know that BIOS will load only the first 512-byte sector from disk.
times 256 dw 0xdada
times 256 dw 0xface

;times 2048 db 0
