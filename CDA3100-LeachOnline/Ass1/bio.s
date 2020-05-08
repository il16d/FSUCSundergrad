# Iho Lopez -- 05/11/2019
# bio.s -- Prints some information about me.
# Register uses:
#       $v0 syscall parameter and return value
#       $a0 syscall parameter

.text
        .globl  main
main:
        la $a0, msg     # address of bio message
        li $v0, 4       # this is the print_string option
        syscall         # perform the syscall

        li $v0, 10      # this is the exit option
        syscall

# Here is the data for the program
        .data
msg:    .asciiz         "My name is Iho Lopez\nI was born in Madrid, Spain\nI am a student at FSU and I am a member of the women's basketbal team at FSU\nI enjoy Playing the drums, traveling and photography"

# end bio.s

