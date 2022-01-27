// Artem Ivanov
// Daniel Couch
// COP 3402

#ifndef __CODEGEN_H
#define __CODEGEN_H

#include "Scanner.h"
#include "Parser.h"

#define MAX_DATA_STACK_HEIGHT 1000
#define MAX_CODE_LENGTH 500

typedef struct
{
  int op, l, m; // < OP code, Lexicographical Level, M>
  /*
        M could mean:
      - A number
      - A program Address
      - A data address
      - The identity of the operator OPR
  */
}instruction;


typedef enum
{
  nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
  multsym = 6, slashsym = 7, oddsym = 8, eqlsym = 9, neqsym = 10, lessym = 11,
  leqsym = 12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16,
  commasym = 17, semicolonsym = 18, periodsym = 19, becomessym = 20, beginsym = 21,
  endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26,
  callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31,
  readsym = 32, elsesym = 33
} token_type;

typedef enum {
  lit = 1, opr = 2 , lod = 3, sto = 4, cal = 5,
  inc = 6, jmp = 7, jpc = 8, sio_9 = 9, sio_10 = 10,
  sio_11 = 11
} op_name;

extern instruction code[500];


//instruction * generate_code(symbol * table, scanner * token);
instruction * genCode(int vFlag, scanner *tokken, symbol *table);


#endif
