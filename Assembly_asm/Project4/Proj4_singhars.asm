; Project 4

; Author: Shawn Singharaj
; Last Modified:	2/22/25
; OSU email address: singhars@oregonstate.edu
; Course number/section:   CS271 Section 400
; Project Number:   4              Due Date: 2/23/25
; Description: Based on user input 1-13, the program will generate an example of pascal's triangle based on how many
; rows the user chooses

INCLUDE Irvine32.inc

LOWER = 1
UPPER = 20

.data
progIntro	BYTE	"Pascal's Triangle Generator - By Shawn Singharaj",13,10,0
intro		BYTE	"This program will print no more than 20 rows of Pascal's Triangle.",13,10,0
prompt		BYTE	"Enter a total number of rows to print, from 1-20: ",0
tooLow		BYTE	"The number you entered is too low, try again.",10,13,0
tooHigh		BYTE	"The number you entered is too high, try again.",10,13,0
user_input	DWORD	?
goodbye		BYTE	"Thanks for using the Pascal's Triangle Generator! Bye!",0
EC2			BYTE	"EC: Extend the range of the program to show up to 20 rows of Pascal's Triangle",13,10,0


.code
main PROC
	; push strings for introduction procedure
	push	OFFSET progIntro
	push	OFFSET intro
	push	OFFSET EC2
	call	introduction

	; push strings for user input procedure
	push	OFFSET prompt
	push	OFFSET tooLow
	push	OFFSET tooHigh
	call	getUserInput

	; push user input to print triangle
	push	user_input
	call	printPascalTriangle

	; push string for farewell procedure
	push	OFFSET goodbye
	call	farewell


	Invoke ExitProcess,0	; exit to operating system
main ENDP


; introduction: Introduces program to user
; takes three strings as parameters and prints them 
; [ebp + 8] = EC2 string
; [ebp + 12] = intro string
; [ebp + 16] = progIntro string
introduction PROC
	push	ebp
	mov		ebp, esp

	; print progIntro
	mov		edx, [ebp + 16] 
	call	writeString
	mov		edx, [ebp + 12]	; print intro
	call	writeString
	mov		edx, [ebp + 8]	; print EC2
	call	writeString
	call	crLf

	pop		ebp
	ret		12				; pop 12 bytes
introduction ENDP


; getUserInput: takes three parameters: prompt string and the two error strings
; and checks if the user input is within the bounds to then store that value in
; user_input 
; [ebp + 8] = tooHigh string
; [ebp + 12] = tooLow string
; [ebp + 16] = prompt string
getUserInput PROC
	push	ebp
	mov		ebp, esp

; user prompt loop, loop while user inputs invalid responses
_promptUser:
	mov		edx, [ebp + 16] ; prompt user printed
	call	writeString
	call	readDec			; user input
	
	cmp		eax, LOWER		; if input is less than 1, jump to _tooLow
	jb		_tooLow
	cmp		eax, UPPER		; if input is greater than 20 jump to _tooHigh
	ja		_tooHigh
	jmp		_good			; if passes, break out of loop

_tooLow:
	mov		edx, [ebp + 12]	; print tooLow 
	call	writeString
	jmp		_promptUser		; reprompt user

_tooHigh:
	mov		edx, [ebp + 8]	; print tooHigh
	call	writeString
	jmp		_promptUser		; reprompt user

_good:
	mov		user_input, eax	; store user input into variable
	pop		ebp
	ret		12				; pop 12 bytes
getUserInput ENDP

; printPascalTriangle: takes the user_input and prints the amount of specified rows
; by calling a helper procedure that prints out the contents of each row in a loop
; [ebp + 8] = user_input
printPascalTriangle PROC
	push	ebp				
	mov		ebp, esp
	
	mov		ecx, 0			; initialize row counter

; loop until the row counter = user_input
_print:
	cmp		ecx, [ebp + 8]
	ja		_done			; if row counter goes above the user_input number, break out of loop

	call	crLf
	push	ecx				; push the current row
	call	printPascalRow	; call helper function to print out contents of current row
	
	inc		ecx				; go to next row
	jmp		_print			
_done:
	pop		ebp
	ret		4				; pop 4 bytes
printPascalTriangle ENDP


; printPascalRow: prints out the contents of each row based on what row it is
; runs a formula to print the value and loops until all values are printed in the row
; [ebp + 8] = ecx which is the current row to be printed
printPascalRow PROC
	push	ebp
	mov		ebp, esp

	mov		ebx, [ebp + 8]	; ebx is equal to the current row
	mov		eax, 1			; first number is always 1
	mov		ecx, 0			; index counter set to 0

	call	writeDec		; print 1

_printRow:
	cmp		ebx, ecx		
	je		_done			; if index counter = row counter, break out of loop
	
	mov		edx, ebx		; current row n stored in edx
	sub		edx, ecx		; n is subtracted from index k (n - k)
	inc		ecx				; k + 1
	mul		edx				; eax * (n-k)
	div		ecx				; new eax / (k + 1)
	
	call	writeDec		; print value

	jmp		_printRow

_done:
	pop		ebp
	ret		4				; pop 4 bytes
printPascalRow ENDP


; farewell: takes the goodbye string and prints to the user
; [ebp + 8] = goodbye string
farewell PROC
	push	ebp
	mov		ebp, esp
	
	call	crLf
	mov		edx, [ebp + 8]	; print goodbye string
	call	writeString

	pop		ebp
	ret		4				; pop 4 bytes
farewell ENDP

END main
