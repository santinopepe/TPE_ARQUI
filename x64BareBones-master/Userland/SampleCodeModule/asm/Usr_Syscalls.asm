section .text

GLOBAL sysCall_read
GLOBAL sysCall_write
GLOBAL sysCall_clear
GLOBAL sysCall_seconds
GLOBAL sysCall_minutes
GLOBAL sysCall_hours
GLOBAL sysCall_sound
GLOBAL sysCall_putRectangle
GLOBAL sysCall_ticks
GLOBAL sysCall_wait
GLOBAL sysCall_ColorWrite
GLOBAL sysCall_writeRegs

sysCall_read:
    mov rax, 0
    int 80h
    ret

sysCall_write:
    mov rax, 1
    int 80h
    ret

sysCall_clear:
    mov rax, 2
    int 80h
    ret

sysCall_seconds:
    mov rax, 3
    int 80h
    ret

sysCall_minutes:
    mov rax, 4
    int 80h
    ret

sysCall_hours:
    mov rax, 5
    int 80h
    ret

sysCall_sound:
    mov rax, 6
    int 80h
    ret

sysCall_putRectangle:
    mov rax, 7
    int 80h
    ret


sysCall_ticks:
    mov rax, 8
    int 80h
    ret

sysCall_wait:
    mov rax, 9
    int 80h
    ret

sysCall_ColorWrite:
    mov rax, 10
    int 80h
    ret

sysCall_writeRegs:
    mov rax, 11
    int 80h
    ret    
