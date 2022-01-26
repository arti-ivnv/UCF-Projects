/*
 Artem Ivanov
 Lecture Assignment 3
 7/7/17
 COP 3223C
 */

// Part 3

#include <stdio.h>
#include <time.h>

int main()
  {
    // Random generator
    srand(time(NULL));
    // Array declaration
    int vape[100];
    int i,sum;
    double average;

    for (i = 1; i <= 100; i++)
      {
        // Random generator
        vape[i] = rand() % 100 + 1;
        // Sum of all arrays
        sum += vape[i];
        printf("%d = %d\n", i, vape[i]);
      }
      printf("Array sum is %d\n", sum);

      // Average of all arrays
      average = (double)sum / 100;
      printf("Array average is %.2lf\n", average);

    return 0;
  }
