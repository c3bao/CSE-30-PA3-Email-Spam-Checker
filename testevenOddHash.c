/*
 * Filename: testevenOddHash
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Unit test program to test the function evenOddHash().
 * Date: Nov 8, 2018
 * Sources of Help: Given file, PA2 writeup
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

/*
 * Unit Test for evenOddHash.s
 *
 * long evenOddHash( char * src );
 *
 */
void testevenOddHash() {

    char * str = "ABCD";

    int hash = HASH_START_VAL;
    hash = hash * HASH_PRIME + 'A';
    hash = hash * HASH_PRIME + 'C';
    hash = hash * HASH_PRIME + 'B';
    hash = hash * HASH_PRIME + 'D';

    /* Validate the hash value. */
    TEST( evenOddHash(str) ==  hash);

    /* Test empty string */
    str = "";
    TEST( evenOddHash(str) == HASH_START_VAL );

    /* Test odd length strings */
    str = "CSE30";
    hash = HASH_START_VAL;
    hash = hash * HASH_PRIME + 'C';
    hash = hash * HASH_PRIME + 'E';
    hash = hash * HASH_PRIME + '0';
    hash = hash * HASH_PRIME + 'S';
    hash = hash * HASH_PRIME + '3';

    TEST( evenOddHash(str) == hash );

    str = "PA3";
    hash = HASH_START_VAL;
    hash = hash * HASH_PRIME + 'P';
    hash = hash * HASH_PRIME + '3';
    hash = hash * HASH_PRIME + 'A';

    TEST( evenOddHash(str) == hash );

    /*  Test long string */
    str = "IGOTREKTBYTHEMIDTERM";
    hash = HASH_START_VAL;
    hash = hash * HASH_PRIME + 'I';
    hash = hash * HASH_PRIME + 'O';
    hash = hash * HASH_PRIME + 'R';
    hash = hash * HASH_PRIME + 'K';
    hash = hash * HASH_PRIME + 'B';
    hash = hash * HASH_PRIME + 'T';
    hash = hash * HASH_PRIME + 'E';
    hash = hash * HASH_PRIME + 'I';
    hash = hash * HASH_PRIME + 'T';
    hash = hash * HASH_PRIME + 'R';

    hash = hash * HASH_PRIME + 'G';
    hash = hash * HASH_PRIME + 'T';
    hash = hash * HASH_PRIME + 'E';
    hash = hash * HASH_PRIME + 'T';
    hash = hash * HASH_PRIME + 'Y';
    hash = hash * HASH_PRIME + 'H';
    hash = hash * HASH_PRIME + 'M';
    hash = hash * HASH_PRIME + 'D';
    hash = hash * HASH_PRIME + 'E';
    hash = hash * HASH_PRIME + 'M';

    TEST( evenOddHash(str) == hash );
   
    /* Test lower case string */
    str = "cse30pa3";
    hash = HASH_START_VAL;
    hash = hash * HASH_PRIME + 'c';
    hash = hash * HASH_PRIME + 'e';
    hash = hash * HASH_PRIME + '0';
    hash = hash * HASH_PRIME + 'a';
    hash = hash * HASH_PRIME + 's';
    hash = hash * HASH_PRIME + '3';
    hash = hash * HASH_PRIME + 'p';
    hash = hash * HASH_PRIME + '3';

    TEST( evenOddHash(str) == hash );

}

int main() {
    fprintf( stderr, "Testing evenOddHash...\n\n" );
    testevenOddHash();
    fprintf( stderr, "\nDone running tests.\n" );
    return 0;
}
