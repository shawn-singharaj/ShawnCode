;project one   (Proj1_singhars.asm)

; Author: Shawn Singharaj
; Last Modified:
; OSU email address: singhars@oregonstate.edu
; Course number/section:   CS271 Section 400
; Project Number: 1                Due Date: 01/26/25
; Description: Take in a user input for x and y, and perform addition, subtraction, and multiplication

INCLUDE Irvine32.inc

.data
myName BYTE "Project 1, Simple Arithmetic by Shawn Singharaj",0
intro BYTE "Enter two numbers, x >= y, and I'll perform some calculations.",0
x DWORD ?
y DWORD ?
prompt_x BYTE "Enter a value for x: ",0
prompt_y BYTE "Enter a value for y, must be less than or equal to x: ",0
y_greater_x BYTE "The value you entered for y is greater than x. Try again. ",0
sum DWORD ?
diff DWORD ?
product DWORD ?
quotient DWORD ?
remainder DWORD ?
plus BYTE " + ",0
minus BYTE " - ",0
multiply BYTE " x ",0
divide BYTE " / ",0
equals BYTE " = ",0
remain BYTE ", remainder: ",0
prompt_loop BYTE "Would you like to quit? Press 1 to restart: ",0
restart_loop DWORD ?
goodbye BYTE "That's all there is to it, goodbye!",0
extra_4 BYTE "EC: Handle division"
extra_3 BYTE "EC: Handle negative results and computes y-x",0
extra_2 BYTE "EC: Check if x>y",0
extra_1 BYTE "EC: Repeat until the user chooses to quit with an in-program option",0


.code
main PROC

; output title and name
mov EDX, OFFSET myName
call WriteString
call CrLf
mov EDX, OFFSET extra_1
call WriteString
call CrLf
mov EDX, OFFSET extra_2
call WriteString
call CrLf
mov EDX, OFFSET extra_3
call WriteString
call CrLf
mov EDX, OFFSET extra_4
call WriteString
call CrLf
call CrLf

_top:
	; first time skip over error message
	JMP _prompt
	
	_error: ; output error message, try again
		call CrLf
		mov EDX, OFFSET y_greater_x
		call WriteString
		call CrLf

	_prompt:
		; output intro and prompts
		mov EDX, OFFSET intro
		call WriteString
		call CrLf
		mov EDX, OFFSET prompt_x
		call WriteString
		call ReadInt
		mov x, EAX
		mov EDX, OFFSET prompt_y
		call WriteString
		call ReadInt
		mov y, EAX
		cmp EAX, x
		JG _error


	; addition
	mov EAX, x
	add EAX, y
	mov sum, EAX

	; output
	call CrLf
	mov EAX, x 
	call WriteInt
	mov EDX, OFFSET plus
	call WriteString
	mov EAX, y
	call WriteInt
	mov EDX, OFFSET equals
	call WriteString
	mov EAX, sum
	call WriteInt
	call CrLf

	; subtraction
	mov EAX, x
	sub EAX, y
	mov diff, EAX

	; output
	mov EAX, x 
	call WriteInt
	mov EDX, OFFSET minus
	call WriteString
	mov EAX, y
	call WriteInt
	mov EDX, OFFSET equals
	call WriteString
	mov EAX, diff
	call WriteInt
	call CrLf

	; multiplication
	mov EAX, x
	mov EBX, y
	mul EBX
	mov product, EAX

	; output
	mov EAX, x 
	call WriteInt
	mov EDX, OFFSET multiply
	call WriteString
	mov EAX, y
	call WriteInt
	mov EDX, OFFSET equals
	call WriteString
	mov EAX, product
	call WriteInt
	call CrLf

	; division
	mov EAX, x
	xor EDX, EDX     ; clear EDX 
	mov EBX, y
	idiv EBX
	mov quotient, EAX
	mov remainder, EDX

	; output
	mov EAX, x 
	call WriteInt
	mov EDX, OFFSET divide
	call WriteString
	mov EAX, y
	call WriteInt
	mov EDX, OFFSET equals
	call WriteString
	mov EAX, quotient
	call WriteInt
	mov EDX, OFFSET remain
	call WriteString
	mov EAX, remainder
	call WriteInt
	call CrLf
	call CrLf

	; prompt loop
	mov EDX, OFFSET prompt_loop
	call WriteString
	call ReadDec
	mov restart_loop, EAX
	cmp restart_loop, 1
	JE _top

; bye bye
mov EDX, OFFSET goodbye
call WriteString

	Invoke ExitProcess,0	; exit to operating system
main ENDP

END main
