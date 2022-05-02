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
	lb $t4, 0($t4)
	bne $t4, $t3, endif	# check if they are equal
	
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
   .data
str1:
   .asciiz "abba"
str2:
   .asciiz "racecar"
str3:
   .asciiz "swap paws",
str4:
   .asciiz "not a palindrome"
str5:
   .asciiz "another non palindrome"
str6:
   .asciiz "almost but tsomla"

# array of char pointers = {&str1, &str2, ..., &str6}
ptr_arr:
   .word str1, str2, str3, str4, str5, str6, 0

yes_str:
   .asciiz " --> Y\n"
no_str:
   .asciiz " --> N\n"

   .text

# main(): ##################################################
#   char ** j = ptr_arr
#   while (*j != 0):
#     rval = is_palindrome(*j)
#     printf("%s --> %c\n", *j, rval ? yes_str: no_str)
#     j++
#
main:
   li   $sp, 0x7ffffffc    # initialize $sp

   # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   subu $sp, $sp, 8        # save s0, s1 on stack before using them
   sw   $s0, 8($sp)        # push $s0
   sw   $s1, 4($sp)        # push $s1

   la   $s0, ptr_arr        # use s0 for j. init ptr_arr
main_while:
   lw   $s1, ($s0)         # use s1 for *j
   beqz $s1, main_end      # while (*j != 0):
   move $a0, $s1           #    print_str(*j)
   li   $v0, 4
   syscall
   move $a0, $s1           #    v0 = is_palindrome(*j)
   jal  is_palindrome
   beqz $v0, main_print_no #    if v0 != 0:
   la   $a0, yes_str       #       print_str(yes_str)
   b    main_print_resp
main_print_no:             #    else:
   la   $a0, no_str        #       print_str(no_str)
main_print_resp:
   li   $v0, 4
   syscall

   addu $s0, $s0, 4       #     j++
   b    main_while        # end while
main_end:

   # EPILOGUE
   move $sp, $fp           # restore $sp
   lw   $ra, ($fp)         # restore saved $ra
   lw   $fp, -4($sp)       # restore saved $fp
   j    $ra                # return to kernel
# end main ################################################
