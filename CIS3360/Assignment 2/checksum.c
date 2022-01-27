/*

I Artem Ivanov (ar286080) affirm that this program is entirely my own work and
that I have neither devoloped my code together with any another person, nor
copied any code from any other person, nor permitted my code to be copied or
otherwise used by any other person, nor have I copied, modified, or otherwise
used programs created by others. I acknowledge that any violation of the above
terms will be treated as academic dishonesty.

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define buffer 100000

int pads_counter(int length, int x)
{
	int amount = 0;

	if (x == 16)
	{
		if (length % 2 == 0)
		{
			return 0;
		}

		amount = 2 - length % 2;
		return amount;
	}

	if (x == 32)
	{
		if (length % 4 == 0)
		{
			return 0;
		}
		amount = 4 - length % 4;
		return amount;
	}

	return amount;
}

char checkSum(char *temp_s, int length, int x)
{
	int i;
	unsigned char check = 0;
	char check_2;

	if(x == 8)
	{
		for(i = 0; i < length; i++)
		{
			check_2 = temp_s[i];
			check += check_2;
		}
	}

	return check;
}

unsigned char *checkSum_16_32(char *temp_s, int length, int x)
{
	int i, j;
	int over = 0;
	int over1 = 0;
	int over2 = 0;
	int over3 = 0;
	unsigned char *check16 = NULL;
	unsigned char *check32 = NULL;

	check16 = malloc(sizeof(char) * 4);
	check32 = malloc(sizeof(char) * 8);

	if (x == 16)
	{
		if (length == 2)
		{
			check16[0] = temp_s[0];
			check16[1] = temp_s[1];
			return check16;
		}
		check16[0] = 0;
		check16[1] = 0;

		for(i = 0; i < length; i++)
		{
			if(i%2 == 0)
			{
				check16[0] += temp_s[i];
			}
			else
			{
				if(check16[1] + temp_s[i] >= 0x100)
				{
					over++;
				}
				check16[1] += temp_s[i];
			}
		}
		check16[0] = check16[0] + over;
		return check16;
	}

	if (x == 32)
	{
		if (length == 4)
		{
			check32[0] = temp_s[0];
			check32[1] = temp_s[1];
			check32[2] = temp_s[2];
			check32[3] = temp_s[3];

			return check32;
		}

		check32[0] = 0;
		check32[1] = 0;
		check32[2] = 0;
		check32[3] = 0;

		for(i = 0; i < length; i++)
		{
			if((i + 4) % 4 == 0)
			{
				check32[0] += temp_s[i];
			}
			else if((i + 4) % 4 == 1)
			{
				if(check32[1] + temp_s[i] >= 0x100)
				{
					over1++;
				}
				check32[1] += temp_s[i];
			}
			else if((i + 4) % 4 == 2)
			{
				if(check32[2] + temp_s[i] >= 0x100)
				{
					over2++;
				}
				check32[2] += temp_s[i];
			}
			else if ((i + 4) % 4 == 3)
			{
				if(check32[3] + temp_s[i] >= 0x100)
				{
					over3++;
				}
				check32[3] += temp_s[i];
			}
		}

		if (over1 > 10)
		{
			check32[0] = check32[0] + 1;
		}
		check32[0] = check32[0] + over1;
		check32[1] = check32[1] + over2;
		check32[2] = check32[2] + over3;

		return check32;

	}


	return 0;
}

int main(int argc, char **argv)
{
	int i = 0, x, j,b;
	int temp, length, bit, pad;
	int total_len;
	unsigned char LOL;
	unsigned char *LOL2;
	unsigned char *LOL3;
	char *temp_s = NULL;


	x = atoi(argv[2]);

	if((x != 8) && (x != 16) && (x != 32))
	{
		fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
		return 1;
	}


	temp_s = malloc(sizeof(char) * 1024);
	LOL2 = malloc(sizeof(char)*2);
	LOL3 = malloc(sizeof(char)*4);


	FILE *ifp;
	ifp = fopen(argv[1], "r");

	while((temp = getc(ifp)) != EOF)
  {
    *(temp_s + i) = (char) temp;
		length++;
    i++;
  }

	pad = pads_counter(length, x);

	total_len = length + pad;

	if(length != total_len)
	{
		for (j = length; j < total_len; j++)
		{
			*(temp_s + j) = 'X';
		}
		length = total_len;
	}


	if (x == 16)
	{
		printf("\n");
		for(b = 0; b < length; b++)
		{
			if (b % 80 == 0 && b != 0)
			{
				printf("\n");
			}
			printf("%c", temp_s[b]);
		}
		printf("\n");
		LOL2 = checkSum_16_32(temp_s, length, x);
		printf("%2d bit checksum is     %02x%02x for all %4d chars\n", x, LOL2[0],LOL2[1], length);
	}
	else if (x == 32)
	{
		printf("\n");
		for(b = 0; b < length; b++)
		{
			if (b % 80 == 0 && b != 0)
			{
				printf("\n");
			}
			printf("%c", temp_s[b]);
		}
		printf("\n");
		LOL3 = checkSum_16_32(temp_s, length, x);
		printf("%2d bit checksum is %02x%02x%02x%02x for all %4d chars\n", x, LOL3[0], LOL3[1], LOL3[2], LOL3[3], length);
	}
	else
	{
		printf("\n");

		for(b = 0; b < length; b++)
		{
			if (b % 80 == 0 && b != 0)
			{
				printf("\n");
			}
			printf("%c", temp_s[b]);
		}

		printf("\n");

		LOL = checkSum(temp_s, length, x);
		printf("%2d bit checksum is %8x for all %4d chars\n", x, LOL, length);
	}

	return 0;
}
