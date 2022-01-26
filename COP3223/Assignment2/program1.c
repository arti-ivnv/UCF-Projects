/*
 Artem Ivanov
 Lecture Assignment 2
 6/23/17
 COP 3223
 */

//Part I

#include <stdio.h>
#include <time.h>

int main ()
  {
    // Variable declaration
    float now = time (NULL);
    int minutes, months, weeks, days;
    int minute_sec,hour_sec,day_sec,week_sec,month_sec,year_sec;
    int hours,years;

    // Counts how many seconds in a minute
    minute_sec = 60;
    // Counts how many seconds in an hour
    hour_sec = 3600;
    // Counts how many seconds in a day
    day_sec = 3600 * 24;
    // Counts how many seconds in a week
    week_sec = day_sec * 7;
    // Counts how many seconds in a month
    month_sec = day_sec * 30.42;
    // Counts how many seconds in a year
    year_sec = day_sec * 365;

    // Arithmetic output
    printf("In a minute are %d seconds. \n", minute_sec);
    printf("In an hour are %d seconds. \n", hour_sec);
    printf("In a day are %d seconds. \n", day_sec);
    printf("In a week are %d seconds. \n", week_sec);
    printf("In a month are %d seconds. \n", month_sec);
    printf("In a year are %d seconds. \n\n", year_sec);

    // Counts how many years left since 1st january 1970
    years = now / year_sec;
    // Counts how many moths left since 1st january 1970
    months = (now - (years * year_sec)) / month_sec;
    // Counts how many weeks left since 1st january 1970
    weeks = ((now - (years * year_sec)) - (months * month_sec)) / week_sec;
    // Counts how many days left since 1st january 1970
    days = ((now - (years * year_sec)) - (months * month_sec) - (weeks * week_sec)) / day_sec;
    // Counts how many hours left since 1st january 1970
    hours = ((now - (years * year_sec)) - (months * month_sec) - (weeks * week_sec) - (days * day_sec)) / hour_sec;

    printf("%.2f seconds passed since 1st january 1970\n\n", now);

    printf("%d years left since 1st january 1970\n\n", years);

    printf("%d months left since 1st january 1970\n\n", months);

    printf("%d weeks left since 1st january 1970\n\n", weeks);

    printf("%d days left since 1st january 1970\n\n", days);

    printf("%d hours left since 1st january 1970\n\n", hours);

    return 0;
  } 
