.text

lui $1, 0x0001
lui $2, 0x0002

addi $3, $0, 0 # led 1
addi $4, $0, 0 # led 2
addi $5, $0, 0 # led 3

start:

lw $6, 3($2)
lw $7, 2($2)
lw $8, 1($2)

nop

or $3, $3, $6
or $4, $4, $7
or $5, $5, $8

nop

sw $3, 1($1)
sw $4, 2($1)
sw $5, 3($1)

j start




