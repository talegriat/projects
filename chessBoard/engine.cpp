#include <iostream>
//#include <iomanip>
#include <cstring>
//#include <cstdlib>
//#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
//#include <signal.h>
//#include <string>
using namespace std;

/* Material values */
#define ValueP   100
#define ValueN   350
#define ValueB   350
#define ValueR   550
#define ValueQ   1100
#define ValueK   2000

enum Piece { empty, pawn, knight, bishop, rook, queen, king, bpawn };

enum Square { A1, B1, C1, D1, E1, F1, G1, H1,
	      A2, B2, C2, D2, E2, F2, G2, H2,
	      A3, B3, C3, D3, E3, F3, G3, H3,
	      A4, B4, C4, D4, E4, F4, G4, H4,
	      A5, B5, C5, D5, E5, F5, G5, H5,
	      A6, B6, C6, D6, E6, F6, G6, H6,
	      A7, B7, C7, D7, E7, F7, G7, H7,
	      A8, B8, C8, D8, E8, F8, G8, H8 };

enum File { A_FILE, B_FILE, C_FILE, D_FILE, E_FILE, F_FILE, G_FILE, H_FILE };


int Value[7] = { 0, ValueP, ValueN, ValueB, ValueR, ValueQ, ValueK};
int ptype[2] = { pawn, bpawn };
char algbr[64][3] =
{ "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
  "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
  "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
  "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
  "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
  "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
  "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
  "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"
};
char algbrfile[9] = "abcdefgh";
char algbrrank[9] = "12345678";

char notation[8] = { " PNBRQK" };
char lnotation[8] = { " pnbrqk" };


void ShowClassicalBoard(const char *boardmap)
{
  unsigned i = 0;
  const char column[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  unsigned row = 8;
  
  for (i =0; i < MAX_BOARD_RANGE; ++i) {
    if ((i >= 0) && (i % 8 == 0)) {
      fprintf(ofp, "\n");
    
      if ( coords == 1 ) {
        if (row >=1)
          fprintf(ofp, "%d ", row--);
        else
          break;
      }
    
    }

    fprintf(ofp, "%c ", boardmap[i]);
  }
  
  if ( coords == 1 ) {
    fprintf(ofp, "  ");
    for (i = 0; i < 8; ++i) {
      fprintf(ofp, "%c ", column[i]);
    }
  }
}


void ShowCBoard (void)
/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
{
   int r, c;

   for (r = 56; r >= 0; r -= 8)
   {
      for (c = 0; c < 8; c++)
      {
         printf ("%2c ", cboard[r + c] ? notation[cboard[r+c]] : '.');
      }
      printf ("\n");
   }
   printf ("\n");
}


void ShowMvboard (void)
/*****************************************************************************
 *
 *  Print the Mvboard[] array.
 *
 *****************************************************************************/
{
   int r, c;

   for (r = 56; r >= 0; r -= 8)
   {
      for (c = 0; c < 8; c++)
      {
         printf ("%2d ", Mvboard[r + c]);
      }
      printf ("\n");
   }
   printf ("\n");
}




  int main()
{
    InitBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR")
    showInitialBoard();
    for (;;){
 
        cin>>buf2;
        char bufx[buf2.length() + 1]; 
        strcpy(bufx, buf2.c_str()); 
        cnt=strlen(bufx);
        bufx[cnt]='\n';
        if (bufx[0]!='.')
            showBoard(bufx);
    }

    return 0;
}