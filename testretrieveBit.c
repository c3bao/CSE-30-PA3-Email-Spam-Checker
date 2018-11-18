/*
 * Filename: testretrieveBit
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Unit test program to test the function retrieveBit().
 * Date: Nov 8, 2018
 * Sources of Help: Given file, PA2 writeup
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

/*
 * Unit Test for retrieveBit.s
 *
 * long retrieveBit( table_t * table, char * string );
 *
 */
void testretrieveBit() {

    long size = DEFAULT_SIZE;

    table_t htbl = {
        .hashFunction = hash,
        .size = size,
        .bitArray = calloc( sizeof(char), (size+CEILING)/BITS )
    };

    table_t rtbl = {
        .hashFunction = revHash,
        .size = size,
        .bitArray = calloc( sizeof(char), (size+CEILING)/BITS )
    };

    char * goodStr = "CSE30";
    char * goodStr2 = "PA3";
    char * badStr = "asldfkjwoieg";
    char * badStr2 = "LASKJFSDLF";
    bitTableAddString(&htbl, goodStr);
    bitTableAddString(&htbl, goodStr2);
    
    TEST( retrieveBit(&htbl, goodStr) == 1 );
    TEST( retrieveBit(&htbl, goodStr2) == 1 );
    TEST( retrieveBit(&htbl, badStr) == 0 );
    TEST( retrieveBit(&htbl, badStr2) == 0 );
}

int main() {
    fprintf( stderr, "Testing retrieveBit...\n\n" );
    testretrieveBit();
    fprintf( stderr, "\nDone running tests.\n" );
    return 0;
}
