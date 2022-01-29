// Artem Ivanov
// COP 3503
// Fall 2019

import java.io.*;
import java.util.*;
import java.lang.*;

public class SneakyQueens
{

  // Converts from a single string coordinate to two digital coordinates
  // Order (k + k) convertor which is Order (k) in overall
  public static int[] convertor(String someCoor)
  {
    int x = 0;
    int y = 0;
    int lit = 0;
    int num = 0;
    int coor[] = new int[2];

    for (int k = 0; k < someCoor.length(); k++)
    {
      if (Character.isLetter(someCoor.charAt(k)))
      {
        lit++;
      }
      else
      {
        num++;
      }
    }

    num = num - 1;
    lit = lit - 1;

    for (int k = 0; k < someCoor.length(); k++)
    {
      Character h = someCoor.charAt(k);

      if (Character.isLetter(someCoor.charAt(k)))
      {
        x += (int)((someCoor.charAt(k) - 96) * Math.pow(26, lit));
        lit--;
      }
      else
      {
        y += (int)((someCoor.charAt(k) - 48) * Math.pow(10, num));
        num--;
      }
    }

    coor[0] = x;
    coor[1] = y;

    return coor;
  }

  // Checking the row or columns coordinates are unique. O(n) operation.
  public static boolean board_check(ArrayList<Integer> digit_coor, int boardSize)
  {
    int board[] = new int[boardSize+1];

    for (int m = 0; m < digit_coor.size(); m++)
    {
      board[digit_coor.get(m)] += 1;

      if (board[digit_coor.get(m)] > 1)
      {
        return false;
      }
    }
    return true;
  }

  // Checking the diagonals coordinates. Workking wrong in some test cases.
  public static boolean board_check_diag(ArrayList<Integer> digit_coor_x,
  ArrayList<Integer> digit_coor_y, int boardSize)
  {
    int board_c_X[] = new int[boardSize+1];
    int board_c_Y[] = new int[boardSize+1];
    int board_c_dia_1[] = new int[boardSize+1];
    int board_c_dia_2[] = new int[boardSize+1];

    if (digit_coor_x.size() == boardSize)
    {
      return true;
    }

    for (int m = 0; m < digit_coor_x.size(); m++)
    {
      board_c_X[digit_coor_x.get(m)]+=digit_coor_x.size();
      board_c_Y[digit_coor_y.get(m)]+=digit_coor_x.size();
    }

    // Seaerching for all duplicates
    int sym = 0;
    for (int m = 1; m < boardSize + 1; m++)
    {
      if ((board_c_X[m] == board_c_Y[m]) && (board_c_X[m] != 0))
      {
        sym++;
      }
      if (sym > 1)
      {
        return false;
      }

      if ((board_c_X[m] == board_c_Y[m+1]) && (board_c_X[m+1] == board_c_Y[m]))
      {
        return false;
      }
    }
    return true;
  }

  // Driver function that orients the operations.
  public static boolean allTheQueensAreSafe(ArrayList<String> list, int boardSize)
  {
    ArrayList<Integer> digit_coor_x = new ArrayList<Integer>();
    ArrayList<Integer> digit_coor_y = new ArrayList<Integer>();

    int temp[] = new int[2];

    // Converting n strings of length m to two numirical coordinates ArrayLists.
    //O(nm) runtime
    for (int n = 0; n < list.size(); n++)
    {
      temp = convertor(list.get(n));

      digit_coor_x.add(temp[0]);
      digit_coor_y.add(temp[1]);
    }

    // Both of those checkers got runtime of O(n) but they work in linear way.
    boolean check_x = board_check(digit_coor_x, boardSize);
    boolean check_y = board_check(digit_coor_y, boardSize);

    if (!check_x || !check_y)
    {
      return false;
    }

    // Checks diagonal intersections. Works wrong in some cases. O(n) operation.
    boolean check_diag = board_check_diag(digit_coor_x, digit_coor_y, boardSize);

    if (!check_diag)
    {
      return false;
    }
    return true;
  }
}
