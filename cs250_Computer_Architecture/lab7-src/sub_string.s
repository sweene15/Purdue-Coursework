//this is the substring code in Assembly

.section	.data

		.align 2
		.comm string, 128
.section	.text

addr_string:		.word string
.global sub_string

sub_string:
	ldr r5, addr_string		//sets r5 to addr_string, which we eventually print out
	stmfd sp!, {r1-r6, lr}
	sub r1, #1			//sub one, this is due to the weird indexing requirements where the first letter is 1, instead of 0
	ldrb r3, [r0], r1		//loads r3 to the byte before the first one we want. We wont actually use this
	sub r4, r2, r1			//set our window length
loop:
	ldrb r3, [r0], #1		//loads r3 to the next byte
	strb r3, [r5], #1		//stores said byte
	subs r4, #1			//decrement our incrementer
	bne loop			//keep looping until its negative
	ldr r0, addr_string		//load er up into r0
	ldmfd sp!, {r1-r6, pc}
