/*
 * Filename: evenOddHash
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Compute the hash key by iterating through the string by even,
 *              then by odd indices.
 * Date: Nov 9, 2018
 * Sources of Help: PA2 writeup
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

/*  Function name: evenOddHash
 *  Function prototype: int evenOddHash( char * str )
 *  Description: Compute the hash key by iterating through the string by even,
 *               then by odd indices.
 *  Parameters: str - The string to get the hash key for
 *  Error Conditions: None
 *  Side Effects: None
 *  Return Value: The hash key of str
 *
 */
int evenOddHash(char * str) {

    int hash = HASH_START_VAL;
    int strLen = strlen(str);

    // Loop through the even indices first
    for( int i = 0; i < strLen; i+=2 ) {
        hash = hash * HASH_PRIME + str[i];
    }

    // Then loop through the odd indices
    for( int i = 1; i < strLen; i+=2 ) {
        hash = hash * HASH_PRIME + str[i];
    }
    return hash;

}

