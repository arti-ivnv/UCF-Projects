/*
 Artem Ivanov
 Assignment 5
 7/27/17
 COP 3223
 */


// Libruary declaration
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constant statements
// Shows how many card suits do we have in numbers
#define SUITS 4
// Shows how many
#define FACES 13
#define POSSIBLE 0
#define USED 1
// Hand size
#define SIZE 5
#define TRUE 1
#define FALSE 0

// Declaration of the functions
// Randomise the cards
void Card_deal(char *suits[], char *faces[], int deck[][FACES], int *player_pref);
// Does hands'(players') preferences and shows names of the cards (Ace of Hearts)
void Hand_deal(char *suits[], char *faces[], int deck[][FACES], int player[][2]);
// Counts specific suit and face of the cards
void Counter(int suits_Hand[], int faces_Hand[], int player[][2]);
// Analyzes what kind of combination do we have and helps to wining array choose a winner
int analyze(int suitsInHand[], int facesInHand[]);

int main()
  {
      char *suits[4] = {"Hearts", "Diamonds", "Spades", "Clubs" };
      char *faces[13] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
      // Controls that the same card would not be capable to repeat
      int deck[4][13] = { POSSIBLE };
      int faces_Hand[FACES], suits_Hand[SUITS];
      // Keeps the hand(player)
      int player[SIZE][2];
      // Keeps the score to find a winner
      int winner[2];
      int i;

      // Random prerequirment (every time new random numbers)
      srand(time(NULL));

      for(i = 0; i < 2; i++)
        {
          Hand_deal(suits,faces,deck,player);
          Counter(suits_Hand, faces_Hand, player);
          // Takes the results of analyzing to find a winner
          winner[i] = analyze(suits_Hand, faces_Hand);
        }

      // Comparing of the scores and results
      if (winner[0] > winner[1])
        {
          printf("First player won!\n");
        }
      else if (winner[0] < winner[1])
        {
          printf("Second player won\n");
        }
      else
        {
          printf("Tie! Freindship won!\n");
        }
    }

    void Hand_deal(char *suits[], char *faces[], int deck[][FACES], int player[][2])
      {
        int player_pref[2];
        int i;

        // Gives to two playrs random cards
        for (i = 0; i < 5; i++)
          {
            Card_deal(suits, faces, deck, player_pref);
            player[i][0]=player_pref[0];
            player[i][1]=player_pref[1];
          }
        printf("\n");
      }

    // Creating random card
    void Card_deal(char *suits[], char *faces[], int deck[][FACES], int *player_pref)
      {
        int face_ind, suit_ind;

        face_ind = rand() % 13;
        suit_ind = rand() % 4;

        while (deck[suit_ind][face_ind] == USED)
          {
            suit_ind = rand() % 4;
            face_ind = rand() % 13;
          }

        player_pref[0] = face_ind;

        player_pref[1] = suit_ind;

        deck[suit_ind][face_ind] = USED;

        printf("%s of %s \n", faces[face_ind], suits[suit_ind]);
      }

    void Counter(int suits_Hand[], int faces_Hand[], int player[][2])
      {
        int i;

        // Nullifies our card suits and faces
        for (i=0;i<4;i++)
          {
            suits_Hand[i]=0;
          }
        for (i=0;i<13;i++)
          {
            faces_Hand[i]=0;
          }

        // Counts how many does the player has specific suits and faces
        for (i = 0; i < 5; i++)
          {
            faces_Hand[player[i][0]]++;
            suits_Hand[player[i][1]]++;
          }

        // Print out results of counting
          for(i = 0; i < 4; i++)
            {
              printf("%d", suits_Hand[i]);
            }
          printf("\n");

          for(i = 0; i < 13; i++)
            {
              printf("%d", faces_Hand[i]);
            }
          printf("\n\n");
      }

      // Given funtin that helps us to analyze combinations
      int analyze(int suits_Hand[], int faces_Hand[])
        {
          int num_consec = 0;
          int rank, suit;
          // Integer thar will show combination rate
          int comb_rate = 0;
          int straight, flush, four, three,pairs;

          straight = FALSE;
          flush = FALSE;
          four = FALSE;
          three = FALSE;
          pairs = 0;

          // Checking for flash
          for (suit = 0; suit < SUITS; suit++)
              if (suits_Hand[suit] == 5)
              flush = TRUE;

          // Checks for straight - eg. One each of 5,6,7,8,9
          // Locate the first card
          rank = 0;
          while (faces_Hand[rank] == 0)
            rank++;

          // Counts the consecutive non-zero faces
          for (; rank < FACES && faces_Hand[rank]; rank++)
            num_consec++;

          if (num_consec == 5)
            {
              straight = TRUE;
            }

          // Checks for 4-of-a-kind, 3-of-a-kind, and pairs
          for (rank = 0; rank < FACES; rank++)
            {
              if (faces_Hand[rank] == 4)
                four = TRUE;
              if (faces_Hand[rank] == 3)
                three = TRUE;
              if (faces_Hand[rank] == 2)
                pairs++;
            }

          if (straight && flush)
            {
              printf("Straight flush\n\n");
              comb_rate = 8;
            }
          else if (four)
            {
              printf ("Four of a kind\n\n");
              comb_rate = 7;
            }
          else if (three && pairs == 1)
            {
              printf ("Full house\n\n");
              comb_rate = 6;
            }
          else if (flush)
            {
              printf ("Flush\n\n");
              comb_rate = 5;
            }
          else if (straight)
            {
              printf ("Straight\n\n");
              comb_rate = 4;
            }
          else if (three)
            {
              printf ("Three of a kind\n\n");
              comb_rate = 3;
            }
          else if (pairs == 2)
            {
              printf ("Two pairs\n\n");
              comb_rate = 2;
            }
          else if (pairs == 1)
            {
              printf("Pair\n\n");
              comb_rate = 1;
            }
          else
            {
              printf("High card\n\n");
              comb_rate = 0;
            }
          return comb_rate;
        }
