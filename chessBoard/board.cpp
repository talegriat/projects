#include "board.h"


#include <iostream>
#include <list>

#include <fcntl.h>
using namespace std;
#define BLACK true
#define WHITE false


int main(){
    Board b;
    GameFile g;
    string wMove;
    string bMove;
    //lower -- black
    //upper White
    //<FEN> ::=  <Piece Placement>
    //   ' ' <Side to move>
    //   ' ' <Castling ability>
    //   ' ' <En passant target square>
    //   ' ' <Halfmove clock>
    //   ' ' <Fullmove counter>
/****
**  1 -- Validate  moves and affect  Fen castling and passant status
**      1.1 solve d4 kind of moves...... processWhiteMove
            1.1.1   create an array with the pawns and other with pieces
            1.1.2   ask each pawn if they can reach the target cell
        1.2 solve Nc3
            1.2.1   ask each pawn or iece if they can reach the target cell
            1.2.2   check if more than one pawn/piece can reach the same spot
        1.3 solve d3xe3, Nxc3
            1.3.1 validarte target cell is not empty and ocupied by an opposite clolor piece
            1.3.2 mark captured piece as out of the board
        1.4 affect castling when moving King or rook
        1.5 K castle (validate and affect FEN)
        1.6 validate for discovery checks before moving
        1.7 validate for check before moving
        1.8 evaluate opposite king check after moving
        1.9 create cell domination heatmap
        1.10 create king safety map
        1.11 create mobility heatmap 

**  4 -- Genearate position evaluation --- number from 1 to 10
**  
****/

    cout<<b<<endl;
    /*
    cout<<"White to Move: ";
    cin >> wMove;
    b.moveWhite(wMove);
    cout<<endl;
    cout<<b<<endl;
    cout<<"Black to Move: ";h
    h

    cin >> bMove;
    b.moveBlack(bMove);
    cout<<endl;
    cout<<b<<endl;
    cout<<b.getFENString();
    cout<<endl;
    */
    g.processFile("./game.pgn");
    cout<<g.moveList()<<endl;
    
    g.parseMoves();
    list<GameMove> l=g.getGameMoves();
    list<GameMove>::iterator i=l.begin();
    //b.initBoard(); // ----IMPORTANT - 20221231 --- Calling it twice cleans the board, but duplicates the number of pieces!!!!

    cout<<b<<endl;
    //cout<<"press enter key to continue...";
    //cin >> wMove;
    GameMove m;
    while (i != l.end()){
        //b.moveWhite((*i)->whiteMove()); 
        //cout<<b<<endl;
        //
        if ((i)->getMoveNumber()>0){
            cout<<(i)->getMoveNumber()<<". "<<(i)->getWhiteMove()<<" - "<<(i)->getBlackMove()<<endl;  
            GameMove gm=*i;          
            b.processWhiteMove(&gm);
            if (b.getEnPassantSide()=='B'){
                b.setEnPassantSide(' ');
            }
            cout<<b<<endl;
            b.processBlackMove(&gm);
            if (b.getEnPassantSide()=='W'){
                b.setEnPassantSide(' ');
            }
            cout<<b<<endl;
            //cout<<"press enter key to continue...";
            //cin >> wMove;
        } else {
            cout<<(i)->getFullResult()<<endl;  
        }
     


        ++i;
    }
}


int test(){
    
    
    /*
    struct Cell* n=buildRows();
    struct Cell* a1=n;
    struct Cell* m=NULL;
    char col=(n)->column;
    
    Color::Modifier WF(Color::FG_RED);
    Color::Modifier DF(Color::FG_DEFAULT);
    Color::Modifier BF(Color::FG_BLUE);
    Color::Modifier WB(Color::BG_YELLOW);
    Color::Modifier DB(Color::BG_DEFAULT);
    Color::Modifier BB(Color::BG_GREEN);
    //cout << "This ->" << red << "word" << def << "<- is red." << endl;
    
    while (n){
        m=(n)->f;
        while ( col <='H' ) {
            cout<<((n)->black? BB:WB)<<((n)->black? BF:WF)<<(n)->column<<(n)->row<<DF<<DB<<" ";
            if ((n)->r){
                n=(n)->r;
                col=(n)->column;
            } else  {
                col='I';
            } 

        }
        cout<<endl;
        n=m;
        if (n)
            col=(n)->column;




    }
    
    int x=b.initBoard("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 39 201 ");
    cout<<b;
    x=b.initBoard("8/8/8/8/8/8/8/8 b KQkq - 1 2 ");
    cout<<b;
    x=b.initBoard("rnbqkbnrr/ppppppppp/88/8p6/4P3/5N2/PPPP2PPP/RNBQKB2R b KQkq e3 49 105 ");
    cout<<b;
    x=b.initBoard("xxxxxxrnbqkbnxrr/ppppppppp/88/2p6/4P3/5N2/PPPP2PPP/RNBQKB2R b - - 1 2 ");
    cout<<b;
    x=b.initBoard("rnbqkbnr/ppppppppp/8/8/8/8/ppppppppp/RNBQKBNR w KQkq - 0 1 ");
    cout<<b<<endl;
    cout<<b.getFENString();
    cout<<endl;

    x=b.initBoard("rnbqkbn1/2ppppppp/8/8/8/pppp4/ppppppppp/RNBQKB2 w KQkq - 0 1 ");
    
    */
// _setmode(_fileno(stdout), _O_U16TEXT);
//int WK = '♛';
//char *s  = u8"\u2654";
//cout<<BB<<BF<<" "<<s<<"  "<<DF<<DB<<endl;    
return 0;
}