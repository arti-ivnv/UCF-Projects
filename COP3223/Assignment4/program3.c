/*
 Artem Ivanov
 Assignment 4
 7/17/17
 COP 3223
 */

// Part 3

#include <stdio.h>

// Function declaration
int compare(int *f_num, int *s_num, int *t_num);

int main ()
  {
    int f_num, s_num, t_num;

    // Programm asks to enter numbers
    printf("Type your first number:");
    scanf("%d", &f_num);
    printf("Type your second number:");
    scanf("%d", &s_num);
    printf("Type your third number:");
    scanf("%d", &t_num);

    // Final result
    printf("\nYour biggest number is %d\n", compare(&f_num, &s_num, &t_num));

    return 0;
  }

  // Function that compares numbers
  int compare (int *f_num, int *s_num, int *t_num)
    {
      if (*f_num > *s_num && *f_num > *t_num)
        return *f_num;
      else if (*s_num > *f_num && *s_num > *t_num)
        return *s_num;
      else
        return *t_num;
    }
