/**
 * File name: retrieveLinkedList.s
 * Author: Chau Vu
 * ID: cs30fgg
 * Date: Nov 17, 2018
 * Description: Return element of the llArray given a table and a string.
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

        .global retrieveLinkedList  @ Specify retrieveLinkedList 
                                    @ as a global symbol

        .text                   @ Switch to Text segment
        .align 2                @ Align on evenly divisible by 4 byte address;
                                @ .align n where 2^n determines alignment

/*
 * Function Name: retrieveLinkedList
 * Function Prototype: linkedList_t * retrieveLinkedList( table_t *table, 
 *                                                        char *string )
 * Description: Given a table and a string, return the element of the
 *              linkedList array.
 * Parameters: * table - a pointer to the table
 *             * str - pointer to the string 
 * Side Effects: None
 * Error Conditions: None
 * Return Value: The element of llArray at idx
 *
 * Registers used:
 *      r0 - arg 1 -- table_t *table
 *      r1 - arg 2 -- char *string
 */
retrieveLinkedList:
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
        ldr     r1, [fp, TABLE_OFFSET]  @ Load address of table
        ldr     r2, =SizeOffset         @ Load offset of size
        ldr     r2, [r2]
        ldr     r1, [r1, r2]            @ Load table->size
        add     r0, r0, r1              @ add result to table->size
        bl      getRemainder            @ getRemainder(result, table->size)
        str     r0, [fp, IDX_OFFSET]    @ Store result in index

        ldr     r0, [fp, TABLE_OFFSET]  @ Load table into r0
        ldr     r2, =ArrayOffset        @ Load offset of llArray
        ldr     r2, [r2]
        ldr     r0, [r0, r2]            @ Load address of table->llArray
        ldr     r3, [fp, IDX_OFFSET]    @ Load index into r3
        lsl     r3, r3, 2               @ Convert index to bytes
        add     r0, r0, r3              @ &(table->llArray[index])
        ldr     r0, [r0]                @ Get the value


@ Standard epilogue
        sub     sp, fp, FP_OFFSET       @ Set sp to top of saved registers
        pop     {fp, pc}                @ Restore fp, lr to pc for return





