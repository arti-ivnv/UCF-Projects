/*
 Artem Ivanov
 Lecture Assignment 2
 6/23/17
 COP 3223
 */

//Part 3

#include <stdio.h>
#include <time.h>

int main()
  {
    //Rangom generator
    int myRandomNumber;
    srand(time(NULL));
    myRandomNumber = rand();

    printf("Your random number is %d .\n",myRandomNumber);

    // Checks if the number is even or odd
    if (myRandomNumber%2==0)
      {
        printf("Your number is even.\n");
      }
    else
      {
        printf("Your number is odd.\n");
      }
    // Checks if the number is divisible by 3
    if (myRandomNumber%3==0)
      {
        printf("Your number divisible by 3.\n");
      }
    // Checks if the number is divisible by 10
    else if (myRandomNumber%10==0)
      {
        printf("Your number divisible by 10\n");
      }
      
    return 0;
  }
