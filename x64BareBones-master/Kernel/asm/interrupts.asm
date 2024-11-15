
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt
GLOBAL _syscallHandler
GLOBAL _exception01Handler

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _exception0Handler
GLOBAL printRegAsm



GLOBAL saveState
EXTERN syscallDispatcher
EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN keyBoardHandler
EXTERN printRegisters
EXTERN getStackBase
EXTERN retUserland
SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ;PARAMETER
	cmp rdi, 1 
	jne .noSave
	
	saveRegisters

	.noSave:
	mov rsi,rsp
	mov rdi,%1
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

%macro saveRegisters 0
	mov [registers+8*0],	rax
	mov [registers+8*1],	rbx
	mov [registers+8*2],	rcx
	mov [registers+8*3],	rdx
	mov [registers+8*4],	rsi
	mov [registers+8*5],	rdi
	mov [registers+8*6],	rbp
	mov [registers+8*7], r8
	mov [registers+8*8], r9
	mov [registers+8*9], r10
	mov [registers+8*10], r11
	mov [registers+8*11], r12
	mov [registers+8*12], r13
	mov [registers+8*13], r14
	mov [registers+8*14], r15

	mov rax, rsp

	add rax, 160 ;Move the stack pointer to the end of the stack

	mov [registers+8*15], rax ;Save the stack pointer
	mov rax, [rsp+15*8] 
	mov [registers+8*16], rax ;Save the instruction pointer
	mov rax, [rsp+17*8]
	mov [registers+8*17], rax ;Save the flags

%endmacro


%macro exceptionHandler 1
	pushState
	saveRegisters

	;Call the exception dispatcher

	mov rdi, %1 ;PARAMETER
	call exceptionDispatcher


	popState         ;Restore the registers
	call getStackBase  ;Get the stack base
	sub rax, 20h
	mov qword [rsp+8*3], rax
	call retUserland  ;Return to userland
	mov qword [rsp], rax
	iretq

%endmacro


printRegAsm:
	mov qword rdi, registers
	call printRegisters
	ret

_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; AX = picSlaveMask
    out	0A1h,al
    pop     rbp
    retn

_syscallHandler:
	pushState
	mov rbp, rsp

	push r9
	mov r9, r8
	mov r8, rcx
	mov rcx, rdx
	mov rdx, rsi
	mov rsi, rdi
	mov rdi, rax
	call syscallDispatcher ;Call the syscall dispatcher
	mov [aux], rax 

	mov al,20h
	out 20h,al

	pop r9
	mov rsp,rbp 
	popState

	mov rax, [aux]
	iretq


;This function saves the state of the registers 
saveState:
	pushState
	saveRegisters
	popState
	ret

;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0 

;Invalid Opcode Exception
_exception01Handler:
	exceptionHandler 6 


haltcpu:
	cli
	hlt
	ret

SECTION .bss
	aux resq 1
	exceptregs resq 18	    ;Registers for exceptions
	registers resq 18		;Registers for keyboard
	capturedReg resb 1		;Flag to know if the registers were captured