# strlen(str)

strlen:
   # PROLOGUE

	subu $sp, $sp , 8	# expand stack by 8 bytes
	sw   $ra, 8($sp)	# push return address by 8 bytes
	sw   $fp, 4($sp)	# push frame pointer by 4 bytes
	addu $fp, $sp, 8	# set frame pointer to the return address

   # BODY

	li   $t0, 0		# set strlen to 0	
	lb   $t1, 0($a0)	# point to firt character

loop:
	beqz $t1, endloop	# checks if the character is null
	add  $a0, $a0, 1	# add 1 to the length of the string
	add  $t0, $t0, 1	# point to the next char
	lb   $t1, 0($a0)	# get the byte of the next char to check if null
	j loop			# end of loop

endloop: 	
	move $v0, $t0		# move result(t0) to the output(v0)

   # EPILOGUE

	move $sp, $fp		# restore stack pointer
	lw   $ra, ($fp)		# restore saved return address
	lw   $fp, -4($sp)	# restore saved frame pointer
	j    $ra		# return to kernel
