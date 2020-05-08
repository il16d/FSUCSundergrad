       section .text
        global  _start



rand:                   ;result in eax
        rdtsc
        ret
print:
        mov     ebx, 1
        mov     eax, 4
        int     0x80
        ret

pick_actor: 
        ;call rand
        rdtsc
        mov ecx, 6
        div ecx    ; remainder is in edx
        
        mov eax, actors
        mov ecx, len1
        add ecx, edx
        add eax, [ecx]
        mov ecx, eax
        
        mov ebx, len11
        add ebx, edx
        add ecx, [ebx]
        mov edx, ecx
        
        
        call print
        ret
pick_action:
        rdtsc ;call rand
        mov ecx, 4
        div ecx    ; remainder is in edx
        
        mov eax, actions
        mov ecx, len2
        add ecx, edx
        add eax, [ecx]
        mov ecx, eax
        
        mov ebx, len22
        add ebx, edx
        add ecx, [ebx]
        mov edx, ecx
        call print
        
        call print
        ret
pick_acted:
        ;call rand
        rdtsc
        mov ecx, 7
        div ecx    ; remainder is in edx
        
        mov eax, acted
        mov ecx, len3
        add ecx, edx
        add eax, [ecx]
        mov ecx, eax
        
        mov ebx, len33
        add ebx, edx
        add ecx, [ebx]
        mov edx, ecx
        call print
        
        ret
order: 
        mov ecx, orderstr
        mov edx, len7
        call print
        
        call pick_actor
        call pick_action
        call pick_acted
        
        mov ecx, newline
        mov edx, 1
        call print
        ret



_start: 






          mov ecx, orders_of
          mov edx, len4
          call print
          
          mov ecx, separator
          mov edx, len5
          call print
          
          
loop1:                
         call rand  ; eax
         mov edx, 7
         mov ecx, 100
         div ecx    ; eax:edx
         sub ecx, edx
         jz loop2
         call order
         call loop1
loop2:  
         mov ecx, epsilon
         mov edx, len6
         call print
          
         call EXIT
         
EXIT:
         int 80h


    ;mov     ecx, msg
    ;mov     edx, len


        section   .data

actors:     db "Grocer1", "Grocer2", "Warehouse1", "Warehouse2", "Market1", "Market2"
len1:       db  0,  7,  14,  24,  34, 41
len11:      db  7,  7,  10,  10,   7,  7

actions:    db "buy", "sell", "deliver", "pick up"
len2:       db 0,3,7,14,21
len22:      db 3,4,7,7

acted:      db "rice", "asparagus", "lettuce", "apples", "oranges", "bread", "celery"   
len3:       db 0,4,13,20,26,33,38,44
len33:       db 4,9,7,6,7,5,6

orders_of:  db "Orders of the day:",0xA
len4 equ $ - orders_of

separator:  db "====================",0xA
len5 equ $ - separator

epsilon:  db "EPSILON",0xA
len6 equ $ - epsilon

orderstr: db "ORDER : "
len7 equ $ - orderstr

newline:         db 0xA

SECTION .bss
    msg1: resd 1 
    msg2: resd 1  

