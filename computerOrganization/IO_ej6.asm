.text

lui $1, 0x0001 # LEDS
lui $2, 0x0002
addi $3, $0, 1
addi $4, $0, 0

start: 
lw $5, 2($2)
nop
nop
nop
or $4, $4, $5
nop
nop
nop


sw $4, 0($1)
j start
