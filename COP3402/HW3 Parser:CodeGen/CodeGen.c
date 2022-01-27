// Daniel Couch
// Artem Ivanov
// COP 3402

// Let's say we have a token list and a symbol table
// then our pr will generate the code without vars and consts
// but we still need them to procede the stack procces.
// CodeGen generates an assemly code that will be transfered to the VM.
// CodeGen --> VM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Scanner.h"
#include "Parser.h"
#include "CodeGen.h"

void emit(int op, int l, int m, instruction * code);
int find(char *id, symbol * table);
void ex(symbol * table, scanner * token, instruction * code);
int getNextToken(scanner * tokken);
void fixAddrCode(int index, instruction * code);


void pr(symbol * table, scanner * tokken, instruction * code);
void bl(symbol * table, scanner * tokken, instruction * code);
void st(symbol * table, scanner * tokken, instruction * code);
void cn(symbol * table, scanner * tokken, instruction * code);
void ex(symbol * table, scanner * tokken, instruction * code);
void tm(symbol * table, scanner * tokken, instruction * code);
void fr(symbol * table, scanner * tokken, instruction * code);

//Global Variables
int symidx, tidx, cidx, token, ifjmp, whilejmp;
int numVariables = 0;

//extern
instruction code[500];

//int main()
instruction * genCode(int vFlag, scanner *tokken, symbol *table)
{
  int z = 0;

  token = tokken[0].kind;

  pr(table, tokken, code);

  char *opName[] = {"lit", "opr", "lod", "sto", "cal", "inc", "jmp", "jpc", "sio", "sio", "sio"};

  //printf("tokken[56].kind = %d and cidx = %d\n", tokken[56].kind, cidx);
  if(vFlag)
  {
    printf("Line\tOP\tL\tM\n");
    for(int i = 0; i < cidx; i++)
    {
      //printf("line #: %d op: %d name: %s l: %d m: %d\n", i, code[i].op, opName[code[i].op - 1], code[i].l, code[i].m);
      printf("%d\t%s\t%d\t%d\n", i, opName[ code[i].op - 1 ], code[i].l, code[i].m);
    }

    printf("TOKENS: \n");
    while(tokken[z].kind != 0)
    {
      printf("%d ", tokken[z].kind);
      z++;
    }
    printf("\n");
  }



  //return 0;
  return code;
}

void pr(symbol * table, scanner * tokken, instruction * code)
{
  while(token != periodsym)
    bl(table, tokken, code);
  //emit the halt flag
  emit(sio_11, 0, 3, code);
}

void bl(symbol * table, scanner * tokken, instruction * code)
{
  if(token == constsym)
  {
    //Moving past the consts since they are already in the sybol table
    while(token != semicolonsym)
    {
      token = getNextToken(tokken);
    }
    token = getNextToken(tokken);
  }
  if(token == varsym)
  {
    while(token != semicolonsym)
    {

      if(token == identsym)
        numVariables++;
      token = getNextToken(tokken);
    }
  }
  token = getNextToken(tokken);
  emit(inc, 0, 4 + numVariables, code);
  st(table, tokken, code);
}


void st(symbol * table, scanner * tokken, instruction * code)
{
  if(token == identsym)
  {
    symidx = find(tokken[tidx].id, table);
    token = getNextToken(tokken);
    token = getNextToken(tokken);
    //token = getNextToken(tokken);
    ex(table, tokken, code);

    emit(sto, table[symidx].level, table[symidx].addr, code);
  }
  if(token == beginsym)
  {
    token = getNextToken(tokken);
    st(table, tokken, code);
    //Might be probalamtic
    while(token == semicolonsym)
    {
      token = getNextToken(tokken);
      st(table, tokken, code);
    }
    token = getNextToken(tokken);
  }
  if(token == ifsym)
  {
    token = getNextToken(tokken);
    cn(table, tokken, code);
    if(token == thensym)
    {
      token = getNextToken(tokken);
    }
    //Save the code index(this is the ifjmp you need to edit)
    ifjmp = cidx;
    emit(jpc, 0, 0, code);
    st(table, tokken, code);
    fixAddrCode(ifjmp, code);
  }
  if(token == whilesym)
  {
    token = getNextToken(tokken);
    //save the cidx (this will be used for the whilejmp)
    whilejmp = cidx;
    cn(table, tokken, code);
    token = getNextToken(tokken);
    //save the code index (this is the jump you need to edit)
    int cx = cidx;
    emit(jpc, 0, 0, code);//tmp line of code to be editted later
    if(token == dosym)
    {
      token = getNextToken(tokken);
    }
    st(table, tokken, code);
    //fix the jmp code from before w/ the first cidx saved

    //fix the jpc at the 2nd code idx using the current cidx
    emit(jmp, 0, whilejmp, code);
    fixAddrCode(cx, code);
  }
  if(token == readsym)
  {
    token = getNextToken(tokken);
    int tmp = find(tokken[tidx].id, table);
    token = getNextToken(tokken);
    emit(sio_10, 0, 2, code);

    //use struff from the symbol table
    emit(sto, table[tmp].level, table[tmp].addr, code);
  }
  if(token == writesym)
  {
    token = getNextToken(tokken);
    int tmp = find(tokken[tidx].id, table);
    // printf("Write sym");
    //Constant
    if(table[tmp].kind == 1)
    {
      emit(lit, 0, table[tmp].val, code);
    }
    //Variable
    if(table[tmp].kind == 2)
    {
      emit(lod, table[tmp].level, table[tmp].addr, code);
    }
    token = getNextToken(tokken);
    emit(sio_9, 0, 1, code);
  }
}

void cn(symbol * table, scanner * tokken, instruction * code)
{
  if(token == oddsym)
  {
    token = getNextToken(tokken);
    ex(table, tokken, code);
    //Emiting odd
    emit(opr, 0, 6, code);
  }
  else
  {
    ex(table, tokken, code);
    int tmp = token;
    token = getNextToken(tokken);
    ex(table, tokken, code);
    switch(tmp)
    {
      case eqlsym:
        emit(2, 0, 8, code);
        break;
      case neqsym:
        emit(2, 0, 9, code);
        break;
      case lessym:
        emit(2, 0, 10, code);
        break;
      case leqsym:
        emit(2, 0, 11, code);
        break;
      case gtrsym:
        emit(2, 0, 12, code);
        break;
      case geqsym:
        emit(2, 0, 13, code);
        break;
    }
  }
}

void ex(symbol * table, scanner * tokken, instruction * code)
{
  if(token == plussym)
  {
    token = getNextToken(tokken);
  }
  else if(token == minussym)
  {
    token = getNextToken(tokken);
    tm(table, tokken, code);
    emit(opr, 0, 1, code);
  }

  tm(table, tokken, code);
  while(token == plussym || token == minussym)
  {
    if(token == plussym)
    {
      token = getNextToken(tokken);
      tm(table, tokken, code);
      //Emmitting addition
      emit(opr, 0, 2, code);
    }
    else if(token == minussym)
    {
      token = getNextToken(tokken);
      tm(table, tokken, code);
      //Emiting subtraction
      emit(opr, 0, 3, code);
    }
  }
}


void tm(symbol * table, scanner * tokken, instruction * code)
{
  fr(table, tokken, code);
  while(token == multsym || token == slashsym)
  {
    if(token == multsym)
    {
      token = getNextToken(tokken);
      fr(table, tokken, code);
      //Emmiting multiplication
      emit(opr, 0, 4, code);
    }
    else if(token == slashsym)
    {
      token = getNextToken(tokken);
      fr(table, tokken, code);
      //Emmiting Division
      emit(opr, 0, 5, code);
    }
  }
}



void fr(symbol * table, scanner * tokken, instruction * code)
{
    if(token == identsym)
    {
      int tmp = find(tokken[tidx].id, table);
      token = getNextToken(tokken);
      //Constant
      if( table[tmp].kind == 1 )
      {
        emit(lit, 0, table[tmp].val, code);
      }
      //Variable
      else if( table[tmp].kind == 2 )
      {
        emit(lod, table[tmp].level, table[tmp].addr, code);
      }
    }
    else if(token == numbersym)
    {
      emit(lit, 0, atoi(tokken[tidx].id),code);
      token = getNextToken(tokken);
    }
    else
    {
      token = getNextToken(tokken);
      ex(table, tokken, code);
      token = getNextToken(tokken);
    }
}

//cx is the current position in the code
//Emits the proper
void emit(int op, int l, int m, instruction * code)
{
  code[cidx].op = op;
  code[cidx].l = l;
  code[cidx].m = m;
  cidx++;
}

//Returns the position off a symbol in the symbol table, or 0 if not found
int find(char *id, symbol * table)
{
  int i = 0;
  while(1)
  {
    if( strcmp(id, table[i].name) == 0 )
      return i;
    i++;
  }
}

//Gets ther next token in the symbol table
int getNextToken(scanner * tokken)
{
  tidx++;
  return tokken[tidx].kind;
}

//This function is for the if st and while st to fix the M value
//and make it point to the correct addr
void fixAddrCode(int index, instruction * code)
{
  code[index].m = cidx;
}
