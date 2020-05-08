# Iho Lopez Tobi
# altfib.s function for the reverse fibbonacci sequence
# 1 -1 2 -3 5 -8 13
# 1 -1 then n = (n-2) - (n-1) for n > 2

OVERFLOW:

    addi    $sp, $sp, -12    # save $ra and $s2-$s3
    sw    $ra, 8($sp)
    sw   $s3, 4($sp)
    sw   $s2, 0($sp)

    subu $t0, $s2, $s3           # overflow check

    negu $s3, $s3               # negate $s3
    xor $t3, $s2, $s3           # check signs
    slt $t3, $t3, $zero
    bne $t3, $zero, RESTORE
    xor $t3, $t0, $s2           # sign of sums match
    slt $t3, $t3, $zero         # if signs match set $t3 to 1
    bne $t3, $zero, out         # overflow

    lw    $s2, 0($sp)           # restore values from stack
    lw   $s3, 4($sp)
    lw   $ra, 8($sp)
    addi    $sp, $sp, 12

    jr $ra


RESTORE:
    lw    $s2, 0($sp)            # restore values
    lw   $s3, 4($sp)
    lw   $ra, 8($sp)
    addi    $sp, $sp, 12

    jr $ra

ALTFIB:
    addi    $sp, $sp, -20       # save $ra and $s0-$s3
    sw    $ra, 16($sp)
    sw   $s3, 12($sp)
    sw   $s2, 8($sp)
    sw   $s1, 4($sp)
    sw    $s0, 0($sp)

    addi $s2, $s2, 1            # initialize first and second terms
    addi $s3, $s3, 0

    move $s0, $a0
    li $t1, 0

LOOP:
    beq $t1, 5, NEW

    la    $a0, space            # print a space after each number
    li    $v0, 4
    syscall

    addi $s1, $s0, 0

    jal OVERFLOW

    sub $t0, $s2, $s3           # subtract the last two nums to get next

    addi $s2, $s3, 0            # shift nums for calculation
    addi $s3, $t0, 0

    move    $a0, $t0
    li    $v0, 1
    syscall

    addi $t1, $t1, 1
    j LOOP

NEW:
    la    $a0, newline        # print a new line after 5th number
    li    $v0, 4
    syscall
    move $a0, $s1             # move next number in sequence to return value
    li $t1, 0
    j LOOP                    # jump back to for loop

EXIT:

    la    $a0, newlinw        # print a new line
    li    $v0, 4
    syscall

    move $v0, $s1             # move next number in sequence to return value
    lw    $s0, 0($sp)         # restore values from stack
    lw   $s1, 4($sp)
    lw   $s2, 8($sp)
    lw   $s3, 12($sp)
    lw    $ra, 16($sp)
    addi    $sp, $sp, 20

    jr    $ra

main:
    la    $a0, welc
    li    $v0, 4
    syscall

    jal ALTFIB

out:

    la    $a0, newline
    li    $v0, 4
    syscall

    la    $a0, overflow
    li    $v0, 4
    syscall

    move    $a0, $t0
    li    $v0, 1
    syscall

    li    $v0, 10         # exit from the program
    syscall

.data
welc: .asciiz "Here are the alternating Fibonacci numbers that I produced:\n\n"
overflow: .asciiz "\nValue causing overflow: "
space: .asciiz    " "
newline: .asciiz "\n"
