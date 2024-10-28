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
GLOBAL sysCall_cursorX
GLOBAL sysCall_cursorY
GLOBAL sysCall_setSize
GLOBAL sysCall_getScreenHeight
GLOBAL sysCall_getCharSize
GLOBAL sysCall_Cursor
GLOBAL getDate
GLOBAL sysCall_snapshotState

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

sysCall_cursorX:
    mov rax, 12
    int 80h
    ret

sysCall_cursorY:
    mov rax, 13
    int 80h
    ret

sysCall_setSize:
    mov rax, 14
    int 80h
    ret

sysCall_getScreenHeight:
    mov rax, 15
    int 80h
    ret

sysCall_getCharSize:
    mov rax, 16
    int 80h
    ret

sysCall_Cursor:
    mov rax, 17
    int 80h
    ret

getDate: 
    push rbp
    mov rbp, rsp

    mov rax, rdi
    out 70h, al
    xor rax, rax
    in al, 71h

    mov rsp, rbp
    pop rbp
    ret
sysCall_snapshotState:
    mov rax, 18
    int 80h
    ret