section .text

GLOBAL read
GLOBAL write
GLOBAL clear
GLOBAL seconds
GLOBAL minutes
GLOBAL hours
GLOBAL sound
GLOBAL square
GLOBAL ticks
GLOBAL wait

read:
    mov rax, 0
    int 80h
    ret

write:
    mov rax, 1
    int 80h
    ret

clear:
    mov rax, 2
    int 80h
    ret

seconds:
    mov rax, 3
    int 80h
    ret

minutes:
    mov rax, 4
    int 80h
    ret

hours:
    mov rax, 5
    int 80h
    ret

sound:
    mov rax, 6
    int 80h
    ret

square:
    mov rax, 7
    int 80h
    ret


ticks:
    mov rax, 8
    int 80h
    ret

wait:
    mov rax, 9
    int 80h
    ret
