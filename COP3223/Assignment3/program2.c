/*
 Artem Ivanov
 Lecture Assignment 3
 7/7/17
 COP 3223C
 */

//Part 2

#include <stdio.h>
#include <time.h>

int main ()
  {
    // Random generator
    srand(time(NULL));
    // Array declaration
    double vape[100];
    int i;
    for (i = 0; i < 100; i++)
      {
        vape[i] = (double)(rand() % 100 + 1) / 2.0;//Random generator
        printf("%2.2lf      ", vape[i]);
          // if statement that separates rows (10 numbers per 1 row)
          if ((i + 1) % 10 == 0)
            {
              printf("\n");
            }
      }
    return 0;
  }
