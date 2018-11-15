/*
 * Filename: testHash
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Unit test program to test the function hash().
 * Date: Nov 7, 2018
 * Sources of Help: Given testhash tester
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

static int hashC(char * str) {

    int hash = HASH_START_VAL;
    int strLen = strlen(str);
    for( int i = 0; i < strLen; i++ ) {
        hash = hash * HASH_PRIME + str[i];
    }
    return hash;

}

/*
 * Unit Test for hash.s
 *
 * long hash( char * src );
 *
 */
void testhash() {

    char * str = "ABCD";
    /* Validate the hash value. */
    TEST( hash(str) == hashC(str) );

    str = "";
    TEST( hash(str) == hashC(str) );

    /*
     * TODO: YOU MUST WRITE MORE TEST CASES FOR FULL POINTS
     */


    //test odd length strings
    str = "CSE30";
    TEST( hash(str) == hashC(str) );

    str = "PA3";
    TEST( hash(str) == hashC(str) );

    str = "cse30pa3";
    TEST( hash(str) == hashC(str) );

    //test long string
    str = "IGOTREKTBYTHEMIDTERM";
    TEST( hash(str) == hashC(str) );
}

int main() {
    fprintf( stderr, "Testing hash...\n\n" );
    testhash();
    fprintf( stderr, "\nDone running tests.\n" );
    return 0;
}
