/*
 * Filename: evenOddHash
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Compute the hash key by interating through the string by even,
 *              then by odd indices.
 * Date: Nov 9, 2018
 * Sources of Help: PA2 writeup
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

int evenOddHash(char * str) {

    int hash = HASH_START_VAL;
    int strLen = strlen(str);
    for( int i = 0; i < strLen; i+=2 ) {
        hash = hash * HASH_PRIME + str[i];
    }
    for( int i = 1; i < strLen; i+=2 ) {
        hash = hash * HASH_PRIME + str[i];
    }
    return hash;

}

