GLOBAL divideByZero
GLOBAL invalidOpCode


section .text

divideByZero:
    mov rax, 0
    div rax
    ret

invalidOpCode:
    db 0xFF, 0xFF
    ret
