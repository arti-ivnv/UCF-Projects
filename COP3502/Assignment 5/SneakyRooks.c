// Artem Ivanov

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SneakyRooks.h"

// Level of difficulty
double difficultyRating(void)
{
  return 3.0;
}

// Hours spent
double hoursSpent(void)
{
  return 13.0;
}

// Counts a power
int pow_fancy(int base, int power)
{
  if (power == 0)
  {
    return 1;
  }
  else
  {
    return base * pow_fancy(base, (power - 1));
  }
}

// Parsing coordinates into numeric system
void parseCoordinateString(char *rookString, Coordinate *rookCoordinate)
{
  int length = 0;
  int str_len = 0;
  int str_len_copy = 0;
  char *digits;
  int n, m, p = 0;

  length = strlen(rookString);

  rookCoordinate->col = 0;
  rookCoordinate->row = 0;

  // Check of how many a-z letters in our coordinate
  for (n = 0; n < length; n++)
  {
    if (rookString[n] >= 97 && rookString[n] <= 122)
    {
      str_len++;
    }
  }

  str_len_copy = str_len;

  // Base conversion of columns from letter to numbers
  for (n = 0; n < str_len; n++)
  {
    str_len_copy--;
    rookCoordinate->col += (rookString[n] - 96) * pow_fancy(26, str_len_copy);
  }

  p = length - str_len;

  // Base conversion of rows
  for (m = str_len; m < length; m++)
  {
    p--;
    rookCoordinate->row += (rookString[m] - 48) * pow_fancy(10, p);
  }
}

// Checks if rooks do not intersect somewhere
int allTheRooksAreSafe(char **rookStrings, int numRooks, int boardSize)
{
  int k = 0;
  int check_col[boardSize];
  int check_row[boardSize];

  Coordinate *store = malloc(sizeof(Coordinate) * numRooks);

  // Make all parts of the array equal to 0
  for (k = 0; k < boardSize; k++)
  {
    check_col[k] = 0;
    check_row[k] = 0;
  }

  // Parsing all the coordinates and analyze columns and rows
  for (k = 0; k < numRooks; k++)
  {
    // Check if our rook is not empty or NULL
    if (rookStrings[k] != NULL && rookStrings[k] != "")
    {
      parseCoordinateString(rookStrings[k], store);

      // Check if our rook is not out of the board
      if (store->col <= boardSize && store->row <= boardSize)
      {
        check_col[store->col]++;
        check_row[store->row]++;
      }
    }
  }

  free(store);

  // Checks if our columns or rows intersect anywhere
  for (k = 0; k < boardSize; k++)
  {
    if (check_col[k] > 1)
    {
      return 0;
    }

    if (check_row[k] > 1)
    {
      return 0;
    }
  }

  return 1;
}
