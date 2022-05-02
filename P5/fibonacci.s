fibonacci:

# PROLOGUE

	subu $sp, $sp, 8        # expand stack by 8 bytes
	sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
	sw   $fp, 4($sp)        # push $fp (4 bytes)
	addu $fp, $sp, 8        # set $fp to saved $ra

# BODY

	bne  $a0, 0, condition	# if a0 != 0 check next condition
	move $v0, $a0		# move param(a0) to return register(v0)
	j return		# jump to epilogue

condition:
	bne  $a0, 1, recursion	# if a0 != 1 check next condition
	move $v0, $a0		# move param(a0) to return register(v0)
	j return		# jump to epilogue

recursion:
	subu $sp, $sp, 4	# move the stack pointer down to save argument on stack
	sw   $a0, 4($sp)	# get the new argument and save it in $a0
	subu $a0, $a0, 1	# subtract the argument by 1
	jal fibonacci		# call the function to compute the n
	subu $sp, $sp, 4	# move the stack pointer down 4 to save result on stack
	sw   $v0, 4($sp)	# move the result of fib(n-1) to register(t0)

	lw   $a0, -8($fp)	# get the new argument and save it in $a0
	subu $a0, $a0, 2	# subtract the argument by 2
	jal fibonacci		# call the function to compute the n-2 argument
	lw   $t0, -12($fp)	# store the first value

	addu $t2 $t1 $t0	# add the two values of (n-1) and (n-2) and store in a register
	addu $v0, $t2, $v0	# add the value stored in the register and add it to the final return value


return:


# EPILOGUE
	
	move $sp, $fp           # restore $sp
	lw   $ra, ($fp)         # restore saved $ra
	lw   $fp, -4($sp)       # restore saved $fp
	j    $ra                # return to kernel

