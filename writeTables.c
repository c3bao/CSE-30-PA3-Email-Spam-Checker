/*
 * Filename: writeTables
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Serialize the three hash tables and write them to outFile
 *              to be read and deserialized back into hashtables later.
 * Date: Nov 14, 2018
 * Sources of Help: PA2 writeup
 */

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

/*  Function name: writeTables
 *  Function prototype: void writeTables( FILE * outFile, table_t * htbl, 
 *                                        table_t * rtbl, table_t * eotbl)
 *  Description: Serialize the three hashtables and write them to outFile
 *               to be read and deserialized back into hashtables in the
 *               original format later.
 *  Parameters: outFile - the file to write to
 *              htbl - hash table
 *              rtbl - reverse hash table
 *              eotbl - even odd table
 *  Error Conditions: None
 *  Side Effects: None
 *  Return Value: None
 *
 */
void writeTables( FILE * outFile, table_t * htbl, table_t * rtbl, 
                  table_t * eotbl ) {
    // Write the size of the tables
    fwrite(&(htbl->size), sizeof(long), 1, outFile);

    // Write the entries of htbl
    fwrite(htbl->bitArray, sizeof(char), (htbl->size+7)/8, outFile);

    // Write the entries rtbl
    fwrite(rtbl->bitArray, sizeof(char), (rtbl->size+7)/8, outFile);


    // Write strings in each bucket of eotbl
    for(int i = 0; i < eotbl->size; i++) {
        linkedList_t * currNode = eotbl->llArray[i];

        while(currNode != NULL) {
            fputs(currNode->value, outFile);
            fputc('\0', outFile);
            currNode = currNode->next;
        }

        fputc('\0', outFile);

        /*
        if(currNode != NULL) {
            fputs(currNode->value, outFile);
            fputc('\0', outFile);

            while(currNode->next != NULL) {
                fputs(currNode->next->value, outFile);
                fputc('\0', outFile);
            }
        }
        */
    }

}

