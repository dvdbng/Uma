.text

lui $1, 0x0001 # LEDS
lui $2, 0x0002
addi $3, $0, 1

j start

sleep: # Sleep for $4*100 ms
	lui $5, 7
	nop
	nop
	nop

	sleep_inner:
		addi $5, $5, -1
		nop
		nop
		nop
		bne $5, $0, sleep_inner

	addi $4, $4, -1
    nop
    nop
    nop
	bne $4, $0, sleep
    jr $ra



start:
nop
nop

sw $3, 2($1)

addi $4,$0,10
jal sleep
nop
sw $0, 2($1)

addi $4,$0,5
jal sleep
nop

j start
