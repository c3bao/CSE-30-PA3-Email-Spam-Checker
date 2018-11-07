/**
 * File name: rangeCheck.s
 * Author: Chau Vu
 * ID: cs30fgg
 * Date: Oct 16, 2018
 * Description: Determines whether the value is within a specified range.
 */

@ Raspberry Pi directives
    .cpu    cortex-a53      @ Version of our Pis
    .syntax unified         @ Modern ARM syntax
    
    .equ    FP_OFFSET, 4    @ Offset from  sp to set fp

    .global rangeCheck      @ Specify rangeCheck as a global symbol

    .text                   @ Switch to Text segment
    .align 2                @ Align on evenly divisible by 4 byte address;
                            @ .align n where 2^n determines alignment

/*
 * Function Name: rangeCheck()
 * Function Prototype: long rangeCheck(long value, long minRange, long maxRange)
 * Description: Determines whether value is in the range between minRange
 *              (inclusive) and maxRange (exclusive).
 * Parameters: value - the value to check if in range
 *             minRange - the lower bound of the range
 *             maxRange - the upper bound of the range
 *
 * Side Effects: None
 *
 * Error Conditions: minRange >= maxRange
 * Return Value: Return -1 if an error occurred. Return 1 if value is in range,
 *               and 0 if not in range.
 *
 * Registers used:
 *      r0 - arg 1 -- value
 *      r1 - arg 2 -- minRange
 *      r2 - arg 3 -- maxRange
 *
 */
rangeCheck:
@ Standard prologue
        push    {fp, lr}            @ Save registers: fp, lr
        add     fp, sp, FP_OFFSET   @ Set fp to base of saved registers

        @ Incoming parameters in r0, r1, r2
        cmp     r1, r2              @ Compare minRange and maxRange
        bge     error               @ If minRange >= maxRange, branch to error
        
        cmp     r0, r1              @ Compare value and minRange
        blt     fail                @ If value < minRange, branch to fail

        cmp     r0, r2              @ Compare value and maxRange
        bge     fail                @ If value >= maxRange, branch to fail

        mov     r3, 1               @ If minRange < value <= maxRange, return 1
        b       end                 @ Branch to end

error:  mov     r3, -1              @ Return -1
        b       end                 @ Branch to end

fail:   mov     r3, 0               @ Return 0
        b       end                 @ Branch to end

end:    mov     r0, r3              @ Return value to r0

@ Standard epilogue
        sub     sp, fp, FP_OFFSET   @ Set sp to top of saved registers
        pop     {fp, pc}            @ Restore fp, restore lr into pc for return
        
        
