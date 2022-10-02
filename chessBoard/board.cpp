#include "board.h"
#include <iostream>

#include <fcntl.h>
using namespace std;
#define BLACK true
#define WHITE false

//insert cell at the front of the column
void insert_f(struct Cell** current){
    struct Cell* newCell = new Cell;
    newCell->row=(*current)->row+1;
    newCell->black=!(*current)->black;
    newCell->column=(*current)->column;
    newCell->b=(*current);
    newCell->f=NULL;

    (*current)->f=newCell;
    
    
}


struct Cell* getCell(char col, int i, bool bl){
    struct Cell* a1=new Cell;
    (a1)->black=bl;
    (a1)->row=i;
    (a1)->column=col;
    return (a1);
}

void buildColumn(struct Cell* c){
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

void linkColumns(Cell* prev, Cell*c){
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

struct Cell* buildRows(){
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



int main(){
    Board b;
    cout<<b;
}

int test(){/*
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




    }*/
// _setmode(_fileno(stdout), _O_U16TEXT);
//int WK = '♛';
//char *s  = u8"\u2654";
//cout<<BB<<BF<<" "<<s<<"  "<<DF<<DB<<endl;    
return 0;
}