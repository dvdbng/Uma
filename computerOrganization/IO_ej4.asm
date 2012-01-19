.text

lui $1, 0x0001 # LEDS
lui $2, 0x0002
addi $3, $0, 1


sleep: # Sleep for $4*100 ms
	beq $4, $0, sleep_exit

	lui $5, 50
	nop
	nop
	nop

	sleep_inner:
		subi $5, $5, 1
		nop
		nop
		nop
		bne $5, $0, sleep_inner
		
	subi $4, $4, 1
	j sleep

	sleep_exit:
		jr $ra


start:

sw $3, $1(2)

addi $4,$0,10
jal sleep

sw $0, $1(2)

addi $4,$0,5
jal sleep

j start
