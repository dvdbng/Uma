.text

loop: j loop

.ktext

lui $1, 0x0001 # LEDS
addi $3, $0, 1

nop
nop
nop

sw $3, 0($1)
