/*
 * Filename: bitTableAddString
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: 
 * Date: Nov 11, 2018
 * Sources of Help: PA2 writeup
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

/*  Function name: bitTableAddString
 *  Function prototype: void bitTableAddString( table_t *table, char *string)
 *  Description: 
 *  Parameters: table - 
 *              string - 
 *  Error Conditions: 
 *  Side Effects: 
 *  Return Value: None
 *
 */
void bitTableAddString( table_t *table , char *string) {
    
    int hash_key = table->hashFunction(string);
    int table_size = table->size;

    int idx = ((hash_key % table_size) + table_size) % table_size;
    char byte = *((*table).bitArray + (idx/8));
    char bitMask = 1 << idx%8;
    byte = byte | bitMask;
}

