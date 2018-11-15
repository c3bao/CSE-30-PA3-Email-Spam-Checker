/*
 * Filename: prependNode
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Push the str element onto the front of the linked list.
 * Date: Nov 9, 2018
 * Sources of Help: PA2 writeup
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

/*  Function name: prependNode
 *  Function prototype: void prependNode( linkedList_t ** head, char * str)
 *  Description: Push the str element onto the front of the linked list pointed
 *               to by head.
 *  Parameters: head - pointer to the head of a linked list
 *              str - The string to insert
 *  Error Conditions: Error with dynamically allocating memory.
 *  Side Effects: The head of the linked list pointed to by head is now str
 *  Return Value: None
 *
 */
void prependNode( linkedList_t ** head, char * str) {
    
    linkedList_t * nodePtr = malloc(sizeof(linkedList_t));

    // If malloc fails, free the memory and return
    if( nodePtr == NULL ) {
        perror(MEM_ERR);
        free(nodePtr);
        return;
    }

    char * strPtr = malloc(sizeof(char) * (strlen(str) + 1));

    // If malloc fails, free the memory and return
    if( strPtr == NULL ) {
        perror(MEM_ERR);
        free(strPtr);
        return;
    }

    // Copy the str into the allocated mem
    nodePtr->value = strncpy(strPtr, str, strlen(str));
    
    nodePtr->next = *head;
    (*head) = nodePtr;
    
}

