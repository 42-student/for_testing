; ------------------------------------------------------------------------------------------
; This is an Linux console program that writes a little triangle of asterisks to standard
; output. Runs on Linux only.
;
;     nasm -felf64 triangle.asm && ld triangle.o && ./a.out
; ------------------------------------------------------------------------------------------

global	_start

section	.text
_start:
	mov	rdx, output		; rdx holds address of the next byte to write
	mov	r8, 1			; initial line lenght
	mov	r9, 0			; number of stars written on line so far

line:
	mov	byte [rdx], "*"		; write single star
	inc	rdx			; advance pointer to next cell to write
	inc	r9			; "count" number so far on line
	cmp	r9, r8			; did we reach the number of stars for this line
	jne	line			; not yet, keep writing on this line

lineDone:
	mov	byte [rdx], 10		; write a new line char
	inc	rdx			; move pointer to where next char goes
	inc	r8			; next line will be one char longer
	mov	r9, 0			; reset count of stars written on this line
	cmp	r8, maxlines		; wait, did we already finish the last line?
	jng	line			; if not, begin writing this line

done:
	mov	rax, 1			; system call for write
	mov	rdi, 1			; file handle 1 is stdout
	mov	rsi, output		; address of string to output
	mov	rdx, dataSize		; number of bytes
	syscall				; invoke operating system to do the write
	mov	rax, 60			; system call for exit
	xor	rdi, rdi		; exit code 0
	syscall				; invoke operating system to exit

section	.bss
maxlines	equ	8
dataSize	equ	44
output:		resb	dataSize


; ------------------------------------------------------------------------------------------
; Instructions explained:
;   - 'mov' moves data
;   - 'inc' increments value by 1
;   - 'cmp' does a comparison
;   - 'jne' jump if not equal
;   - 'jng' jump if not greater
;   - 'syscall' invokes a system call to the operating system
;   - 'xor' performs a bitwise exclusive OR operation
;   - 'equ' defines a constant value
;   - 'resb' reserves a specified number of bytes in the uninitialized data section
;
; Sections explained:
;   - '.text' section for executable code
;   - '.bss' section for uninitialized data
; ------------------------------------------------------------------------------------------

