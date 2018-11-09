/**
 * File name: hash.s
 * Author: Chau Vu
 * ID: cs30fgg
 * Date: Oct 7, 2018
 * Description: Create the hash key of a string from str with a hashing
 *              algorithm.
 */

@ Raspberry Pi directives
        .cpu    cortex-a53      @ Version of our Pis
        .syntax unified         @ Modern ARM syntax
    
        .equ    FP_OFFSET, 4    @ Offset from  sp to set fp
        .equ    SP_SPACE, 16    
        .equ    STR_OFFSET, -8
        .equ    HASH_OFFSET, -12
        .equ    STRLEN_OFFSET, -16

        .global hash            @ Specify hash as a global symbol

        .text                   @ Switch to Text segment
        .align 2                @ Align on evenly divisible by 4 byte address;
                                @ .align n where 2^n determines alignment

/*
 * Function Name: hash
 * Function Prototype: int hash( char * str )
 * Description: Create an integer hash key from str
 * Parameters: str - 
 * Side Effects: None
 * Error Conditions: 
 * Return Value: The hash key of str
 *
 * Registers used:
 *      r0 - arg 1 -- str
 *      r1 - i
 */
hash:
@ Standard prologue
        push    {fp, lr}                @ Save registers fp, lr
        add     fp, sp, FP_OFFSET       @ Set fp to base of saved registers

        sub     sp, sp, SP_SPACE        @ Push sp up to make space

        str     r0, [fp, STR_OFFSET]    @ Store str onto the stack

        ldr     r1, =HashStartVal       @ Retrieve value of HashStartVal
        ldr     r1, [r1]
        str     r1, [fp, HASH_OFFSET]   @ Store onto the stack as hash

        ldr     r0, [fp, STR_OFFSET]    @ Load str pointer from stack
        bl      strlen                  @ Call strlen(str)
        str     r0, [fp, STRLEN_OFFSET] @ Store strLen to stack

        ldr     r0, [fp, STRLEN_OFFSET] @ Load strLen from stack
        mov     r1, 0                   @ i = 0
        cmp     r1, r0                  @ Compare i to strLen
        bge     endLoop                 @ if i >= strLen, branch to endLoop

loop:
        ldr     r2, [fp, HASH_OFFSET]   @ Load hash from stack
        ldr     r3, =HashPrime          @ Load HashPrime to r3
        ldr     r3, [r3]

        mul     r2, r2, r3              @ hash = hash * HashPrime

        ldr     r0, [fp, STR_OFFSET]    @ Load str pointer
        add     r0, r0, r1              @ Get address of str[i]
        ldrb    r0, [r0]                @ Get value of str[i]

        add     r2, r2, r0              @ hash = hash + str[i]

        str     r2, [fp, HASH_OFFSET]

        add     r1, r1, 1               @ Increment i (i++)
        ldr     r0, [fp, STRLEN_OFFSET]
        cmp     r1, r0                  @ Compare the loop condition 
        blt     loop                    @ Loop again if i < strLen

endLoop:
        
        ldr     r0, [fp, HASH_OFFSET]   @ Load hash to r0 for return

@ Standard epilogue
        sub     sp, fp, FP_OFFSET       @ Set sp to top of saved registers
        pop     {fp, pc}                @ Restore fp, lr to pc for return





