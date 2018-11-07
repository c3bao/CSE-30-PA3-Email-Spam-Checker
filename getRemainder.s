/**
 * File name: getRemainder.s
 * Author: Chau Vu
 * ID: cs30fgg
 * Date: Oct 16, 2018
 * Description: Calculates and returns the remainder of the division
 *              between the dividend and the divisor; it should act like
 *              the modulus operator in C.
 */

@ Raspberry Pi directives
    .cpu    cortex-a53      @ Version of our Pis
    .syntax unified         @ Modern ARM syntax
    
    .equ    FP_OFFSET, 4    @ Offset from  sp to set fp

    .global getRemainder    @ Specify getRemainder as a global symbol

    .text                   @ Switch to Text segment
    .align 2                @ Align on evenly divisible by 4 byte address;
                            @ .align n where 2^n determines alignment

/*
 * Function Name: getRemainder
 * Function Prototype: long getRemainder( long dividend, long divisor )
 * Description: Calculates and returns the remainder of the division between
 *              dividend and the divisor; it should act like the modulus
 *              operator in C.
 * Parameters: dividend - The number to be divided
 *             divisor - The number to be divided by
 *
 * Side Effects: None
 *
 * Error Conditions: Divisor is 0
 * Return Value: The remainder
 *
 * Registers used:
 *      r0 - arg 1 -- dividend
 *      r1 - arg 2 -- divisor
 *
 */
getRemainder:
@ Standard prologue
        push    {fp, lr}            @ Save registers: fp, lr
        add     fp, sp, FP_OFFSET   @ Set fp to base of saved registers

        @ Incoming parameters in r0, r1, r2
        sdiv    r2, r0, r1          @ r2 = r0/r1
        mul     r3, r2, r1          @ r3 = r2 * r1
        sub     r0, r0, r3          @ r0 = r0 - r3
                                    @ r0 stores the remainder
        

@ Standard epilogue
        sub     sp, fp, FP_OFFSET   @ Set sp to top of saved registers
        pop     {fp, pc}            @ Restore fp, restore lr into pc for return
        
        
