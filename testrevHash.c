/*
 * Filename: testrevHash
 * Author: TODO
 * Userid: TODO
 * Description: Unit test program to test the function revHash().
 * Date: TODO
 * Sources of Help: TODO
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

static int revHashC(char * src) {

  /* TODO
   * Put C version of revHash here
   */

  return 0;

}

/*
 * Unit Test for revHash.s
 *
 * long revHash( char * src );
 *
 */
void testrevHash() {

  char * src = "ABCD";
  /* Validate the hash value. */
  TEST( revHash(src) == revHashC(src) );
  
  src = "";
  TEST( revHash(src) == revHashC(src) );
  
  /*
   * TODO: YOU MUST WRITE MORE TEST CASES FOR FULL POINTS
   */

}

int main() {
  fprintf( stderr, "Testing revHash...\n\n" );
  testrevHash();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
