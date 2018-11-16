/*
 * Filename: testpopulateTables
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Unit test program to test the function populateTables().
 * Date: Nov 7, 2018
 * Sources of Help: PA2 writeup, discussion
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"


/*
 * Unit Test for populateTables.c
 *
 * long populateTables( table_t * htbl, table_t * rtbl, table_t * eotbl,
 *                      FILE * dataFile);
 *
 */
void testpopulateTables() {

    long size = MIN_SIZE;

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
        .llArray = calloc( size, sizeof(linkedList_t) )
    };

    FILE * dataFile = fopen("emails_10", "rb");
    populateTables(&htbl, &rtbl, &eotbl, dataFile);

    for(int i = 0; i < eotbl.size; i++) {
        if(eotbl.llArray[i] != NULL) {
            printf("%s\n", eotbl.llArray[i]->value);
            if(eotbl.llArray[i]->next != NULL) {
                printf("%s\n", eotbl.llArray[i]->next->value);
            }
        }
    }
}

int main() {
    fprintf( stderr, "Testing populateTables...\n\n" );
    testpopulateTables();
    fprintf( stderr, "\nDone running tests.\n" );
    return 0;
}
