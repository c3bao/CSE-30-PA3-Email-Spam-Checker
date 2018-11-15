/**
 * File name: llTableAddString.s
 * Author: Chau Vu
 * ID: cs30fgg
 * Date: Oct 7, 2018
 * Description: Create the llTableAddString key of a string from str with a llTableAddStringing
 *              algorithm.
 */

@ Raspberry Pi directives
        .cpu    cortex-a53      @ Version of our Pis
        .syntax unified         @ Modern ARM syntax
    
        .equ    FP_OFFSET, 4    @ Offset from  sp to set fp
        .equ    SP_SPACE, 24    
        .equ    TABLE_OFFSET, -8
        .equ    STR_OFFSET, -12
        .equ    HASH_OFFSET, -16
        .equ    IDX_OFFSET, -20

        .global llTableAddString            @ Specify llTableAddString as a global symbol

        .text                   @ Switch to Text segment
        .align 2                @ Align on evenly divisible by 4 byte address;
                                @ .align n where 2^n determines alignment

/*
 * Function Name: llTableAddString
 * Function Prototype: void llTableAddString( table_t *table, char *string )
 * Description: Set the 
 * Parameters: str - 
 * Side Effects: None
 * Error Conditions: 
 * Return Value: The llTableAddString key of str
 *
 * Registers used:
 *      r0 - arg 1 -- table_t *table
 *      r1 - arg 2 -- char *string
 */
llTableAddString:
@ Standard prologue
        push    {fp, lr}                @ Save registers fp, lr
        add     fp, sp, FP_OFFSET       @ Set fp to base of saved registers

        sub     sp, sp, SP_SPACE        @ Push sp up to make space
        
        str     r0, [fp, TABLE_OFFSET]  @ Store *table to the stack
        str     r1, [fp, STR_OFFSET]    @ Store *string to the stack

        ldr     r1, [fp, TABLE_OFFSET]  @ Load address of table
        ldr     r2, =HashFunctionOffset @ Load offset of hashFunction
        ldr     r2, [r2]
        ldr     r1, [r1, r2]            @ Load table->hashFunction
        ldr     r0, [fp, STR_OFFSET]    @ Load address of string
        blx     r1                      @ call table->hashFunction(string)
        str     r0, [fp, HASH_OFFSET]   @ store result in hash

        ldr     r1, [fp, TABLE_OFFSET]  @ Load address of table
        ldr     r2, =SizeOffset         @ Load offset of size
        ldr     r2, [r2]
        ldr     r1, [r1, r2]            @ Load table->size
        ldr     r0, [fp, HASH_OFFSET]   @ Load hash from stack
        bl      getRemainder            @ getRemainder(hash, table->size)
        add     r0, r0, r1              @ add result to table->size
        bl      getRemainder            @ getRemainder(result, table->size)
        str     r0, [fp, IDX_OFFSET]    @ Store result in index

        ldr     r0, [fp, TABLE_OFFSET]  @ Load table into r0
        ldr     r2, =ArrayOffset        @ Load offset of llArray
        ldr     r2, [r2]
        ldr     r0, [r0, r2]            @ Load table->llArray
        ldr     r3, [fp, IDX_OFFSET]    @ Load index into r3
        lsl     r3, r3, 2               @ convert index to bytes
        add     r0, r0, r3              @ Calculate &(table->llArray[index])
        ldr     r1, [fp, STR_OFFSET]    @ Load string to r1
        bl      prependNode

@ Standard epilogue
        sub     sp, fp, FP_OFFSET       @ Set sp to top of saved registers
        pop     {fp, pc}                @ Restore fp, lr to pc for return





