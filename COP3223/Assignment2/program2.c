/*
 Artem Ivanov
 Lecture Assignment 2
 6/23/17
 COP 3223
 */

// part 2

#include <stdio.h>

int main ()
  {
    int user_num;

    printf ("Enter a number between 1 and 20\n");
    scanf("%d",&user_num);

    // Swtitch statement
    switch (user_num)
      {
        // Roman number for 1
        case 1:
          printf("You entered I.\n");
          break;
        // Roman number for 2
        case 2:
          printf("You entered II.\n");
          break;
        // Roman number for 3
        case 3:
          printf("You entered III.\n");
          break;
        // Roman number for 4
        case 4:
          printf("You entered IV.\n");
          break;
        // Roman number for 5
        case 5:
          printf("You entered V.\n");
          break;
        // Roman number for 6
        case 6:
          printf("You entered VI.\n");
          break;
        // Roman number for 7
        case 7:
          printf("You entered VII.\n");
          break;
        // Roman number for 8
        case 8:
          printf("You entered VIII.\n");
          break;
        // Roman number for 9
        case 9:
          printf("You entered IX.\n");
          break;
        // Roman number for 10
        case 10:
          printf("You entered X.\n");
          break;
        // Roman number for 11
        case 11:
          printf("You entered XI.\n");
          break;
        // Roman number for 12
        case 12:
          printf("You entered XII.\n");
          break;
        // Roman number for 13
        case 13:
          printf("You entered XIII.\n");
          break;
        // Roman number for 14
        case 14:
          printf("You entered XIV.\n");
          break;
        // Roman number for 15
        case 15:
          printf("You entered XV.\n");
          break;
        // Roman number for 16
        case 16:
          printf("You entered XVI.\n");
          break;
        // Roman number for 17
        case 17:
          printf("You entered XVII.\n");
          break;
        // Roman number for 18
        case 18:
          printf("You entered XVIII.\n");
          break;
        // Roman number for 19
        case 19:
          printf("You entered XIX.\n");
          break;
        // Roman number for 20
        case 20:
          printf("You entered XX.\n");
          break;
        default:
          printf("Sorry, you entered incorrect number.\n");
        // If statement that turn off the program if a number out of range
        if (!(0>=user_num>20))
          {
            printf("Error!!!\n");
            exit (-1);
          }
      }
    return 0;
  }
