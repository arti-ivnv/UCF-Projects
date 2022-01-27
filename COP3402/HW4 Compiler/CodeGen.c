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

int findPro(char *id, symbol * table);

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
int symidx, tidx, cidx, token, ifjmp, whilejmp, mainjmp;
int numVariables = 0;
int lexlvl = 0;

//for the cal operation
int numProc = 0;
int numJMP = 0;

int procM[5] = { };

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
    // // fprintf(outFile, "Line\tOP\tL\tM\n");
    for(int i = 0; i < cidx; i++)
    {
      //printf("line #: %d op: %d name: %s l: %d m: %d\n", i, code[i].op, opName[code[i].op - 1], code[i].l, code[i].m);
      printf("%d\t%s\t%d\t%d\n", i, opName[ code[i].op - 1 ], code[i].l, code[i].m);
      // fprintf(outFile, "%d\t%s\t%d\t%d\n", i, opName[ code[i].op - 1 ], code[i].l, code[i].m);
    }

    printf("\n\nTOKENS: \n");
    // fprintf(outFile, "\n\nTOKENS: \n");
    while(tokken[z].kind != 0)
    {
      printf("%d ", tokken[z].kind);
      // fprintf(outFile, "%d ", tokken[z].kind );
      z++;
    }
    printf("\n");
    // fprintf(outFile, "\n");
  }



  //return 0;
  return code;
}

void pr(symbol * table, scanner * tokken, instruction * code)
{
  while(token != periodsym){
    // printf("tokken name is %s and kind is: %d\n", tokken[tidx].id, tokken[tidx].kind);
    bl(table, tokken, code);
  }

  //emit the halt flag
  emit(sio_11, 0, 3, code);
  // printf("here?\n");
}

void bl(symbol * table, scanner * tokken, instruction * code)
{
  // printf("yes we are in block tidx = %d\n", tidx);
  int procjmp = 0;
  procjmp = tidx;
  table[tidx].addr = cidx;
  emit(jmp, 0, 0, code);
  numJMP++;
  // printf("numJMP = %d\n", numJMP);


  if(token == constsym)
  {
    //Moving past the consts since they are already in the sybol table
    //enter();
    while(token != semicolonsym)
    {
      //enter();
      token = getNextToken(tokken);
    }
    token = getNextToken(tokken);
  }
  if(token == varsym)
  {
    while(token != semicolonsym)
    {

      if(token == identsym){
        // printf("yes\n");
        numVariables++;
        //enter(1, token, lexlvl, table, tokken);
      }
      token = getNextToken(tokken);
    }
    token = getNextToken(tokken);
    // printf("tidx = %d , token = %d , token name is %s\n", tidx, token, tokken[tidx].id);
  }
  while(token == procsym){
    numProc++;
    // printf("token = %d ,", token);
    // printf("token id %d and token name: %s and the tidx is %d\n", tokken[tidx].kind, tokken[tidx].id, tidx);
    token = getNextToken(tokken);

    // printf("token = %d ,", token);
    // printf("token id %d and token name: %s and the tidx is %d\n", tokken[tidx].kind, tokken[tidx].id, tidx);

    if(token == semicolonsym)
      token = getNextToken(tokken);


    // int proc = findPro(tokken[tidx].id, table);
    // table[proc].mark = cidx;

    // printf("cur proc = %s and cidx = %d\n", tokken[tidx].id, cidx);
    int tmp = find(tokken[tidx].id, table);
    token = getNextToken(tokken);
    // printf("token = %d ,", token);
    // printf("token id %d and token name: %s and the tidx is %d\n", tokken[tidx].kind, tokken[tidx].id, tidx);

    token = getNextToken(tokken);
    // printf("token = %d ,", token);
    // printf("token id %d and token name: %s and the tidx is %d\n", tokken[tidx].kind, tokken[tidx].id, tidx);

    // lexlvl++;

    // printf("cur code idx = %d\n", cidx);
    table[tmp].addr = numJMP;

    bl(table + 1, tokken, code);
    // printf("cur code idx = %d\n", cidx);
    // printf("numProc = %d\n", numProc);

    procM[numProc] = cidx;
    // printf("procM[numProc] = %d\n",procM[numProc] );
    // table[tmp].addr = procM[numProc - 1];
    if(procM[numProc - 1])
    {
      table[tmp].addr = numJMP;
    }

      table[tmp].addr = procM[numProc];


    // calM = cidx;
    // printf("the cur lex lvl is %d\n", lexlvl);
    // lexlvl--;

    if(token == semicolonsym)
      token = getNextToken(tokken);

  }
  // printf("peepee\n");
  // token = getNextToken(tokken);
  fixAddrCode(table[procjmp].addr, code);
  // printf("cidx = %d\n", cidx);

  // printf("lol\n");

  table[procjmp].addr = cidx;

  // printf("wow\n");

  emit(inc, 0, 4 + numVariables, code);
  numVariables = 0;
  st(table, tokken, code);
  emit(opr, 0, 0, code);
  // printf("token = %d ,", token);

  // printf("token id %d and token name: %s and the tidx is %d\n", tokken[tidx].kind, tokken[tidx].id, tidx);

  // printf("end\n");
}


void st(symbol * table, scanner * tokken, instruction * code)
{
  // printf("token = %d ,", token);
  // printf("token id %d and token name: %s and the tidx is %d\n", tokken[tidx].kind, tokken[tidx].id, tidx);
  if(token == identsym)
  {
    // printf("yes identsym\n");
    // printf("token = %d ,", token);
    // printf("token id %d and token name: %s and the tidx is %d\n", tokken[tidx].kind, tokken[tidx].id, tidx);
    symidx = find(tokken[tidx].id, table);
    // printf("peepee\n");
    token = getNextToken(tokken);
    token = getNextToken(tokken);
    // printf("yes before ex()\n");
    ex(table, tokken, code);

    emit(sto, lexlvl - table[symidx].level, table[symidx].addr, code);
  }
  if(token == callsym){
    // printf("we are in call now!!!\n");
    token = getNextToken(tokken);
    // printf("token name = %s\n", tokken[tidx].id);
    // printf("cidx = %d\n", cidx);
    //Find the entry for procedure unmarked and closest in lexlevel
    symidx = find(tokken[tidx].id, table);
    // emit(cal, lexlvl - table[symidx].level, table[symidx].addr, code);//m = procedure's m from the symbol table
    // emit(cal, table[symidx].level, table[symidx].addr, code);
    // printf("-------[# %d]-----\n", symidx);
		// printf("Kind: %d \n", table[symidx].kind);
		// printf("Name: %s \n", table[symidx].name);
		// printf("Val: %d \n", table[symidx].val);
		// printf("Level: %d \n", table[symidx].level);
		// printf("Addr: %d \n", table[symidx].addr);
		// printf("Mark: %d \n", table[symidx].mark);
		// printf("---------------\n");
		// printf("\n");


    emit(cal, 0, table[symidx].addr, code);
    //emit(cal, 0, calM, code);
    token = getNextToken(tokken);//might be bad
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
    if(token == elsesym){
      fixAddrCode(ifjmp, code);
      token = getNextToken(tokken);
      int elsejmp = cidx;
      emit(jmp, 0, 0, code);
      st(table, tokken, code);
      fixAddrCode(elsejmp, code);
    }
    else{
      fixAddrCode(ifjmp, code);
    }
    // fixAddrCode(ifjmp, code);
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
      // printf();
      // printf("lexlvl - table[tmp].level = %d\n", lexlvl - table[tmp].level);
      int test = 0;
      test = lexlvl - table[tmp].level;
      // printf("test = %d\n", test);
      // emit(lod, lexlvl - table[tmp].level, table[tmp].addr, code);
      emit(lod, test, table[tmp].addr, code);
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
    while(token == plussym || token == minussym){
      if(token == plussym){
        token = getNextToken(tokken);
        tm(table, tokken, code);
        emit(opr, 0, 2, code);
      }
      if(token == minussym){
        token = getNextToken(tokken);
        tm(table, tokken, code);
        emit(opr, 0, 3, code);
      }
    }
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
        // emit(lod, table[tmp].level, table[tmp].addr, code);
        emit(lod, lexlvl - table[tmp].level, table[tmp].addr, code);

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

int findPro(char *id, symbol * table){
  int pos = 0;
  int i = 0;
  while(1){
    if(table[i].kind == 3){
      if(strcmp(id, table[i].name) == 0)
        pos = i;
    }
    i++;
  }
  return pos;
}

//Returns the position off a symbol in the symbol table, or 0 if not found
int find(char *id, symbol * table)
{
  int i = 500;
  /*
  while(1)
  {
    // if( strcmp(id, table[i].name) == 0 )
    //   return i;
      }
    }
    i++;
  }
*/

  int pos = 0;
  while(i != 0){
  if(strcmp(id, table[i].name) == 0){
    if(table[i].level <= lexlvl){
      pos = i;
      break;
    }
  }
  i--;
  }
  return pos;
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
