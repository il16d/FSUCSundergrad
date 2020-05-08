#Iho Lopez

# e ^ x = 1 + x / 1 + x ^ 2 / 2! + x ^ 3 / 3! + ...

	.text
exp:

	mov.d $f10 ,$f12    # f0 is result, $f12 is input
	abs.d $f12, $f12    # x = abs(x)
	l.d $f0, one	    # f0 is 1		# $f12 = 999
	li $t0, 1           # count

	addi	$sp, $sp, -4  # adjust stack
	sw	$ra, 0($sp)	      # save the return address

    jal loop

    lw	$ra, 0($sp)	    # restore the return address
    addi	$sp, $sp, 4	# adjust pointer

	l.d $f12, zero
    c.lt.d $f6, $f10		    # is input < 0 ?
    bc1f inverse				# then exit

	jr $ra

inverse:
	l.d $f12, one
	div.d $f0, $f12, $f0
	jr $ra

loop:

	li $t1, 0               #  next term
	l.d $f2, one
	addi	$sp, $sp, -4	# adjust stack
    sw	$ra, 0($sp)	        # save return address
    jal term #term loop
	lw	$ra, 0($sp)	         # restore return address
    addi	$sp, $sp, 4	     # adjust stack pointer to pop 2 items

	l.d $f4, conse			# $f4 = 1.0e-15   the message is term
	div.d $f6, $f2, $f0		# f6 = res / sum
	c.lt.d $f6, $f4		    # is divisor < 1.0e-15 ?
    bc1t expr
    nop

    add.d $f0, $f0, $f2
    addi $t0, $t0, 1

    j loop

term:
	beq $t0, $t1, termexit	    # for t1 = 0 to t0
	mul.d $f2, $f12, $f2		# f2 = f2 * f12
	addi $t1, $t1, 1			# t1 += 1
	mtc1.d $t1, $f4
    cvt.d.w $f4, $f4
	div.d $f2, $f2, $f4		    # f2 = f2 / f13
	j term

termexit:
	jr $ra

expr:
	jr $ra

exit:
	la	$a0, adios
    li	$v0, 4
    syscall

    li	$v0, 10				# exit
    syscall

main:
    la    $a0, intro
    li    $v0, 4
    syscall

    j expdriver

    expdriver:
    la    $a0, enter           # ask for input
    li    $v0, 4
    syscall

    li    $v0, 7              # read value of x as double
    syscall

    l.d $f12, flag            # $f12 = 999        f16 is f12
    c.eq.d $f0, $f12          # is x == 999 ?
    bc1t exit                 # exit
    nop

    la    $a0, answer         # display result message
    li    $v0, 4
    syscall

    li $v0, 3                #input
    mov.d $f12, $f0
    syscall

    la    $a0, is
    li    $v0, 4
    syscall

    jal exp                   # if x != 999 then call exp

    li $v0, 3                #result
    mov.d $f12, $f0
    syscall

# print exp
    j expdriver







	.data

intro:  .asciiz "Let's test our exponential function"
enter: .asciiz "\nEnter a value for x (or 999 to exit): "
answer:   .asciiz "\nOur approximation for e^"
is:    .asciiz " is "
adios: .asciiz "\nCome back soon!"

flag:  .double   999.0
zero:  .double    0.0
one:   .double     1.0
conse: .double   1.0e-15
