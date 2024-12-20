GLOBAL cpuVendor
GLOBAL getKey
Global getSec
Global getMin
Global getHour
GLOBAL beep
GLOBAL stop_beep
GLOBAL .startFunc
GLOBAL .endFunc
GLOBAL inb
GLOBAL outb

section .text
	


cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

; Function to get the key from the keyboard
getKey:
	push rbp
	mov rbp, rsp
	
	xor rax, rax
	in al, 0x60

	mov rsp, rbp
	pop rbp
	ret

; Functions to get the time from the RTC
getSec:
	push rbp
	mov rbp, rsp

	mov al, 0x00
	out 0x70, al
	in al, 0x71

	mov rsp, rbp
	pop rbp
	ret


getMin:
	push rbp
	mov rbp, rsp

	mov al, 0x02
	out 0x70, al
	in al, 0x71

	mov rsp, rbp
	pop rbp
	ret


getHour:
	push rbp
	mov rbp, rsp

	mov al, 0x04
	out 0x70, al
	in al, 0x71

	mov rsp, rbp
	pop rbp
	ret

; Functions to beep
beep:
	push rbp
    push rdx
	mov rbp, rsp

	mov al, 0xB6
	out 43h, al

    mov rdx, 0
    mov rax, 1193180
    div rdi
    
	out 42h, al
	mov al, ah
	out 42h, al

	in al, 61h
 	or al, 03h
	out 61h, al

	mov rsp, rbp
    pop rdx
	pop rbp
	ret

stop_beep:
  	in al, 61h
	and al, 0xFC
	out 61h, al
  	ret





inb:				; Functions for the correct use of the beep
	push rbp
	mov rbp, rsp

    mov rdx,rdi
    in al,dx		; 8 bit pasage

	mov rsp, rbp
	pop rbp
	ret

outb:
	push rbp
	mov rbp, rsp

    mov rax, rsi    
    mov rdx, rdi
	out dx, al		; 8 bit pasage

	mov rsp, rbp
	pop rbp
	ret

