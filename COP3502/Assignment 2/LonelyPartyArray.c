// Artem Ivanov
// COP 3502C, Fall 2018

#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"


// Creating a party and allocating memory for it.
LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
  // Checks if recieved arguments
  if (num_fragments <= 0 || fragment_length <= 0)
  {
    return NULL;
  }

  // Allocates memory for our struct
  LonelyPartyArray *party = malloc(sizeof(LonelyPartyArray));

  // Checks if malloc worked.
  if (party == NULL)
  {
    return NULL;
  }

  party->size = 0;
  party->num_fragments = num_fragments;
  party->fragment_length = fragment_length;
  party->num_active_fragments = 0;

  // Allocates memory for struct's fragments
  party->fragments = calloc(num_fragments, sizeof(int *));

  // Check if calloc worked, if not, free other memory before returning.
  if (party->fragments == NULL)
  {
    free(party);
    return NULL;
  }

  // Allocates memory for number of fragments
  party->fragment_sizes = calloc(num_fragments, sizeof(int));

  // Check if calloc worked, if not, free other memory before returning.
  if (party->fragment_sizes == NULL)
  {
    free(party->fragments);
    free(party);
    return NULL;
  }

  printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n", num_fragments*fragment_length, party->num_fragments);
  return party;
}

// Destroying a party and free the memory inside of it.
LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
  int i;

  free(party->fragment_sizes);

  for (i = 0; i < party->num_fragments; i++)
  {
    free(party->fragments[i]);
  }

  free(party->fragments);
  free(party);

  printf("-> The LonelyPartyArray has returned to the void.\n");
  return NULL;
}

// Allocates memory for party fragments and set integers into the party fragments
int set(LonelyPartyArray *party, int index, int key)
{
  int i,b,n;
  int min_ind;
  int max_ind;

  // Check if party was allocated
  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in set().\n");
    return LPA_FAILURE;
  }

  // Algorythms to find coordinates for our fragment element
  b = index / party->fragment_length;
  i = index % party->fragment_length;

  // Checks if index is vcalid
  if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
  {
    printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", index, b, index-(party->fragment_length*b));
    return LPA_FAILURE;
  }

  if (party->fragments[b] == NULL && party->fragment_sizes[b] == 0)
  {
    party->fragments[b] = malloc (sizeof(int) * party->fragment_length);

    for (n = 0; n < party->fragment_length; n++)
    {
      party->fragments[b][n] = UNUSED;
    }

    party->fragments[b][i] = key;
    party->size++;
    party->num_active_fragments++;
    party->fragment_sizes[b]++;

    if (index >= party->fragment_length)
    {
      max_ind = (party->fragment_length * (b + 1)) - 1;
      min_ind = max_ind - (party->fragment_length - 1);
    }
    else
    {
      min_ind = 0;
      max_ind = party->fragment_length - 1;
    }

    printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n", b, party->fragment_length, min_ind, max_ind);
    return LPA_SUCCESS;
  }

  if (party->fragments[b][i] != UNUSED)
  {
    party->fragments[b][i] = key;
    return LPA_SUCCESS;
  }

  party->fragments[b][i] = key;
  party->fragment_sizes[b]++;
  party->size++;

  return LPA_SUCCESS;
}

// Allows us to get integers form the party
int get(LonelyPartyArray *party, int index)
{
  int i,b;
  int back;

  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in get().\n");
    return LPA_FAILURE;
  }

  b = index / party->fragment_length;//which fragment_ind
  i = index % party->fragment_length;//wich cell in specific fragment

  if ((party != NULL && index < 0) || (party != NULL && index > (party->num_fragments * party->fragment_length - 1)))
  {
    printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", index, index/party->fragment_length, index - (party->fragment_length * b));
    return LPA_FAILURE;
  }

  if (party->fragments[b] == NULL)
  {
    return UNUSED;
  }

  if(party->fragments[b] != NULL)
  {
    return party->fragments[b][i];
  }
  return LPA_FAILURE;
}

// Allows is delete integers from the party
int delete(LonelyPartyArray *party, int index)
{
  int i,b;
  int max_ind,min_ind;

  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in delete().\n");
    return LPA_FAILURE;
  }

  b = index / party->fragment_length;
  i = index % party->fragment_length;

  if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
  {
    printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", index, index/party->fragment_length, index - (party->fragment_length * b));
    return LPA_FAILURE;
  }
  if (party->fragments[b] == NULL)
  {
    return LPA_FAILURE;
  }

  if (party->fragments[b][i] == UNUSED)
  {
    return LPA_FAILURE;
  }
  if (party->fragments[b][i] != UNUSED)
  {
    party->fragments[b][i] = UNUSED;
    party->size--;
    party->fragment_sizes[b]--;
  }

  if(party->fragment_sizes[b] == 0)
  {
    if (index >= party->fragment_length)
    {
      max_ind = (party->fragment_length * (b + 1)) - 1;
      min_ind = max_ind - (party->fragment_length - 1);
    }
    else
    {
      min_ind = 0;
      max_ind = party->fragment_length - 1;
    }

    printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n", b, party->fragment_length, min_ind, max_ind);
    free(party->fragments[b]);
    party->fragments[b] = NULL;
    party->num_active_fragments--;
  }

  return LPA_SUCCESS;
}

// Linear search that search for specific integer in party fragments
int containsKey(LonelyPartyArray *party, int key)
{
  int i,b;

  if (party == NULL)
  {
    return 0;
  }

  if (party->fragment_sizes[b] == 0)
  {
    return 0;
  }

  // Linear search
  for(b = 0; b < party->num_fragments; b++)
  {
    if(party->fragments[b] != NULL)
    {
      for(i = 0; i < party->fragment_length; i++)
      {
        if (party->fragments[b][i] == key)
        {
          return 1;
        }
      }
    }
  }

  return 0;
}

// Checks if we set an integer
int isSet(LonelyPartyArray *party, int index)
{
  int b, i;

  if (party == NULL)
  {
    return 0;
  }

  b = index / party->fragment_length;
  i = index % party->fragment_length;

  if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
  {
    return 0;
  }

  if(party->fragments[b] == NULL)
  {

    return 0;
  }

  if (party->fragments[b][i] == UNUSED)
  {
    return 0;
  }

  return 1;
}

// Prints the value stored at the corresponded index
int printIfValid(LonelyPartyArray *party, int index)
{
  int i,b;

  if (isSet(party,index) == 0)
  {
    return LPA_FAILURE;
  }

  b = index / party->fragment_length;
  i = index % party->fragment_length;

  printf("%d\n",party->fragments[b][i]);
  return LPA_SUCCESS;
}

// Resets the party and returns it to original form
LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
  int i, b;

  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().\n");
    return party;
  }

  for (i = 0; i < party->num_fragments; i++)
  {
    party->fragment_sizes[i] = 0;
  }

  for (b = 0; b < party->num_fragments; b++)
  {
    free(party->fragments[b]);
    party->fragments[b] = NULL;
  }

  party->size = 0;
  party->num_active_fragments = 0;

  printf("-> The LonelyPartyArray has returned to its nascent state. (capacity: %d, fragments: %d)\n",party->num_fragments * party->fragment_length, party->num_fragments);
  return party;
}

// Returns number of elements curretly in the LPA, except UNUSED cells
int getSize(LonelyPartyArray *party)
{
  if (party == NULL)
  {
    return -1;
  }

  return party->size;
}

// Returns the maximum number of elements party can hold
int getCapacity(LonelyPartyArray *party)
{
  if (party == NULL)
  {
    return -1;
  }

  return party->num_fragments * party->fragment_length;
}

// Returns maximum number of elements party can hold without allocating new array
int getAllocatedCellCount(LonelyPartyArray *party)
{

  if (party == NULL)
  {
    return -1;
  }

  return party->num_active_fragments * party->fragment_length;
}

// Returns the number of bytes of standart array
long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
  long long unsigned int mem_0;

  if (party == NULL)
  {
    return 0;
  }

  mem_0 = party->num_fragments * party->fragment_length * sizeof(int);

  return mem_0;
}

//Returns the number of bytes currently taken up in memory by the LPA
long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
  long long unsigned int mem = 0;

  if (party == NULL)
  {
    return 0;
  }

  mem += sizeof(LPA*);
  mem += sizeof(LPA);
  mem += (sizeof(int) * party->num_fragments);
  mem += (sizeof(int*) * party->num_fragments);
  mem += (sizeof(int) * party->num_active_fragments * party->fragment_length);

  return mem;
}

// Creats a clone struct for LPA
LonelyPartyArray *cloneLonelyPartyArray(LonelyPartyArray *party)
{
  int i,b;

  LonelyPartyArray *clone = malloc(sizeof(LonelyPartyArray));

  // Check if malloc worked.
  if (party == NULL)
  {
    return NULL;
  }

  clone->size = party->size;
  clone->num_fragments = party->num_fragments;
  clone->fragment_length = party->fragment_length;
  clone->num_active_fragments = party->num_active_fragments;

  clone->fragments = calloc(clone->num_fragments, sizeof(int *));

  if (clone->fragments == NULL)
  {
    destroyLonelyPartyArray(clone);
    return NULL;
  }

  for (b = 0; b < clone->num_fragments; b++)
  {
    if(party->fragments[b] != NULL)
    {
      clone->fragments[b] = malloc (sizeof(int) * clone->fragment_length);

      if (clone->fragments[b] == NULL)
      {
        destroyLonelyPartyArray(clone);
        return NULL;
      }

      for (i = 0; i < clone->fragment_length; i++)
      {
        clone->fragments[b][i] = party->fragments[b][i];
      }
    }
  }

  clone->fragment_sizes = calloc(clone->num_fragments, sizeof(int));

  if (clone->fragment_sizes == NULL)
  {
    destroyLonelyPartyArray(clone);
    return NULL;
  }

  for (i = 0; i < clone->fragment_length; i++)
  {
    if (clone->fragment_sizes[i] == 0)
    {
      clone->fragment_sizes[i] = party->fragment_sizes[i];
    }
  }

  printf("-> Successfully cloned the LonelyPartyArray. (capacity: %d, fragments: %d)\n",clone->num_fragments * clone->fragment_length, clone->num_fragments);
  return clone;
}
