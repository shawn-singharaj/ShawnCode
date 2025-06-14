; Dog Years Template (DogYears.asm)

; Author: shawn
; Last Modified:
; OSU email address: ONID_ID@oregonstate.edu
; Course number/section:   CS271 Section ???
; Project Number:                 Due Date:
; Description: This file is provided as a template from which you may work
;              when developing assembly projects in CS271.

INCLUDE Irvine32.inc

; (insert macro definitions here)

; (insert constant definitions here)
DOG_FACTOR = 7

.data
userName BYTE 33 DUP(0) ; string
userAge DWORD ? ; int
intro_1 BYTE "Hi, my name is Shawn, I'm here to tell you your age in dog years.", 0
prompt_1 BYTE "What's your name? ", 0
intro_2 BYTE "Hey, ", 0
prompt_2 BYTE "What is your age? ", 0
dogAge DWORD ? ; calculated
result_1 BYTE "Your age is ",0
result_2 BYTE " in dog years.",0
bye BYTE "Bye ",0

.code
main PROC
; introduce programmer
mov EDX, OFFSET intro_1
call WriteString
call CrLf


; get name and age
mov EDX, OFFSET prompt_1
call WriteString
mov EDX, OFFSET userName ; preconiditon of readstring
mov ECX, 32 ; max length saved in ECX, EDX holds pointer to string
call ReadString
call CrLf
mov EDX, OFFSET prompt_2
call WriteString
call ReadDec ; precondition of readdec: value saved in EAX
mov userAge, EAX

; calc age
mov EAX, userAge
mov EBX, DOG_FACTOR
mul EBX
mov dogAge, EAX

; output
mov EDX, OFFSET result_1
call WriteString
mov EAX, dogAge
call WriteDEC ; unsigned  INT for signed
mov EDX, OFFSET result_2
call WriteString
call CrLf
mov EDX, OFFSET bye
call WriteString
mov EDX, OFFSET userName
call WriteString
call CrLf

	Invoke ExitProcess,0	; exit to operating system
main ENDP

; (insert additional procedures here)

END main
