isqrt:

   # PROLOGUE

	subu $sp, $sp , 8	# expand stack by 8 bytes
	sw   $ra, 8($sp)	# push return address by 8 bytes
	sw   $fp, 4($sp)	# push frame pointer by 4 bytes
	addu $fp, $sp, 8	# set frame pointer to the return address

   # BODY

	bge $a0, 2, recursion	# check if a0 is less than 2
	move $v0, $a0		# move param into output register
	j ret

recursion:
	subu $sp, $sp, 4	# extend stack by 4
	sw $a0, 4($sp)		# store param
	srl $a0, $a0, 2		# shift 	
	jal isqrt
	lw $a0, -8($fp)	
	subu $sp, $sp, 4	# create space for result of issqrt
	sw $v0, 4($sp)		# store result
	move $t0, $v0		# move output into register
	sll $t1, $t0, 1
	add $t2, $t1, 1		# add by one to create large

	mul $t3, $t2, $t2	# square the large value

	ble $t3, $a0, else
	move $v0, $t1
	j ret

else:
	move $v0, $t2

ret:

   # EPILOGUE

	move $sp, $fp		# restore stack pointer
	lw   $ra, ($fp)		# restore saved return address
	lw   $fp, -4($sp)	# restore saved frame pointer
	j $ra			# return to kernel
