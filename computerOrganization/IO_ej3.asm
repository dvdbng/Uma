.text

lui $1, 0x0001 # LEDS
lui $2, 0x0002

start:

lw $3, 0($2)

nop
nop
nop

srl $4, $3, 1
srl $5, $3, 2
srl $6, $3, 3
srl $7, $3, 4

andi $4, $4, 1
andi $5, $5, 1
andi $6, $6, 1
andi $7, $7, 1

sw $4, $1(0)
sw $5, $1(1)
sw $6, $1(2)
sw $7, $1(3)

j start
