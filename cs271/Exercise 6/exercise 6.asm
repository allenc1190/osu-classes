;Author: Allen Chan
;Course: CS 271
;Description: Get user name and ask how many fibonacci numbers they want. Then print numbers based on input.
;Date: 2/16/20

INCLUDE Irvine32.inc

.data
	intro BYTE "Fibonacci Numbers", 0
	intro2 BYTE "Programmed by Allen Chan", 0
	askname BYTE "What's your name?: ", 0
	buffer BYTE 21 DUP(0)  
	namee DWORD ?
	greet BYTE "Hello, ", 0
	instruction BYTE "Enter the number of Fibonacci terms to be displayed ", 0
	instruction2 BYTE "Give the number as an integer in the range [1 .. 46].", 0
	askterm BYTE "How many Fibonacci terms do you want?: ", 0
	num DWORD ?
	error BYTE "Out of range. Enter a number in [1 .. 46]", 0
	end1 BYTE "Results certified by Allen Chan.", 0
	end2 BYTE "Goodbye, ", 0
	min DWORD 0
	max DWORD 47
	first BYTE "1 ", 0
	first2 BYTE "1 1", 0
	space BYTE "	", 0
	prev1 DWORD ?
	prev2 DWORD ?
	temp  DWORD ?
	five DWORD 5
	ec BYTE "**EC: Fibonacci numbers prints in align columns.**", 0

.code
	main PROC
		;print intro
		mov edx, offset ec
		call writestring
		call crlf

		mov edx, offset intro
		call writestring

		call crlf
		mov edx, offset intro2
		call writestring

		call crlf
		call crlf

		;ask name
		mov edx, offset askname
		call writestring

		;get name
		mov edx, offset buffer
		mov ecx, sizeof buffer
		call readstring
		mov namee, eax

		;greet
		mov edx, offset greet
		call writestring

		mov edx, offset buffer
		call writestring
		call crlf

		;print instructions
		mov edx, offset instruction
		call writestring
		call crlf

		mov edx, offset instruction2
		call writestring
		call crlf
		call crlf


		again:
		;ask num
		mov edx, offset askterm
		call writestring

		;enter num
		call readint
		mov num, eax
		call crlf

		;check input
		cmp eax, min
		jle less

		cmp eax, max
		jge greater

		je one
		cmp eax, 2
		je two

		jmp continue

		less:
		greater:
		mov edx, offset error
		call writestring
		call crlf
		jmp again
		
		continue:

		;print fibonacci
		mov ecx, num
		sub ecx, 3
		mov eax, 1
		call writedec

		mov edx, offset space
		call writestring
		call writedec

		mov edx, offset space
		call writestring

		mov prev2, eax
		mov eax, 2
		call writedec

		mov edx, offset space
		call writestring

		mov prev1, eax

		;calculate fibonacci
		calculate:
		add eax, prev2
		call writedec

		mov edx, offset space
		call writestring

		;moving numbers
		mov temp, eax
		mov eax, prev1
		mov prev2, eax
		mov eax, temp
		mov prev1, eax
		mov edx, ecx

		;check if need new line after 5 numbers
		cdq
		div five
		cmp edx, 0
		jne next
		call crlf

		next:
		mov eax, temp
		loop calculate
		call crlf
		call crlf
		jmp toend
		
		;print first number because first 2 numbers always 1
		one:
		mov edx, offset first
		call writestring
		call crlf
		jmp toend

		;print first 2 numbers
		two:
		mov edx, offset first2
		call writestring
		call crlf
		jmp toend

		;ending
		toend:
		mov edx, offset end1
		call writestring

		call crlf

		mov edx, offset end2
		call writestring

		mov edx, offset buffer
		call writestring

		call crlf

		exit
	main ENDP


END main