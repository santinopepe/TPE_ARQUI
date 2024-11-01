GLOBAL divideByZero
GLOBAL invalidOpCode


section .text

; Here we generate a divide by zero exception
divideByZero:
    mov rax, 0
    div rax
    ret

; Here we generate an invalid opcode exception
invalidOpCode:
    mov cr6, rax 
    ret
