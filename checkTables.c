/*
 * Filename: checkTables
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

/*  Function name: checkTables
 *  Function prototype: int checkTables( char * str, table_t * htbl, 
 *                                      table_t * rtbl, table_t * eotbl )
 *  Description: Check if string is found in the three tables.
 *  Parameters: htbl - hash table
 *              rtbl - reverse hash table
 *              eotbl - even odd table
 *              str - string to check
 *  Error Conditions: None
 *  Side Effects: None
 *  Return Value: Number of tables str was found in, or EXACT_MATCH if it is
 *                found in all three tables and linked list in eotbl.
 *
 */
int checkTables( char * str, table_t * htbl, table_t * rtbl, 
                     table_t * eotbl ) {
    int tableCount = 0;     // Keep track of how many times the string appear

    // Get the hash bit of hash table
    int hashBit = retrieveBit(htbl, str);
    
    // String is found in hash table
    if( hashBit == 1 ) {
        tableCount += 1;

        // Get the hash bit of reverse hash table
        int revBit = retrieveBit(rtbl, str);

        // String is found in reverse hash table
        if( revBit == 1 ) {
            tableCount += 1;

            // Get the linkedList containing the string
            linkedList_t  * ll = retrieveLinkedList(eotbl, str);

            // If string is in the even odd table
            if( ll != NULL ) {
                tableCount += 1;
                linkedList_t * curr = ll;

                // Compare the specific string value to check for exact match
                while( curr != NULL ) {
                    if( strcmp(curr->value, str) == 0 ) {
                        return EXACT_MATCH;
                    }
                    curr = curr->next;
                }
            }
        }
    }

    return tableCount;
}
