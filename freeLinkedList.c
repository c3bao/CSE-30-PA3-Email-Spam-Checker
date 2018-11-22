/*
 * Filename: freeLinkedList
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Frees all elements in the input linked list.
 * Date: Nov 9, 2018
 * Sources of Help: PA3 writeup
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

/*  Function name: freeLinkedList
 *  Function prototype: void freeLinkedList( linkedList_t * head)
 *  Description: Frees all elements in the input linked list.
 *  Parameters: head - pointer to the head of a linked list
 *  Error Conditions: None
 *  Side Effects: The input linked list is freed from memory
 *  Return Value: None
 *
 */
void freeLinkedList( linkedList_t * head) {
    
    linkedList_t * currNode = head;

    // Traverse through the linked list
    while( currNode != NULL ) {
        linkedList_t * next = currNode->next;

        // Free the value first
        free(currNode->value);

        // Then free the node
        free(currNode);
        currNode = next;
    }
}

