
# Stephen P. Leach --09/15/15(use your name and current date)
# hello.s--a traditional "Hello World" first program
# Register use:
# $v0 syscall parameter and return value
# $a0 syscall parameter
    
    
    .globl    main
main:
    la  $a0, msg # address of "Hello World" message
    li  $v0, 4   # this is the print_string option
    syscall      # perform the system call

    li  $v0, 10  # this is the exit option
    syscall      # perform the system call
# Here is the data for the program
    .data
msg:   .asciiz   "Hello World\n"
# end hello.s
