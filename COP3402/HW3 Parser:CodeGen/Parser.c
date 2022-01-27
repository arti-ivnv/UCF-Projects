// Artem Ivanov
// Daniel Couch
// COP 3402


// Parser should check the grammar. And either send a valid token list and symbol table to the CodeGen either throw an error.
// Parser --> CodeGen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Scanner.h"
#include "Parser.h"

#define MAX_SYMBOL_TABLE_SIZE 501

int ind = 0, tp = 1, address = 4, seek = 0;
symbol symbol_table[MAX_SYMBOL_TABLE_SIZE];

scanner block(scanner *sweetyTokens, symbol *symbol_table, scanner token);
scanner const_dec(scanner *sweetyTokens, symbol *symbol_table, scanner token);
scanner var_dec(scanner *sweetyTokens, symbol *symbol_table, scanner token);
scanner statement(scanner *sweetyTokens, symbol *symbol_table, scanner token);
scanner expression(scanner *sweetyTokens, symbol *symbol_table, scanner token);
scanner term (scanner *sweetyTokens, symbol *symbol_table, scanner token);
scanner factor(scanner *sweetyTokens, symbol *symbol_table, scanner token);
scanner condition(scanner *sweetyTokens, symbol *symbol_table, scanner token);

void search(scanner *sweetyTokens, symbol *symbol_table, scanner token);


scanner block(scanner *sweetyTokens, symbol *symbol_table, scanner token)
{

	token = sweetyTokens[ind];

	// Const declaration
	if (token.kind == 28)
	{
		ind++;
		token = sweetyTokens[ind];
		// printf("Token index (const in): %d\n", ind);
		// printf("Token here (const in): %s\n", token.id);
		token = const_dec(sweetyTokens, symbol_table, token);
		// printf("CONST DECLARATION: DONE\n");
		// printf("-----------------------\n");
		// printf("\n");
		// printf("Token index: %d\n", token.index);
		// printf("Token here: %s\n", token.id);
		token = sweetyTokens[ind];
	}

	// Var declaration
	if (token.kind == 29)
	{

		ind++; // var passed
		token = var_dec(sweetyTokens, symbol_table, token);
		// printf("VAR DECLARATION: DONE\n");
		// printf("-----------------------\n");
		// printf("\n");

		token = sweetyTokens[ind];
	}

	// printf("INDEX: %d\n", ind);
	// printf("Token goes before the statement: %s\n", token.id);

	while (token.kind != 19)
	{
		if (token.kind == 0)
		{
			printf("Error: Period missed\n");
			exit (0);
		}
		if (token.kind == 18)
		{
			printf("Error: Wrongly usage of semicolom\n");
			exit(0);
		}

		// printf("INDEX: %d\n", ind);
		// printf("Token goes to statement: %s\n", token.id);

		token = statement(sweetyTokens, symbol_table, token);

		token = sweetyTokens[ind];

	}

	return token;
}

scanner const_dec(scanner *sweetyTokens, symbol *symbol_table, scanner token)
{

	if(token.kind == 18)
	{
		ind++;
		return token;
	}

	token = sweetyTokens[ind];
	// printf("Token index: %d\n", ind);
	// printf("Token here: %s\n", token.id);

	if (token.kind != 2)
	{
		printf("Error: Identifier expected\n");
		exit(0);
	}

	symbol_table[tp].kind = 1;
	strcpy(symbol_table[tp].name, token.id);
	symbol_table[tp].level = 0;
	symbol_table[tp].addr = 0;
	symbol_table[tp].mark = 0;
	//insert(ind, tp, sweetyTokens, symbol_table, token);
	ind++;
	token = sweetyTokens[ind];
	// printf("Token index: %d\n", ind);
	// printf("Token here: %s\n", token.id);


	if (token.kind != 9)
	{
		printf("Error: Equal sign expected\n");
		exit(0);
	}

	ind++;
	token = sweetyTokens[ind];

	// printf("Token index: %d\n", ind);
	// printf("Token here: %s\n", token.id);

	if (token.kind != 3)
	{
		printf("Error: Number expected\n");
		exit(0);
	}

	symbol_table[tp].val = atoi(token.id);
	ind++;
	token = sweetyTokens[ind];
	tp++;
	// printf("Token index: %d\n", ind);
	// printf("Token here: %s\n", token.id);

	if (token.kind == 17)
	{
		ind++;
		token = sweetyTokens[ind];
		token = const_dec(sweetyTokens, symbol_table, token);
		ind++;
	}
	else if (token.kind == 18)
	{
		// printf("-----semicolom found-----------\n");
		// printf("Token index: %d\n", ind);
		// printf("Token here: %s\n", token.id);
		return token;
	}
	else
	{
		printf("Error: Comma or semicolom expected\n");
		exit (0);
	}


}

void search(scanner *sweetyTokens, symbol *symbol_table, scanner token)
{
	int check;
	seek = tp;
	token = sweetyTokens[ind];
	// printf("SEATCHING FOR: %s\n", token.id);
	// printf("SEATCHING: %d\n", ind);
	while (seek != 0)
	{
		check = strcmp(token.id, symbol_table[seek].name);
		if (check == 0)
		{
			// printf("GOT IT !\n");
			return;
		}
		seek--;
	}
	printf("Error: const or variable %s is not declared\n",token.id);
	exit(0);
}

scanner var_dec(scanner *sweetyTokens, symbol *symbol_table, scanner token)
{

	token = sweetyTokens[ind];

	// printf("Token index: %d\n", ind);
	// printf("Token name: %s\n", token.id);

	// Passed Identifier
	if (token.kind != 2)
	{
		printf("Error: Identifier expected in var declaration\n");
		exit(0);
	}

	symbol_table[tp].kind = 2;
	strcpy(symbol_table[tp].name, token.id);
	symbol_table[tp].val = 0;
	symbol_table[tp].level = 0;
	symbol_table[tp].addr = address;
	symbol_table[tp].mark = 0;

	tp++;
	address++;
	ind++;
	token = sweetyTokens[ind];

	// Passed colom
	if (token.kind == 17)
	{
		ind++;
		token = var_dec(sweetyTokens, symbol_table, token);
	}
	// Passed semicolom
	else if (token.kind == 18)
	{
		// printf("semicolom - found\n");
		// printf("INNER INDEX: %d\n", ind);
		// printf("Token kind heeeere is: %s \n", token.id);
		// printf("---------------\n");
		ind++;
		return token;
	}
	else
	{
		printf("Error: Comma or semicolom expected in var declaration after identidier\n");
		exit (0);
	}


}

scanner statement(scanner *sweetyTokens, symbol *symbol_table, scanner token)
{
	// printf("-----------statement step---------\n");
	// printf("INDEX stat: %d\n", ind);
	// printf("Token stat: %s\n", token.id);

	// var statement
	if (token.kind == 2)
	{
		search(sweetyTokens, symbol_table, token);
		ind++;
		token = sweetyTokens[ind];

		if (token.kind != 20)
		{
			printf("Error: := sign missed in a statement \n");
			exit (0);
		}

		ind++;
		token = sweetyTokens[ind];
		// printf("INDEX: %d\n", ind);
		// printf("Token statement: %s\n", token.id);
		token = expression(sweetyTokens, symbol_table, token);

		// printf("\n");
		// printf("VAR STATEMENT: DONE\n");
		// printf("-----------------------\n");
		// printf("\n");
	}

	// begin statement
	else if (token.kind == 21)
	{

		ind++;
		token = sweetyTokens[ind];
		token = statement(sweetyTokens, symbol_table, token);

		if (token.kind != 18)
		{
			printf("Error: semicolom expected in 'begin' statement\n");
			exit (0);
		}

		ind++;
		token = sweetyTokens[ind];

		while (token.kind != 22)
		{
			if (token.kind == 0 || token.kind == 19)
			{
				printf("Error: End token missed\n");
				exit (0);
			}

			token = sweetyTokens[ind];
			token = statement(sweetyTokens, symbol_table, token);

			// printf("------>INDEX beg: %d\n", ind);
			// printf("------>Token beg: %s\n", token.id);

			if (token.kind != 18)
			{
				printf("Error: semicolom expected in 'begin' statement\n");
				exit (0);
			}

			ind++;
			token = sweetyTokens[ind];
			// printf("INDEX BEF/END after (while): %d\n", ind);
			// printf("Tokken in BEF/END after (while): %s\n", token.id);
		}


		ind++;
		token = sweetyTokens[ind];

		// printf("------>INDEX beg: %d\n", ind);
		// printf("------>Token beg: %s\n", token.id);

		// printf("\n");
		// printf("BEGIN/END STATEMENT: DONE\n");
		// printf("-----------------------\n");
		// printf("\n");
	}

	// If then statement
	else if (token.kind == 23)
	{
		ind++;
		token = sweetyTokens[ind];

		token = condition(sweetyTokens, symbol_table, token);
		token = sweetyTokens[ind];
		// printf("------>INDEX cond: %d\n", ind);
		// printf("------>Token cond: %s\n", token.id);

		if (token.kind != 24)
		{
			printf("Error: 'then' missed in if - statement\n");
			exit (0);
		}

		ind++;
		token = sweetyTokens[ind];
		token = statement(sweetyTokens, symbol_table, token);
		token = sweetyTokens[ind];

		// printf("\n");
		// printf("IF THEN STATEMENT: DONE\n");
		// printf("-----------------------\n");
		// printf("\n");

	}

	// While do statement
	else if (token.kind == 25)
	{
		ind++;
		token = sweetyTokens[ind];

		token = condition(sweetyTokens, symbol_table, token);
		token = sweetyTokens[ind];

		if (token.kind != 26)
		{
			printf("Error: 'do' missed in while - statement\n");
			exit (0);
		}

		ind++;
		token = sweetyTokens[ind];
		token = statement(sweetyTokens, symbol_table, token);
		token = sweetyTokens[ind];

		// printf("\n");
		// printf("WHILE DO STATEMENT: DONE\n");
		// printf("-----------------------\n");
		// printf("\n");
	}

	// write statement
	else if (token.kind == 31)
	{
		ind++;
		token = sweetyTokens[ind];

		// Identifier afer write
		if (token.kind != 2)
		{
			printf("Error: Missed identifier in 'read' statement\n");
			exit (0);
		}
		search(sweetyTokens, symbol_table, token);
		ind++;
		token = sweetyTokens[ind];
	}

	// read statement
	else if (token.kind == 32)
	{
		ind++;
		token = sweetyTokens[ind];

		// Identifier afer read
		if (token.kind != 2)
		{
			printf("Error: Missed identifier in 'read' statement\n");
			exit (0);
		}
		search(sweetyTokens, symbol_table, token);
		ind++;
		token = sweetyTokens[ind];
		// printf("------>INDEX read: %d\n", ind);
		// printf("------>Token read: %s\n", token.id);
	}

	return token;
}

scanner expression(scanner *sweetyTokens, symbol *symbol_table, scanner token)
{
	token = sweetyTokens[ind];
	//printf("-----------expression step---------\n");
	// printf("INDEX exp: %d\n", ind);
	// printf("Token ex: %s\n", token.id);

	if (token.kind == 4 || token.kind == 5)
	{
		// printf("-----------expression step---------\n");
		// printf("INDEX exp: %d\n", ind);
		// printf("Token ex: %s\n", token.id);

		ind++;
		token = sweetyTokens[ind];
		token = term(sweetyTokens, symbol_table, token);
	}

	token = term(sweetyTokens, symbol_table, token);
	token = sweetyTokens[ind];

	// printf("INDEX exp continue: %d\n", ind);
	// printf("Token ex contimue: %s\n", token.id);


	while (token.kind == 4 || token.kind == 5)
	{
		// printf("-----------expression step---------\n");
		// printf("INDEX exp: %d\n", ind);
		// printf("Token ex: %s\n", token.id);

		// printf("we are on sum or sub!\n");
		ind++;
		token = sweetyTokens[ind];

		token = term(sweetyTokens, symbol_table, token);
		// printf("INDEX exp after (while): %d\n", ind);
		// printf("Token exp after (while): %s\n", token.id);
		// ind++;
	}

	return token;
}

scanner term(scanner *sweetyTokens, symbol *symbol_table, scanner token)
{
	// printf("-----------term step---------\n");
	// printf("INDEX term: %d\n", ind);
	// printf("Token term: %s\n", token.id);

	token = factor(sweetyTokens, symbol_table, token);
	ind++;
	token = sweetyTokens[ind];

	// printf("INDEX term 2: %d\n", ind);
	// printf("Token term 2: %s\n", token.id);

	while (token.kind == 6 || token.kind == 7)
	{
		// printf("-----------term step---------\n");
		// printf("INDEX term (while): %d\n", ind);
		// printf("Token term (while): %s\n", token.id);
		// printf("we are on mult or div!\n");
		ind++;
		token = sweetyTokens[ind];
		token = factor(sweetyTokens, symbol_table, token);

		ind++;
		token = sweetyTokens[ind];
		// printf("INDEX term after (while): %d\n", ind);
		// printf("Token term after (while): %s\n", token.id);
	}

	return token;
}

scanner factor(scanner *sweetyTokens, symbol *symbol_table, scanner token)
{
	// printf("-----------factor step---------\n");
	// printf("INDEX fact: %d\n", ind);
	// printf("Token fact: %s\n", token.id);

	token = sweetyTokens[ind];
	// printf("INDEX fact 2: %d\n", ind);
	// printf("Token fact 2: %s\n", token.id);
	if (token.kind == 2)
	{
		token = sweetyTokens[ind];
		search(sweetyTokens, symbol_table, token);
		// printf("-----------------------------\n");
		return token;
	}
	else if(token.kind == 3)
	{
		token = sweetyTokens[ind];
		return token;
	}
	else if(token.kind == 15)
	{
		ind++;
		token = sweetyTokens[ind];
		token = expression(sweetyTokens, symbol_table, token);
	 	if(token.kind != 16)
		{
			printf("Error: ')' expected\n");
			exit (0);
		}
	}
	else
	{
		printf("Error: missed factor\n");
		exit (0);
	}

}

scanner condition(scanner *sweetyTokens, symbol *symbol_table, scanner token)
{
	token = sweetyTokens[ind];

	if (token.kind == 8)
	{
		ind++;
		token = sweetyTokens[ind];

		token = expression(sweetyTokens, symbol_table, token);
	}
	else
	{
		token = sweetyTokens[ind];

		token = expression(sweetyTokens, symbol_table, token);
		token = sweetyTokens[ind];

		if (token.kind != 10 && token.kind != 11 && token.kind != 12 && token.kind != 13 && token.kind != 14 && token.kind != 9)
		{
			printf("Error: Relation symbol missed \n");
			exit(0);
		}
		ind++;
		token = sweetyTokens[ind];

		token = expression(sweetyTokens, symbol_table, token);
	}
	return token;
}

symbol *parser(scanner *sweetyTokens, int vFlag, int lFlag, int aFlag)
{
	scanner token;


	token = block(sweetyTokens, symbol_table, token);

	if (lFlag || aFlag || vFlag)
	{
		printf("NO GRAMATICAL ERRORS DETECTED\n");
		printf("=============================\n\n");
	}
	return symbol_table;
}
