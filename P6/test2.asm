.text
j main
nop
main:
	addi $s0 $0 100
	addi $s1 $0 1234
	addi $s2 $0 134345
	addi $s3 $0 111111
	lui $s5 0xABCD
	lui $s6 0x1A24
#
	addu $t0 $s1 $s0
	addu $t1 $s4 $t0
	sw $t1 0($0)

	addu $t0 $s0 $s4
	nop
	addu $t1 $s5 $t0
	sw $t1 4($0)

	addu $t0 $s2 $s5
	nop
	nop
	addu $t1 $s4 $t0
	sw $t1 8($0)

	addu $t0 $s4 $s3
	addu $t1 $t0 $s2
	sw $t1 12($0)

	addu $t0 $s3 $s1
	nop
	addu $t1 $t0 $s0
	sw $t1 16($0)

	addu $t0 $s0 $s0
	nop
	nop
	addu $t1 $t0 $s1
	sw $t1 20($0)
#R-R
#
	addu $t0 $s1 $s0
	addiu $t1 $t0 31765
	sw $t1 24($0)

	addu $t0 $s0 $s1
	nop
	addiu $t1 $t0 2955
	sw $t1 28($0)

	addu $t0 $s2 $s0
	nop
	nop
	addiu $t1 $t0 6277
	sw $t1 32($0)
#R-I
#
	addu $t0 $s5 $s5
	beq $t0 $s1 to0
	nop
to0: 
	addi $t7 $t7 1
	nop

	addu $t0 $s3 $s0
	nop
	beq $t0 $s5 to1
	nop
to1:
	addi $t7 $t7 1
	nop

	addu $t0 $s1 $s4
	nop
	nop
	beq $t0 $s0 to2
	nop
to2:
	addi $t7 $t7 1
	nop

	addu $t0 $s0 $s1
	beq $s4 $t0 to3
	nop
to3: 
	addi $t7 $t7 1
	nop

	addu $t0 $s1 $s0
	nop
	beq $s5 $t0 to4
	nop
to4: 
	addi $t7 $t7 1
	nop

	addu $t0 $s5 $s1
	nop
	nop
	beq $s5 $t0 to5
	nop
to5: 
	addi $t7 $t7 1
	nop
#R-B
#
	addu $t0 $s1 $s3
	sb $t0 36($0)

	addu $t0 $s4 $s1
	nop
	sb $t0 40($0)

	addu $t0 $s1 $s5
	nop
	nop
	sb $t0 44($0)
#R-S
#
	addu $t0 $s1 $s1
	mthi $t0

	addu $t0 $s3 $s5
	nop
	mthi $t0

	addu $t0 $s0 $s3
	nop
	nop
	mthi $t0
#R-MT
#
	addu $t0 $s2 $s4
	mult $t0 $s5

	addu $t0 $s3 $s4
	nop
	mult $t0 $s2

	addu $t0 $s5 $s1
	nop
	nop
	mult $t0 $s3

	addu $t0 $s3 $s3
	mult $s1 $t0

	addu $t0 $s2 $s2
	nop
	mult $s5 $t0

	addu $t0 $s4 $s0
	nop
	nop
	mult $s3 $t0
#R-MD
#
	addu $t0 $s1 $s2
	blez $t0  to6
	nop
to6: 
	addi $t7 $t7 1
	nop

	addu $t0 $s4 $s5
	nop
	blez $t0  to7
	nop
to7: 
	addi $t7 $t7 1
	nop

	addu $t0 $s3 $s3
	nop
	nop
	blez $t0  to8
	nop
to8: 
	addi $t7 $t7 1
	nop

	addu $t0 $s5 $s0
	sll $t1 $t0 3
	sw $t1 48($0)

	addu $t0 $s2 $s3
	nop
	sll $t1 $t0 0
	sw $t1 52($0)

	addu $t0 $s2 $s4
	nop
	nop
	sll $t1 $t0 2
	sw $t1 56($0)
#else
#####
#
	lb $t0 56($0)
	addu $t1 $s0 $t0
	sw $t1 60($0)

	lb $t0 60($0)
	nop
	addu $t1 $s2 $t0
	sw $t1 64($0)

	lb $t0 64($0)
	nop
	nop
	addu $t1 $s1 $t0
	sw $t1 68($0)

	lb $t0 68($0)
	addu $t1 $t0 $s0
	sw $t1 72($0)

	lb $t0 72($0)
	nop
	addu $t1 $t0 $s1
	sw $t1 76($0)

	lb $t0 76($0)
	nop
	nop
	addu $t1 $t0 $s3
	sw $t1 80($0)
#L_R
#
	lb $t0 80($0)
	addiu $t1 $t0 31299
	sw $t1 84($0)

	lb $t0 84($0)
	nop
	addiu $t1 $t0 22134
	sw $t1 88($0)

	lb $t0 88($0)
	nop
	nop
	addiu $t1 $t0 8170
	sw $t1 92($0)
#L-I
#
	lb $t0 92($0)
	beq $t0 $s4 to9
	nop
to9: 
	addi $t7 $t7 1
	nop

	lb $t0 92($0)
	nop
	beq $t0 $s3 to10
	nop
to10: 
	addi $t7 $t7 1
	nop

	lb $t0 92($0)
	nop
	nop
	beq $t0 $s3 to11
	nop
to11: 
	addi $t7 $t7 1
	nop

	lb $t0 92($0)
	beq $s4 $t0 to12
	nop
to12: 
	addi $t7 $t7 1
	nop

	lb $t0 92($0)
	nop
	beq $s5 $t0 to13
	nop
to13: 
	addi $t7 $t7 1
	nop

	lb $t0 92($0)
	nop
	nop
	beq $s0 $t0 to14
	nop
to14: 
	addi $t7 $t7 1
	nop
#L-B
#
	lb $t0 92($0)
	sb $t0 96($0)

	lb $t0 96($0)
	nop
	sb $t0 100($0)

	lb $t0 100($0)
	nop
	nop
	sb $t0 104($0)
#L-S
#
	lb $t0 104($0)
	mthi $t0

	lb $t0 104($0)
	nop
	mthi $t0

	lb $t0 104($0)
	nop
	nop
	mthi $t0
#L-MT
#
	lb $t0 104($0)
	mult $t0 $s4

	lb $t0 104($0)
	nop
	mult $t0 $s5

	lb $t0 104($0)
	nop
	nop
	mult $t0 $s1

	lb $t0 104($0)
	mult $s4 $t0

	lb $t0 104($0)
	nop
	mult $s3 $t0

	lb $t0 104($0)
	nop
	nop
	mult $s1 $t0
#L-MD
#
	lb $t0 104($0)
	blez $t0  to15
	nop
to15: 
	addi $t7 $t7 1
	nop

	lb $t0 104($0)
	nop
	blez $t0  to16
	nop
to16: 
	addi $t7 $t7 1
	nop

	lb $t0 104($0)
	nop
	nop
	blez $t0 to17
	nop
to17: 
	addi $t7 $t7 1
	nop

	lb $t0 104($0)
	sll $t1 $t0 0
	sw $t1 108($0)

	lb $t0 108($0)
	nop
	sll $t1 $t0 5
	sw $t1 112($0)

	lb $t0 112($0)
	nop
	nop
	sll $t1 $t0 3
	sw $t1 116($0)
#else
#####
#
	mfhi $t0
	addu $t1 $s5 $t0
	sw $t1 120($0)

	mfhi $t0
	nop
	addu $t1 $s0 $t0
	sw $t1 124($0)

	mfhi $t0
	nop
	nop
	addu $t1 $s1 $t0
	sw $t1 128($0)

	mfhi $t0
	addu $t1 $t0 $s3
	sw $t1 132($0)

	mfhi $t0
	nop
	addu $t1 $t0 $s3
	sw $t1 136($0)

	mfhi $t0
	nop
	nop
	addu $t1 $t0 $s5
	sw $t1 140($0)
#MF-R
#
	mfhi $t0
	addiu $t1 $t0 12476
	sw $t1 144($0)

	mfhi $t0
	nop
	addiu $t1 $t0 18729
	sw $t1 148($0)

	mfhi $t0
	nop
	nop
	addiu $t1 $t0 29393
	sw $t1 152($0)
#MF-I
#
	mfhi $t0
	beq $t0 $s0 to18
	nop
to18: 
	addi $t7 $t7 1
	nop

	mfhi $t0
	nop
	beq $t0 $s5 to19
	nop
to19: 
	addi $t7 $t7 1
	nop

	mfhi $t0
	nop
	nop
	beq $t0 $s3 to20
	nop
to20: 
	addi $t7 $t7 1
	nop

	mfhi $t0
	beq $s0 $t0 to21
	nop
to21: 
	addi $t7 $t7 1
	nop

	mfhi $t0
	nop
	beq $s3 $t0 to22
	nop
to22: 
	addi $t7 $t7 1
	nop
	
	mfhi $t0
	nop
	nop
	beq $s3 $t0 to23
	nop
to23: 
	addi $t7 $t7 1
	nop
#MF-B
#
	mfhi $t0
	sb $t0 156($0)

	mfhi $t0
	nop
	sb $t0 160($0)

	mfhi $t0
	nop
	nop
	sb $t0 164($0)
#MF-S
#
	mfhi $t0
	mthi $t0

	mfhi $t0
	nop
	mthi $t0

	mfhi $t0
	nop
	nop
	mthi $t0
#MF-MT
#
	mfhi $t0
	mult $t0 $s1

	mfhi $t0
	nop
	mult $t0 $s0

	mfhi $t0
	nop
	nop
	mult $t0 $s4

	mfhi $t0
	mult $s0 $t0

	mfhi $t0
	nop
	mult $s5 $t0

	mfhi $t0
	nop
	nop
	mult $s5 $t0
#MF-MD
#
	mfhi $t0
	blez $t0  to24
	nop
to24: 
	addi $t7 $t7 1
	nop

	mfhi $t0
	nop
	blez $t0  to25
	nop
to25: 
	addi $t7 $t7 1
	nop

	mfhi $t0
	nop
	nop
	blez $t0  to26
	nop
to26: 
	addi $t7 $t7 1
	nop

	mfhi $t0
	sll $t1 $t0 3
	sw $t1 168($0)

	mfhi $t0
	nop
	sll $t1 $t0 1
	sw $t1 172($0)

	mfhi $t0
	nop
	nop
	sll $t1 $t0 0
	sw $t1 176($0)
#else
#####
#
	lui $t0 10911
	addu $t1 $s1 $t0
	sw $t1 180($0)

	lui $t0 32189
	nop
	addu $t1 $s4 $t0
	sw $t1 184($0)

	lui $t0 13117
	nop
	nop
	addu $t1 $s4 $t0
	sw $t1 188($0)

	lui $t0 32613
	addu $t1 $t0 $s1
	sw $t1 192($0)

	lui $t0 26907
	nop
	addu $t1 $t0 $s2
	sw $t1 196($0)

	lui $t0 7593
	nop
	nop
	addu $t1 $t0 $s1
	sw $t1 200($0)
#I-R
#
	lui $t0 17403
	addiu $t1 $t0 7088
	sw $t1 204($0)

	lui $t0 29968
	nop
	addiu $t1 $t0 3455
	sw $t1 208($0)

	lui $t0 10064
	nop
	nop
	addiu $t1 $t0 24906
	sw $t1 212($0)
#I-I
#
	lui $t0 30982
	beq $t0 $s3 to27
	nop
to27: 
	addi $t7 $t7 1
	nop

	lui $t0 27191
	nop
	beq $t0 $s3 to28
	nop
to28:
	addi $t7 $t7 1
	nop
	
	lui $t0 20604
	nop
	nop
	beq $t0 $s2 to29
	nop
to29: 
	addi $t7 $t7 1
	nop
	
	lui $t0 12216
	beq $s5 $t0 to30
	nop
to30:
	addi $t7 $t7 1
	nop

	lui $t0 14525
	nop
	beq $s3 $t0 to31
	nop
to31: 
	addi $t7 $t7 1
	nop

	lui $t0 2877
	nop
	nop
	beq $s1 $t0 to32
	nop
to32: 
	addi $t7 $t7 1
	nop
#I-B
#
	lui $t0 2707
	sb $t0 216($0)

	lui $t0 11602
	nop
	sb $t0 220($0)
	
	lui $t0 15770
	nop
	nop
	sb $t0 224($0)
#I-S
	lui $t0 5278
	mthi $t0
	
	lui $t0 1507
	nop
	mthi $t0

	lui $t0 32545
	nop
	nop
	mthi $t0
#I-MT
#
	lui $t0 26572
	mult $t0 $s3

	lui $t0 6063
	nop
	mult $t0 $s3

	lui $t0 24094
	nop
	nop
	mult $t0 $s3
	
	lui $t0 7084
	mult $s0 $t0

	lui $t0 28263
	nop
	mult $s2 $t0

	lui $t0 29960
	nop
	nop
	mult $s1 $t0
#I-MD
#
	lui $t0 18330
	blez $t0  to33
	nop
to33: 
	addi $t7 $t7 1
	nop

	lui $t0 1149
	nop
	blez $t0  to34
	nop
to34: 
	addi $t7 $t7 1
	nop

	lui $t0 18148
	nop
	nop
	blez $t0  to35
	nop
to35: 
	addi $t7 $t7 1
	nop

	lui $t0 6152
	sll $t1 $t0 4
	sw $t1 228($0)

	lui $t0 32464
	nop
	sll $t1 $t0 0
	sw $t1 232($0)

	lui $t0 18853
	nop
	nop
	sll $t1 $t0 2
	sw $t1 236($0)
#else
#####

