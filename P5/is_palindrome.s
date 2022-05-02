is_palindrome:

   # PROLOGUE

	subu $sp, $sp , 8	# expand stack by 8 bytes
	sw   $ra, 8($sp)	# push return address by 8 bytes
	sw   $fp, 4($sp)	# push frame pointer by 4 bytes
	addu $fp, $sp, 8	# set frame pointer to the return address

   # BODY

	subu $sp, $sp, 4	# create room for int i, len
	sw $a0, 4($sp)		# store string on the stack
	jal strlen		# call strlen
	move $t1, $v0		# move int from v0 to register
	div $t2, $t1, 2		# divide strlen by 2
	lw $a0, -8($fp)		# load string from fp
	subu $t1, $t1, 1	# len - 1
	subu $sp, $sp, 4	# create room for int i, len
	li $t0, 0		# i = 0
	sw $t0, 4($sp)		# store i
	
loop:
	bge $t0, $t2, returnT	# check if i < len/2
	
	addu $t3, $a0, $t0	
	lb $t3, 0($t3)

	subu $t4, $t1, $t0	# len - i
	addu $t5, $a0, $t4
	lb   $t5, 0($t5)
	bne $t5, $t3, endif	# check if they are equal
	
	addu $t0, $t0, 1	# i++

	j loop
	
endif:
	li $v0, 0		# return 0
	j return		# go to epilogue
	
returnT:
	li $v0, 1		# return 1

return:

   # EPILOGUE

	move $sp, $fp		# restore stack pointer
	lw   $ra, ($fp)		# restore saved return address
	lw   $fp, -4($sp)	# restore saved frame pointer
	j    $ra		# return to kernel


strlen:
   # PROLOGUE

	subu $sp, $sp , 8	# expand stack by 8 bytes
	sw   $ra, 8($sp)	# push return address by 8 bytes
	sw   $fp, 4($sp)	# push frame pointer by 4 bytes
	addu $fp, $sp, 8	# set frame pointer to the return address

   # BODY

	li   $t0, 0		# set strlen to 0	
	lb   $t1, 0($a0)	# point to firt character

floop:
	beqz $t1, endloop	# checks if the character is null
	add  $a0, $a0, 1	# add 1 to the length of the string
	add  $t0, $t0, 1	# point to the next char
	lb   $t1, 0($a0)	# get the byte of the next char to check if null
	j floop			# end of loop

endloop: 	
	move $v0, $t0		# move result(t0) to the output(v0)
	
   # EPILOGUE

	move $sp, $fp		# restore stack pointer
	lw   $ra, ($fp)		# restore saved return address
	lw   $fp, -4($sp)	# restore saved frame pointer
	j $ra			# return to kernel
