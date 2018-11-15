/*
 * Filename: testprependNode
 * Author: Chau Vu
 * Userid: cs30fgg
 * Description: Unit test program to test the function prependNode().
 * Date: Nov 7, 2018
 * Sources of Help: PA2 writeup, discussion
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"


/*
 * Unit Test for prependNode.c
 *
 * long prependNode( linkedList_t ** head, char * str );
 *
 */
void testprependNode() {

    linkedList_t * llPtr = malloc(sizeof(linkedList_t));
    llPtr->value = "OLD";
    llPtr->next = NULL;

    linkedList_t * head = llPtr;

    // TEST 1
    char * str = "NEW";
    prependNode(&head, str);

    TEST( strcmp(head->value, str) == 0);

    // TEST 2
    str = "NEWER";
    prependNode(&head, str);

    TEST( strcmp(head->value, "NEWER") == 0);
    TEST( strcmp((*(*head).next).value, "NEW") == 0);

    // TEST 3
    str = "NEWEST";
    prependNode(&head, str);
    
    TEST( strcmp(head->value, "NEWEST") == 0);
    TEST( strcmp( (head->next)->value, "NEWER") == 0 );
    TEST( strcmp((*(*head).next).value, "NEWER") == 0);
    TEST( strcmp(((head->next)->next)->value, "NEW") == 0 );
    //freeLinkedList(llPtr); 

}

int main() {
    fprintf( stderr, "Testing prependNode...\n\n" );
    testprependNode();
    fprintf( stderr, "\nDone running tests.\n" );
    return 0;
}
