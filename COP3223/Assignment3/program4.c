/*
 Artem Ivanov
 Lecture Assignment 3
 7/7/17
 COP 3223C
 */

// Part 4

#include <stdio.h>
#include <time.h>

int main()
  {
    // Array declaration (Dice throws)
    int dice[1000];
    // Array declaration (counter)
    int count[6];
    int i,j;
    // Random generator
    srand(time(NULL));

    for(i = 1; i <= 1000; i++)
      {
        // Random generator
        dice[i] = (rand() % 6 + 1);
        printf("%d ", dice[i]);

        // Statements that counts results
        if (dice[i] == 1)
          {
            count[1]++;
          }
        else if (dice[i] == 2)
          {
            count[2]++;
          }
        else if (dice[i] == 3)
          {
            count[3]++;
          }
        else if (dice[i] == 4)
          {
            count[4]++;
          }
        else if (dice[i] == 5)
          {
            count[5]++;
          }
        else
          {
            count[6]++;
          }
      }

      //Counter output
    for (j = 1; j <= 6; j++)
      {
        printf("\n%d occurs %d times.\n", j, count[j]);
      }
    return 0;
  }
