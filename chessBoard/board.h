#include "colormod.h" // namespace Color
#include <iostream>
#include <string>       // std::string
#include <sstream>      // std::stringbuf
using namespace std;
#define BLACK true
#define WHITE false


struct Cell{
    bool empty=true;
    bool black=true; 
    char column=' '; // a to f
    int row=0;  //1 to 8
    //char *s  = u8"\u2654"
    char piece='_';
    bool blackPiece=false;
    struct Cell* l=NULL;
    struct Cell* r=NULL;
    struct Cell* f=NULL;
    struct Cell* b=NULL;
    struct Cell* lf=NULL;
    struct Cell* lb=NULL;
    struct Cell* rf=NULL;
    struct Cell* rb=NULL;
    
};

class Board {

    struct Cell *fenArray[64];
    void initCells();
    void buildColumn(Cell* );
    void linkColumns(Cell* , Cell*);
    struct Cell* buildRows();
    struct Cell* getCell(char , int , bool );
    
    void buildFENArray();

    char* getChessPiece(char );
    bool whiteToMove=true;
    char wCastling='B';  //B=Both; K=king side,Q=Queenside
    char bCastling='b';  //b=Both; k=king side,q=Queenside
    char passant[2];
    int halfMove=0;
    int fullMoves=1;

    

public:
    struct Cell* a1;
    struct Cell* a8;
    Board();
    std::string printBoard();
    friend ostream& operator<<(std::ostream& os, Board b) { return os << b.printBoard();   }
    int initBoard(std::string  ) ;
    string getFENString();

};


Board::Board(){
    struct Cell* n=buildRows();
    a1=n;
    initBoard("rnbqkbnr/ppppppppp/8/8/8/8/ppppppppp/RNBQKBNR w KQkq - 0 1 ");
    buildFENArray();
}

struct Cell* Board::getCell(char col, int i, bool bl){
    struct Cell* a1=new Cell;
    (a1)->black=bl;
    (a1)->row=i;
    (a1)->column=col;
    return (a1);
}

void Board::buildColumn(struct Cell* c){
    while ((c)->row <8 ){
        struct Cell* n=new Cell;
        (n)->column=(c)->column;
        (n)->row=(c)->row+1;
        (n)->black=!(c)->black;
        (n)->b=c;
        (c)->f=n;
        c=n;
    }
   
    if ((c)->column=='a'){
        a8=c;
    }

}   

void Board::linkColumns(Cell* prev, Cell*c){
    struct Cell* current=NULL;
    struct Cell*  previous=NULL;
    struct Cell*  cf=NULL;
    struct Cell*  pf=NULL;
    struct Cell*  cb=NULL;
    struct Cell*  pb=NULL;
    
    current=c;
    previous=prev;
    int i=(current)->row; 
    while (i <9 ){
        (current)->l=previous;
        (previous)->r=current;
        
        //
        cf=(current)->f;
        cb=(current)->b;
        pf=(previous)->f;
        pb=(previous)->b;
        if (cf!=NULL  ){
            (current)->lf=pf;
            (current)->lb=pb;
            (previous)->rf=cf;
            (previous)->rb=cb;

            (cf)->lb=prev;
            (pf)->rb=current;
        } else {
            (current)->lf=pf;
            (current)->lb=pb;
            (previous)->rf=cf;
            (previous)->rb=cb;
        }
        //


        current=(current)->f;
        previous=(previous)->f;
        i++;
    }
}

struct Cell* Board::buildRows(){
    struct Cell* a1=NULL;

    bool cl=BLACK;
    char col='a';
    struct Cell* prev=NULL;
    while (col <='h'){
        struct Cell* c = getCell(col,1, cl);
        buildColumn(c);
        col=(char)col+1;
        cl=!cl;
        if (prev){
            linkColumns(prev,c);
        }else{
            a1=c;
        }
        prev=c;
    }
    return a1;
}   

std::string Board::printBoard() {
    std::string buffer;
    struct Cell* m;
    char col=' ';
    stringstream aux;
    Color::Modifier WF(Color::FG_RED);
    Color::Modifier DF(Color::FG_DEFAULT);
    Color::Modifier BF(Color::FG_BLUE);
    Color::Modifier WB(Color::BG_WHITE);
    Color::Modifier DB(Color::BG_DEFAULT);
    Color::Modifier BB(Color::BG_BLACK);
    //cout << "This ->" << red << "word" << def << "<- is red." << endl;
    struct Cell* n=a8;
    
    buffer+=(whiteToMove? "White to move \n":"Black to Move \n");
    switch (wCastling) {
        case 'B' :
            buffer+= "White can castle on K  and Q sides \n";
            break;
        case 'n':
            buffer+= "white can't castle\n";
            break;
        case 'K':
            buffer+= "white can castle on K side\n";
            break;
        case 'Q':   //B=Both; K=king side,Q=Queenside
            buffer+= "white can castle on Q sides \n";
            break;
        default:
            break;
    }
    switch (bCastling) {
        case 'b' :
            buffer+= "Blak can castle on K  and Q sides \n";
            break;
        case 'n':
            buffer+= "Black can't castle\n";
            break;
        case 'k':
            buffer+= "Black can castle on K side\n";
            break;
        case 'q':   //B=Both; K=king side,Q=Queenside
            buffer+= "Black can castle on K  and Q sides \n";
            break;
        default:
            break;
    }
    buffer+=" Passant: ";
    buffer+= passant;
    buffer+=" Half moves:";
    aux << halfMove;
    buffer +=aux.str();
    buffer+=" Game moves:";
    aux.str("");
    aux << fullMoves;
    buffer +=aux.str();
    buffer+="\n";
      
    
    
    while (n){
        m=(n)->b;
        col=(n)->column;
        while ( col <='h' ) {
            buffer+=((n)->black? BB.str():WB.str());
            buffer+=((n)->blackPiece? BF.str():WF.str());
            //buffer+=" ";
            buffer+=getChessPiece((n)->piece);
            buffer+=" ";
            //buffer+= to_string((n)->row)  ;
            buffer+=DF.str();
            buffer+=DB.str();
            //buffer+=" ";
            if ((n)->r){
                n=(n)->r;
                col=(n)->column;
            } else  {
                col='i';
            } 
        }
        buffer+="\n";
        n=m;
    }
    // _setmode(_fileno(stdout), _O_U16TEXT);
    //int WK = '♛';
    buffer+="\n"; 
    return buffer;
}

void Board::buildFENArray( ){
    struct Cell *current=a8;
    struct Cell *nextRank=(current)->b;
    for (int i=0 ; i<64 ; i++){
        fenArray[i]=current;
        if ((current)->r){
            current=(current)->r;
        }else if(nextRank){
            current=nextRank;
            nextRank=(current)->b;
        }

    }
} 

string Board::getFENString(){
    string fenString;

    struct Cell *current=a8;
    struct Cell *nextRank=(current)->b;
    int emptyCells=0;
    for (int i=0 ; i<64 ; i++){
        stringstream aux;
        if (fenArray[i]->piece!=' '){
            if (emptyCells==0){
                fenString+=fenArray[i]->piece;
            }else{
                aux<< emptyCells; 
                fenString+=aux.str();
                fenString+=fenArray[i]->piece;
                emptyCells=0;
            }
        } else {
            emptyCells++;
        }
        if (((i+1)%8)==0 ){
            if (emptyCells==0){
                fenString+= ((i==63)? " ":"/") ;
            }else{
                aux<< emptyCells; 
                fenString+=aux.str();
                fenString+= ((i==63)? " ":"/") ;
                emptyCells=0;
            }
        }

    }
    fenString+= (whiteToMove? "w ":"b ") ;

    switch (wCastling) {
        case 'B' :
            fenString+= "KQ";
            break;
        case 'n':
            break;
        case 'K':
            fenString+= "K";
            break;
        case 'Q':   //B=Both; K=king side,Q=Queenside
            fenString+= "Q";
            break;
        default:
            break;
    }
    switch (bCastling) {
        case 'b' :
            fenString+= "kq ";
            break;
        case 'n':
            fenString+= "- ";
            break;
        case 'k':
            fenString+= "k ";
            break;
        case 'q':   //B=Both; K=king side,Q=Queenside
            fenString+= "q ";
            break;
        default:
            break;
    }
    fenString+= passant;
    stringstream hm;
    hm<< halfMove; 
    fenString+=hm.str();
    fenString+=" ";
    stringstream fm;
    fm<< fullMoves; 
    fenString+=fm.str();

    //halfMove=0;
    //fullMoves=1;
    return fenString;
}


   //lower -- black
    //upper White
    //starts at Rank 8
    //starts at column a
    //<FEN> ::=  <Piece Placement>
    //   ' ' <Side to move>
    //   ' ' <Castling ability>
    //   ' ' <En passant target square>
    //   ' ' <Halfmove clock>
    //   ' ' <Fullmove counter>
    //    "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2 "
int Board::initBoard(std::string bp )  {
    if (bp==""){
        return 1;
    }
    bool piecesComplete=false;
    bool sideToMoveComplete=false;
    bool castlingComplete=false;
    bool passantComplete=false;
    bool halfMoveComplete=false;
    bool fullMovesComplete =false;
    struct Cell* current=a8;
    struct Cell* nextRank=(current)->b;
    string whitePieces="RNBQKP";
    string blackPieces="rnbqkp";
    string numbers="12345678";
    char arr[2];
    char col='-';
    char row=' ';
    char halfMoverArr[2];
    halfMoverArr[0]=' ';
    halfMoverArr[1]=' ';
    char fullMoverArr[3];
    fullMoverArr[0]=' ';
    fullMoverArr[1]=' ';
    fullMoverArr[2]=' ';
    whiteToMove=true;
    wCastling='B';  //B=Both; K=king side,Q=Queenside
    bCastling='b';  //b=Both; k=king side,q=Queenside
    passant[0]='-';
    passant[1]='-';
    halfMove=0;
    fullMoves=1;

    int i=0;
    for(std::string::iterator it = bp.begin(); it != bp.end(); ++it) {

        int x=0;
        stringstream aux;
        if (!piecesComplete){
            if( *it!=' '){
                if( *it=='/'){
                    current=nextRank;
                    nextRank=(current)->b;
                } else{
                    // check we have not reached the end of the board
                    if (current!=NULL){
                        if (whitePieces.find(*it) != string::npos ) {
                            (current)->blackPiece=false;
                            (current)->piece=*it;
                            current=(current)->r;
                        }
                        if (blackPieces.find(*it) != string::npos ) {
                            (current)->blackPiece=true;
                            (current)->piece=*it;
                            current=(current)->r;
                        }
                        if (numbers.find(*it) != string::npos ){
                            aux<< *it; 
                            aux >> x;
                            while (x>0 & current!=NULL){
                                (current)->blackPiece=false;
                                (current)->piece=' ';
                                current=(current)->r;
                                x--;
                            }
                        }
                    }
                }

            } else {
                piecesComplete=true;
                ++it;
            }
        }
        if (piecesComplete & !sideToMoveComplete){
             if( *it!=' '){
                 switch (*it)  {
                    case 'w':         
                        whiteToMove=true;
                        break;
                    case 'b':         
                        whiteToMove=false;
                        break;
                    case 'W':         
                        whiteToMove=true;
                        break;
                    case 'B':         
                        whiteToMove=false;
                        break;
                    default:
                        whiteToMove=true;
                        break;
                }

            } else {
                sideToMoveComplete=true;
                ++it;
            }
        }
        if (sideToMoveComplete & !castlingComplete){
             if( *it!=' '){
                 switch (*it)  {
                    case '-':         
                        wCastling='n';  //B=Both; K=king side,Q=Queenside;N=none
                        bCastling='n';  //b=Both; k=king side,q=Queenside;N=none
                        break;
                    case 'K':         
                        wCastling='K';
                        break;
                    case 'Q': 
                        if   (wCastling='K'){      
                            wCastling='B';
                        } else {
                            wCastling='Q';
                        }
                    break;
                    case 'k':         
                        bCastling='k';
                        break;
                    case 'q':         
                        if   (bCastling='k'){      
                            bCastling='b';
                        } else {
                            bCastling='q';
                        }
                        break;
                    default:
                        break;
                }

            } else {
                castlingComplete=true;
                ++it;
            }
        }
        if (castlingComplete & !passantComplete){
             if( *it!=' '){
                 switch (*it)  {
                    case 'a':
                        col='a';         
                    break;
                    case 'b':         
                        col='b';         
                    break;
                    case 'c':         
                        col='c';         
                    break;
                    case 'd':         
                        col='d';         
                    break;
                    case 'e':         
                        col='e';         
                    break;
                    case 'f':         
                        col='f';         
                    break;
                    case 'g':         
                        col='g';         
                    break;
                    case 'h':         
                        col='h';         
                    break;
                    case '3':         
                        row='3';         
                    break;
                    case '6':         
                        row='6';         
                    break;
                default:
                    break;
                }

            } else {
                passant[0]=col;
                passant[1]=row;
                passantComplete=true;
                ++it;
            }
        }
        if (passantComplete & !halfMoveComplete){

             if( *it!=' '){
                 switch (*it)  {
                    case '0':
                        if (i<2){
                            halfMoverArr[i++]='0';
                        }         
                    break;
                    case '1':         
                        if (i<2){
                            halfMoverArr[i++]='1';
                        }         
                    break;
                    case '2':         
                        if (i<2){
                            halfMoverArr[i++]='2';
                        }         
                    break;
                    case '3':         
                        if (i<2){
                            halfMoverArr[i++]='3';
                        }         
                    break;
                    case '4':         
                        if (i<2){
                            halfMoverArr[i++]='4';
                        }         
                    break;
                    case '5':         
                        if (i<2){
                            halfMoverArr[i++]='5';
                        }         
                    break;
                    case '6':         
                        if (i<2){
                            halfMoverArr[i++]='6';
                        }         
                    break;
                    case '7':         
                        if (i<2){
                            halfMoverArr[i++]='7';
                        }         
                    break;
                    case '8':         
                        if (i<2){
                            halfMoverArr[i++]='8';
                        }         
                    break;
                    case '9':         
                        if (i<2){
                            halfMoverArr[i++]='9';
                        }         
                    break;
                default:
                    break;
                }

            } else {
                aux<< halfMoverArr; 
                aux >> x;
                halfMove=x;
                halfMoveComplete=true;
                i=0;
                ++it;
            }
        }
        if (halfMoveComplete & !fullMovesComplete){

             if( *it!=' '){
                 switch (*it)  {
                    case '0':
                        if (i<3){
                            fullMoverArr[i++]='0';
                        }         
                    break;
                    case '1':         
                        if (i<3){
                            fullMoverArr[i++]='1';
                            aux<< fullMoverArr; 
                            aux >> x;
                            fullMoves=x;
                        }         
                    break;
                    case '2':         
                        if (i<3){
                            fullMoverArr[i++]='2';
                            aux<< fullMoverArr; 
                            aux >> x;
                            fullMoves=x;
                        }         
                    break;
                    case '3':         
                        if (i<3){
                            fullMoverArr[i++]='3';
                            aux<< fullMoverArr; 
                            aux >> x;
                            fullMoves=x;
                        }         
                    break;
                    case '4':         
                        if (i<3){
                            fullMoverArr[i++]='4';
                            aux<< fullMoverArr; 
                            aux >> x;
                            fullMoves=x;
                        }         
                    break;
                    case '5':         
                        if (i<3){
                            fullMoverArr[i++]='5';
                            aux<< fullMoverArr; 
                            aux >> x;
                            fullMoves=x;
                        }         
                    break;
                    case '6':         
                        if (i<3){
                            fullMoverArr[i++]='6';
                            aux<< fullMoverArr; 
                            aux >> x;
                            fullMoves=x;
                        }         
                    break;
                    case '7':         
                        if (i<3){
                            fullMoverArr[i++]='7';
                            aux<< fullMoverArr; 
                            aux >> x;
                            fullMoves=x;
                        }         
                    break;
                    case '8':         
                        if (i<3){
                            fullMoverArr[i++]='8';
                            aux<< fullMoverArr; 
                            aux >> x;
                            fullMoves=x;
                        }         
                    break;
                    case '9':         
                        if (i<3){
                            fullMoverArr[i++]='9';
                            aux<< fullMoverArr; 
                            aux >> x;
                            fullMoves=x;
                        }         
                    break;
                default:
                    break;
                }

            } else {
                aux<< fullMoverArr; 
                aux >> x;
                fullMoves=x;
                fullMovesComplete=true;
            }
        }
    }

    return 0;
}

char* Board::getChessPiece(char p) {
    char *r;
    switch (p)  {
    case 'p':
        r=(char *)u8"\u265F"; //
        break;
    case 'r':
        r=(char *)u8"\u265C";
        break;
    case 'n':
        r=(char *)u8"\u265E";
        break;
    case 'b':
        r=(char *)u8"\u265D";
        break;
    case 'q':
        r=(char *)u8"\u265B";
        break;
    case 'k':
        r=(char *)u8"\u265A";
        break;
    case 'P':
        r=(char *)u8"\u2659";
         r=(char *)u8"\u265F"; //
        break;
    case 'R':
        r=(char *)u8"\u2656";
        r=(char *)u8"\u265C";
        break;
    case 'N':
        r=(char *)u8"\u2658";
        r=(char *)u8"\u265E";
        break;
    case 'B':
        r=(char *)u8"\u2657";
        r=(char *)u8"\u265D";
        break;
    case 'Q':
        r=(char *)u8"\u2655";
        r=(char *)u8"\u265B";
        break;
    case 'K':
        r=(char *)u8"\u2654";
        r=(char *)u8"\u265A";
        break;

    default:
         r=(char *)" ";   
         break;
    }
    return r;
}



class Piece {
    struct Cell initialCell;
    struct Cell currentCell;
    bool onBoard=false;
    bool withOpenColumn=false;
    bool withOpenRank=false;
    bool withOpenFRD=false;
    bool withOpenFLD=false;
    bool withOpenBRD=false;
    bool withOpenBLD=false;
    bool alreadyMoved=false;
    bool nextToKing=false;
    bool protectingPiece=false;
    bool coveringOtherPiece=false;
    bool coveringKing=false;
    bool blockingCheck=false;
    bool above5thRank=false;
    bool attackinglowerPiece=false;
    bool attackingSimilarPiece=false;
    bool attackingHigherPiece=false;

public:
    Piece();    
    
}
class Board {

    struct Cell *fenArray[64];
    void initCells();
    void buildFENArray();

    int fullMoves=1;

    

public:
    struct Cell* a1;
    Board();
    int initBoard(std::string  ) ;
    
};