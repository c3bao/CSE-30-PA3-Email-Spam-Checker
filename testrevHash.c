/*
 * Filename: testrevHash
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Unit test program to test the function revHash().
 * Date: Nov 8, 2018
 * Sources of Help: Given file, PA2 writeup
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

static int revHashC(char * str) {

    int hash = HASH_START_VAL;
    int strLen = strlen(str);
    for( int i = (strLen - 1); i >= 0; i-- ) {
        hash = hash * HASH_PRIME + str[i];
    }
    return hash;

}

/*
 * Unit Test for revHash.s
 *
 * long revHash( char * src );
 *
 */
void testrevHash() {

    char * str = "ABCD";
    /* Validate the hash value. */
    TEST( revHash(str) == revHashC(str) );

    str = "";
    TEST( revHash(str) == revHashC(str) );

    /*
     * TODO: YOU MUST WRITE MORE TEST CASES FOR FULL POINTS
     */
    str = "CSE30";
    TEST( revHash(str) == revHashC(str) );

    str = "PA3";
    TEST( revHash(str) == revHashC(str) );

    //test long string
    str = "IGOTREKTBYTHEMIDTERM";
    TEST( revHash(str) == revHashC(str) );

    // Test Lower Case
    str = "cse30pa3";
    TEST( revHash(str) == revHashC(str) );
}

int main() {
    fprintf( stderr, "Testing revHash...\n\n" );
    testrevHash();
    fprintf( stderr, "\nDone running tests.\n" );
    return 0;
}
