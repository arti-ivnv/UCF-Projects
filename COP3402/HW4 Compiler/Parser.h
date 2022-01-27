// Artem Ivanov
// Daniel Couch
// COP 3402

#ifndef __PARSER_H
#define __PARSER_H

#include "Scanner.h"

// We can assume L is 0. Since we have only one AR
typedef struct
{
	int kind; 				// const = 1, var = 2, procedure = 3
	char name[10]; 		// name up to 11
	int val; 					// number assigned to the identifier
	int level; 				// L level
	int addr;					// M address
	int mark;					// to indicate unavailable or delete variable
} symbol;

symbol *parser(scanner *sweetyTokens, int vFlag, int lFlag, int aFlag);

#endif
