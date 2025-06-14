; Program: Temperature Statistics
; Author: Campbell Carlberg
; Description: This program generates random temperature readings, 
; calculates daily highs and lows, computes average high and low, and displays it

.386
.model flat, stdcall
.stack 4096
ExitProcess PROTO, dwExitCode:DWORD
INCLUDE Irvine32.inc

; Global constants
DAYS_MEASURED = 14
TEMPS_PER_DAY = 11
MIN_TEMP = 20
MAX_TEMP = 80
ARRAYSIZE = DAYS_MEASURED * TEMPS_PER_DAY

.data
; Arrays and variables
tempArray      DWORD ARRAYSIZE DUP(?)       ;array to store all temperature readings
dailyHighs     DWORD DAYS_MEASURED DUP(?)    ;array to store daily high temperatures
dailyLows      DWORD DAYS_MEASURED DUP(?)    ;array to store daily low temperatures
averageHigh    DWORD ?                       ;average of daily high temperatures
averageLow     DWORD ?                       ;average of daily low temperatures

; Strings for output
intro1         BYTE "Welcome to Chaotic Temperature Statistics, by Campbell Carlberg", 0
intro2         BYTE "This program generates a series of temperature readings, X per day for Y days", 0
intro3         BYTE "(depending on CONSTANTs), and performs some basic statistics on them: daily high and low", 0
intro4         BYTE "and average high and low temps. It then prints these results, with descriptive titles.", 0
tempTitle      BYTE "The temperature readings are as follows (one row is one day):", 0
highTitle      BYTE "The highest temperature of each day was:", 0
lowTitle       BYTE "The lowest temperature of each day was:", 0
avgHighTitle   BYTE "The (truncated) average high temperature was:", 0
avgLowTitle    BYTE "The (truncated) average low temperature was:", 0
farewell       BYTE "Thanks for using Chaotic Temperature Statistics. Goodbye!", 0

.code
main PROC
    ;seed random num generator
    call Randomize

    ;introduce the program
     push OFFSET intro2  
     push OFFSET intro1  
     call printGreeting  

    push OFFSET intro4 
    push OFFSET intro3  
    call printGreeting 

    ;generate temperatures
    push OFFSET tempArray
    call generateTemperatures

    ;find daily highs
    push OFFSET dailyHighs
    push OFFSET tempArray
    call findDailyHighs

    ;find daily lows
    push OFFSET dailyLows
    push OFFSET tempArray
    call findDailyLows

    ;calc averages
    push OFFSET averageLow
    push OFFSET averageHigh
    push OFFSET dailyLows
    push OFFSET dailyHighs
    call calcAverageLowHighTemps

    ;display temperature array
    push TEMPS_PER_DAY    ;columns per row
    push DAYS_MEASURED    ;number of rows
    push OFFSET tempArray
    push OFFSET tempTitle
    call displayTempArray

    ;display daily highs
    push TEMPS_PER_DAY         ;columns per row
    push 1                     ;number of rows
    push OFFSET dailyHighs
    push OFFSET highTitle
    call displayTempArray

    ;display daily lows
    push TEMPS_PER_DAY         ;columns per row
    push 1                     ;number of rows
    push OFFSET dailyLows
    push OFFSET lowTitle
    call displayTempArray

    ;display average high temperature
    push averageHigh
    push OFFSET avgHighTitle
    call displayTempWithString

    ;display average low temperature
    push averageLow
    push OFFSET avgLowTitle
    call displayTempWithString

    ;farewell message
    push OFFSET farewell
    call printFarewell

    INVOKE ExitProcess, 0
main ENDP

;-----------------------------------------------------------
; Description: Displays two string intros
;-----------------------------------------------------------
printGreeting PROC
    push ebp
    mov ebp, esp
    mov edx, [ebp + 8]    ;address of first string
    call WriteString
    call Crlf
    mov edx, [ebp + 12]
    call WriteString
    call Crlf
    call Crlf
    pop ebp
    ret 8
printGreeting ENDP

;-----------------------------------------------------------
; Description: Displays an exit message
;-----------------------------------------------------------
printFarewell PROC
    call Crlf
    push ebp
    mov ebp, esp
    mov edx, [ebp + 8]    ;address of string
    call WriteString
    call Crlf
    pop ebp
    ret 4
printFarewell ENDP

;-----------------------------------------------------------
; Description: Fills tempArray with random temperatures.
;-----------------------------------------------------------
generateTemperatures PROC
    push ebp
    mov ebp, esp
    mov esi, [ebp + 8]    ;address of tempArray
    mov ecx, ARRAYSIZE
generateLoop:
    mov eax, MAX_TEMP
    sub eax, MIN_TEMP
    inc eax
    call RandomRange
    add eax, MIN_TEMP
    mov [esi], eax
    add esi, 4
    loop generateLoop
    pop ebp
    ret 4
generateTemperatures ENDP

;-----------------------------------------------------------
; Description: Finds the highest temperature for each day.
;-----------------------------------------------------------
findDailyHighs PROC
    push ebp
    mov ebp, esp
    push ebx
    push edx
    push ecx

    mov esi, [ebp + 8]    ;pointer to tempArray
    mov edi, [ebp + 12]   ;pointer to dailyHighs
    xor ebx, ebx          ;EBX = day counter (0 to DAYS_MEASURED - 1)

highs_outer_loop:
    cmp ebx, DAYS_MEASURED
    jge highs_done

    ;day * TEMPS_PER_DAY
    mov ecx, ebx
    imul ecx, TEMPS_PER_DAY   ;ECX = day base index
    mov edx, ecx
    shl edx, 2                ;byte offset for the first element
    mov eax, [esi + edx]      ;initialize highest temperature for the day

    ;inner loop
    mov edx, 1                ;inner loop counter j = 1
highs_inner_loop:
    cmp edx, TEMPS_PER_DAY
    jge store_high
    ;compute absolute index = (day * TEMPS_PER_DAY + j)
    mov ecx, ebx
    imul ecx, TEMPS_PER_DAY   ;ECX = day base index
    add ecx, edx              ;ECX = absolute index for current element
    shl ecx, 2              ;convert index to byte offset
    cmp eax, [esi + ecx]
    jge skip_high_update
    mov eax, [esi + ecx]      ;update highest temperature
skip_high_update:
    inc edx
    jmp highs_inner_loop

store_high:
    ;store into dailyhighs
    mov ecx, ebx
    shl ecx, 2
    mov [edi + ecx], eax
    inc ebx
    jmp highs_outer_loop

highs_done:
    pop ecx
    pop edx
    pop ebx
    pop ebp
    ret 8
findDailyHighs ENDP

;-----------------------------------------------------------
; Description: Finds the lowest temperature for each day.
;-----------------------------------------------------------
findDailyLows PROC
    push ebp
    mov ebp, esp
    push ebx
    push edx
    push ecx

    mov esi, [ebp + 8]    ;pointer to tempArray
    mov edi, [ebp + 12]   ;pointer to dailyLows
    xor ebx, ebx          ;EBX = day counter (0 to DAYS_MEASURED - 1)

lows_outer_loop:
    cmp ebx, DAYS_MEASURED
    jge lows_done

    ;compute base index for current day: day * TEMPS_PER_DAY
    mov ecx, ebx
    imul ecx, TEMPS_PER_DAY   ;ECX = day base index
    mov edx, ecx
    shl edx, 2                ;byte offset for the first element
    mov eax, [esi + edx]      ;initialize lowest temperature for the day

    ;inner loop: iterate through remaining temperatures for the day
    mov edx, 1                ;inner loop counter j = 1
lows_inner_loop:
    cmp edx, TEMPS_PER_DAY
    jge store_low
    ;day * TEMPS_PER_DAY + j
    mov ecx, ebx
    imul ecx, TEMPS_PER_DAY   ;ECX = day base index
    add ecx, edx              ;ECX = absolute index for current element
    shl ecx, 2                ;convert index to byte offset
    cmp eax, [esi + ecx]
    jle skip_low_update
    mov eax, [esi + ecx]     
skip_low_update:
    inc edx
    jmp lows_inner_loop

store_low:
    ;store computed low into dailyLows[day]
    mov ecx, ebx
    shl ecx, 2
    mov [edi + ecx], eax
    inc ebx
    jmp lows_outer_loop

lows_done:
    pop ecx
    pop edx
    pop ebx
    pop ebp
    ret 8
findDailyLows ENDP

;-----------------------------------------------------------
; Description: Calculates the truncated average of daily highs and lows.
;-----------------------------------------------------------
calcAverageLowHighTemps PROC
    push ebp
    mov ebp, esp
    ;calculate average high temperature
    mov esi, [ebp + 8]    ;pointer to dailyHighs
    mov eax, 0
    mov ecx, DAYS_MEASURED
sumHighs:
    add eax, [esi + ecx*4 - 4]
    loop sumHighs
    cdq
    mov ecx, DAYS_MEASURED
    idiv ecx
    mov ebx, [ebp + 16]   ;address of averageHigh
    mov [ebx], eax

    ;calculate average low temperature
    mov esi, [ebp + 12]   ;pointer to dailyLows
    mov eax, 0
    mov ecx, DAYS_MEASURED
sumLows:
    add eax, [esi + ecx*4 - 4]
    loop sumLows
    cdq
    mov ecx, DAYS_MEASURED
    idiv ecx
    mov ebx, [ebp + 20]   ;address of averageLow
    mov [ebx], eax

    pop ebp
    ret 16
calcAverageLowHighTemps ENDP

;-----------------------------------------------------------
; Displays array with a title
;-----------------------------------------------------------
displayTempArray PROC
    push ebp
    mov ebp, esp
    mov edx, [ebp + 8]    ;print the title
    call WriteString
    call Crlf
    call Crlf

    mov esi, [ebp + 12]   ;array base address
    mov ecx, [ebp + 16]   ;number of rows
    mov ebx, [ebp + 20]   ;number of columns 
    
display_row_loop:
    mov edi, 0            ;column index

display_col_loop:
    mov eax, [esi + edi*4]  ;get the temperature value
    call WriteDec           ;print the number
    mov al, ' '
    call WriteChar
    call WriteChar          ;add an extra space for alignment

    inc edi
    cmp edi, ebx
    jl display_col_loop     ;print all columns in the row

    call Crlf              
    mov eax, ebx
    shl eax, 2              ;multiply columns by 4 to get byte offset
    add esi, eax
    loop display_row_loop   ;continue for all rows

    call Crlf               ;extra spacing after the section
    pop ebp
    ret 16
displayTempArray ENDP

;-----------------------------------------------------------
;Displays a descriptive string followed by a temperature value
;-----------------------------------------------------------
displayTempWithString PROC
    push ebp
    mov ebp, esp
    call Crlf
    mov edx, [ebp + 8]      ;print title
    call WriteString
    mov eax, [ebp + 12]     ;get temp value
    call WriteDec
    call Crlf
    pop ebp
    ret 8
displayTempWithString ENDP


END main
