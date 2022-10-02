#include "colormod.h" // namespace Color
#include <iostream>
#include <string>       // std::string
#include <sstream>      // std::stringbuf
using namespace std;
#define BLACK true
#define WHITE false


struct Cell{
    bool occupied=false;
    bool black=true; 
    char column=' '; // a to f
    int row=0;  //1 to 8
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

    struct Cell cells[64];
    void initCells();
    void buildColumn(Cell* );
    void linkColumns(Cell* , Cell*);
    struct Cell* buildRows();
    struct Cell* getCell(char , int , bool );

    

public:
    struct Cell* a1;
    Board();
    std::string printBoard();
    friend ostream& operator<<(std::ostream& os, Board b) { return os << b.printBoard();   }

};


Board::Board(){
    struct Cell* n=buildRows();
    a1=n;
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
    char col='A';
    struct Cell* prev=NULL;
    while (col <='H'){
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
    Color::Modifier WF(Color::FG_RED);
    Color::Modifier DF(Color::FG_DEFAULT);
    Color::Modifier BF(Color::FG_BLUE);
    Color::Modifier WB(Color::BG_YELLOW);
    Color::Modifier DB(Color::BG_DEFAULT);
    Color::Modifier BB(Color::BG_GREEN);
    //cout << "This ->" << red << "word" << def << "<- is red." << endl;
    struct Cell* n=a1;
    while (n){
        m=(n)->f;
        col=(n)->column;
        while ( col <='H' ) {
            buffer+=((n)->black? BB.str():WB.str());
            buffer+=((n)->black? BF.str():WF.str());
            buffer+=(n)->column;
            buffer+= to_string((n)->row)  ;
            buffer+=DF.str();
            buffer+=DB.str();
            buffer+=" ";
            if ((n)->r){
                n=(n)->r;
                col=(n)->column;
            } else  {
                col='I';
            } 
        }
        buffer+="\n";
        n=m;
    }
    // _setmode(_fileno(stdout), _O_U16TEXT);
    //int WK = '♛';
    char *s  = u8"\u2654";
    buffer+=BB.str();
    buffer+=BF.str();
    buffer+=" ";
    buffer+=s;
    buffer+="  ";
    buffer+=DF.str();
    buffer+=DB.str();
    buffer+="\n";    
    return buffer;
}



