;	Project 5 

; Author: Shawn Singharaj
; Last Modified: 3/2/25
; OSU email address: singhars@oregonstate.edu
; Course number/section:   CS271 Section 400
; Project Number:     5            Due Date: 3/2/25
; Description: generate a series of temperature readings over a certain amount of days into one array
;				and display low and highs along with averages of them. 

INCLUDE Irvine32.inc


; constants
DAYS_MEASURED	= 14
TEMPS_PER_DAY	= 11
MIN_TEMP		= 20
MAX_TEMP		= 80
ARRAY_SIZE	    EQU TEMPS_PER_DAY * DAYS_MEASURED

.data
intro		BYTE	"Temperature Statistics by Shawn Singharaj",13,10,0
progIntro	BYTE	"This program generates a series of temperature readings 11 times per day over 14 days, and performs statistics on them.",13,10,0
tempHeader	BYTE	"The temperature readings are as follows:",13,10,0
tempArray   DWORD	ARRAY_SIZE DUP(?)
highArray	DWORD	DAYS_MEASURED DUP(?)
lowArray	DWORD	DAYS_MEASURED DUP(?)
highHeader	BYTE	"The highest temperature of each day was:",13,10,0
lowHeader	BYTE	"The lowest temperature of each day was:",13,10,0
avgLow		DWORD	?
avgHigh		DWORD	?
avgHighHead	BYTE	"The average high temperature was: ",0
avgLowHead	BYTE	"The average low temperature was: ",0
goodbye		BYTE	"Thanks for using Temperature Statistics, goodbye!",0


.code
main PROC
	call	randomize			; set randomize seed

	push	OFFSET progIntro	; push two strings and print them
	push	OFFSET intro
	call	printGreeting

	push	OFFSET tempArray	; push the empty array to generate temperatures
	call	generateTemperatures

	push	OFFSET highArray	; push the empty highs array and the filled array to fill the empty array
	push	OFFSET tempArray
	call	findDailyHighs

	push	OFFSET lowArray		; push the empty lows array and the filled array to fill the empty array
	push	OFFSET tempArray
	call	findDailyLows

	push	ARRAY_SIZE			; push big array size and the array to print it
	push	OFFSET tempArray
	push	OFFSET tempHeader
	call	displayTempArray

	push	TEMPS_PER_DAY		; push the highs array size + array to print it
	push	OFFSET highArray
	push	OFFSET highHeader
	call	displayTempArray

	push	TEMPS_PER_DAY		; push the lows aray size + array to print it
	push	OFFSET lowArray
	push	OFFSET lowHeader
	call	displayTempArray
	

	push	OFFSET avgLow		; push the references to the average low and high to be calculated + the two arrays
	push	OFFSET avgHigh
	push	OFFSET lowArray
	push	OFFSET highArray
	call	calcAverageLowHighTemps

	push	avgLow				; push the averages calculated above and print the results
	push	OFFSET avgLowHead
	push	avgHigh
	push	OFFSET avgHighHead
	push	OFFSET goodbye
	call	displayTempwithString


	Invoke ExitProcess,0	; exit to operating system
main ENDP

; printGreeting
; Prints the strings that introduce the program
; Preconditions: none
; Postconditions: none
; Receives: [ebp + 8] = intro string, [ebp + 12] = progIntro string
; Returns: none
;----------------------------------------
printGreeting PROC
	push	ebp
	mov		ebp, esp

	mov		edx, [ebp + 8]
	call	writeString
	mov		edx, [ebp + 12]
	call	writeString
	
	pop		ebp
	ret		8
printGreeting ENDP

; generateTemperatures
; Randomly generates temperatures to be put into the big array
; Preconditions: none
; Postconditions: none
; Receives: [ebp + 8] = offset of tempArray
; Returns: none
;----------------------------------------
generateTemperatures PROC
	push	ebp
	mov		ebp, esp

	sub		esp, 4	; local DWORD variable for ecx

	mov		eax, TEMPS_PER_DAY			
	mov		ebx, DAYS_MEASURED
	mul		ebx							; temperatures taken per day * days measured
	mov		DWORD PTR [ebp - 4], eax	; store into local variable
	mov		ecx, [ebp - 4]					

	mov		edi, [ebp + 8]				; address of tempArray set in edi

	mov		ebx, 0
	mov		eax, MAX_TEMP
	mov		edx, 2
	div		edx
	mov		edx, eax

_firstTemp:
	mov		eax, MAX_TEMP	; load max temperature into eax for randomRange
	call	randomRange		; generate random number below max temp
	cmp		eax, MIN_TEMP	; compare to min temperature
	jb		_firstTemp	

	; loop for as many times as temps per day * days measured
_fillArray:
	cmp		ebx, TEMPS_PER_DAY
	jne		_continue
	mov		ebx, 0

_continue:
	mov		eax, MAX_TEMP	; load max temperature into eax for randomRange
	call	randomRange		; generate random number below max temp
	cmp		eax, MIN_TEMP	; compare to min temperature
	jb		_fillArray		; if it is below, then generate again

	cmp		ebx, edx
	ja		_descending

_ascending:
	cmp		eax, [edi - 4]
	jb		_fillArray

_descending:
	cmp		eax, [edi - 4]
	jle		_fillArray

	mov		[edi], eax		; if it is valid, populate index with that value
	add		edi, 4			; increment array
	inc		ebx
	loop	_fillArray

	add		esp, 4
	pop		ebp
	ret		4
generateTemperatures ENDP

; findDailyHighs
; Goes through the big array and for each day, finds the high and puts that high into an array of daily highs
; Preconditions: big array must be populated
; Postconditions: none
; Receives: [ebp + 8] = offset of tempArray, [ebp + 12] = offset of empty high array
; Returns: none
;----------------------------------------
findDailyHighs PROC
	push	ebp
	mov		ebp, esp

	sub		esp, 4						; make space for local variable to store a new minimum temp to compare

	mov		ecx, DAYS_MEASURED			

	mov		edi, [ebp + 8]				; big array address stored in edi
	mov		esi, [ebp + 12]				; new smaller array address stored in esi

	; loop as many times as days measured 
_outerLoop:						
	cmp		ecx, 0
	je		_exit 
	mov		ebx, TEMPS_PER_DAY				; initialize the inner loop to the amount of temperatures read per day
	
	mov		DWORD PTR [ebp - 4], MIN_TEMP	; intialize high temp to min temp

	; loop as many times as temp readings per day to find high of one day
_innerLoop:
	cmp		ebx, 0							
	je		_exitInnerLoop
	mov		eax, [edi]		
	cmp		eax, [ebp - 4]				; compare current index/temp reading to the current highest temperature
	jb		_continueInner
	mov		[ebp - 4], eax				; if the temperature is higher, then that becomes the newest high
_continueInner:
	add		edi, 4						; increment array
	dec		ebx							; decrement inner loop counter
	jmp		_innerLoop
_exitInnerLoop:							
	mov		eax, [ebp - 4]				; store the new high to eax to be moved into the new array
	mov		[esi], eax
	add		esi, 4						; increment the new array to next index
	loop	_outerLoop
	
_exit:
	add		esp, 4
	pop		ebp
	ret		8
findDailyHighs ENDP

; findDailyLows
; Goes through the big array and for each day, finds the low and puts that low into an array of daily lows
; Preconditions: big array must be populated
; Postconditions: none
; Receives: [ebp + 8] = offset of tempArray, [ebp + 12] = offset of empty low array
; Returns: none
;----------------------------------------
findDailyLows PROC
	push	ebp
	mov		ebp, esp

	sub		esp, 4						; make space for local variable to store a new minimum temp to compare

	mov		ecx, DAYS_MEASURED			; initialize the inner loop to the amount of temperatures read per day

	mov		edi, [ebp + 8]				; big array address stored in edi
	mov		esi, [ebp + 12]				; new smaller array address stored in esi

	; loop as many times as days measured 
_outerLoop:
	cmp		ecx, 0
	je		_exit 
	mov		ebx, TEMPS_PER_DAY				; initialize the inner loop to the amount of temperatures read per day
	
	mov		DWORD PTR [ebp - 4], MAX_TEMP	; intialize low temp to the max temp 

	; loop as many times as temp readings per day to find low of one day
_innerLoop:
	cmp		ebx, 0
	je		_exitInnerLoop
	mov		eax, [edi]
	cmp		eax, [ebp - 4]				; compare current index/temp reading to the current highest temperature
	ja		_continueInner
	mov		[ebp - 4], eax				; if the temperature is lower, then that becomes the newest low
_continueInner:
	add		edi, 4						; increment big array
	dec		ebx							; decrement inner loop counter
	jmp		_innerLoop
_exitInnerLoop:	
	mov		eax, [ebp - 4]				; store the new low to eax to be moved into the new array
	mov		[esi], eax
	add		esi, 4						; increment the new array to next index
	loop	_outerLoop
	
_exit:
	add		esp, 4
	pop		ebp
	ret		8
findDailyLows ENDP

; calcAverageLowHighTemps
; Goes through the lows and highs arrays and calculates the average of them to be returned
; Preconditions: both arrays must be populated
; Postconditions: none
; Receives: [ebp + 8] = offset of highs array, [ebp + 12] = offset of lows array, [ebp + 16] = offset of avgHighs to be returned
; [ebp + 20] = offest of avgLows to be returned
; Returns: the averages of lows and highs arrays
;----------------------------------------
calcAverageLowHighTemps PROC
	push	ebp
	mov		ebp, esp

	sub		esp, 4				; make space for local variable that holds up the added up highs and lows

	mov		edi, [ebp + 8]		; highs array
	mov		esi, [ebp + 12]		; lows array 

	mov		ecx, TEMPS_PER_DAY	
	mov		DWORD PTR [ebp - 4], 0 ; initialize to 0

	; loop for as many temperatures are taken per day
_highLoop:
	mov		eax, [edi]			
    add		[ebp - 4], eax			; add current index into local variable
	add		edi, 4					; increment array
	loop	_highLoop

	mov		ebx, TEMPS_PER_DAY
	mov		eax, [ebp - 4]
	xor		edx, edx
	div		ebx						; total highs / length of array

	mov     ebx, [ebp + 16]			; load the address of avgHigh 
    mov     [ebx], eax

	mov		ecx, TEMPS_PER_DAY	
	mov		DWORD PTR [ebp - 4], 0	; initialize to 0 for lows
_lowLoop:
	mov		eax, [esi]
    add		[ebp - 4], eax			; add current index into local variable
	add		esi, 4					; increment array
	loop	_lowLoop

	mov		ebx, TEMPS_PER_DAY
	mov		eax, [ebp - 4]
	xor		edx, edx
	div		ebx						; total lows / length of array

	mov		ebx, [ebp + 20]
	mov		[ebx], eax				; load address of avgLow
	
	add		esp, 4
	pop		ebp
	ret		16
calcAverageLowHighTemps ENDP

; displayTempArray
; Prints the passed in array
; Preconditions: array must be populated 
; Postconditions: none
; Receives: [ebp + 8] = String header for array, [ebp + 12] = offset of array, [ebp + 16] = length of array
; Returns: none
;----------------------------------------
displayTempArray PROC
	push	ebp
	mov		ebp, esp

	sub		esp, 4
	mov		DWORD PTR [ebp - 4], 0		; make room for local variable that decides if the array is the big array that needs
										; to a new line to be printed for every day

	mov		edx, [ebp + 8]				; print header for array
	call	crLf
	call	writeString

	mov		edx, 0						; counter for new line initialized to 0

	mov		edi, [ebp + 12]				; array address stored in edi

	mov		ecx, [ebp + 16]				; length of array
	cmp		ecx, ARRAY_SIZE				; compare if the length passed in is the big array
	jne		_printArray					
	mov		DWORD PTR [ebp - 4], 1		; if its the big array, then the local varaible is = 1
	
_printArray:							
	cmp		ecx, 0
	je		_exit
	mov		eax, [ebp - 4]		
	cmp		eax, 0
	je		_printLine					; if it is not the big array, then skip the newline printing

_bigArray:
	cmp		edx, TEMPS_PER_DAY			; if edx, which keeps track of when to print a new line = how many temps are taken per day, print new line
	jne		_printLine
	call	crLf
	mov		edx, 0						; reset counter to 0

_printLine:
	mov		al, ' '						; print space
	call	writeChar
	mov		eax, [edi]					; print temperature in index
	call	writeDec
	add		edi, 4						; increment array
	inc		edx							; increment counter
	loop	_printArray
	
_exit:
	call	crLf
	add		esp, 4
	pop		ebp
	ret		20
displayTempArray ENDP

; displayTempwithString
; Prints out the results for the averages of lows and highs arrays
; Preconditions: none 
; Postconditions: none
; Receives: [ebp + 8] = String for goodbye message, [ebp + 12] = header for high average, [ebp + 16] = high average
; [ebp + 20] = header for low average, [ebp + 24] = low average
; Returns: none
;----------------------------------------
displayTempwithString PROC
	push	ebp
	mov		ebp, esp

	call	crLf
	mov		edx, [ebp + 12]		; print header for high average
	call	writeString
	mov		eax, [ebp + 16]		; print high average
	call	writeDec
	call	crLf
	mov		edx, [ebp + 20]		; print header for low average
	call	writeString
	mov		eax, [ebp + 24]		; print low average
	call	writeDec
	call	crLf
	mov		edx, [ebp + 8]		; print goodbye
	call	writeString 
	call	crLf

	pop		ebp
	ret		20
displayTempwithString ENDP

END main
