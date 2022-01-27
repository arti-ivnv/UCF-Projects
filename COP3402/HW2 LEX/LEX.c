// Artem Ivanov
// Daniel Couch
// COP 3402
// HW 2 LEX

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Defining max length of identifier and number.
#define LENGTH_ID 11
#define LENGTH_NUM 5

typedef enum
{
  nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
  multsym = 6, slashsym = 7, oddsym = 8, eqlsym = 9, neqsym = 10, lessym = 11,
  leqsym = 12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16,
  commasym = 17, semicolonsym = 18, periodsym = 19, becomessym = 20, lbracesym = 21,
  rbracesym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26,
  callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31,
  readsym = 32, elsesym = 33
} token_type;

// Structure that helps us to manage tokkens.
typedef struct
{
  int kind;
  char id[LENGTH_ID];
} thing;

// Functuion checks if our possible tokken is a reserved word.
int isReserved (thing tokken[], char **word, int rw_num[], int z)
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
int isIdentidier(thing tokken[], int z)
{
  if (!isalpha(tokken[z].id[0]))
  {
    return 0;
  }

  return 1;
}

// Checks if our string has a proper number format.
// Length checked before entering this function.
int isDigit(thing tokken[], int z)
{
  if (!isdigit(tokken[z].id[0]))
  {
    return 0;
  }
  return 1;
}

int main (int argc, char **argv)
{
  int comments = 0;
  char c;
  int i = 0, z = 0, j = 0;
  int flag = 0;
  thing tokken[500];

  char *inName = argv[1];
  char *outName = argv[2];


  FILE *inFile = fopen(inName, "r");
  FILE *format = fopen(inName, "r");
  FILE *outFile = fopen(outName, "w");

  // List of reserved words
  char *word[] = {"const", "var", "procedure", "call", "if", "then", "else", "while", "do", "read", "write", "odd", "null"};

  // Numirical representation of the reserved words
  int rw_num[] = {constsym, varsym, procsym, callsym, ifsym, thensym, elsesym,
                  whilesym, dosym, readsym, writesym, oddsym, nulsym};

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
      perror("Incorrect format of input number cannot be the first character of reserved word or variable name.");
      fprintf(outFile, "Incorrect format of input number cannot be the first character of reserved word or variable name.\n");
      return(-1);
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
        perror("Your identifier is too long (Should be no longer than 11)");
        fprintf(outFile, "Your identifier is too long (Should be no longer than 11)\n");
        return(-1);
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
        perror("One of your numbers is too big (Max 5 digits)");
        fprintf(outFile, "One of your numbers is too big (Max 5 digits)\n");
        return(-1);
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
         // Case for the Left Brace symbol
     		case '{':
     			tokken[z].id[0] = c;
     			tokken[z].kind = lbracesym;
          z++;
     			break;
        // Case for Right Brace symbol
     		case '}':
     			tokken[z].id[0] = c;
     			tokken[z].kind = rbracesym;
          z++;
     			break;
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
            fprintf(outFile, "You cannot use : without =\n");
            perror("You cannot use : without =");
            return (-1);
          }

     			break;
        // Case for the slash symbol
     		case '/':
     			tokken[z].id[0] = c;
     			tokken[z].kind = slashsym;
          z++;
     			break;
     		default:
     			fprintf(outFile, "Unreadable symbol: %c\n", c);
          perror("Unreadable symbol");
     			exit(0);
   	    }

     }
    }
  }

  // Formatting for the first part of the output
  fprintf(outFile, "Source Program:\n");
  char o = getc(format);
  while(o!=EOF)
  {
    fprintf(outFile, "%c", o);
    o = getc(format);
  }

  // Formatting the output for the Lexeme Table
  fprintf(outFile, "\n\nLexeme Table:\nlexeme\t\ttoken type\n");

  // Loops thorugh the tokken array and prints the identfier and the token_type
  while(tokken[j].kind != 0)
  {
    fprintf(outFile, "%s\t\t%d\n", tokken[j].id, tokken[j].kind);
    j++;
  }

  // Formatting for the Lemexe List
  fprintf(outFile, "\n\nLexeme List:\n");

  for(int k = 0; tokken[k].kind != 0; k++){
    // If identsym then we need to print the vaiable name as well
    if(tokken[k].kind == 2)
      fprintf(outFile, "%d %s ", tokken[k].kind, tokken[k].id);
    // Else just print the token_type
    else
      fprintf(outFile, "%d ", tokken[k].kind);
  }


  fclose(inFile);
  fclose(format);
  fclose(outFile);


  return 0;
}
