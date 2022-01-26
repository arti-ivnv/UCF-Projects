/*
Artem Ivanov
Assignment 1
5/25/17
COP 3223
 */

//program 1

#include <stdio.h> //Library Declaration

int main()
    {
        // Declaration
        long int user_1, user_2, user_3;
        long int user_4, user_5, sum;
        long double average;

        // Output and input information
        printf ("Enter your first value: \n");
        scanf ("%ld",&user_1);
        printf ("You entered: %ld \n",user_1);
        printf ("Enter your second value: \n");
        scanf ("%ld",&user_2);
        printf ("You entered: %ld \n",user_2);
        printf ("Enter your third value: \n");
        scanf ("%ld",&user_3);
        printf ("You entered: %ld \n",user_3);
        printf ("Enter your fourth value: \n");
        scanf ("%ld",&user_4);
        printf ("You entered: %ld \n",user_4);
        printf ("Enter your fifth value: \n");
        scanf ("%ld",&user_5);
        printf ("You entered: %ld \n\n",user_5);

        // sum of all of the users' numbers
        sum = user_1 + user_2 + user_3 + user_4 + user_5;
        printf ("The sum of the numbers you entered is: %ld \n",sum);

        // average of all of the users' numbers
        average = (double) sum / 5;
        printf ("The average is: %.2Lf \n",average);

        return 0;
    }
