# mash(x, y)

mash:
	# PROLOGUE

	subu $sp, $sp , 8	# expand stack by 8 bytes
	sw   $ra, 8($sp)	# push return address by 8 bytes
	sw   $fp, 4($sp)	# push frame pointer by 4 bytes
	addu $fp, $sp, 8	# set frame pointer to the return address

	# BODY

	lw $t0, 4($fp)		# load x into t0
	lw $t1, 8($fp)		# load y into t1

	mul  $v0, $t0, 10	# multiply x(t0) by 10 and save it in the return address(v0)
	add  $v0, $v0, $t1	# add 10x with y(t1) and save it in the return address(v0)

	# EPILOGUE

	move $sp, $fp		# restore stack pointer
	lw   $ra, ($fp)		# restore saved return address
	lw   $fp, -4($sp)	# restore saved frame pointer
	j    $ra		# return to kernel
