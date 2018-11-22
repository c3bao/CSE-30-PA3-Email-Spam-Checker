/*
 * Filename: launchUserQuery
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Handle user interaction to search the tables and prints out the
 *              result for each search.
 * Date: Nov 18, 2018
 * Sources of Help: PA3 writeup, discussion slides
 */

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"
#include "pa3Strings.h"

/*  Function name: launchUserQuery
 *  Function prototype: void launchUserQuery( table_t * htbl, table_t * rtbl, 
 *                                           table_t * eotbl)
 *  Description: Handle user interaction to search the tables and prints out the
 *               result for each search.
 *  Parameters: htbl - hash table
 *              rtbl - reverse hash table
 *              eotbl - even odd table
 *  Error Conditions: None
 *  Side Effects: None
 *  Return Value: None
 *
 */
void launchUserQuery( table_t * htbl, table_t * rtbl, table_t * eotbl) {

    printf(USER_PROMPT);
    char str[BUFSIZ] = {NULL_TERMINATOR};  //local char array
    char *ptr = str;
    // Get all the lines of the dataFile
    while(fgets( str, BUFSIZ, stdin) != NULL ) {
        // Change \n to \0
        char *newLinePtr = strchr(ptr, NEW_LINE);
        *newLinePtr = NULL_TERMINATOR;
        // Convert all characters to lower case
        for( int i = 0; i < strlen(str); i++) {
            str[i] = tolower(str[i]);
        }

        if( *ptr == NULL_TERMINATOR ) {
            printf(USER_PROMPT);
            continue;
        }

        // Count number of times str appears in the tables
        int tableCount = checkTables(ptr, htbl, rtbl, eotbl);

        // Output the appropriate response depending on number
        //talbes 
        if( tableCount == EXACT_MATCH ) {
            printf(FOUND_IN_ALL, str);
        }

        // If string is found in one or more tables
        else if( tableCount >= 1 ) {
            printf(FOUND_IN_SOME, str, tableCount);
        }

        // If string not found
        else {
            printf(WORD_NOT_FOUND, str);
        }

        printf(USER_PROMPT);
    }
    printf("%c", NEW_LINE);

}

