// Artem Ivanov
// Daniel Couch
// COP 3402
// HW 1 VM


#include <stdio.h>
#include <stdlib.h>
#include "CodeGen.h"
#include "Parser.h"
#include "Scanner.h"
#include "VM.h"



// Constans
#define MAX_DATA_STACK_HEIGHT 1000
#define MAX_CODE_LENGTH 500



// typedef struct
// {
//   int op, l, m; // < OP code, Lexicographical Level, M>
//   /*
//         M could mean:
//       - A number
//       - A program Address
//       - A data address
//       - The identity of the operator OPR
//   */
// }instruction;

// This function helps to output the stack
void stack_printer(int *stack, int bp, int sp, int *inc, int vFlag)//, FILE *outFile)
{

  int sum = 0;
  int opps = 0;
  int f = 0;

  // Summation of all stack allocations
  for (int k = 0; k <= 999; k++)
  {
    sum += inc[k];
  }
  if (vFlag == 1)
  {
    // Straight printer that prints our stack and counts where we need to put "|" char
    for(int j = MAX_DATA_STACK_HEIGHT - 1; j >= MAX_DATA_STACK_HEIGHT - sum; j--)
    {
      printf("%d ", stack[j]);



      // fprintf(outFile, "%d ", stack[j]);
      // opps++;

      // if (opps == inc[f] && j != MAX_DATA_STACK_HEIGHT - sum)
      // {
      //   printf("| ");
      //   // fprintf(outFile, "| ");
      //   opps = 0;
      //   f++;
      // }
    }
  }

  return;
}

// Prototype of the base function
int base(int l, int base, int *);

void virtual_machine(instruction *code, int vFlag)
{
  // Default values that will be changed later in the code
  int pc = 0;
  int halt = 1;
  int sp = MAX_DATA_STACK_HEIGHT;
  int bp = sp - 1;
  int ir = 0;
  int z = 0;
  int i = 0;

  // Arrays that help us to print
  int inc[MAX_DATA_STACK_HEIGHT-1] = {};

  char *opName[] = {"lit", "opr", "lod", "sto", "cal", "inc", "jmp", "jpc", "sio", "sio", "sio"};

  // Creating a code (same as text) array of structs that holds the input informartion
  // instruction code[MAX_CODE_LENGTH];

  // Creating a stack array and initializing all members to 0
  int stack[MAX_DATA_STACK_HEIGHT] = { };

  if (vFlag == 1)
  {
    // Read in command line arguments and stores them into inName and outName
    //char * inName = argv[1];
    //char * outName = argv[2];

    // FILE * inFile = fopen(inName, "r");
    // FILE * outFile = fopen(outName, "w");

    // Formatting
    // fprintf(outFile, "Line\tOP\tL\tM\n");
    // printf("Line\tOP\tL\tM\n");

    // This loops gets all of the information from the file and then outputs the first part of the
    // output
    // for (int i = 0; fscanf(inFile, "%d %d %d", &code[i].op, &code[i].l, &code[i].m) != EOF; i++)
    // {
    //   fprintf(outFile, "%d\t%s\t%d\t%d\n", i, opName[code[i].op-1], code[i].l, code[i].m);
    //   printf("%d\t%s\t%d\t%d\n", i, opName[code[i].op-1], code[i].l, code[i].m);
    // }

     // Spacing out the 2 outputs
     // fprintf(outFile, "\n\n\n");
     printf("\n\n\n");

     // Sets up the formatting for the columns for the outputs
     // fprintf(outFile, "\t\tpc\tbp\tsp\tstack\n");
      printf("\t\tpc\tbp\tsp\tstack\n");
     //
     // // Shows the Initial values of the program counter, base pointer, and stack pointer
     // fprintf(outFile, "Initial values\t%d\t%d\t%d\n", pc, bp, sp);
      printf("Initial values\t%d\t%d\t%d\n", pc, bp, sp);
    }

   // The body of the code that runs until the halt flag is changed with op code 11
   while (halt)
   {
      // Fetch Cycle
      // This sets the ir int equal to the pc int so we hold the spot of that op code so the VM
      // knows what instruction to do first not skip any instructions.
      ir = pc;

      if (vFlag == 1)
      {
      // Header of the second output
      printf("%d %s %d %d\t", pc, opName[code[ir].op - 1], code[ir].l, code[ir].m);
      }
       // fprintf(outFile, "%d %s %d %d\t", pc, opName[code[ir].op - 1], code[ir].l, code[ir].m);

      pc++;

      //Execute
      switch (code[ir].op)
      {
        // LIT
         case 1:
              sp--;
              stack[sp] = code[ir].m;
              inc[z] += 1;

              if (vFlag == 1)
              {
                printf("%d\t%d\t%d\t", pc, bp, sp);
                // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
                stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
              }
              break;
         // OPR
         case 2:
               switch (code[ir].m)
               {
                 //RET
                  case 0:
                    sp = bp + 1;
                    pc = stack[sp-4];
                    bp = stack[sp-3];
                    inc[z] = 0;
                    z--;

                    if (vFlag == 1)
                    {
                      printf("%d\t%d\t%d\t", pc, bp, sp);
                      // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
                    }
                     // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
                    stack_printer(stack, bp, sp, inc, vFlag);//, outFile);

                    break;
                  //NEG
                  case 1:
                    stack[sp] = -stack[sp];

                    if (vFlag == 1)
                    {
                      printf("%d\t%d\t%d\t", pc, bp, sp);
                    }
                    // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
                    stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
                    break;
                  //ADD
                  case 2:
                   sp++;
                   stack[sp] = stack[sp] + stack[sp-1];
                   inc[z]--;

                   if (vFlag == 1)
                   {
                     printf("%d\t%d\t%d\t", pc, bp, sp);
                   }
                   // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
                   stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
                   break;
                  //SUB
                  case 3:
                   sp++;
                   stack[sp] = stack[sp] - stack[sp-1];
                   inc[z]--;

                   if (vFlag == 1)
                   {
                     printf("%d\t%d\t%d\t", pc, bp, sp);
                   }
                   // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
                   stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
                   break;
                  //MUL
                  case 4:
                   sp++;
                   stack[sp] = stack[sp] * stack[sp-1];
                   inc[z]--;

                   if (vFlag == 1)
                   {
                     printf("%d\t%d\t%d\t", pc, bp, sp);
                   }
                   // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
                   stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
                   break;
                  //DIV
                  case 5:
                   sp++;
                   stack[sp] = stack[sp] / stack[sp-1];
                   inc[z]--;

                   if (vFlag == 1)
                   {
                     printf("%d\t%d\t%d\t", pc, bp, sp);
                   }
                   // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
                   stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
                   break;
                  //ODD
                  case 6:
                   stack[sp] = stack[sp] % 2;
                   inc[z]--;

                   if (vFlag == 1)
                   {
                     printf("%d\t%d\t%d\t", pc, bp, sp);
                   }
                   // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
                   stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
                   break;
                  //MOD
                  case 7:
                   sp++;
                   stack[sp] = stack[sp] % stack[sp-1];
                   inc[z]--;

                   if (vFlag == 1)
                   {
                     printf("%d\t%d\t%d\t", pc, bp, sp);
                   }
                   // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
                   stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
                   break;
                  //EQL
                  case 8:
                   sp++;
                   stack[sp] = stack[sp] == stack[sp-1];
                   inc[z]--;

                   if (vFlag == 1)
                   {
                     printf("%d\t%d\t%d\t", pc, bp, sp);
                   }
                   // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
                   stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
                   break;
                  //NEQ
                  case 9:
                    sp++;
                    stack[sp] = stack[sp] != stack[sp-1];
                    inc[z]--;

                    if (vFlag == 1)
                    {
                      printf("%d\t%d\t%d\t", pc, bp, sp);
                    }
                    // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
                    stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
                    break;
                  //LSS
                  case 10:
                    sp++;
                    stack[sp] = stack[sp] < stack[sp-1];
                    inc[z]--;

                    if (vFlag == 1)
                    {
                      printf("%d\t%d\t%d\t", pc, bp, sp);
                    }
                    // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
                    stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
                    break;
                  //LEQ
                  case 11:
                    sp++;
                    stack[sp] = stack[sp] <= stack[sp-1];
                    inc[z]--;

                    if (vFlag == 1)
                    {
                      printf("%d\t%d\t%d\t", pc, bp, sp);
                    }
                    // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
                    stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
                    break;
                  //GTR
                  case 12:
                    sp++;
                    stack[sp] = (stack[sp] > stack[sp-1]);
                    inc[z]--;

                    if (vFlag == 1)
                    {
                      printf("%d\t%d\t%d\t", pc, bp, sp);
                    }
                    // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
                    stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
                    break;
                  //GEQ
                  case 13:
                    sp++;

                    stack[sp] = (stack[sp]>=stack[sp-1]);
                    inc[z]--;

                    if (vFlag == 1)
                    {
                      printf("%d\t%d\t%d\t", pc, bp, sp);
                    }
                    // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
                    stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
                    break;
               }
               // printf("2\n");
               break;
         // LOD
         case 3:
              sp--;
              stack[sp] = stack[base(code[ir].l, bp, stack)-code[ir].m];
              inc[z] += 1;

              if (vFlag == 1)
              {
                printf("%d\t%d\t%d\t", pc, bp, sp);
              }
              // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
              stack_printer(stack,bp, sp, inc, vFlag);//, outFile);
              break;
         // STO
         case 4:
              inc[z] -= 1;

              stack[base(code[ir].l, bp, stack)-code[ir].m] = stack[sp];
              sp++;

              if (vFlag == 1)
              {
                printf("%d\t%d\t%d\t", pc, bp, sp);
              }
              // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
              stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
              // printf("4\n");
              break;
         // CAL
         case 5:
              stack[sp - 1] = 0;                            //Return Value
              stack[sp - 2] = base(code[ir].l, bp, stack);  //Static Link
              stack[sp - 3] = bp;                           //Dynamic Link
              stack[sp - 4] = pc;                           //Return address
              bp = sp - 1;
              pc = code[ir].m;
              z++;

              if (vFlag == 1)
              {
                printf("%d\t%d\t%d\t", pc, bp, sp);
              }
              // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
              stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
              break;
         // INC
         case 6:
              sp = sp - code[ir].m;

              if (inc[z] != 0)
              {
                z++;
                inc[z] += code[ir].m;
              }
              else
              {
                inc[z] = code[ir].m;
              }

              if (vFlag == 1)
              {
                printf("%d\t%d\t%d\t", pc, bp, sp);
              }
              // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
              stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
              break;
         // JMP
         case 7:
              pc = code[ir].m;

              if (vFlag == 1)
              {
                printf("%d\t%d\t%d\t", pc, bp, sp);
              }
              // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
              stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
              // printf("7\n");
              break;
         // JPC
         case 8:
              if (stack[sp] == 0)
              {
                   pc = code[ir].m;
              }
              sp++;
              inc[z] -= 1;

              if (vFlag == 1)
              {
                printf("%d\t%d\t%d\t", pc, bp, sp);
              }
              // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
              stack_printer(stack, bp, sp, inc, vFlag);//, outFile);

              break;
         // SIO 0,1
         case 9:
              //print(stack[sp])
              sp++;

              if (vFlag == 1)
              {
              printf("%d\t%d\t%d\t", pc, bp, sp);
              for(int i = MAX_DATA_STACK_HEIGHT - 1; i >= sp; i--)
              {
                //fprintf(outFile, "%d ", stack[i]);
                printf("%d ", stack[i]);
              }
              // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
              // for(int i = MAX_DATA_STACK_HEIGHT - 1; i >= sp; i--)
              // {
              //   //fprintf(outFile, "%d ", stack[i]);
              // }
              }
              break;
         // SIO 0,2
         case 10:
              sp--;
              printf("\n");
              printf("Enter your number: ");
              scanf("%d", &stack[sp]);
              printf("\n");

              inc[z] += 1;
              if (vFlag == 1)
              {
                printf("%d\t%d\t%d\t", pc, bp, sp);
              }
              // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
              stack_printer(stack, bp, sp, inc, vFlag);//, outFile);
              break;
         // SIO 0,3
         case 11:
              // fprintf(outFile, "%d\t%d\t%d\t", pc, bp, sp);
              // for(int i = MAX_DATA_STACK_HEIGHT - 1; i >= sp; i--)
              // {
              //   // fprintf(outFile, "%d ", stack[i]);
              // }
              if (vFlag == 1)
              {
                printf("%d\t%d\t%d\t", pc, bp, sp);
                for(int i = MAX_DATA_STACK_HEIGHT - 1; i >= sp; i--)
                {
                  // fprintf(outFile, "%d ", stack[i]);
                  printf("%d ", stack[i]);
                }
              }
              halt = 0;
              break;
      }
      // fprintf(outFile, "\n");
      if (vFlag == 1)
      {
        printf("\n");
      }
   }

   // Closes each of the file that is being passed into the function
   // fclose(inFile);
   // fclose(outFile);


   return;
}

int base( int l, int base, int * stack) // l stand for L in the instruction format
{
  int b1; //find base L levels down
  b1 = base;
  while (l > 0)
  {
    b1 = stack[b1-1];
    l--;
  }
  return b1;
}
