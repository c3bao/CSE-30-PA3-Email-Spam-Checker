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
    eotbl->llArray = malloc( sizeof(linkedList_t) * size );

    // Read the htbl contents
    fread(htbl->bitArray, sizeof(char), (htbl->size+CEILING)/BITS, inFile);

    // Read the rtbl contents
    fread(rtbl->bitArray, sizeof(char), (rtbl->size+CEILING)/BITS, inFile);

    // Read eotbl contents
    char buf[BUFSIZ];
    int bufSize = 0;
    int numNewBytes = 0;    // Number of bytes fread reads in
    char * ptr;     // Pointer to find NULL_TERMINATOR
    int index = 0;
    char * strPtr;  // Pointer used to keep track of string
    int llidx = 0;  //linkedList array index

    while( (numNewBytes = fread(buf + bufSize, 1,
                    BUFSIZ - bufSize, inFile)) > 0 ) {
        bufSize += numNewBytes;
        ptr = buf;      // Pointer to iterate
        strPtr = buf;   // Pointer used to keep track of strings
        int temp = bufSize;
        index = 0;
        while( index < temp ) {
            // If there is a \0, increment the index in llArray
            if( *strPtr == NULL_TERMINATOR ) {
                llidx++;
                index++;
                strPtr++;
                bufSize--;
            }

            // If encounter a non null character
            else {
                ptr = strPtr;
                // Find the next \0
                while( *ptr != NULL_TERMINATOR && index < temp ) {
                    ptr++;
                    index++;
                }

                // If the string is complete, prepend it to the llArray
                if( *ptr == NULL_TERMINATOR) {
                    prependNode( &(eotbl->llArray[llidx]) , strPtr );
                    bufSize -= (strlen(strPtr)+1);
                    strPtr = ptr + 1;
                    index++;
                }
            }

        }

        if( bufSize > 0 ) {
            memmove(buf, buf+ (BUFSIZ - bufSize), bufSize);
        }

    }
   
}

