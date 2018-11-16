/*
 * Filename: testwriteTables
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Unit test program to test the function writeTables().
 * Date: Nov 7, 2018
 * Sources of Help: PA2 writeup, discussion
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"
#include "freeLinkedList.c"


/*
 * Unit Test for writeTables.c
 *
 * long writeTables( FILE * outFile, table_t * htbl, table_t * rtbl,
 *                   table_t * eotbl);
 *
 */
void testwriteTables() {

    long size = DEFAULT_SIZE;

    table_t htbl = {
        .hashFunction = hash,
        .size = size,
        .bitArray = calloc( sizeof(char), (size+7)/8 )
    };

    table_t rtbl = {
        .hashFunction = revHash,
        .size = size,
        .bitArray = calloc( sizeof(char), (size+7)/8 )
    };

    table_t eotbl = {
        .hashFunction = evenOddHash,
        .size = size,
        .llArray = malloc( sizeof(linkedList_t)*size )
    };

    FILE * outFile = fopen("MYSOL", "wb");
    FILE * dataFile = fopen("emails_all", "rb");
    populateTables(&htbl, &rtbl, &eotbl, dataFile);
 
    writeTables(outFile, &htbl, &rtbl, &eotbl);

    fclose(outFile);
    fclose(dataFile);

    for(int i = 0; i < eotbl.size; i++) {
        freeLinkedList(eotbl.llArray[i]);
    }
    free(htbl.bitArray);
    free(rtbl.bitArray);
}

int main() {
    fprintf( stderr, "Testing writeTables...\n\n" );
    testwriteTables();
    fprintf( stderr, "\nDone running tests.\n" );
    return 0;
}
