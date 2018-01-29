.section	.rodata
scanSI:
	.ascii "%d\000"
scanEI:
	.ascii "%d\000"
scanStr:
	.ascii "%s\000"
printer:
	.ascii "The substring of the given string is '%s'\n"

.data
	.align 2
	.comm start_index, 4
	.comm end_index, 4
	.comm in_string, 256
	.comm out_string, 256
sIPrompt:
	.asciz "Please enter start index:\n"
eIPrompt:
	.asciz "Please enter end index:\n"
strPrompt:
	.asciz "Please enter string prompt:\n"
.text

addr_si:	.word start_index
addr_ei:	.word end_index
addr_scanSI:	.word scanSI
addr_scanEI:	.word scanEI
addr_scanStr:	.word scanStr
addr_out:	.word out_string
addr_in:	.word in_string
addr_printer:	.word printer
.global main

main:

	stmfd sp!, {r0-r6, lr}

	ldr r0, =strPrompt		//Prompt, scan in, repeat.
	bl printf

	ldr r0, addr_scanStr
	ldr r1, addr_in
	bl scanf

	ldr r0, =sIPrompt
	bl printf

	ldr r0, addr_scanSI
	ldr r1, addr_si
	bl scanf

	ldr r0, =eIPrompt
	bl printf

	ldr r0, addr_scanEI
	ldr r1, addr_ei
	bl scanf

	ldr r0, addr_in			//loads in values to param regs
	ldr r1, addr_si
	ldr r1, [r1]
	ldr r2, addr_ei
	ldr r2, [r2]

	bl sub_string			//runs subroutine

	mov r1, r0			//prints
	ldr r0, addr_printer
	bl printf

	ldmfd sp!, {r0-r6, pc}
