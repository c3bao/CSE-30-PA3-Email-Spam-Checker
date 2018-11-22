/*
 * Filename: bitTableAddString
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Hash the string into the bitTable
 * Date: Nov 11, 2018
 * Sources of Help: PA3 writeup
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

/*  Function name: bitTableAddString
 *  Function prototype: void bitTableAddString( table_t *table, char *string)
 *  Description: Hash the string into the bitTable
 *  Parameters: table - the table to hash the string into
 *              string - the string to be hashed in
 *  Error Conditions: None
 *  Side Effects: None
 *  Return Value: None
 *
 */
void bitTableAddString( table_t *table , char *string) {
   
    // Get the hash key of the string
    int hash_key = table->hashFunction(string);
    int table_size = table->size;

    // Generate the index using the hashkey and the table size
    int idx = ((hash_key % table_size) + table_size) % table_size;

    // OR the bit mask into the appropriate location at the specific index
    table->bitArray[idx/BITS] |= (1 << (idx % BITS));
}

