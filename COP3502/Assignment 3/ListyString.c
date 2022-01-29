// Artem Ivanov

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ListyString.h"

// Checks for listy length
int listyLength(ListyString *listy)
{
	if (listy == NULL)
	{
		return -1;
	}

	if (listy->head == NULL)
	{
		return 0;
	}

	return listy->length;
}

// Delete characters if there is no str, otherwise replaces chars of the list with the key
void replaceChar(ListyString *listy, char key, char *str)
{
	ListyString *new_str;
	ListyNode *temp, *temp2, *tail, *current, *prev, *tail_str;
	int m;

	if (listy == NULL || listy->head == NULL)
	{
		return;
	}

	temp = listy->head;
	temp2 = NULL;
	current = NULL;
	tail = NULL;
	prev = NULL;
	tail_str = NULL;


	// Checks if our operation contains string. otherwise, delete operation.
	if (str == NULL || str[0] == '\0')
	{
		if (listy->length == 1 && temp->data == key)
		{
			listy->head = NULL;
			listy->length = 0;
			return;
		}

		while (temp != NULL)
		{
			if (temp->data != key && temp->next != NULL)
			{
				current = temp;
			}

			if (temp->next == NULL)
			{
				tail = temp;
			}

			if (temp->data == key)
			{
				if (temp == listy->head)
				{
					listy->head = temp->next;
					listy->length--;
					free(temp);
				}
				else if (temp->next != NULL)
				{
					current->next = temp->next;
					listy->length--;
					free(temp);
				}
				else
				{
					tail = current;
					tail->next = NULL;
					listy->length--;
					free(temp);
				}
			}

			temp = temp->next;
		}
	}
	else
	{
		while (temp != NULL)
		{
			if (temp->next != NULL)
			{
				if (temp->next->data == key)
				{
					 prev = temp;
				}
			}
			else
			{
				tail = temp;
			}

			if (temp->data == key)
			{
				new_str = createListyString(str);
				listy->length += new_str->length - 1;

				if (temp == listy->head)
				{
					listy->head = new_str->head;
				}
				else
				{
					prev->next = new_str->head;
				}

				temp2 = new_str->head;
				free(temp);

				while (temp2 != NULL)
				{
					if (temp2->next == NULL)
					{
						tail_str = temp2;
					}

					temp2 = temp2->next;
				}

				tail_str->next = temp->next;
			}

			temp = temp->next;
		}
	}

}

// Creates a clone of our listy list.
ListyString *cloneListyString(ListyString *listy)
{

	int n;

	if (listy == NULL)
	{
		return NULL;
	}

	ListyString *clone_string = malloc(sizeof(ListyString));
	ListyString *clone_temp;
	clone_temp->head = listy->head;
	clone_string->length = 0;

	for(n = 0; n < listy->length; n++)
	{
		ListyNode *clone_node = malloc(sizeof(ListyNode));
		ListyNode *ctemp;

		clone_string->length++;
		clone_node->data = clone_temp->head->data;

		clone_node->next = NULL;

		if(n == 0)
		{
			clone_string->head = clone_node;
			ctemp = clone_node;
			clone_temp->head = clone_temp->head->next;
		}
		else
		{
		  ctemp->next = clone_node;
			ctemp = ctemp->next;
			clone_temp->head = clone_temp->head->next;
		}

	}
	return clone_string;
}

ListyString *listyCat(ListyString *listy, char *str)
{
	int k;
	ListyString *new_str;
	ListyNode *temp;

	if (listy == NULL && str == NULL)
	{
		return NULL;
	}

	if (listy == NULL && (str != NULL && str[0] != '\0'))
	{
		new_str = createListyString(str);
		return new_str;
	}

	if (listy != NULL && (str == NULL || str[0] == '\0'))
	{
		return listy;
	}

	if ((listy->head == NULL && listy->length == 0) && str != NULL)
	{
		new_str = createListyString(str);
		listy->head = new_str->head;
		listy->length = new_str->length;
		return listy;
	}

	temp = listy->head;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	for (k = 0; k < strlen(str); k++)
	{
		ListyNode *listy_n = malloc(sizeof(ListyNode));
		ListyNode *temp1;

		listy->length++;
		listy_n->data = str[k];
		listy_n->next = NULL;

		temp->next = listy_n;
		temp = temp->next;
	}
	return listy;
}

// Compares two strings.
int listyCmp(ListyString *listy1, ListyString *listy2)
{
	int k = 0, x = 0;
	char string1[1024], string2[1024];
	ListyNode *temp1, *temp2;

	if (listy1 == NULL && listy2 == NULL)
	{
		return 0;
	}

	else if (listy1 == NULL && listy2 != NULL)
	{
		return 1;
	}

	else if (listy2 == NULL && listy1 != NULL)
	{
		return 1;
	}

	else if ((listy1->head == NULL && listy1->length ==0) && (listy2->head == NULL && listy2->length == 0))
	{
		return 0;
	}

	else
	{
		temp1 = listy1->head;
		temp2 = listy2->head;

		while (temp1 != NULL)
		{
			string1[k] = temp1->data;
			temp1 = temp1->next;
			k++;
		}

		string1[k] = '\0';

		while (temp2 != NULL)
		{
			string2[x] = temp2->data;
			temp2 = temp2->next;
			x++;
		}

		string2[x] = '\0';

		return strcmp(string1, string2);
	}
}

// Output our list when we ask.
void printListyString(ListyString *listy)
{
	if (listy == NULL || listy->head == NULL)
	{
		printf("(empty string)");
		printf("\n");
		return;
	}

	ListyNode *temp1;
	temp1 = listy->head;

	while (temp1 != NULL)
	{
		printf("%c", temp1->data);
		temp1 = temp1->next;
	}
	printf("\n");
}

// Reverse our list.
void reverseListyString(ListyString *listy)
{
	ListyNode *temp1, *temp2, *temp3;

	if (listy == NULL)
	{
		return;
	}

	temp1 = NULL;
	temp2 = listy->head;
	temp3 = NULL;

	while (temp2 != NULL)
	{
		temp3 = temp2->next;
		temp2->next = temp1;
		temp1 = temp2;
		temp2 = temp3;
	}

	listy->head = temp1;
}

// Destroying our list and free the memory.
ListyString *destroyListyString(ListyString *listy)
{
	if (listy == NULL)
	{
		return NULL;
	}
	if (listy->head == NULL)
	{
		return NULL;
	}

	while (listy->head != NULL)
	{
		free(listy->head);
		listy->head = listy->head->next;
	}

	free(listy);

	return NULL;
}

// Allocates memory and and creates a list.
ListyString *createListyString(char *str)
{
	int k;

	if (str == NULL || str[0] == '\0')
	{
		ListyString *listy = malloc(sizeof(ListyString));
		listy->head = NULL;
		listy->length = 0;
		return listy;
	}

	ListyString *listyS = malloc(sizeof(ListyString));
	listyS->length = 0;

	for (k = 0 ; k < strlen(str); k++)
	{
		ListyNode *listy = malloc(sizeof(ListyNode));
		ListyNode *temp;

		listyS->length++;
		listy->data = str[k];
		listy->next = NULL;

		if (k == 0)
		{
			listyS->head = listy;
			temp = listy;
		}
		else
		{
		  temp->next = listy;
			temp = temp->next;
		}
	}

	return listyS;
}

// Reads the file and works with the function.
int processInputFile(char *filename)
{
	int i = 0, counter = 0, func_id = 0;
	char sign, key, buffer[1024];
	char *str = NULL;
	ListyString *listy = NULL;

	FILE *ifp = NULL;

	if ((ifp = fopen(filename, "r")) == NULL)
	{
		return 1;
	}

	fscanf(ifp, "%s", buffer);
	listy = createListyString(buffer);

	while (fscanf(ifp, "%s", buffer) != EOF)
	{
		str = malloc(sizeof(char) * (strlen(buffer)));
		strcpy(str, buffer);

		if (str[0] == '!')
		{
			printListyString(listy);
			continue;
		}

		if (str[0] == '?')
		{
			printf("%d\n", listyLength(listy));
			continue;
		}


		if (str[0] == '~')
		{
			reverseListyString(listy);
			continue;
		}

		if (str[0] == '-')
		{
			sign = '-';
			continue;
		}

		if (sign == '-')
		{
			key = str[0];
			str = NULL;
			replaceChar(listy, key, str);
			continue;
		}

		if (str[0] == '+')
		{
			sign = '+';
			continue;
		}

		if (sign == '+')
		{
			listy = listyCat(listy, str);
			continue;
		}

		if (str[0] == '@')
		{
			sign = '@';
			continue;
		}

		if (sign == '@' && counter == 0)
		{
			key = str[0];
			counter = 1;
			continue;
		}

		if (sign == '@' && counter == 1)
		{
			replaceChar(listy, key, str);
			continue;
		}

		free(str);
	}

	return 0;
}

// gets the name of the input file.
int main (int argc, char **argv)
{
	char *filename;

	filename = malloc(sizeof(char) * 21);

	strcpy(filename, argv[1]);

	processInputFile(filename);

	return 0;
}
