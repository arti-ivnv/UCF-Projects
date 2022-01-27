// Artem Ivanov
// Daniel Couch

// Scaner should transfer the token list to Parser.
// Scanner --> Parser


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Scanner.h"

// Defining max length of identifier and number.
#define LENGTH_ID 11
#define LENGTH_NUM 5

typedef enum
{
  nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
  multsym = 6, slashsym = 7, oddsym = 8, eqlsym = 9, neqsym = 10, lessym = 11,
  leqsym = 12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16,
  commasym = 17, semicolonsym = 18, periodsym = 19, becomessym = 20, beginsym = 21,
  endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26,
  constsym = 28, varsym = 29, writesym = 31, readsym = 32
} token_type;


// Functuion checks if our possible tokken is a reserved word.
int isReserved (scanner tokken[], char **word, int rw_num[], int z)
{
  int i = 0;
  int check;

  // Checker for appropriate format of the variable.
  if(!isalpha(tokken[z].id[0]))
  {
    return 0;
  }

  // Loop all the reserved words and compaatring the input string to identify if
  // it is a reserved word.
  for (i = 0; i < 12; i++)
  {
    check = strcmp(tokken[z].id, word[i]);
    if (check == 0)
    {
      // Returns tokken number if it is a reserved word.
      return rw_num[i];
    }
  }

  return 0;
}

// Checks if current stiring has a proper format of identifier.
// Length checked before entering this function.
int isIdentidier(scanner tokken[], int z)
{
  if (!isalpha(tokken[z].id[0]))
  {
    return 0;
  }

  return 1;
}

// Checks if our string has a proper number format.
// Length checked before entering this function.
int isDigit(scanner tokken[], int z)
{
  if (!isdigit(tokken[z].id[0]))
  {
    return 0;
  }
  return 1;
}

scanner *lex(char *inputfile, int lFlag)
{
  int comments = 0;
  char c;
  int i = 0, z = 0, j = 0;
  int flag = 0;
  scanner tokken[500];
  scanner *tokken_list = malloc(500 * sizeof(scanner));

  FILE *inFile = NULL;

  if ((inFile = fopen(inputfile, "r")) == NULL)
  {
    printf("Error:There is no %s in the folder\n", inputfile);
    exit (0);
  }


  // List of reserved words
  // Took out: "call", "procedure" "else"
  // Added: "begin", "end"
  char *word[] = {"const", "var", "if", "then", "while", "do", "read", "write", "odd", "null", "begin", "end"};

  char tokenNames[][15] = {
    "", "nulsym", "identsym", "numbersym", "plussym", "minussym",
    "multsym", "slashsym", "oddsym", "eqlsym", "neqsym", "lessym",
    "leqsym", "gtrsym", "geqsym", "lparentsym", "rparentsym",
    "commasym", "semicolonsym", "periodsym", "becomessym", "beginsym",
    "endsym", "ifsym", "thensym", "whilesym", "dosym",
    "", "constsym", "varsym", "", "writesym",
    "readsym"
  };

  // Numirical representation of the reserved words
  // Took out: elsesym, callsym, procsym,
  int rw_num[] = {constsym, varsym, ifsym, thensym, whilesym, dosym,
                  readsym, writesym, oddsym, nulsym, beginsym, endsym};

  // Turns each piece of the code into tokens
  while (!feof(inFile))
  {
    c = getc(inFile);
    // If the program finds a comment identifier then we ignore until the
    // End comment identifier is found.
    if (comments == 1)
    {
      // Case where the end comment identifier is found
      if (c == '*' && getc(inFile) == '/')
      {
        z--;
        comments = 0;
        continue;
      }
      // Case where the end comment identifier is NOT found
      // Ignore char.
      else
      {
        getc(inFile);
        continue;
      }
    }
    // Checks fot a wrong spelling of variable.
    if (isdigit(tokken[z].id[0]) && isalpha(c))
    {
      perror("Error: Incorrect format of input number cannot be the first character of reserved word or variable name.");
      exit(0);
    }

    // Works with identidiers and reserved words.
    // Puts characters into the tokken struct.
    if (isalpha(c) || (isdigit(c) && (isalpha(tokken[z].id[0]))))
    {
      tokken[z].id[i] = c;
      i++;

      // Check if our identfier or a reserved word has an acceptable length.
      if (i > LENGTH_ID)
      {
        perror("Error: Your identifier is too long (Should be no longer than 11)");
        exit(0);
      }
    }

    // Works with numbers only.
    // Puts characters into the tokken struct.
    if (isdigit(c) && (!isalpha(tokken[z].id[0])))
    {

      tokken[z].id[i] = c;
      i++;

      // Check if our number has an acceptable length.
      if (i > LENGTH_NUM)
      {
        perror("Error: One of your numbers is too big (Max 5 digits)");
        exit(0);
      }
    }


    // If we hit a space, tab, new line, or any symbol.
    if (isspace(c) || ispunct(c))
    {
     // If it is a symbol we are going here.
     if(isspace(c))
     {
       // Initializing our flag to 0 if space. (< >) != (<>)
       flag = 0;

       // Checks if our input string is a reserved word if so, initializing its
       // tokken to the tokken[].kind of current string
       if (isReserved(tokken, word, rw_num, z) != 0)
       {
         tokken[z].kind = isReserved(tokken, word, rw_num, z);
         z++;
         i = 0;
         continue;
       }
       // Checks if our input string is an identidier if so, initializing identsym
       // to the tokken[].kind of current string
       if (!isReserved(tokken, word, rw_num, z) && isIdentidier(tokken, z))
       {
         tokken[z].kind = identsym;
         z++;
         i = 0;
         continue;
       }
       // Checks if our input string is a number if so, initializing numbersym
       // to the tokken[].kind of current string
       if (isDigit(tokken, z))
       {
         tokken[z].kind = numbersym;
         z++;
         i = 0;
         continue;
       }
     }
     // We are going here if we hit any symbol
     if(ispunct(c))
     {
       // Checks if our input string is a reserved word if so, initializing its
       // tokken to the tokken[].kind of current string
       if (isReserved(tokken, word, rw_num, z) != 0)
       {
         tokken[z].kind = isReserved(tokken, word, rw_num, z);
         z++;
         i = 0;
       }
       // Checks if our input string is an identidier if so, initializing identsym
       // to the tokken[].kind of current string
       if (!isReserved(tokken, word, rw_num, z) && isIdentidier(tokken, z))
       {
         tokken[z].kind = identsym;
         z++;
         i = 0;
       }
       // Checks if our input string is a number if so, initializing numbersym
       // to the tokken[].kind of current string
       if (isDigit(tokken, z))
       {
         tokken[z].kind = numbersym;
         z++;
         i = 0;
       }

       // Case for tokenizing special symbols and operations
       switch (c)
     	 {

        // Case for the plus symbol
     		case '+':
     			tokken[z].id[0] = c;
     			tokken[z].kind = plussym;
          z++;
     			break;
        // Case for the minus symbol
     		case '-':
     			tokken[z].id[0] = c;
     			tokken[z].kind = minussym;
          z++;
     			break;
        //Case for the multiplication symbol
     		case '*':
          // Checks the previous symbol is '/', so if have to turn on comments.
          if (tokken[z-1].id[0] == '/')
          {
            comments = 1;
            break;
          }
          // If the comment identfier is not found then its multiplication
          else
          {
          tokken[z].id[0] = c;
     			tokken[z].kind = multsym;
          z++;
          break;
          }
        // Case for the left parentesis symbol
     		case '(':
     			tokken[z].id[0] = c;
     			tokken[z].kind = lparentsym;
          z++;
     			break;
        // Case for the right parentesis symbol
     		case ')':
     			tokken[z].id[0] = c;
     			tokken[z].kind = rparentsym;
          z++;
     			break;
        // Case for comma symbol
     		case ',':
     			tokken[z].id[0] = c;
     			tokken[z].kind = commasym;
          z++;
     			break;
        // Case for the equal symbol
     		case '=':
          // If previously we have not used '<' or '>' then flag is 0 and it is
          // an equal symbol
          if (flag == 0)
          {
       			tokken[z].id[0] = c;
       			tokken[z].kind = eqlsym;
            z++;
       			break;
          }
          // Checks to see if previously we turned on flag to 1 then it is a
          // less or equal symbol
          else if (flag == 1)
          {
            z--;
            tokken[z].id[0] = '<';
            tokken[z].id[1] = c;
       			tokken[z].kind = leqsym;
            z++;
            flag = 0;
       			break;
          }
          // Checks to see if previously we turned on flag to 2 then it is a
          // greater or equal symbol
          else if (flag == 2)
          {
            z--;
            tokken[z].id[0] = '>';
            tokken[z].id[1] = c;
       			tokken[z].kind = geqsym;
            z++;
            flag = 0;
       			break;
          }
        // Case for the period symbol
     		case '.':
     			tokken[z].id[0] = c;
     			tokken[z].kind = periodsym;
          z++;
     			break;
        // Case for less than symbol also flags the program for the equals case
        // and for the <> case. Initialize flag to 1 when used first time.
     		case '<':
     			tokken[z].id[0] = c;
     			tokken[z].kind = lessym;
          z++;
          flag = 1;
     			break;
        // Case for Greater than symbol also flages the program
        // for the equals case.
     		case '>':
          // Use as regular greater symbol if flag is 0
          if(flag == 0)
          {
            tokken[z].id[0] = c;
       			tokken[z].kind = gtrsym;
            z++;
            flag = 2;
       			break;
          }
          // Checks to see the id before to see if its <> to make the
          // symbol not equal to
          else
          {
            z--;
            tokken[z].id[0] = '<';
            tokken[z].id[1] = c;
       			tokken[z].kind = neqsym;
            z++;
            flag = 0;
       			break;
          }
        // Case for the semi colon
     		case ';':
     			tokken[z].id[0] = c;
     			tokken[z].kind = semicolonsym;
          z++;
     			break;
        // Case for the becomes and checks to see if its followed by '='
        // If not throws an error
     		case ':':
          if(getc(inFile) == '=')
          {
            tokken[z].id[0] = c;
            tokken[z].id[1] = '=';
     			  tokken[z].kind = becomessym;
            ungetc(' ', inFile);
            z++;
          }
          else
          {
            perror("(Error: You cannot use : without = ");
            exit(0);
          }

     			break;
        // Case for the slash symbol
     		case '/':
     			tokken[z].id[0] = c;
     			tokken[z].kind = slashsym;
          z++;
     			break;
     		default:
          perror("Error: Unreadable symbol");
     			exit(0);
   	    }

     }
    }
  }

  if (lFlag == 1)
  {
    printf("\n\nLexeme Table:\nlexeme\t\ttoken type\n");

  // Loops thorugh the tokken array and prints the identfier and the token_type
    while(tokken[j].kind != 0)
    {
      printf("%s\t\t%d\n", tokken[j].id, tokken[j].kind);
      j++;
    }
  // Formatting for the Lemexe List
    printf("\n\nLexeme List:\n");

    for(int k = 0; tokken[k].kind != 0; k++)
    {
      // If identsym then we need to print the vaiable name as well
      if(tokken[k].kind == 2)
      {
        printf("%d %s ", tokken[k].kind, tokken[k].id);
      }
      else if(tokken[k].kind == 3)
      {
        printf("%d %s ", tokken[k].kind, tokken[k].id);
      }
      // Else just print the token_type
      else
      {
        printf("%d ", tokken[k].kind);
      }
    }

    printf("\n");
    printf("\n");
  }
  fclose(inFile);
  // fclose(outFile);

  for(int z = 0; tokken[z].kind != 0; z++)
  {
    tokken_list[z] = tokken[z];
  }


  return tokken_list;
}
