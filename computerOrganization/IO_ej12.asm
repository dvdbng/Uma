.text

addi $1, $0, 1
lui $3, 2
lui $2, 1
addi $8, $0, 0

nop
nop
nop

opread:
	lw $7, 1($3)
	nop
	nop
	nop
	beq $7, $0, opnext0
	nop
	addi $8, $0, 1
	j opread
	nop
opnext0:
	lw $7, 2($3)
	nop
	nop
	nop
	beq $7, $0, opnext1
	nop
	addi $8, $0, 2
	j opread
	nop
opnext1:
	lw $7, 3($3)
	nop
	nop
	nop
	beq $7, $0, opread
	nop
	addi $8, $0, 0
	j opread
	nop



.ktext
mfc0 $25, $14
mfc0 $26, $13

lw $9, 0($3)

nop
nop
beq $8, $0, op_and
sub $8, $8, $1
nop
nop
nop
beq $8, $0, op_add
nop
beq $8, $1, op_sub
nop

j error_handler

op_and:
	and $5, $5, $9
	nop
	j display
	nop
op_add:
	addu $5, $5, $9
	nop
	j display
	nop
op_sub:
	sub $5, $5, $9
	nop
	nop
display:
	add $10, $0, $5
	andi $11, $5, 0xFFF0
	nop
	nop
	nop
	bne $11, $0, error_handler

	andi $11, $10, 1
	srl $10, $10, 1
	nop
	nop
	nop
	andi $12, $10, 1
	srl $10, $10, 1
	sw $11, 0($2)
	nop
	nop
	andi $13, $10, 1
	srl $10, $10, 1
	sw $12, 1($2)

	nop
	nop
	andi $14, $10, 1
	srl $10, $10, 1
	sw $13, 2($2)
	nop
	sw $14, 3($2)

	
	eret
	jr $25
	nop


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

error_handler:
	addi $4, $0, 5
	sw $1 0($2)
	sw $1 1($2)
	sw $1 2($2)
	sw $1 3($2)
	jal sleep
	nop
	addi $4, $0, 5
	sw $0 0($2)
	sw $0 1($2)
	sw $0 2($2)
	sw $0 3($2)
	jal sleep
	nop
	j error_handler
	



