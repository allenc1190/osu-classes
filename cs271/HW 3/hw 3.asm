;Author: Allen Chan
;Course: CS 271
;Description: Get user input to calculate sum and average using the stack
;Date: 2/26/20
;EC DESCRIPTION: Used call showfpustack to show how the stack is working

INCLUDE Irvine32.inc

.data
	intro byte "Integer and Floating-Point Arithmetic", 0
	intro2 byte "Programmed by Allen Chan", 0
	askname byte "What's your name?: ", 0
	namee dword ?
	greet byte "Hello, ", 0
	greet2 byte ", do you want to perform integer or floating-point arithmetic?", 0
	greet3 byte "Please type 0 for integer or 1 for floating point arithmetic: ", 0
	buffer byte 21 DUP(0)
	choice dword ?
	opt1 dword 0
	opt2 dword 1
	int_arith byte "You choose to perform integer arithmetic. Please enter 5 numbers: ", 0
	flt_arith byte "You choose to perform floating point arithmetic. Please enter 5 numbers: ", 0
	askagain byte "Do you want to perform another calculation? Please enter 0 for no or 1 for yes: ", 0
	choice2 dword ?
	goodbye byte "Goodbye ", 0
	sum_msg byte "The sum of the numbers you enter is: ", 0
	avg_msg byte "The average of the numbers is: ", 0
	sum real4 0.0
	floatdiv real4 5.0
	sum2 real4 0.0


	;EXTRA CREDIT
	ec byte "EC: DESCRIPTION: ", 0
	ec2 byte "Used call showfpustack to show how the stack is working", 0

.code
	main PROC
	again:
		;INTRODUCTION
		mov edx, offset intro
		call writestring
		call crlf
		mov edx, offset intro2
		call writestring
		call crlf
		mov edx, offset ec
		call writestring
		mov edx, offset ec2
		call writestring
		call crlf
		call crlf


		;USER INSTRUCTION
		mov edx, offset askname
		call writestring
		mov edx, offset buffer
		mov ecx, sizeof buffer
		call readstring
		mov namee, eax

		mov edx, offset greet
		call writestring

		mov edx, offset buffer
		call writestring

		mov edx, offset greet2
		call writestring
		call crlf


		;GET THE DATA
		mov edx, offset greet3
		call writestring

		call readint
		mov choice, eax

		cmp eax, opt1
		je zero

		cmp eax, opt2
		je one

		zero:
		mov edx, offset int_arith
		call writestring
		jmp continue

		one:
		mov edx, offset flt_arith
		call writestring
		call crlf
		;jmp continue2
		jmp calcsumfloat

		continue:
		mov ecx, 5
		dec ecx
		call readint
		push eax
		jmp calcintsum


		;continue2:
		;mov ecx, 5
		;dec ecx
		;call readfloat
		;push eax
		;jmp calcsumfloat


		;CALCULATE SUM INT
		calcintsum:
		loop1:
		call readint
		pop ebx
		add eax, ebx
		push eax
		loop loop1


		;DISPLAY SUM INT
		call crlf
		mov edx, offset sum_msg
		call writestring
		call writedec


		;CALCULATE AVERAGE INT
		mov ebx, 5
		cdq
		div ebx


		;DISPLAY AVG INT
		call crlf
		mov edx, offset avg_msg
		call writestring
		call writedec
		jmp ask


		;CALCULATE SUM FLOAT
		calcsumfloat:
		mov ecx, 5
		finit

		loop2:
		fld sum
		call readfloat
		faddp
		fst sum
		loop loop2



		;DISPLAY SUM FLOAT
		call crlf
		fld sum
		mov edx, offset sum_msg
		call writestring
		call writefloat

		;CALCULATE AVG FLOAT
		fld sum
		fdiv floatdiv
		fst sum2

		;DISPLAY AVG FLOAT
		call crlf
		mov edx, offset avg_msg
		call writestring

		fld sum2
		call writefloat
		call showfpustack
		
		pop	ebp
		pop sum
		;pop sum2


		;CHOOSE BETWEEN CONTINUE OR EXIT
		ask:
		call crlf
		call crlf
		mov edx, offset askagain
		call writestring
		call readint
		mov choice, eax	

		cmp eax, opt1
		je exitt

		cmp eax, opt2
		pop eax
		je again


		;GOODBYE
		exitt:
		call crlf
		mov edx, offset goodbye
		call writestring

		mov edx, offset buffer
		call writestring
	

		exit
	main ENDP


END main






push OFFSET	rngnum	; 16
		push OFFSET	invalid1 ; 12
		push OFFSET	instruction ; 8
		call getnum

		;generate random numbers
		push OFFSET	array
		push rngnum
		call rng

		;print and fill unsorted array
		push OFFSET	array
		push rngnum
		push OFFSET	space
		push OFFSET	unsorted
		call printarr

		;sort numbers
		push rngnum
		push OFFSET	array
		call sorting
 
		;print and fill sorted array
		push OFFSET	array
		push rngnum
		push OFFSET	space
		push OFFSET	sorted
		call printarr

		;print and find median of array
		push OFFSET array ;16
		push rngnum ;12
		push OFFSET median; 8
		call findmedian

		;end
		push OFFSET	ending
		call end1