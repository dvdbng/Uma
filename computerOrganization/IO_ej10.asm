.text

lui $1, 0x0001 # LEDS
lui $2, 0x0002
addi $3, $0, 1

start: 
lw $5, 1($2)
nop
nop
nop

beq $5, $3, overflow

nop
nop
nop

j start


overflow:
nop
nop
nop
lui $5, 0x7fff
add $5, $5, $5

.ktext


mfc0 $25, $14
mfc0 $26, $13

nop
nop
nop

beq $26, $0, led0

nop
nop
nop
sw $3, 3($1)
eret
jr $25

nop
nop
nop

led0:
sw $3, 0($1)
eret
jr $25
