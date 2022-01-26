/*
 Artem Ivanov
 Assignment 4
 7/17/17
 COP 3223
 */

// Part 1

#include <stdio.h>

// Function declaration
double Function(int *Array, int ar_size);

int main()
  {
    int Array[] = {78, 90, 56, 99, 88, 68, 92};
    int ar_size = 7;

    // Average of the array
    double average = Function(Array,ar_size);

    // Final result
    printf("The resulting average is %.2lf \n", average);

    return 0;
  }


  // Function that counts averege of the array
  double Function(int *Array, int ar_size)
    {
      int sum = 0;
      double average;

      // For loop that counts sum of all elements
      for(int i = 0; i < ar_size; i++)
        {
          sum += Array[i];
        }

      // Counts average of the array
      average = (double)sum / ar_size;

      // Return result into a main function
      return average;
    }
