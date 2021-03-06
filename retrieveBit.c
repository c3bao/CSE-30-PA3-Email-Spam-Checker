/*
 * Filename: retrieveBit
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Given a table and a string, figure out if this string is in
 *              the table and return the bit at the correct table index.
 * Date: Nov 17, 2018
 * Sources of Help: PA2 writeup
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

/*  Function name: retrieveBit
 *  Function prototype: void retrieveBit( table_t *table, char *string)
 *  Description: Given a table and a string, figure out if this string is
 *               in the table and return the bit at the correct table index.
 *  Parameters: table - The table to look for the string in
 *              string - The string that we're looking for
 *  Error Conditions: None
 *  Side Effects: None
 *  Return Value: None
 *
 */
int retrieveBit( table_t *table , char *string) {
   
    // Get the hash key of the string
    int hash_key = table->hashFunction(string);
    int table_size = table->size;

    // Generate an index with the hash key and the table size
    int idx = ((hash_key % table_size) + table_size) % table_size;
    
    // AND the bitmask with the corresponding bit
    int bit = (table->bitArray[idx/BITS]) & (1 << (idx % BITS));

    // Shift the bit to return
    bit = bit >> idx%BITS;

    return bit;
}

