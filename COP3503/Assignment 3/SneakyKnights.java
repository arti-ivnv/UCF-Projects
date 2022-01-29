// Artem Ivanov
// COP 3503, Fall 2019

import java.util.*;
import java.io.*;
import java.lang.*;


public class SneakyKnights
{

  // Converts entire String to two integers, using Horner's Rule and returns an array.
  public static int[] hornersParser(String str)
  {
    int parse_let = str.charAt(0) - 96;
    int parse_num = 0;
    int length = str.length();

    for (int i = 1; i < length; i++)
    {
      if (Character.isLetter(str.charAt(i)))
      {
        parse_let = parse_let * 26 + (str.charAt(i) - 96);
      }
      else
      {
        parse_num = parse_num * 10 + (str.charAt(i) - 48);
      }
    }

    int coor[] = new int[2];

    coor[0] = parse_let;
    coor[1] = parse_num;

    return coor;
  }

  // Simple checker, gets an array and converts into new string in format of "c1xc2"
  // Then, checks if there is something exists on the moves.
  public static boolean allTheKnightsAreSafe(ArrayList<String> coordinateStrings, int boardSize)
  {
    HashSet<String> Knights = new HashSet<>();
    int actual_coor[] = new int[2];

    // Parsing each input coordinate from the strarter ArrayList
    for(int i = 0; i < coordinateStrings.size(); i++)
    {
      // Checks if input coordinate is in an appropriate form
      if (!Character.isLetter(coordinateStrings.get(i).charAt(0)))
        return false;

      actual_coor = hornersParser(coordinateStrings.get(i));

      // Checks if input coordinate is not out of chess board
      if (actual_coor[0] > boardSize || actual_coor[1] > boardSize)
        return false;

      // Converts two integer coordinates into string "num1xnum2"
      String coordinate = Integer.toString(actual_coor[0])
        + "x" + Integer.toString(actual_coor[1]);

      // Creates 8 maximum moves of a single knight
      String coordinate1 = Integer.toString(actual_coor[0] + 1)
        + "x" + Integer.toString(actual_coor[1] + 2);
      String coordinate2 = Integer.toString(actual_coor[0] + 2)
        + "x" + Integer.toString(actual_coor[1] + 1);
      String coordinate3 = Integer.toString(actual_coor[0] + 2)
        + "x" + Integer.toString(actual_coor[1] - 1);
      String coordinate4 = Integer.toString(actual_coor[0] + 1)
        + "x" + Integer.toString(actual_coor[1] - 2);
      String coordinate5 = Integer.toString(actual_coor[0] - 1)
        + "x" + Integer.toString(actual_coor[1] - 2);
      String coordinate6 = Integer.toString(actual_coor[0] - 2)
        + "x" + Integer.toString(actual_coor[1] - 1);
      String coordinate7 = Integer.toString(actual_coor[0] - 2)
        + "x" + Integer.toString(actual_coor[1] + 1);
      String coordinate8 = Integer.toString(actual_coor[0] - 1)
        + "x" + Integer.toString(actual_coor[1] + 2);

      // Checks if the position of a new knight is not occupied
      if (Knights.contains(coordinate))
        return false;

      // Adds new knight on the chess board
      Knights.add(coordinate);

      // Next 8 blocks of if statements check if a specific move exists and
      // check if an actual knight can attack other knights
      if (actual_coor[0] + 1 <= boardSize && actual_coor[0] + 1 > 0
      && actual_coor[1] + 2 <= boardSize && actual_coor[1] + 2 > 0)
      {
        if (Knights.contains(coordinate1))
          return false;

      }

      if (actual_coor[0] + 2 <= boardSize && actual_coor[0] + 2 > 0
      && actual_coor[1] + 1 <= boardSize && actual_coor[1] + 1 > 0)
      {
        if (Knights.contains(coordinate2))
          return false;

      }

      if (actual_coor[0] + 2 <= boardSize && actual_coor[0] + 2 > 0
      && actual_coor[1] - 1 <= boardSize && actual_coor[1] - 1 > 0)
      {
        if (Knights.contains(coordinate3))
          return false;

      }

      if (actual_coor[0] - 2 <= boardSize && actual_coor[0] - 2 > 0
      && actual_coor[1] + 1 <= boardSize && actual_coor[1] + 1 > 0)
      {
        if (Knights.contains(coordinate4))
          return false;

      }

      if (actual_coor[0] - 1 <= boardSize && actual_coor[0] - 1 > 0
      && actual_coor[1] - 2 <= boardSize && actual_coor[1] - 2 > 0)
      {
        if (Knights.contains(coordinate5))
          return false;

      }

      if (actual_coor[0] - 2 <= boardSize && actual_coor[0] - 2 > 0
      && actual_coor[1] - 1 <= boardSize && actual_coor[1] - 1 > 0)
      {
        if (Knights.contains(coordinate6))
          return false;

      }

      if (actual_coor[0] - 2 <= boardSize && actual_coor[0] - 2 > 0
      && actual_coor[1] + 1 <= boardSize && actual_coor[1] + 1 > 0)
      {
        if (Knights.contains(coordinate7))
          return false;

      }

      if (actual_coor[0] - 1 <= boardSize && actual_coor[0] - 2 > 0
      && actual_coor[1] + 2 <= boardSize && actual_coor[1] + 2 > 0)
      {
        if (Knights.contains(coordinate8))
          return false;

      }
    }
    return true;
  }

}
