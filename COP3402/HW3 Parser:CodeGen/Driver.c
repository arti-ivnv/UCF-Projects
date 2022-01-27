// Artem Ivanov
// Daniel Couch
// COP 3402

#include <stdio.h>
#include <stdlib.h>
#include "Scanner.h"
#include "Parser.h"
#include "CodeGen.h"
#include "VM.h"

int main (int argc, char **argv)
{

	if(argc < 2)
	{
		printf("Error: Please include the input file name\n");
		exit(0);
	}

	int aFlag = 0, vFlag = 0, lFlag = 0;

	if(argc == 2)
	{
		printf("in:\n");
		printf("\n\nout:\n\n\n");
	}
	else
	{
		for(int i = 2; i < argc; i++)
		{
			//Print assemly code or not
			if(argv[i][1] == 'a')
				aFlag = 1;
			//Print lexemes and tokens or not
			else if(argv[i][1] == 'l')
				lFlag = 1;
			//Print virtual machine trace or not
			else if(argv[i][1] == 'v')
				vFlag = 1;
		}
		// printf("aFlag = %d, vFlag = %d, lFlag = %d\n", aFlag, vFlag, lFlag);
	}


	scanner *sweetyTokens = lex(argv[1], lFlag);
	symbol *table = parser(sweetyTokens, vFlag, lFlag, aFlag);
	instruction  * code = genCode(aFlag, sweetyTokens, table);
	virtual_machine(code, vFlag);

		// Symbol table out
	// for (int i = 0; i < 8; i++)
	// {
	// 	printf("-------[# %d]-----\n", i);
	// 	printf("Kind: %d \n", table[i].kind);
	// 	printf("Name: %s \n", table[i].name);
	// 	printf("Val: %d \n", table[i].val);
	// 	printf("Level: %d \n", table[i].level);
	// 	printf("Addr: %d \n", table[i].addr);
	// 	printf("Mark: %d \n", table[i].mark);
	// 	printf("---------------\n");
	// 	printf("\n");
	// }
		// instruction *code = generate_code(table, list);
		// virtual_machine(code);



		return 0;
}
