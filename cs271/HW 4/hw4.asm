;Author: Allen Chan
;Course: CS 271
;Description: Get user to enter size of array and print random numbers into the array based on size user enters. Then sort from greatest to least and print. Find median of array.
;Date: 3/6/20

INCLUDE Irvine32.inc

min = 10
max = 200

lo = 100
hi = 999

.data
	intro1 byte "Array and Sorting", 0
	intro2 byte	"Programed by Allen Chan", 0
	instruction	byte "Please enter a number between 10 - 200: ", 0
	num1 dword ?
	unsorted byte "Unsorted random numbers are: ", 0
	sorted byte "Sorted numbers are: ", 0
	median byte "The median is: ", 0
	invalid1 byte "Invalid. Please enter another number", 0
	ending byte	"Goodbye", 0
	space dword "	", 0
	rngnum	dword ?
	array dword	max	dup(?)
	temp dword	?
	userinput dword ?

.code
	;INTRODUCTION
	intro PROC

		mov	edx, offset intro1
		call writestring
		call crlf
		mov edx, offset intro2
		call writestring

		ret

	intro ENDP



	;GET NUMBER BETWEEN 10-200
	getnum PROC

		push ebp
		mov	ebp, esp

		again:
			call crlf
			mov	edx, [ebp + 8]
			call writestring

			call readint
			mov num1, eax

			cmp num1, min
			jl invalid

			cmp num1, max
			jg invalid
		
			mov ebx, 10

			cmp eax, ebx
			jl invalid

			jmp valid

		invalid:
			jmp again

		valid:
			mov ebx, [ebp + 12]
			mov [ebx], eax
			;mov userinput, eax
			pop ebp
			ret 8

	getnum ENDP



	;GENERATE RANDOM NUMBERS
	rng PROC

		push ebp
		mov	ebp, esp

		mov eax, hi
		sub	eax, lo
		inc	eax

		mov	ecx, [ebp + 12]
		mov edi, [ebp + 8]
		loop1:
			call randomrange
			add eax, lo
			mov	[edi], eax
			add edi, type dword
			loop loop1

			pop ebp
			ret 8

	rng	ENDP



	;PRINT AND FILL THE ARRAY
	printarr PROC

		push ebp
		mov	ebp, esp

		mov	edx, [ebp + 8]
		call writestring
		call crlf

		mov	ecx, [ebp + 16]
		mov	esi, [ebp + 20]
		mov	edx, [ebp + 12]
		mov	ebx, 0

		fillarr:
			mov	eax, [esi]
			call writedec

			inc	ebx
			mov	edx, [ebp + 12]
			call writestring

			;check if need new line after 10 #'s
			add	esi, 4
			cmp	ebx, 10
			je	newline

			jmp	continue

		newline:
			mov	ebx, 0
			call crlf

		continue:
			loop fillarr
			call crlf
			call crlf
			pop	ebp
			ret	16

	printarr ENDP



	;SORTING NUMBERS
	sorting PROC

		push ebp
		mov	ebp, esp

		mov	eax, [ebp + 8]
		mov	temp, eax
		mov	ecx, eax
		dec	ecx

		loop1:
			push ecx
			mov	ecx, temp
			mov	esi, [ebp + 12]

		loop2:
			mov	eax, [esi]
			cmp	[esi + 4],	eax
			jl loop3

			push [esi + 4]
			push [esi]

			call switch

			pop	[esi]
			pop	[esi + 4]

		loop3:
			add	esi, 4
			loop loop2
			pop	ecx
			loop loop1
	
		pop	ebp
		ret	8

	sorting ENDP



	;SWITCH NUMBERS
	switch PROC

		push ebp
		mov	ebp, esp

		mov	eax, [ebp + 12]
		mov	ebx, [ebp + 8]
		mov	[ebp + 12], ebx
		mov	[ebp + 8], eax

		pop ebp
		ret

	switch ENDP	



	;FIND THE MEDIAN
	findmedian PROC

		push ebp
		mov ebp, esp

		mov	edx, [ebp + 12]
		call writestring
	
		mov esi, [ebp + 16]
		mov eax, [ebp + 8]
		mov ebx, 2
		cdq
		div ebx
		cmp edx, 0
		je even1

		;if array is odd
		odd1:
			mov	ebx, 4
			mul	ebx
			add	esi, eax
			mov	eax, [esi]

			call writedec
			call crlf

			jmp continue2

		;if array is even
		even1:
			mov	ebx, 4
			mul	ebx
			add	esi, eax
			mov	eax, [esi]
			add	eax, [esi - 4]
			mov	ebx, 2
			cdq
			div	ebx

			call writedec
			inc eax
			call crlf

		continue2:
			call crlf
			pop	ebp
			ret	8

	 findmedian ENDP



	 ;ENDING
	 end1 PROC

		push ebp
		mov ebp, esp

		mov	edx, [ebp + 8]
		call writestring
		call crlf

		pop	ebp
		ret 8

	 end1 ENDP

	main PROC

		call randomize
		call intro

		;get num
		push offset	rngnum ;12
		push offset	instruction ;8
		call getnum

		;generate random numbers
		push rngnum ;12
		push offset	array ;8
		call rng

		;print and fill unsorted array
		push offset	array ;20
		push rngnum ;16
		push offset	space ;12
		push offset	unsorted ;8
		call printarr

		;sort numbers
		push offset	array ;12
		push rngnum ;8
		call sorting
 
		;print and fill sorted array
		push offset	array ;20
		push rngnum ;16
		push offset	space ;12
		push offset	sorted ;8
		call printarr

		;print and find median of array
		push offset array ;16
		push offset median ;12
		push rngnum ;8
		call findmedian

		;end
		push offset	ending
		call end1

		exit

	main ENDP

END main