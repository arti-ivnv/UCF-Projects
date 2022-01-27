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

#define max 512
#define buffer 10000

int key_convert (int temp_key)
{

  if (temp_key >= 'a' && temp_key <= 'z')
  {
    return temp_key;
  }

  if(temp_key >= 'A' && temp_key <= 'Z')
  {
    temp_key = temp_key + 32;
    return temp_key;
  }

  return 0;
}

int plaintext_convert (int temp_pl)
{

  if (temp_pl >= 'a' && temp_pl <= 'z')
  {
    return temp_pl;
  }

  if(temp_pl >= 'A' && temp_pl <= 'Z')
  {
    temp_pl = temp_pl + 32;
    return temp_pl;
  }

  return 0;
}

char vigenere_cypher (char *cypher ,char *key, char *plaintext)
{
  int i, n, j, x;
  int key_v[max];
  int plaintext_v[max];

  for (i = 0; i < max; i++)
  {
    key_v[i] = (key[i]-97);
  }

  for (j = 0; j < max; j++)
  {
    plaintext_v[j] = (plaintext[j]-97);
  }

  for (n = 0; n < max; n++)
  {
    if (plaintext_v[n] + key_v[n] >=26)
    {
      cypher[n] = ((plaintext_v[n] + key_v[n])%26)+97;
    }
    else
    {
      cypher[n] = (plaintext_v[n] + key_v[n])+97;
    }
  }

  return *cypher;
}

int main(int argc, char **argv)
{
  int length, length_k, length_p, length_c;
  int i = 0, a,t,j=0;
  int temp_pl, temp_key;
  char *plaintext = NULL;
  char *key = NULL;
  char *cypher = NULL;

  plaintext = malloc(sizeof(char) * (buffer));
  key = malloc(sizeof(char) * (buffer));
  cypher = malloc(sizeof(char) * (max + 1));

  FILE *fp_key;
  fp_key = fopen(argv[1], "r");
  FILE *fp_pltx;
  fp_pltx = fopen(argv[2], "r");

  if (fp_key == NULL)
  {
    printf("ERROR: There is not such file in directory.\n");
    return 1;
  }

  while((temp_key = getc(fp_key))!=EOF)
  {
    if (key_convert(temp_key) != 0)
    {
      temp_key = key_convert(temp_key);
      *(key + i) = (char) temp_key;
      i++;
    }
  }
  length_k = strlen(key);

  printf("\n\n");
  printf("Vigenere Key:\n");

  for (i=0; i <= length_k; i++)
  {
    if(i % 80 == 0)
    {
      printf("\n");
    }
    printf("%c",*(key+i));
  }
  printf("\n\n\n");

  length = strlen(key);

  for (a = length; a<max; a++)
  {
    for(t = 0; t < (max - length); t++)
    {
      key[length + t] = key[t];
    }
  }

  if (fp_pltx == NULL)
  {
    printf("ERROR\n");
    return 1;
  }


  while((temp_pl = getc(fp_pltx))!=EOF)
  {
    if (plaintext_convert(temp_pl) != 0)
    {
      temp_pl = plaintext_convert(temp_pl);
      *(plaintext + j) = (char) temp_pl;
      j++;
      if (j == max)
      {
        break;
      }
    }
  }

  length = strlen(plaintext);

  if(length != max)
  {
    for (a = length; a < max; a++)
    {
      plaintext[a] = 'x';
    }
  }

  vigenere_cypher (cypher, key, plaintext);

  length_p = strlen(plaintext);
  length_c = strlen(cypher);

  printf("Plaintext:\n");
  for (i=0; i <= length_p; i++)
  {
    if(i % 80 == 0)
    {
      printf("\n");
    }
    printf("%c",*(plaintext+i));
  }

  printf("\n\n\n");

  printf("Ciphertext:\n");
  for (i=0; i <= length_c; i++)
  {
    if(i % 80 == 0)
    {
      printf("\n");
    }
    printf("%c",*(cypher+i));
  }

  printf("\n\n");

  free(plaintext);
  free(key);
  free(cypher);
  fclose(fp_key);
  fclose(fp_pltx);

  return 0;
}
