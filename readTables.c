/*
 * Filename: readTables
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Read from inFile and populate the three hashtables serialized
 *              in writeTables().
 * Date: Nov 14, 2018
 * Sources of Help: PA3 writeup
 */

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

/*  Function name: readTables
 *  Function prototype: void readTables( FILE * outFile, table_t * htbl, 
 *                                        table_t * rtbl, table_t * eotbl)
 *  Description: Read from inFile and populate the three hashtables serialized
 *               in writeTables().
 *  Parameters: inFile - The file to read from
 *              htbl - hash table
 *              rtbl - reverse hash table
 *              eotbl - even odd table
 *  Error Conditions: None
 *  Side Effects: None
 *  Return Value: None
 *
 */
void readTables( FILE * inFile, table_t * htbl, table_t * rtbl, 
        table_t * eotbl ) {

    long size;

    // Read the size of the tables
    fread(&size, sizeof(long), 1, inFile);

    // Initialize the hash table
    htbl->hashFunction = hash;
    htbl->size = size;
    htbl->bitArray = calloc( sizeof(char), (size+CEILING)/BITS);

    // Initialize the reverse hash table
    rtbl->hashFunction = revHash;
    rtbl->size = size;
    rtbl->bitArray = calloc( sizeof(char), (size+CEILING)/BITS);

    // Initialize the even odd hash table
    eotbl->hashFunction = evenOddHash;
    eotbl->size = size;
    eotbl->bitArray = malloc( sizeof(linkedList_t) * size );

    // Read the htbl contents
    fread(htbl->bitArray, sizeof(char), (htbl->size+CEILING)/BITS, inFile);

    // Read the rtbl contents
    fread(rtbl->bitArray, sizeof(char), (rtbl->size+CEILING)/BITS, inFile);

    // Read eotbl contents
    char buf[BUFSIZ];
    int bufSize = 0;
    int numNewBytes = 0;
    char * ptr;
    int curr = 0;
    char * strPtr;

    while( (numNewBytes = fread(buf + bufSize, 1,
                    BUFSIZ - bufSize, inFile)) > 0 ) {
        bufSize += numNewBytes;
        int llidx = 0;  // Index of the linkedList array

        ptr = buf;      // Pointer to iterate
        strPtr = buf;   // Pointer used to keep track of strings

        while( curr < sizeof(buf) ) {
            // If there is a \0, increment the index in llArray
            if( *strPtr == NULL_TERMINATOR ) {
                llidx++;
                curr++;
                strPtr++;
            }

            // If encounter a non null character
            else {
                ptr = strPtr + 1;
                // Find the next \0
                while( *ptr != NULL_TERMINATOR ) {
                    ptr++;
                    curr++;
                }
                // If reach end of file and string is not null terminated,
                // use memmove to move to the front of buf
/*
                if( curr == sizeof(buf) && *ptr != NULL_TERMINATOR ) {
                    memmove(buf, buf + (BUFSIZ - bufSize), bufSize );
                    break;
                }
*/
                prependNode( &(eotbl->llArray[llidx]) , strPtr );
                strPtr = ptr + 1;
                curr++;

                bufSize -= strlen(strPtr);
            }

        }

        if( bufSize > 0 ) {
            memmove(buf, buf+ (BUFSIZ - bufSize), bufSize);
        }

    }

    fclose(inFile);

}

