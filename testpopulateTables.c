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

    table_t eotbl = {
        .hashFunction = evenOddHash,
        .size = size,
        .llArray = calloc( size, sizeof(linkedList_t) )
    };

    // TEST EMAILS_10
    FILE * dataFile = fopen("emails_1000", "rb");
    populateTables(&htbl, &rtbl, &eotbl, dataFile);

    int count = 0;

    // Check if all 10 emails are populated in llArray
    for(int i = 0; i < eotbl.size; i++) {
        linkedList_t * currNode = eotbl.llArray[i];

        while(currNode != NULL) {
            printf("%s\n", currNode->value);
            count++;
            currNode = currNode->next;
        }
    }

    TEST(count == 1000);

}
int main() {
    fprintf( stderr, "Testing populateTables...\n\n" );
    testpopulateTables();
    fprintf( stderr, "\nDone running tests.\n" );
    return 0;
}
