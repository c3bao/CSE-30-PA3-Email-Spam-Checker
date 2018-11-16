/*
 * Filename: create.c
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: The main driver for the create portion of the program. Parse
 *              the command line arguments, build the hastables of email data,
 *              and serialize the hashtables to a file.
 * Date: Nov 15, 2018
 * Sources of Help: PA3 writeup, Discussion slides, Piazza, tutors
 */ 

#include <stdio.h>

#include "pa3.h"
#include "test.h"
#include "pa3Strings.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

static struct option getopt_longOpts[] = {
    {
        LONG_SIZE_FLAG, optional_argument, 0, SIZE_FLAG
    },

    {
        LONG_HELP_FLAG, optional_argument, 0, HELP_FLAG
    },

    {
        LONG_INFILE_FLAG, required_argument, 0, INFILE_FLAG
    },

    {
        LONG_OUTPUT_FLAG, required_argument, 0, OUTPUT_FLAG
    }
};


/**
 *  Perform input checking by parsing the command line arguments and checking
 *  for errors. If all inputs are valid, it will display the BCD clock for a
 *  specified (or default) number of ticks.
 *  Otherwise, it will print the error message(s).
 *
 *  Return: EXIT_FAILURE if an error occurred
 *          EXIT_SUCCESS if no error occurred
 */
int main(int argc, char* argv[] ) {
    int opt;
    int size;
    int flagCounter;
    char* endptr;
    FILE * inFile;  // file with data
    FILE * outFile; // file to write to


    /* Parse the command line arguments */
    while((opt = getopt_long(argc, argv, CREATE_FLAGS, 
                    getopt_longOpts, 0)) != -1) {
        switch(opt) {

            case HELP_FLAG:
                fprintf( stdout, LONG_CREATE_USAGE );
                return EXIT_SUCCESS;

            case SIZE_FLAG:
                errno = 0;
                size = strtol(optarg, &endptr, BASE);

                // Check if size is a valid number
                if(*endptr != '\0') {
                    fprintf(stderr, INVALID_NUM, optarg);
                    fprintf(stderr, SHORT_CREATE_USAGE );
                    return EXIT_FAILURE;
                }

                // Check for overflow
                else if( errno != 0 ) {
                    char buffer[BUFSIZ];
                    snprintf( buffer, BUFSIZ, TOO_LARGE_NUM, optarg, BASE);
                    perror(buffer);
                    fprintf(stderr, SHORT_CREATE_USAGE );
                    return EXIT_FAILURE;
                }

                else {
                    // Check if size is within range
                    if( rangeCheck( size, MIN_SIZE, MAX_SIZE+1) != 1 ) {
                        fprintf(stderr, TABLE_SIZE_ERR, MIN_SIZE, MAX_SIZE);
                        fprintf(stderr, SHORT_CREATE_USAGE );
                        return EXIT_FAILURE;
                    }
                }

                break;

            case INFILE_FLAG:
                errno = 0;
                inFile = fopen( optarg, "rb");
                if ( inFile == NULL ) {
                    perror(FILTER_ERR);
                    fprintf(stderr, SHORT_CREATE_USAGE );
                    return EXIT_FAILURE;
                }
                flagCounter++;
                break;

            case OUTPUT_FLAG:
                errno = 0;
                outFile = fopen( optarg, "wb");
                if ( outFile == NULL ) {
                    perror(WTABLE_FILE_ERR);
                    fprintf(stderr, SHORT_CREATE_USAGE );
                    return EXIT_FAILURE;
                }
                flagCounter++;
                break;

            default:
                size = DEFAULT_SIZE;
                // Missing either of infile flag or output flag
                if( flagCounter == 0 ) {
                    fprintf(stderr, ARG_ERR);
                    fprintf(stderr, SHORT_CREATE_USAGE );
                    return EXIT_FAILURE;
                }
                break;
        }

    }
    /*
       if(opterr != 0) {
       printf("IN OPTERR\n");
       fprintf(stderr, SHORT_CREATE_USAGE );
       return EXIT_FAILURE;
       }
       */


    if(size == 0) {
        size = DEFAULT_SIZE;
    }

    if(optind != argc) {
        fprintf(stderr, EXTRA_ARGS, argv[0] );
        fprintf(stderr, SHORT_CREATE_USAGE );
        return EXIT_FAILURE;
    }

    table_t htbl = {
        .hashFunction = hash,
        .size = size,
        .bitArray = calloc( sizeof(char), (size+7)/8 )
    };


    // If calloc/malloc fails, free the memory and return
    if( htbl.bitArray == NULL ) {
        perror(MEM_ERR);
        fprintf(stderr, SHORT_CREATE_USAGE );
        free(htbl.bitArray);
        return EXIT_FAILURE;
    }

    table_t rtbl = {
        .hashFunction = revHash,
        .size = size,
        .bitArray = calloc( sizeof(char), (size+7)/8 )
    };

    if( rtbl.bitArray == NULL ) {
        perror(MEM_ERR);
        fprintf(stderr, SHORT_CREATE_USAGE );
        free(rtbl.bitArray);
        return EXIT_FAILURE;
    }

    table_t eotbl = {
        .hashFunction = evenOddHash,
        .size = size,
        .llArray = malloc( sizeof(linkedList_t *)*size )
    };

    if( eotbl.llArray == NULL ) {
        perror(MEM_ERR);
        fprintf(stderr, SHORT_CREATE_USAGE );
        free(eotbl.llArray);
        return EXIT_FAILURE;
    }

    populateTables(&htbl, &rtbl, &eotbl, inFile);

    writeTables(outFile, &htbl, &rtbl, &eotbl);

    fclose(inFile);
    fclose(outFile);

    for(int i = 0; i < eotbl.size; i++) {
        freeLinkedList(eotbl.llArray[i]);
    }

    free(htbl.bitArray);
    free(rtbl.bitArray);

}
