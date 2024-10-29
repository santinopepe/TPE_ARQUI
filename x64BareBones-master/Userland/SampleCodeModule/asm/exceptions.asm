

section .text
GLOBAL divideByZero
GLOBAL invalidOpCode

divideByZero:
    mov rax, 0
    div rax
    ret

invalidOpCode:
    rtpmc
    ret
