.text

lui $1, 0x0001
lui $2, 0x0002

start:

lw $6, 3($2)
lw $7, 2($2)
lw $8, 1($2)

nop

sw $6, 1($1)
sw $7, 2($1)
sw $8, 3($1)

j start
