/*
 Artem Ivanov
 Lecture Assignment 3
 7/7/17
 COP 3223C
 */

//Part 1

#include <stdio.h>

int main ()
  {
    // Array declaration
    int vape[10] = {12, 89, 52, 22, 34, 45, 68, 71, 99, 1};
    int i;
      // Loop for output
      for (i = 0; i < 10; i++)
        {
          printf ("One numer of the array is %d \n", vape[i]);
        }
    return 0;
  }
