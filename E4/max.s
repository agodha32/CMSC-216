# max(x, y)

max:
	# PROLOGUE

	subu $sp, $sp, 8	# expand stack by 8 bytes
	sw   $ra, 8($sp)	# push the return address by 4 bytes
	sw   $fp, 4($sp)	# push the frame pointer by 4 bytes
	addu $fp, $sp, 8	# set the frame pointer to the set return address

	# BODY

	bgt  $a0, $a1, else	# check if x(a0) > y(a1) if true go to else
	move $v0, $a1		# move y(a1) to return register(v0)
	j endif

else:
	move $v0,$a0		# move x(a0) to return register(v0) 

endif:

	# EPILOGUE

	move $sp, $fp		# restore the stack pointer
	lw   $ra, ($fp)		# restore the saved return address
	lw   $fp, -4($fp)	# restore the saved frame pointer
	jr   $ra		# return to the kernal
