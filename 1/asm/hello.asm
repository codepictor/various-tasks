;nasm -o hello.o -felf64 -l hello.lst hello.asm
;gcc -o hello hello.o

SECTION .data
msg     db "Hello, world!",0xa  
fmt     db "%s"
len     equ $ - msg
SECTION .text
global main           ; the program entry point
extern printf
main:

;mov eax, 4      ; 'write' syscall
;mov ebx, 1      ; file descr. 1 (stdout)
;mov ecx, msg    ; pointer to the data
;mov edx, len    ; amount of data
;int 0x80        ; call to the kern


push rax
push rcx

mov rdi,fmt	; msg1 format
mov rsi,msg	; msg output string
xor rax,rax	; arg number
call printf

pop rcx
pop rax


mov rax, 1      ; '_exit' syscall
mov rbx, 0      ; zero exit code (success)
int 0x80        ; call t
