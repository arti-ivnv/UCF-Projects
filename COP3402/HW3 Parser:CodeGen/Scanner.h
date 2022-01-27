// Artem Ivanov
// Daniel Couch
// COP 3402

#ifndef __SCANNER_H
#define __SCANNER_H


#define LENGTH_ID 11

typedef struct
{
  int kind;
  char id[LENGTH_ID];
  int index;
} scanner;

scanner *lex(char *inputfile, int lFlag);

#endif
