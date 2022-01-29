// Artem Ivanov

#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"

// Supporting list to hold our tree data
typedef struct helper_list
{
  int *pre_ar;
  int *post_ar;
  int counter_pr;
  int counter_po;
}list;

// Difficulty
double difficultyRating(void)
{
  return 2.0;
}

// Hours Spent
double hoursSpent(void)
{
  return 10.0;
}

// Checks if our trees are reflected
int isReflection(node *a, node *b)
{
  // Both of the nodes are NULL or we have an emtpty tree/subtree
  if (a == NULL && b == NULL)
  {
    return 1;
  }

  // If values in the nodes are reflected
  if (a != NULL && b != NULL)
  {
    if (a->data == b->data)
    {
      return isReflection(a->left, b->right) && isReflection(a->right, b->left);
    }
    else
    {
      return 0;
    }
  }
  // If only one node is NULL
  else
  {
    return 0;
  }
}

// Clones an original tree. Reflection helper
node *cloneTree(node *root)
{
  node *clone = malloc(sizeof(node));

  // Base case for recusion
  if (root == NULL)
  {
    free(clone);
    return NULL;
  }


  clone->data = root->data;

  // Goes through the tree/subtree recursively
  clone->left = cloneTree(root->left);
  clone->right = cloneTree(root->right);

  return clone;
}

// Swaps nodes of a clone tree to make them reflection
void mr_Swap(node *reflection)
{
  // Base case
  if (reflection == NULL)
  {
    return;
  }

  node *temp = malloc(sizeof(node));

  // Basic swap operation
  temp = reflection->left;
  reflection->left = reflection->right;
  reflection->right = temp;

  // Function goes through left and right sides of the tree/subtree
  mr_Swap(reflection->left);
  mr_Swap(reflection->right);
}

// Makes reflection of a tree
node *makeReflection(node *root)
{
  node *reflection = malloc(sizeof(node));

  // reflection of an empty tree
  if (root == NULL)
  {
    free(reflection);
    return NULL;
  }

  // Makes a clone of an actual tree, then swaps nodes. Reflection as a result
  reflection = cloneTree(root);
  mr_Swap(reflection);

  return reflection;
}

// Counts how many nodes are in the tree
int Node_counter(node *c)
{
  if (c == NULL)
  {
    return 0;
  }

  return 1 + Node_counter(c->right) + Node_counter(c->left);
}

// Post order operation that works with the tree data
void post_order(node *c, list *anime_list)
{
  if (c == NULL)
  {
    return;
  }

  post_order(c->left, anime_list);
  post_order(c->right, anime_list);

  anime_list->post_ar[anime_list->counter_po] = c->data;
  anime_list->counter_po++;
}

// Pre order operation that works with the tree data
void pre_order(node *c, list *anime_list)
{
  if (c == NULL)
  {
    return;
  }

  anime_list->pre_ar[anime_list->counter_pr] = c->data;
  anime_list->counter_pr++;

  pre_order(c->left, anime_list);
  pre_order(c->right, anime_list);
}

// Compares two post order of one tree with pre order of another
int comparison (list *anime_list, int elements)
{
  int i = 0;

  // Simply checks if nodes' data of one tree is the same of another
  while (i != elements)
  {
    if (anime_list->post_ar[i] != anime_list->pre_ar[i])
    {
      return 0;
    }
    else
    {
      i++;
    }
  }

  return 1;
}

// "Clean up after yourself." (Dr.Szumlanski)
list *Destroyer(list *anime_list)
{
	free(anime_list->pre_ar);
  anime_list->pre_ar = NULL;

  free(anime_list->post_ar);
  anime_list->post_ar = NULL;

  free(anime_list);
  anime_list = NULL;

	return NULL;
}

// Checks if our trees are "kindredSpirits"
int kindredSpirits(node *a, node *b)
{
  int n = 0;
  int elements_a = 0, elements_b = 0;
  int elements;
  int comp;
  int comp2;

  // If our trees are both empty, both of them are kindredSpirits
  if (a == NULL && b == NULL)
  {
    return 1;
  }

  // Counting of how many elements are in the trees
  elements_a = Node_counter(a);
  elements_b = Node_counter(b);

  // If trees have different numbers of nodes they are not kindredSpirits
  if (elements_a != elements_b)
  {
    return 0;
  }
  else
  {
    elements = elements_a;
  }


  list *anime_list = malloc(sizeof(list));
  anime_list->post_ar = calloc(elements_a, sizeof(int));
  anime_list->pre_ar = calloc(elements_a, sizeof(int));
  anime_list->counter_po = 0;
  anime_list->counter_pr = 0;

  pre_order(a, anime_list);
  post_order(b, anime_list);

  comp = comparison(anime_list, elements);

  // Clean up our list to work with it further
  for (n = 0; n < elements; n++)
  {
    anime_list->post_ar[n] = 0;
    anime_list->pre_ar[n] = 0;
  }

  anime_list->counter_po = 0;
  anime_list->counter_pr = 0;

  // Checking if reverse case is the same
  post_order(a, anime_list);
  pre_order(b, anime_list);

  comp2 = comparison(anime_list, elements);

  // Clean up the list, since we do not need it anymore
  Destroyer(anime_list);

  // (True) If pre order of one is the same of post order of another or reverse
  return comp || comp2;
}
