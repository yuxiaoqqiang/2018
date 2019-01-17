#»ù´¡²âÊÔ
.text
j main
	nop
f:
	addi $sp,$sp,-8
	sw $ra,0($sp)
	sh $s0,4($sp)
	addu $2,$2,$1
	lbu $2,12($a0)
	addu $2,$2,$2
	addiu $2,$2,-1       
	beq $s0,$2,FALSE   
	nop
	add $s1,$s0,$0
	addi $s0,$s0,-1   
	jal f
	addu $30,$30,$ra    
	addu $s0,$s0,$s1
	lw $ra,0($sp)
	lh $s0,4($sp)
	addi $sp,$sp,8
	jalr $1 $ra
	nop		   
	
FALSE:	
	addi $v0,$0,1
	lw $ra,0($sp)
	lh $s0,4($sp)
	addi $sp,$sp,8
	jr $ra
	nop            
	
main:
	lui $a0,0x0000
	lui $sp,0x0000
	lui $28,0xabcd
	ori $1,10
	bne $1,$a0,jump1
	nop
	and $27,$27,$1
jump1:	
	bgtz $1,jump2
	nop
	and $27,$27,$1
jump2:
	bgez $a0,jump3
	nop
	and $27,$27,$1	
jump3:	
	bltz $28,jump4
	nop
	and $27,$27,$1
jump4:	
	blez $sp,jump5
	nop
	and $27,$27,$1
	
jump5:	ori $sp,0x0080    
	sw $1,0($a0)	 
	ori $2,1
	sw $2,12($a0)	 
	lhu $s0,0($a0)     
	addi $s0,$s0,1   
	lui $ra,0x000a
	jal f
	sw $ra,8($a0)	  
	
	sub $s2,$1,$0		
	srav $4,$s2,$s1		
	sllv $5,$s1,$s2		
	srlv $6,$s2,$s1		

	lui $s3,0x04		
	subu $7,$s3,$s0
	slt $8,$s3,$s2
	sltu $9,$s0,$s3

	sra $10,$6,0x02		
	lui $10 0x0039
	sll $11,$6,0x03
	nop
	lui $12,0x0003
	srl $13,$6,0x00000001
	nop
	nop
	slti $14,$12,0x0001
	sw $14,8($0)
	
	mult $s0,$s1
	mflo $15
	mfhi $14
	sw $15 16($0)
	div $s0,$s1
	mflo $26
	sw $26,20($0)
	mfhi $26
	sw $26 24($0)
	mthi $s0
	mfhi $26
	sw $26 28($0)
	mtlo $s1
	mflo $26
	sw $26 32($0)

	or $20,$s0,$s1
	lui $21,0x0100
	nor $22,$s2,$s1
	nop
	andi $23,$21,0x1234
	xor $24,$3,$4
	nop
	nop
	sltiu $25,$23,0x00000001

	sb $v0,4($0)	 
