;Project3    

; Author: Shawn Singharaj
; Last Modified: 2/7/25
; OSU email address: singhars@oregonstate.edu
; Course number/section:   CS271 Section 400
; Project Number:  3               Due Date: 2/9/25
; Description: The user inputs temperature readings and the number of cold, cool, warm and hot days are outputted back along with
;				the max, min, and average temperature readings.

INCLUDE Irvine32.inc

HOT  =	50
COLD = -30


.data
intro_1		BYTE	"The Temperature Program by Shawn Singharaj",0
prompt_1	BYTE	"What's your name? ",0
intro_2		BYTE	"Nice to meet you, ",0
user_name	BYTE	33 DUP(0)
prompt_2	BYTE	"Please enter 7 temperatures in Celsius ranging from -30 to 50 degrees.",10,13,0
prompt_temp BYTE	"Temperature: ",0
too_cold	BYTE	"Warm up, buttercup.",0
too_hot		BYTE	"Hell nah.",0
loop_prompt	BYTE	"How many temperature readings do you want to enter? ",0
loop_count	DWORD	0
loop_limit	DWORD	?
max_temp	SDWORD	0
min_temp	SDWORD	0
num_cold	DWORD	0
num_cool	DWORD	0
num_hot		DWORD	0
num_warm	DWORD	0
average		DWORD	0
coldest_day	BYTE	"The minimum temp reading was ",0
hottest_day	BYTE	"The maximum temp reading was ",0
avg_temp	BYTE	"The average temp was ",0
cold_res	BYTE	"Number of cold days: ",0
cool_res	BYTE	"Number of cool days: ",0
warm_res	BYTE	"Number of warm days: ",0
hot_res		BYTE	"Number of hot days: ",0
goodbye		BYTE	"See ya, ",0
extra_1		BYTE	"EC 1: User chooses number of temperature readings",10,13,0



.code
main PROC
; introduce self
	mov		edx, OFFSET intro_1
	call	WriteString
	call	CrLf
	mov		edx, OFFSET extra_1
	call	WriteString
	call	CrLf

; get user name
	mov		edx, OFFSET prompt_1
	call	WriteString
	mov		edx, OFFSET user_name
	mov		ecx, 32
	call	ReadString 
	call	CrLf
	mov		edx, OFFSET intro_2
	call	WriteString
	mov		edx, OFFSET user_name
	call	WriteString
	call	CrLf
	mov		edx, OFFSET prompt_2
	call	WriteString
	call	CrLf

	; get number of temperatures the user wants to input
	mov		edx, OFFSET loop_prompt
	call	WriteString
	call	readInt
	mov		loop_limit, eax
	call	CrLf
	mov		ebx, loop_limit	; store into ebx to compare to current iteration
	

; loop 7 times to get user inputs
_userInput:
	cmp		loop_count,  ebx ; loop until loop_count equals to loop_limit
	jae		_showResults

	; prompt user input
	mov		edx, OFFSET prompt_temp
	call	WriteString
	call	ReadInt


	cmp		eax, COLD	; if input is less than -30, jump  to loop again
	jl		_tooLow
	cmp		eax, HOT	; if input is greater than 50, jump to loop again
	jg		_tooHigh
	jmp		_validInput

; if user input is too low
_tooLow:
	mov		edx, OFFSET too_cold
	call	WriteString
	call	CrLf
	jmp		_userInput

; if user input is too high
_tooHigh:
	mov		edx, OFFSET too_hot
	call	WriteString
	call	CrLf
	jmp		_userInput

; when input is valid
_validInput:
	add		average, eax	 ; add current value to average
	inc		loop_count		 ; increment looop count
	cmp		eax, min_temp
	jg		_maxTemp		 ; jump to max temp if it isnt lowest
	
_minTemp:
	mov		min_temp, eax
	jmp		_cold			; jump past max temp

_maxTemp:
	cmp		eax, max_temp
	jl		_cold			; jump past if not max temp
	mov		max_temp, eax

_cold:
	cmp		eax, 0
	jns		_cool			; jump to cool if not cold
	inc		num_cold
	jmp		_userInput

_cool:
	cmp		eax, 15
	jg		_warm			; jump to warm if not cool
	inc		num_cool
	jmp		_userInput

_warm:
	cmp		eax, HOT
	jg		_hot			; jump to hot if not warm
	inc		num_warm
	jmp		_userInput

_hot:
	inc		num_hot
	jmp		_userInput		; must be hot, so jump back to next input

_showResults:
	; find average
	xor		edx, edx
	mov		eax, average
	idiv	ebx
	mov		average, eax

	; display coldest, hottest, and average temps
	call	CrLf
	mov		edx, OFFSET coldest_day
	call	WriteString
	mov		eax, min_temp
	call	WriteInt
	call	CrLf
	mov		edx, OFFSET hottest_day
	call	WriteString
	mov		eax, max_temp
	call	WriteInt
	call	CrLf
	mov		edx, OFFSET avg_temp
	call	WriteString
	mov		eax, average
	call	WriteInt
	call	CrLf

	; display number of days per category
	mov		edx, OFFSET cold_res
	call	WriteString
	mov		eax, num_cold
	call	WriteDec
	call	CrLf
	mov		edx, OFFSET cool_res
	call	WriteString
	mov		eax, num_cool
	call	WriteDec
	call	CrLf
	mov		edx, OFFSET warm_res
	call	WriteString
	mov		eax, num_warm
	call	WriteDec
	call	CrLf
	mov		edx, OFFSET hot_res
	call	WriteString
	mov		eax, num_hot
	call	WriteDec
	call	CrLf

	; goodbye
	mov		edx, OFFSET goodbye
	call	WriteString
	mov		edx, OFFSET	user_name
	call	WriteString


	Invoke ExitProcess,0	; exit to operating system
main ENDP

END main
