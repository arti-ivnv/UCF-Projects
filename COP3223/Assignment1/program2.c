/*
Artem Ivanov
Assignment 1
5/25/17
COP 3223
 */

//program 2

// Library Declaration
#include <stdio.h>

int main()
    {
        //Variables declaration
        float Length, Width, Height;
        double volume_inch, volume_feet;

        // inputs and outputs
        printf ("Enter your Lenght (in inches): ");
        scanf ("%f",&Length);
        printf ("\nEnter your Width (in inches): ");
        scanf ("%f",&Width);
        printf ("\nEnter your Heigth (in inches): ");
        scanf ("%f",&Height);

        // arithmetic
        volume_inch = Length * Width * Height;
        volume_feet = volume_inch/1728;

        // final output
        printf ("\nThe volume is %.2lf cubic inches.\n", volume_inch);
        printf ("The volume is %.2lf cubic feet.\n", volume_feet);


        return 0;
    }
