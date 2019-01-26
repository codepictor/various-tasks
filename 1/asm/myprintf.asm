section .text
global main

		jmp main


;=======================================================================================
; binnum
; creating the string with output binary number
; Entry: output number in the stack (outnum)
; Result: string 'answer'
; Destroy: rax, rbx, rcx, rdx
;=======================================================================================
binnum:
		push rbp
		mov rbp, rsp

		xor rdx, rdx   				; rdi = 0 (number of current digit of output number)
		mov rax, [rbp + 16]			; rax = number
		
binnum_for:	rol rax, 1                         	; number << 1
		jc binnum_one                             ; checking the flag CF
		mov byte [answer + rdx], '0'		; if (CF == 0) current_digit = 0
		jmp binnum_check

binnum_one:	mov byte [answer + rdx], '1'		; else current_digit = 1

binnum_check:	inc rdx                                 ; rdi++					
		cmp rdx, 64				; in 64-bit system (in register there are 64 bits)
		je binnum_finish
		jmp binnum_for

binnum_finish:	mov byte [answer + rdx], '$'		; ending of the output string
		call outnum				; printing the result

		pop rbp
		ret
;=======================================================================================
; end of binnum
;=======================================================================================



;=======================================================================================
; hexnum
; creating the string with output hex number
; Entry: output number in the stack (outnum)
; Result: string 'answer'
; Destroy: rax, rbx, rcx, rdx, rdi
;======================================================================================= 
hexnum:
		push rbp
		mov rbp, rsp

		xor rdi, rdi                        	; rdi = 0 (counter)
		mov rax, [rbp + 16]			; rax = number
		mov cl, 60				; offset for getting in dl the current digit
		mov rbx, 0xf000000000000000             ; for getting in rdx the current digit (1111000...0000)

hexnum_for:	mov rdx, rax				; copy the current digit -> rdx
		and rdx, rbx				; getting in rdx the current digit
		shr rdx, cl				; getting in dl the current digit
		add dl, '0'       	     		; getting in dl ASCII-code of the current digit
		cmp dl, '9'                             ; if (A <= current digit <= F)
		jna hexnum_nletter                      ; calculation ASCII-code of the current digit if it is A, B, C, D, E, F
		add dl, 7			        ; if (the current digit is A, B, C, D, E, F) ASCII-code += 7
hexnum_nletter: mov [answer + rdi], dl			; copying ASCII-code of the current digit to the string 'answer'
		shr rbx, 4
		sub cl, 4
      		inc rdi                                 ; counter++
		cmp rbx, 0
		jne hexnum_for

		mov byte [answer + rdi], '$'		; ending of the output string
		call outnum				; printing the result

		pop rbp
		ret
;=======================================================================================
; end of hexnum
;=======================================================================================



;=======================================================================================
; octnum
; creaing the string with output oct number
; Entry: output number in the stack (outnum)
; Result: string 'answer'
; Destroy: rax, rbx, rcx, rdx, rdi
;======================================================================================= 
octnum:
		push rbp
		mov rbp, rsp

		xor rdi, rdi                        	; rdi = 0 (counter)
		mov rax, [rbp + 16]			; rax = number
		mov cl, 63				; offset for getting in dl the current digit
		mov rbx, 0x8000000000000003             ; rbx = 10000000...0011

octnum_for:	mov rdx, rax				; copying the current number -> rdx
		and rdx, rbx				; getting in rdx the current digit
		shr rdx, cl				; getting in dl the current digit
		add dl, '0'       	     		; al += '0'
		mov [answer + rdi], dl
		ror rbx, 3
		sub cl, 3
      		inc rdi                                 ; counter++
		cmp rdi, 22
		jne octnum_for
		
		mov byte [answer + rdi], '$'		; ending of the output string
		call outnum				; printing the result

		pop rbp
		ret
;=======================================================================================
; end of octnum
;=======================================================================================


;=======================================================================================
; decnum
; creating the string with output dec number
; Entry: output number in the stack (outnum)
; Result: string 'answer'
; Destroy: rax, rbx, rcx, rdx
;=======================================================================================
decnum:
		push rbp
		mov rbp, rsp

		mov rax, [rbp + 16]			; rax = number
		mov rbx, 20                             ; di = 20 (index of the current digit)
		mov ecx, 10                             ; divisor = 10
		
decnum_for:	xor rdx, rdx				; rdx = 0
		div ecx                                 ; rax / ecx (ecx = 10)
		add dl, '0'                             ; dl is ASCII code of digit
		dec rbx
		mov [answer + rbx], dl            
		cmp rbx, 0
		ja decnum_for
		
		mov byte [answer + 20], '$'		; ending of the string
		call outnum				; printing the result
		
		pop rbp
		ret
;=======================================================================================
; end of decnum
;=======================================================================================



;=======================================================================================
; outnum
; printing the number (without leading zeros)
; Entry: none (but this function uses 'string')
; Result: the number on the screen
; Destroy: rax, rbx, rcx, rdx
;=======================================================================================
outnum:
		push rbp
		mov rbp, rsp

		mov rcx, answer				; rcx is address of the beginning of the string
		xor rdx, rdx				; rdx = 0

outnum_for1:	inc rcx					; removing leading zeros
		cmp byte [rcx - 1], '0'
		je outnum_for1
		dec rcx

outnum_for2:	inc rdx					; calculation of the length of the string
		cmp byte [rcx + rdx - 1], '$'
		jne outnum_for2
		dec rdx

		cmp byte [rcx], '$'			; if the number == 0 print '0'
		jne outnum_finish
		dec rcx
		inc rdx

outnum_finish:	mov rax, 4				; printing the result
		mov rbx, 1
		int 0x80

		pop rbp
		ret
;=======================================================================================
; end of outnum
;=======================================================================================



; ======================================================================================
; stringout 
; printing a string
; Entry: address of the string in the stack
; Result: printed string on the screen
; Destroy: rax, rbx, rcx, rdx
; ======================================================================================
outstring:
		push rbp
		mov rbp, rsp

		mov rax, [rbp + 16]			; rax = address of the string
		xor rdx, rdx				; rdx is a number of the current symbol

outstring_for:	cmp byte [rax + rdx], 0			; checking the end of the string
		je outstring_out
		inc rdx
		jmp outstring_for

outstring_out:	mov rcx, rax				; printing the string
		mov rax, 4
		mov rbx, 1
		int 0x80

		pop rbp
		ret
; ======================================================================================
; end of outstring
; ======================================================================================


		
; ======================================================================================
; outsymbol
; printing a symbol
; Entry: a symbol in the stack
; Result: printed symbol on the screen
; Destroy: rax, rbx, rcx, rdx
; ======================================================================================

outsymbol:
		push rbp
		mov rbp, rsp

		mov rcx, [rbp + 16]			; output symbol is in cl
		mov [answer], cl			

		mov rax, 4				; printing the symbol
		mov rbx, 1
		mov rcx, answer
		mov rdx, 1				; number of output symbols
		int 0x80

		pop rbp
		ret
; ======================================================================================
; end of outsymbol
; ======================================================================================


; ======================================================================================
; output
; calling appropriate function (binnum, hexnum, etc)
; Entry: number of printed arguments, specificator (both in the stack)
; Result: calling appropriate function (only one)
; Destroy: rax, rbx, rcx (other functions like 'binnum' or 'hexnum' can destroy other registers - see descriptions of these functions)
; ======================================================================================
output:
		push rbp
		mov rbp, rsp

		mov rax, [rbp + 24]			; specificator of output in al
		mov rcx, [rbp + 16]			; number of printed arguments in rcx
		mov rbx, rbp				
		add rbx, 64				; the first argument of 'myprintf'
		shl rcx, 3				; rcx = rcx * 8 (for 64-bit)
		add rbx, rcx				; address of the current argument in rbx
		shr rcx, 3				; rcx = rcx / 8 (for 64-bit)
		mov rbx, [rbx]				; the current argument in rbx
		push rax				; saving rax, rbx, rcx, rdx
		push rcx				; because of calling other functions
		push rbx

		cmp al, 'b'				; printing binary number
		jne output1
		mov rax, binnum   
		
output1:	cmp al, 'x'				; printing hex number
		jne output2
		mov rax, hexnum

output2:	cmp al, 'o'				; printing oct number
		jne output3
		mov rax, octnum
		
output3:	cmp al, 'd'				; printing dec number
		jne output4
		mov rax, decnum
				
output4:	cmp al, 'c'				; printing a character
		jne output5
		mov rax, outsymbol

output5:	cmp al, 's'				; printing a string
		jne output_call
		mov rax, outstring

output_call:	call rax
		pop rbx					
		pop rcx
		pop rax
		pop rbp
		ret
; ======================================================================================
; end of output
; ======================================================================================


; ======================================================================================
; myprintf
; it is my own 'printf'!
; Entry: arguments and the format string in the stack (the format string must be on the top)
; Result: printing on the screen
; Destroy: rax, rbx, rcx, rdx, rsi
; ======================================================================================
myprintf:
		push rbp
		mov rbp, rsp

		xor rbx, rbx				; index of current symbol in the string 'fmt'
		xor rcx, rcx				; rcx is number of put arguments
		mov rsi, [rbp + 16]			; rsi is address of string 'fmt'

myprintf_for:	mov dl, [rsi + rbx]			; current symbol of 'fmt' is in dh
		cmp dl, 0x00				; checking ending of the string
		je myprintf_end				; if the last symbol is 0x00 'myprintf' will finish
		cmp dl, '%'				
		je myprintf_perc

myprintf_symb:	push rax				; printing ordinary symbol or '%'
		push rbx
		push rcx
		push rdx
		call outsymbol
		pop rdx
		pop rcx
		pop rbx
		pop rax
		inc rbx
		jmp myprintf_for

myprintf_perc:	inc rbx					; analysis of the symbol '%'
		mov dl, [rsi + rbx]
		cmp dl, '%'
		je myprintf_symb
		push rbx				; rbx is index of current symbol in the string 'fmt'
		push rdx				; specificator of output in dl
		push rcx				; rcx is number of put arguments
		call output				; printing
		pop rcx
		pop rdx
		pop rbx
		inc rcx
		inc rbx
		jmp myprintf_for

myprintf_end:	pop rbp
		ret
; ======================================================================================
; end of myprintf
; ======================================================================================








main:		push 100
		push 3802
		push '3'
		push '<'
		push qword me


		push qword msg2
		push qword 98
		push qword msg1
		push qword 3802
		push qword 1234567890
		push qword 255
		push qword 0
		

		
		

		push qword fmt
		call myprintf
		add rsp, 12*8

		mov rax, 1
		mov rbx, 0
		int 0x80


section .data
		fmt:	  db "%o %b %d %x 1423 %s %c %%^ %s %% %s %c%c %x %d%%", 0xa, 0x00
		;fmt:	  db "What is today? It's %s, %d of %s.%s %c%c %x %d%%, %s %c%c %x %d%%", 0xa, 0
		me:	  db "I", 0
                answer:   times 100 db 0
		msg1: 	  db "abc", 0
		msg2:	  db "azaza", 0
		


