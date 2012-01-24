.text
loop: j loop


.ktext

mfc0 $25, $14
mfc0 $26, $13

lui $1, 0x0001 # LEDS
lui $2, 0x0002

nop
nop
nop

lw $3, 0($2)

nop
nop
nop


andi $4, $3, 1
srl $3, $3, 1

nop
nop
nop

andi $5, $3, 1
srl $3, $3, 1

sw $4, 0($1)
nop
nop

andi $6, $3, 1
srl $3, $3, 1

sw $5, 1($1)
nop
nop

andi $7, $3, 1

sw $6, 2($1)
nop
nop
sw $7, 3($1)


eret
jr $25
