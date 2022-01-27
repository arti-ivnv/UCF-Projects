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

int ind = 0, tp = 1, address = 4, seek = 0, l = 0, m = 0;
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
	int check = 0;
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
		token = sweetyTokens[ind];
	}

	// Var declaration
	if (token.kind == 29)
	{

		ind++; // var passed
		token = sweetyTokens[ind];
		token = var_dec(sweetyTokens, symbol_table, token);
		// printf("VAR DECLARATION: DONE\n");
		// printf("-----------------------\n");
		// printf("\n");
		token = sweetyTokens[ind];
		// printf("INDEX stat: %d\n", ind);
		// printf("Token stat: %s\n", token.id);

	}

	// Proc declaration
	if (token.kind == 30)
	{
		ind++;
		token = sweetyTokens[ind];

		// checks if procedure has a name
		if (token.kind != 2)
		{
			printf("Error: name of the procedure missed\n");
			exit(0);
		}

		symbol_table[tp].kind = 3;
		strcpy(symbol_table[tp].name, token.id);
		symbol_table[tp].val = 0;
		symbol_table[tp].level = l;
		symbol_table[tp].addr = 0;
		symbol_table[tp].mark = m;

		l++;
		tp++;
		ind++;
		address = 4;

		token = sweetyTokens[ind];

		// checks if procedure has a semicolom after the name
		if (token.kind != 18)
		{
			printf("Error: Missed semicolom in procedure declaration\n");
		}

		ind++;
		token = sweetyTokens[ind];
		// printf("INDEX stat: %d\n", ind);
		// printf("Token stat: %s\n", token.id);
		token = block(sweetyTokens, symbol_table, token);

		if (token.kind != 19)
		{
			ind++;
		}

		seek = tp;
		token = sweetyTokens[ind];
		// printf("SEATCHING FOR: %s\n", token.id);
		// printf("SEATCHING: %d\n", ind);
		while (seek != 0)
		{
			if (symbol_table[seek].level == l && symbol_table[seek].mark != 1)
			{
				if (symbol_table[seek].level > 0)
				{
					symbol_table[seek].mark = 1;
				}
			}
			seek--;
		}

		token = sweetyTokens[ind];
		l--;

	}

	// Statement parser
	while (token.kind != 19)
	{
		if (token.kind == 0)
		{
			printf("Error: Period missed or semicolom in a procedure\n");
			exit (0);
		}

		if (token.kind == 18 && l == 0)
		{
			printf("Error: Wrongly usage of semicolom\n");
			exit(0);
		}
		else if (token.kind == 18 && l != 0)
		{
			// l--;
			return token;
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

	token = sweetyTokens[ind];

	if (token.kind != 2)
	{
		printf("Error: Identifier expected in const declaration\n");
		exit(0);
	}

	symbol_table[tp].kind = 1;
	strcpy(symbol_table[tp].name, token.id);
	symbol_table[tp].level = l;
	symbol_table[tp].addr = 0;
	symbol_table[tp].mark = m;

	ind++;
	token = sweetyTokens[ind];
	// printf("Token index: %d\n", ind);
	// printf("Token here: %s\n", token.id);


	if (token.kind != 9)
	{
		printf("Error: Equal sign expected in const declaration\n");
		exit(0);
	}

	ind++;
	token = sweetyTokens[ind];

	// printf("Token index: %d\n", ind);
	// printf("Token here: %s\n", token.id);

	if (token.kind != 3)
	{
		printf("Error: Number expected in const declaration\n");
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
	}
	else if (token.kind == 18)
	{
		ind++;
		return token;
	}
	else
	{
		printf("Error: Comma or semicolom expected in const declaration\n");
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
			return;
		}
		seek--;
	}
	printf("Error: const or variable or procedure %s is not declared\n", token.id);
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
	symbol_table[tp].level = l;
	symbol_table[tp].addr = address;
	symbol_table[tp].mark = m;

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

	// Call statement
	else if (token.kind == 27)
	{
		ind++;
		token = sweetyTokens[ind];

		if (token.kind != 2)
		{
			printf("Error: Identifier expected after 'call'\n");
			exit(0);
		}
		search(sweetyTokens, symbol_table, token);

		ind++;
		token = sweetyTokens[ind];
	}

	// begin statement
	else if (token.kind == 21)
	{

		ind++;
		token = sweetyTokens[ind];
		token = statement(sweetyTokens, symbol_table, token);

		if (token.kind == 18)
		{
			ind++;
			token = sweetyTokens[ind];

			if (token.kind == 22)
			{
				printf("Error: Extra semicolom in 'begin' statement\n");
				exit(0);
			}

			while (token.kind != 22)
			{
				if (token.kind == 0 || token.kind == 19)
				{
					printf("Error: End token missed\n");
					exit (0);
				}

				token = sweetyTokens[ind];
				token = statement(sweetyTokens, symbol_table, token);

				if (token.kind != 18 && token.kind != 22)
				{
						printf("Error: semicolom or end missed in 'begin' statement\n");
						exit(0);
				}

				if (token.kind == 18)
				{
					ind++;
					token = sweetyTokens[ind];

					if(token.kind == 22)
					{
						printf("Error: Extra semicolom in 'begin' statement\n");
						printf("Error: Probably you have got a semicolom one line before 'end'\n");
						exit(0);
					}
				}

				// printf("INDEX BEF/END after (while): %d\n", ind);
				// printf("Tokken in BEF/END after (while): %s\n", token.id);
			}
		}
		//
		ind++;
		token = sweetyTokens[ind];
	}

	// If statement
	else if (token.kind == 23)
	{
		ind++;
		token = sweetyTokens[ind];

		if (token.kind == 19 || token.kind == 18)
		{
			printf("Error: Condition expected after 'if'\n");
			exit(0);
		}

		token = condition(sweetyTokens, symbol_table, token);
		token = sweetyTokens[ind];
		 // printf("------>INDEX cond: %d\n", ind);
		 // printf("------>Token cond: %s\n", token.id);

		// 'then' check
		if (token.kind != 24)
		{
			printf("Error: 'then' must occure after if - statement\n");
			exit (0);
		}

		ind++;
		token = sweetyTokens[ind];

		if (token.kind == 19 || token.kind == 18)
		{
			printf("Error: Statemnt expected after 'then'\n");
			exit(0);
		}

		token = statement(sweetyTokens, symbol_table, token);
		token = sweetyTokens[ind];

		// printf("\n");
		// printf("IF THEN STATEMENT: DONE\n");
		// printf("-----------------------\n");
		// printf("\n");

		// 'else' check
		if (token.kind == 33)
		{
			ind++;
			token = sweetyTokens[ind];

			if (token.kind == 19 || token.kind == 18)
			{
				printf("Error: Statemnt expected after 'else'\n");
				exit(0);
			}

			token = statement(sweetyTokens, symbol_table, token);
			token = sweetyTokens[ind];
		}

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
			printf("Error: 'then' missed in while - statement\n");
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
		printf("No errors, program is syntactically correct\n");
		printf("===========================================\n\n");
	}

	// for (int i = 0; i < 30; i++)
	// {
	// 	printf("-------[# %d]-----\n", i);
	// 	printf("Kind: %d \n", symbol_table[i].kind);
	// 	printf("Name: %s \n", symbol_table[i].name);
	// 	printf("Val: %d \n", symbol_table[i].val);
	// 	printf("Level: %d \n", symbol_table[i].level);
	// 	printf("Addr: %d \n", symbol_table[i].addr);
	// 	printf("Mark: %d \n", symbol_table[i].mark);
	// 	printf("---------------\n");
	// 	printf("\n");
	// }
	return symbol_table;
}
