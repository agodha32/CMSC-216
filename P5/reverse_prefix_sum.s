reverse_prefix_sum:
 
   # PROLOGUE

	subu $sp, $sp , 8	# expand stack by 8 bytes
	sw   $ra, 8($sp)	# push return address by 8 bytes
	sw   $fp, 4($sp)	# push frame pointer by 4 bytes
	addu $fp, $sp, 8	# set frame pointer to the return address

   # Body

	lw $t0, 0($a0)
	bne $t0, -1, recursion	# go to else if param is not equal to -1	
	li $v0, 0		# return 0
	j return

recursion:	
	subu $sp, $sp, 4	# expand stack by 4
	sw $a0, 4($sp)		# store the arr
	addu $a0, $a0, 4
	jal reverse_prefix_sum	# call recursive method
	subu $sp, $sp, 4
	sw $v0, 4($sp)
	lw $a0, -8($fp)		# restore 
	move $t1, $v0
	lw $t2, 0($a0)
	addu $t1, $t1, $t2
	sw $t1, 0($a0)
	move $v0, $t1

return:

   # EPILOGUE

	move $sp, $fp		# restore stack pointer
	lw   $ra, ($fp)		# restore saved return address
	lw   $fp, -4($sp)	# restore saved frame pointer
	j $ra			# return to kernel 

