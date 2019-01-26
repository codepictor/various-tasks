;=======================================================================================
;			File password.asm
;			Date 01.03.2015
;
;			Checking input word (password)
;=======================================================================================

.model tiny
.code
org 100h

begin:		mov ah, 09h           				; greeting
		mov dx, offset msg_greeting
		int 21h

		mov ah, 0ah                                     ; scanning a string
		mov dx, offset string
		int 21h

		mov bl, 0                                       ; length of the password will be in 'bl'
passwd:		cmp password[bx], '$'                           ; comparing symbol 'password[bx]' and '$'
		je next                                         ; jump if we reach ending of the password
		inc bl                                          ; bl++
		jmp passwd                                      ; continuation of calcuation length of the password
	
next:		cmp string[1], bl 				; comparing length of the password and length of input string
		jne bad                                         ; if they are not equal, jump 'bad'
		mov cx, bx                                      ; copy 'bx' -> 'cx'
		mov bx, 0                                       ; bx = 0 (length of the password is in cx now)

compare:	mov al, password[bx]
		cmp string[bx + 2], al                          ; comparing symbol 'string[bx + 2]' and 'password[bx]'
		jne bad                                         ; if they are not equal, jump 'bad'
		inc bx                                          ; bx++
		cmp bx, cx                                      
		jnl good                                        ; if (bx == cx) the password and input string are equal
		jmp compare

good:	   	mov ah, 09h                                     ; printing message about correct password
		mov dx, offset msg_correct
		int 21h
		jmp finish
	
bad:		mov ah, 09h                                     ; printing message about incorrect password
		mov dx, offset msg_incorrect
		int 21h

finish:		mov ax, 4c00h                                   ; exit
		int 21h


.data
		msg_greeting  db 	10, 13, 'Please, enter your password', 10, 13, '$'
		string        db 	90, 99 dup(0)
		password      db 	'helloasm$'
		msg_correct   db 	'Correct password$'
		msg_incorrect db 	'Incorrect password$'

end begin

;=======================================================================================
;					END
;=======================================================================================
