//Name: Artem Ivanov

#include "Glowworm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printGlowworm (int tail, int head, int maxLength);


// I use main function in case to scan input arguments, analyze input string, compare string characters.
//Also, main function oriented to give us the output of our Glowworm in case of character situation.
int main(int argc, char **argv)
{
	int length,string_len;
	int grow_time=0;
	int head_indx=2, tail_indx=0;
	int i;

	//We assign the overall length and string length according to console arguments.
	length =  atoi(argv[1]);
	string_len = strlen(argv[2]);

	//The first output of our Glowworm creation.
	//Also, we are using the first if statement here in case of safety because our overall length must be bigger than 3 and less than 50.
	if (length>=3 && length<=50)
	{
		printf("%s\n\n",argv[2]);
		printf("Glowworm appears! Hooray!\n");
		printGlowworm(tail_indx,head_indx,length);

	//In further loops and statements we are scanning our string and compare characters in this string.
	//According to the character, statements uses a specific version of printGlowworm function.
		for (i=0;i<string_len;i++)
		{
			if (argv[2][i]=='o'||argv[2][i]=='O'||argv[2][i]=='@')
			{
				if((head_indx-tail_indx)==(length-1)||(tail_indx-head_indx)==(length-1)||tail_indx-head_indx==1)//add some
				{
					printf("Glowworm chills:\n");
					printGlowworm(tail_indx,head_indx,length);
				}
				else
				{
				head_indx++;
				grow_time++;

				if (head_indx == length||head_indx>length)
				{
					head_indx = 0;
				}
				if (head_indx == length||head_indx>length)
				{
					head_indx = 0;
				}
				printf("Glowworm grows:\n");
				printGlowworm(tail_indx,head_indx,length);
				}
			}
			else if (argv[2][i]=='s'||argv[2][i]=='S')
			{
				if (head_indx==0)
				{
					head_indx = length;
				}
				if((head_indx-tail_indx)==2)
				{
					printf("Glowworm chills:\n");
					printGlowworm(tail_indx,head_indx,length);
				}
				else
				{
					head_indx--;
					printf("Glowworm shrinks:\n");
					printGlowworm(tail_indx,head_indx,length);
				}
			}
			else if (argv[2][i]=='-'||argv[2][i]=='=')
			{
				tail_indx++;
				head_indx++;
				if (head_indx == length||head_indx>length)
				{
					head_indx = 0;
				}
				else if (tail_indx == length)
				{
					tail_indx = 0;
				}
				printf("Glowworm inches forward:\n");
				printGlowworm(tail_indx,head_indx,length);

			}
			else if (argv[2][i]=='x'||argv[2][i]=='X'||argv[2][i]=='%')
			{
				if (head_indx == 0)
				{
					head_indx= -100;
				}
				else
				{
				head_indx = head_indx * -1;
				}
				printf("Glowworm meets its demise. SAD.\n");
				printGlowworm(tail_indx,head_indx,length);
				return 0;
			}
			else
			{
				printf("Glowworm chills:\n");
				printGlowworm(tail_indx,head_indx,length);
			}
		}

	}
	else
	{
		printf("Your length out of range.\n");
	}

	return 0;
}


//In printGlowworm function we are using an algorithm that will print characters in the specific way.
void printGlowworm (int tail, int head, int maxLength)
{

	int oThing_num = head-1;
	int dead = 0;
	int b = 0,i = 0,z=0,f=0,l=0,e=0,m=0;
	char tail_c = '~';
	char oThing = 'O';
	char head_c = 'G';
	char grow = 'o';
	char dying_O = 'X';
	char dying_G = 'x';

//In this if statement we are looking if our Glowworm is dead.
	if (head < 0)
	{
		if (head == -100)
		{
			head = 0;
			dead = 1;
			oThing_num = maxLength -1;
		}
		else
		{
			head = head * -1;
			dead = 1;
		}
	}

//This if statement needed to print basic position of a Glowworm.
	if (head == 2 && head>tail)
	{
		printf("%c",tail_c);

		if(dead==1)
		{
			printf("%c",dying_O);
			printf("%c",dying_G);
			printf("\n");
		}
		else
		{
			printf("%c",oThing);
			printf("%c",head_c);
			printf("\n");
		}
		while (b<maxLength)
		{
			printf("=");
			b++;
		}
		printf("\n\n");
	}


	if (tail<head && head!=2)
	{
		//This for loop is looking if we need a space.
		for (i=0;i<tail;i++)
		{
			printf(" ");
		}

		printf("%c",tail_c);

		//This for loop is looking if our Glowworm is growing
		for (i=tail+1;i<head-1;i++)
		{
			printf("%c",grow);
		}

		//This if statement checks is if our Glowworm is dead, if so prints dead result.
		if (dead==1)
		{
			printf("%c",dying_O);
			printf("%c",dying_G);
		}
		else
		{
			printf("%c",oThing);
			printf("%c",head_c);
		}

		printf("\n");
		while (f<maxLength)
		{
			printf("=");
			f++;
		}
		printf("\n\n");
	}

 //This situation doing the same as previous but in opposite way.
	else if (head<tail)
	{
		for(z=0;z<head-1;z++)
		{
			printf("%c",grow);
		}
		if(head==0)
		{
			if (dead==1)
			{
				printf("%c",dying_G);
			}
			else
			{
				printf("%c",head_c);
			}
		}
		else
		{
			if (dead == 1)
			{
				printf("%c",dying_O);
				printf("%c",dying_G);
			}
			else
			{
				printf("%c",oThing);
				printf("%c",head_c);
			}
		}
		 for(i=head+1;i<tail;i++)
		{
			printf(" ");
		}
		printf("%c",tail_c);
		if (oThing_num + 1 == 0)
		{
			oThing_num = maxLength-1;
		}
		if (oThing_num < tail)
		{
			for (e=tail+1;e<maxLength;e++)
			{
				printf("%c",grow);
			}
		}
		for(l=tail+1;l<oThing_num;l++)
		{
			printf("%c",grow);
		}
		if (head==0)
		{
			if(dead==1)
			{
				printf("%c",dying_O);
			}
			else
			{
				printf("%c",oThing);
			}
		}

		printf("\n");
		while (f<maxLength)
		{
			printf("=");
			f++;
		}
		printf("\n\n");
	}

}
