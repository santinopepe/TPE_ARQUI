GLOBAL divideByZero
GLOBAL invalidOpCode


section .text

divideByZero:
    mov rax, 0
    div rax
    ret

invalidOpCode:
    mov cr6, rax 
    ret
