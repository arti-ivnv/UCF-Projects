/*
 Artem Ivanov
 Assignment 4
 7/17/17
 COP 3223
 */

// Part 2

#include <stdio.h>

// Function declaration
char grade(double *score);

int main()
  {
    double score;

    // Ask for the score
    printf ("Enter your score:");
    scanf ("%lf",&score);

    // Final result
    printf ("Your grade is %c \n",grade(&score));

    return 0;
  }

  // Function that defines our grade
  char grade(double *score)
    {
      if (*score >= 90)
        return 'A';
      else if (*score >= 80)
        return 'B';
      else if (*score >= 70)
        return 'C';
      else if (*score >= 60)
        return 'D';
      else
        return 'F';
    }
