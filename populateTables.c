/*
 * Filename: populateTables
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Populate the hash tables by reading in dataFile and calling
 *              addString function for each table.
 * Date: Nov 13, 2018
 * Sources of Help: PA2 writeup
 */

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

/*  Function name: populateTables
 *  Function prototype: void populateTables( table_t * htbl, table_t * rtbl, 
 *                                           table_t * eotbl, FILE * dataFile)
 *  Description: Populate the hash tables by reading in dataFile and calling
 *               addString function for each table.
 *  Parameters: htbl - hash table
 *              rtbl - reverse hash table
 *              eotbl - even odd table
 *              dataFile - each line in this file is an email address
 *  Error Conditions: None
 *  Side Effects: None
 *  Return Value: None
 *
 */
void populateTables( table_t * htbl, table_t * rtbl, table_t * eotbl,
                     FILE * dataFile) {

    if( dataFile != NULL ) {
        char line[BUFSIZ];  //local char array
        char *ptr = line;   
        // Get all the lines of the dataFile
        while(fgets( line, BUFSIZ, dataFile) != NULL ) {
            // Change \n to \0
            char *newLinePtr = strchr(ptr, '\n');
            *newLinePtr = '\0';
            // Convert all characters to lower case
            for( int i = 0; i < strlen(line); i++) {
                line[i] = tolower(line[i]);
            }

            ptr = line;

            bitTableAddString(htbl, ptr);
            bitTableAddString(rtbl, ptr);
            llTableAddString(eotbl, ptr);

            printf("%s\n", line);
        }
    }
    
        
}

