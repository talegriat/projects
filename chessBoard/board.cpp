#include "board.h"


#include <iostream>
#include <list>

#include <fcntl.h>
using namespace std;
#define BLACK true
#define WHITE false

void processGame(list<GameMove> l){
    Board b;
    list<GameMove>::iterator i=l.begin();
    string wMove;
    string bMove;
    GameMove m;
    while (i != l.end()){
        //b.moveWhite((*i)->whiteMove()); 
        //cout<<b<<endl;
        //
        if ((i)->getMoveNumber()>0){
            cout<<(i)->getMoveNumber()<<". "<<(i)->getWhiteMove()<<endl;  
            GameMove gm=*i;          
            b.processWhiteMove(&gm);
            if (b.getEnPassantSide()=='B'){
                b.setEnPassantSide(' ');
                b.passant[0]='-';
                b.passant[1]='-';
            }
            cout<<b<<endl;
            b.whiteToMove=false;
            cout<<(i)->getMoveNumber()<<". "<<(i)->getWhiteMove()<<" - "<<(i)->getBlackMove()<<endl;  
            b.processBlackMove(&gm);
            if (b.getEnPassantSide()=='W'){
                b.setEnPassantSide(' ');
                b.passant[0]='-';
                b.passant[1]='-';
            }
            cout<<b<<endl;
            b.whiteToMove=true;
            //cout<<"press enter key to continue...";
            //cin >> wMove;
        } else {
            cout<<(i)->getFullResult()<<endl;  
        }
     


        ++i;
    }
}



int main(){

    GameFile g;

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
        1.5 add move counter
        1.5.1 add half move counter since last capture
        1.6 validate for discovery checks before moving
        1.7 validate for check before moving
        1.8 evaluate opposite king check after moving
        1.9 create cell domination heatmap
        1.10 create king safety map
        1.11 create mobility heatmap 

**  4 -- Genearate position evaluation --- number from 1 to 10
**  
****/

    g.processFile("./game.pgn");
    //cout<<g.moveList()<<endl;
    
    while (g.hasMoreGames()){
        cout<<g.currentGame()<<endl;
        list<GameMove> l=g.getNextGameMoves();
        processGame(l);

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