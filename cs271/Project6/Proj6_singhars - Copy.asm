; Project 6 

; Author: Shawn Singharaj
; Last Modified: 3/16/25
; OSU email address: singhars@oregonstate.edu
; Course number/section:   CS271 Section 400
; Project Number:  6               Due Date: 3/16/25
; Description: Takes temperature measurements from a file and prints out in the correct order

INCLUDE Irvine32.inc


; mGetString
; Outputs a string and a user string input, which also returns the size of the input
; Preconditions: None
; Receives: 
;	prompt = string address for user prompt
;	string = address of string that is to be the user input
; Returns:
;	string = user input
mGetString MACRO prompt, string
	mov		edx, OFFSET prompt	; output prompt
	call	writeString

	mov		edx, OFFSET string	; move user input into edx
	mov		ecx, MAX_LENGTH		; mov the max length of the string to be read into
	call	readString			; user input

	mov		string[ecx], 0		; null terminator at end
	;mov		bytesRead, eax		; save size of input
ENDM

; mDisplayString 
; Outputs a string
; Preconditions: None
; Receives: 
;	string = string to be outputted
; Returns: None
mDisplayString MACRO string
	mov		edx, OFFSET string
	call	writeString
ENDM

; mDisplayChar
; Outputs a char
; Preconditions: None
; Receives: 
; char = char to be outputted
; Returns: None
mDisplayChar MACRO char
	mov		al, char
	call	writeChar

ENDM

MAX_LENGTH = 101	; ambiguous max length
DELIMITER = 44		; ',' comma
TEMPS_PER_DAY = 24	; 24

.data
intro		BYTE	"Welcome to the intern error corrector. I'll read in a ','-delimited file storing temperature values.",13,10,0
intro2		BYTE	"The file must be ASCII-formatted. The program will reverse the ordering and provide the correct temperature.",13,10,0
prompt		BYTE	"Enter the name of the file to be read in: ",0
input		BYTE	MAX_LENGTH DUP(?)
fstring		BYTE	MAX_LENGTH DUP(?)
temp_arr	SDWORD	MAX_LENGTH DUP(?)
bytesRead	DWORD	?
fileError	BYTE	"Error. Can't open file.",0
fileHandle	DWORD	?
updMessage	BYTE	"The corrected order of the temperature is:",13,10,0
goodbye		BYTE	"Thanks for using the intern error corrector! Bye!",0

.code
main PROC

	mDisplayString intro				; print the intro strings
	mDisplayString intro2
	
	mGetString prompt, input			; get user input for text file

	mov		edx, OFFSET input			; take user input and open file
	call	OpenInputFile
	jc		_fileError					; if condition not met (unable to open file), jump to end with error msg

	mov		fileHandle, eax				; file handle
	mov		edx, OFFSET fstring			
	mov		ecx, MAX_LENGTH
	call	ReadFromFile				; store file string into edx and read from the file
	mov		bytesRead, eax				; store the number of bytes into bytesRead

	call	CloseFile					; close the file
			
	push	OFFSET fstring
	push	OFFSET temp_arr
	call	ParseTempsFromString		; call proc to convert to int array
		
	call	crLf
	call	crLf
	mDisplayString updMessage			
	push	OFFSET temp_arr				
	call	WriteTempsReverse			; print array in reverse

	call	crLf
	call	crLf
	mDisplayString goodbye				; goodbye message

	jmp _finish

_fileError:
	mDisplayString fileError			; output error message

_finish:
	Invoke ExitProcess,0	; exit to operating system
main ENDP



; ParseTempsFromString
; Takes the string from the read in file and converts into an array of integers based off the ASCII values of each character 
; and broken up by a delimiter
; Preconditions: String must be not empty, a string of number characters, and separated by delimiter
; Posconditions: changes registers edi, esi, eax, ecx, ebx
; Receives:
;	[ebp + 8] = the resulting array to be returned, [ebp + 12] = the string to be converted to the array
; Local vars: 
;	[ebp - 1]: sign flag that increments when a '-' is encountered, makes the resulting integer a negative when stored
;	[ebp - 5]: numint, the running value that is to be used to convert the ASCII value to the actual integer
; Returns:
;	[ebp + 12] = array of integers after conversion from string
ParseTempsFromString PROC
	push	ebp
	mov		ebp, esp

	mov		esi, [ebp + 12]		; input string
	mov		edi, [ebp + 8]		; output array
	mov		ecx, TEMPS_PER_DAY

	sub		esp, 5
	mov		BYTE PTR [ebp - 1], 0	; sign flag
	mov		SDWORD PTR [ebp - 5], 0	; numint
	

_ConversionLoop:
	lodsb
	cmp		al, DELIMITER				; compare current char to ','
	je		_NewChar					
	cmp		al, 45						; compare current char to '-'
	je		_negative
	mov		BYTE PTR [ebp - 1], 0		; set sign flag to not negative
_continue:
	sub		al, 48						; find actual value of current char to integer
	mov		bl, al						; move that into bl
	mov		eax, 10						; move 10 into eax to be multiplied
	mul		SDWORD PTR [ebp - 5]		; multiply 10 by numint, store in eax
	movzx	ebx, bl						; sign extend bl to ebx
	add		eax, ebx					; add number (eax) to converted ascii character (integer in ebx)
	mov		SDWORD PTR [ebp - 5], eax	; move eax to numint
	jmp		_ConversionLoop

_negative:
	inc		BYTE PTR [ebp - 1]
	lodsb
	jmp		_continue

_NewChar:
	mov		eax, SDWORD PTR [ebp - 5]	; move numint into eax
	mov		bl, BYTE PTR [ebp - 1]
	cmp		bl,	0						; compare sign flag to 0 (positive)
	je		_alreadyPositive
	
	neg		eax							; make numint into negative for array

_alreadyPositive:			
	stosd								; store into edi
	mov		SDWORD PTR [ebp - 5], 0		; reset numint
	loop	_ConversionLoop

	add		esp, 5
	pop		ebp
	ret		12
ParseTempsFromString ENDP

; WriteTempsReverse
; Takes the array after being converted and outputs it to the terminal in reverse order with the delimiter between each number
; Preconditions: Array must not be empty and made of (S)DWORD integers
; Posconditions: changes registers edi, eax, ecx, ebx
; Receives:
;	[ebp + 8] = the address of the array to be printed
; Returns: None 
WriteTempsReverse PROC
	push	ebp
	mov		ebp, esp

	mov		edi, [ebp + 8]			; store array address into edi
	mov		ecx, TEMPS_PER_DAY		; loop as many times as temperatures taken in that day
	mov		eax, TEMPS_PER_DAY	
	mov		ebx, 4
	mul		ebx						; temps per day * 4 - 1 = last index of array
	sub		eax, 4				
	mov		ebx, eax				; store last index of array to ebx
	add		edi, ebx				; set edi address to last index


	_printArray:							
	mov		eax, [edi]				; print temperature in index
	call	writeInt
	mDisplayChar DELIMITER
	sub		edi, 4					; increment array
	loop	_printArray

	pop		ebp
	ret		4
WriteTempsReverse ENDP

END main
