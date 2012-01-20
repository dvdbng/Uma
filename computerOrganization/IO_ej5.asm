.text

lui $1, 0x0001 # LEDS
lui $2, 0x0002
addi $3, $0, 1

j start

sleep: # Sleep for $4*100 ms
	lui $5, 5
	sleep_inner:
		nop
		nop
		nop
		addi $5, $5, -1
		nop
		nop
		nop
		bne $5, $0, sleep_inner

	nop
	nop
	nop
	addi $4, $4, -1
	nop
	nop
	nop	
    	bne $4, $0, sleep
	nop
	nop
	nop
	jr $ra


start:

nop
nop
nop

sw $0, 3($1)
sw $3, 0($1)
addi $4,$0,10
jal sleep

nop
nop
nop

sw $0, 0($1)
sw $3, 1($1)

addi $4,$0,10
jal sleep

nop
nop
nop

sw $0, 1($1)
sw $3, 2($1)

addi $4,$0,10
jal sleep

nop
nop
nop

sw $0, 2($1)
sw $3, 3($1)

addi $4,$0,10
jal sleep

nop
nop
nop

j start
