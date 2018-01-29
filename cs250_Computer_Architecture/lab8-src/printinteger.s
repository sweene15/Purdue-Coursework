.text
	.align	2
.global	printd
.global printx
printd:
	stmfd	sp!, {r4, lr}	//Start up, if not neg, branch to next mthd
	subs	r4, r0, #0	//otherwise cnt, if negative, negate and print
	bge	main_printd	// '-'. Move on to next mthd
	mov	r0, #45
	bl	putchar
	rsb	r4, r4, #0
main_printd:
	add	r3, r4, #9	//Check if > 10
	cmp	r3, #18
	bls	mod_and_printd		//If so we branch to our putchar function's function
	ldr	r3, .LMagicNumber	//Else we divide by 10 and call with new 'n', recursively
	smull	r2, r3, r3, r4
	mov	r0, r4, asr #31		//Dividing by 10... (formula from the python file reworked to fit this,
	rsb	r0, r0, r3, asr #2	//same magic number though, and very similar regardless
	bl	printd			//Branch back to the top, recursively
mod_and_printd:
	ldr	r0, .LMagicNumber	//We're not done with the magic number and division yet, we need
	smull	r3, r0, r0, r4		//to get the modulus to print
	mov	r3, r4, asr #31
	rsb	r0, r3, r0, asr #2
	add	r0, r0, r0, asl #2
	sub	r0, r4, r0, asl #1	//Alright, we've got the mod now, in r0
	add	r0, r0, #48		//We add 48 to make it the char value
	bl	putchar			//and print
	ldmfd	sp!, {r4, pc}
.LMagicNumber:				//This is just formatting our magic number
	.word	0x66666667
	.align	2

printx:	//This is designed fairly similar to the previous as I ended up doing that first. Exceptions are
	stmfd	sp!, {r4, lr}				//no negation code, and also no divide by 10 because
	mov	r4, r0					//divide by 16 is bit-shift-able
	add	r3, r0, #15
	cmp	r3, #30					// n > 16?
	bls	mod_and_printx					//branch if its not
	mov	r0, r3
	cmp	r4, #0
	movge	r0, r4
	mov	r0, r0, asr #4				//divide n by 16 and ...
	bl	printx					//recursive loop, like previous
mod_and_printx:
	mov	r0, r4, asr #31			//getting the modulus of n
	mov	r0, r0, lsr #28
	add	r4, r4, r0
	and	r4, r4, #15
	rsb	r0, r0, r4
	cmp	r0, #9				//check if its 0-9
	addle	r0, r0, #48			//ascii shifts based on that
	addgt	r0, r0, #87
	bl	putchar
	ldmfd	sp!, {r4, pc}			//printing
