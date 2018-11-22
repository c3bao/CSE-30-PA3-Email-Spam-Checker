/*
 * Filename: search.c
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Performs the funcitonality for the search program. Parse the
 *              command line arguments and handle any encountered errors.
 *              Create the hash tables and fills them by reading from the
 *              input file. Performs an interactive search and print stats
 *              if needed.
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

#define correctFlag 1

static struct option getopt_longOpts[] = {
    {
        LONG_HELP_FLAG, no_argument, 0, HELP_FLAG
    },

    {
        LONG_INFILE_FLAG, required_argument, 0, INFILE_FLAG
    },

    {0, 0, 0, 0} // handle the case --h
};


/**
 *  Performs the funcitonality for the search program. Parse the command line
 *  arguments and handle any encountered errors.
 *  Create the hash tables and fills them by reading from the input file.
 *  Performs an interactive search and print stats if needed.
 *
 *  Return: EXIT_FAILURE if an error occurred
 *          EXIT_SUCCESS if no error occurred
 */
int main(int argc, char* argv[] ) {
    int opt;
    int flagCounter;    // Keep track of inFile flag
    int size = DEFAULT_SIZE;
    FILE * inFile;  // file with data


    /* Parse the command line arguments */
    while((opt = getopt_long(argc, argv, SEARCH_FLAGS, 
                    getopt_longOpts, 0)) != -1) {
        switch(opt) {

            case HELP_FLAG:
                fprintf( stdout, LONG_SEARCH_USAGE );
                return EXIT_SUCCESS;

           
            case INFILE_FLAG:
                errno = 0;
                inFile = fopen( optarg, "rb");
                // If fopen fails
                if ( inFile == NULL ) {
                    perror(RTABLE_FILE_ERR);
                    fprintf(stderr, SHORT_SEARCH_USAGE );
                    return EXIT_FAILURE;
                }
                flagCounter++;
                break;

             default:
                fprintf(stderr, SHORT_SEARCH_USAGE );
                return EXIT_FAILURE;
                break;
        }

    }

    // Missing either of infile flag or output flag
    if( flagCounter != correctFlag ) {
        fprintf(stderr, MISSING_INFILE);
        fprintf(stderr, SHORT_SEARCH_USAGE );
        return EXIT_FAILURE;
    }

    // If there's extra argument for a flag
    if(optind != argc) {
        fprintf(stderr, EXTRA_ARGS, argv[0] );
        fprintf(stderr, SHORT_SEARCH_USAGE );
        return EXIT_FAILURE;
    }

    // Hash Table
    table_t htbl = {
        .hashFunction = hash,
        .size = size,
        .bitArray = calloc( sizeof(char), (size+CEILING)/BITS )
    };


    // If calloc/malloc fails, free the memory and return
    if( htbl.bitArray == NULL ) {
        perror(MEM_ERR);
        fprintf(stderr, SHORT_SEARCH_USAGE );
        free(htbl.bitArray);
        return EXIT_FAILURE;
    }

    // Reverse Table
    table_t rtbl = {
        .hashFunction = revHash,
        .size = size,
        .bitArray = calloc( sizeof(char), (size+7)/8 )
    };

    // If calloc fails, free the memory and return
    if( rtbl.bitArray == NULL ) {
        perror(MEM_ERR);
        fprintf(stderr, SHORT_SEARCH_USAGE );
        free(rtbl.bitArray);
        return EXIT_FAILURE;
    }

    // Even Odd Table
    table_t eotbl = {
        .hashFunction = evenOddHash,
        .size = size,
        .llArray = malloc( sizeof(linkedList_t *)*size )
    };

    // If malloc fails, free memory and return
    if( eotbl.llArray == NULL ) {
        perror(MEM_ERR);
        fprintf(stderr, SHORT_SEARCH_USAGE );
        free(eotbl.llArray);
        return EXIT_FAILURE;
    }

    // Read the tables from the inFile
    readTables(inFile, &htbl, &rtbl, &eotbl );

    launchUserQuery(&htbl, &rtbl, &eotbl);

    // Close inFile and outFile
    fclose(inFile);

    // Free the llArray
    for(int i = 0; i < eotbl.size; i++) {
        freeLinkedList(eotbl.llArray[i]);
    }

    // Free the bitArrays
    free(htbl.bitArray);
    free(rtbl.bitArray);

    return EXIT_SUCCESS;
}
