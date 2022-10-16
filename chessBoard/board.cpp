#include "board.h"
#include <iostream>

#include <fcntl.h>
using namespace std;
#define BLACK true
#define WHITE false


int main(){
    Board b;
    //lower -- black
    //upper White
    //<FEN> ::=  <Piece Placement>
    //   ' ' <Side to move>
    //   ' ' <Castling ability>
    //   ' ' <En passant target square>
    //   ' ' <Halfmove clock>
    //   ' ' <Fullmove counter>
/****
**  1 -- read Moves for both black and white
**  2 -- Validate  moves and affect  Fen castling and passant status
**  3 -- Genearate position evaluation --- number from 1 to 10
**  
****/

    cout<<b<<endl;
    cout<<b.getFENString();
    cout<<endl;

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