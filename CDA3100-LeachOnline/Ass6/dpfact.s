#Iho Lopez Tobi


dpfact:	
      li	$t0, 1		# initialize product to 1.0
	  mtc1	$t0, $f0
	  cvt.d.w	$f0, $f0

again:
      slti	$t0, $a0, 2		# test for n < 2
	  bne	$t0, $zero,done	# if n < 2, return

	  mtc1	$a0, $f2		# move n to floating register
	  cvt.d.w	$f2, $f2		# and convert to double precision

	  mul.d	$f0, $f0, $f2	# multiply product by n
	
	  addi	$a0, $a0, -1	# decrease n
	  j	again		        # and loop

done:
 	  jr	    $ra		    # return to calling routine





main:

      la	$a0, intro	    # print intro
      li	$v0, 4
	  syscall

loop:

    la     $a0, enter       # "Request a value for n"
    li    $v0, 4
    syscall

    li    $v0, 5            # Read value of n
    syscall

    move  $a0, $v0          # save the value into $a0


    blt   $a0, $zero, out   # if n < 0, exit program

    li    $v0, 1            # Print the value of n
    syscall

    addi    $sp, $sp, -4    # push the stack
    sw    $a0, 0($sp)

    la    $a0, answer       # "! is "
    li    $v0, 4
    syscall

    lw    $a0, 0($sp)       # restore stack
    addi    $sp, $sp, 4

    jal    dpfact          # call the "dpfact"

    mov.d $f12, $f0        # copy the answer

    li    $v0, 3          # print $a0
    syscall

    la    $a0, newline    # print a newline
    li    $v0, 4
    syscall

    j    loop


out:  la	$a0, adios
	  li	$v0, 4
	  syscall
	  
	  li	$v0, 10		# exit from the program
	  syscall
	
	  .data
intro:    .asciiz	"Welcome to the double factorial tester!\n"
enter:    .asciiz  "Enter a value for n (or a negative value to exit): "
answer:   .asciiz  "! is "
newline:  .asciiz  "\n"
adios:    .asciiz  "Come back soon!\n"
