#include "colormod.h" // namespace Color
#include <iostream>
#include <string>       // std::string
#include <sstream>      // std::stringbuf
#include "GameFile.h"
using namespace std;
#define BLACK true
#define WHITE false



class Piece;

struct Cell{
    bool empty=true;
    bool black=true; 
    char column=' '; // a to f
    int row=0;  //1 to 8
    //char *s  = u8"\u2654"
    char pieceType='_';
    bool blackPiece=false;
    struct Cell* l=NULL;
    struct Cell* r=NULL;
    struct Cell* f=NULL;
    struct Cell* b=NULL;
    struct Cell* lf=NULL;
    struct Cell* lb=NULL;
    struct Cell* rf=NULL;
    struct Cell* rb=NULL;
    Piece *piece=NULL;
    
};



class Piece {


public:
    struct Cell *initialCell;
    struct Cell *currentCell;
    struct Cell *previousCell;
    bool isBlackPiece=false;
    bool onBoard=true;
    bool onOpenColumn=false;
    bool onHalfOpenColumn=false;
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
    int rank=0;
    char col=' ';
    char type=' ';
    //struct Cell availableCellsToMove[28];

    Piece();    
    void assess();
    bool hasOpenColumn();
    bool hasHalfOpenColumn();
    bool hasOpenRank();
    bool hasOpenFRD();
    bool hasOpenFLD();
    bool hasOpenBRD();
    bool hasOpenBLD();
    bool isNextToKing();
    bool isCoveringPieces();;
    bool isCoveringKing();
    bool isBlockingCheck();
    void init(struct Cell *);
    bool isNextTo(char, int );
    int xDistanceTo(char, int );
    int yDistanceTo(char, int );
    bool moveTo(char , int);
    struct Cell *getCell(char ,int );
    bool captureOn(char , int );
};

Piece::Piece(){

}

void Piece::init(struct Cell *initial){
    currentCell=initial;
    previousCell=initial;
    initialCell=initial;
    onBoard=true;
    rank=initial->row;
    col=initial->column;
    type=initial->pieceType;
    //assess();
}
void Piece::assess(){
    /*
    onOpenColumn=hasOpenColumn();
    onHalfOpenColumn=hasHalfOpenColumn();
    withOpenRank=hasOpenRank();
    withOpenFRD=hasOpenFRD();
    withOpenFLD=hasOpenFLD();
    withOpenBRD=hasOpenBRD();
    withOpenBLD=hasOpenBLD();
    alreadyMoved=false;
    nextToKing=isNextToKing();
    coveringOtherPiece=isCoveringPieces();;
    coveringKing=isCoveringKing();
    blockingCheck=isBlockingCheck();
    above5thRank=((rank>5) ? true : false);
    */
}

bool Piece::isNextTo(char tCol, int tRank){
    char oCol=currentCell->column;
    int oRank=currentCell->row;
    int x = abs(oRank-tRank);
    int y=  abs((int)oRank-(int)tRank); //

    if (x==1 & y==1){
        return true;
    }

    if (x==0 & y==1){
        return true;
    }

    if (x==1 & y==0){
        return true;
    }
    return false;
}

int Piece::xDistanceTo(char tCol, int tRank){
    int oRank=currentCell->row;
    int x = abs(oRank-tRank);
    return x;
}
int Piece::yDistanceTo(char tCol, int tRank){
    char oCol=currentCell->column;
    int y = abs((int)oCol- (int)tCol);
    return y;
}

struct Cell * Piece::getCell(char tCol,int tRank){
    char oCol=currentCell->column;
    int oRank=currentCell->row;
    struct Cell *target=currentCell;
    //int x=oCol==tCol;
    //int y=oRank==tRank;

    if (oCol<tCol){
        while (oCol!=tCol){
            target=target->r;
            oCol=target->column;
        }
    } 

    if (oCol>tCol){
        while (oCol!=tCol){
            target=target->l;
            oCol=target->column;
        }

    } 
    
    if (oRank<tRank){
        while (oRank!=tRank){
            target=target->f;
            oRank=target->row;
        }
    } 

    if (oRank>tRank){
        while (oRank!=tRank){
            target=target->b;
            oRank=target->row;
        }

    } 
    return target;
}


bool Piece::moveTo(char tCol,int tRank){
    bool valid=false;
    struct Cell *target=getCell(tCol, tRank);
    bool empty=target->empty;
    if (!empty){
        return valid;
    } else {
        currentCell->empty=true;
        target->empty=false;
        valid=true;
    }

    target->pieceType=currentCell->pieceType;
    currentCell->pieceType=' ';

    target->blackPiece=currentCell->blackPiece;
    currentCell->blackPiece=false;

    target->piece= this;  //currentCell->piece;
    currentCell->piece=NULL;


    previousCell=currentCell;
    currentCell=target;
    
    onBoard=true;
    
    alreadyMoved=true;
    if (tRank>5){
        above5thRank=true;
    } else{
        above5thRank=false;
    }
    rank=tRank;
    col=tCol;
    return valid;
}

bool Piece::captureOn(char tCol, int tRank){
    bool valid=false;
    struct Cell *target=getCell(tCol, tRank);
    bool empty=target->empty;
    bool isTargetPieceBlack=target->blackPiece;

    if (isBlackPiece!=isTargetPieceBlack){
        valid=true;
    } else {
        return false;
    }
    
    if (empty){
        return false; ----Check pasant
    } else {
        currentCell->empty=true;
        target->empty=false;
        valid=true;
    }


    target->pieceType=currentCell->pieceType;
    currentCell->pieceType=' ';

    target->blackPiece=currentCell->blackPiece;
    currentCell->blackPiece=false;

    //---
    (target->piece)->onBoard=false;
    (target->piece)->rank=0;
    (target->piece)->col=' ';
    (target->piece)->previousCell=currentCell;
    (target->piece)->currentCell=NULL;
    //---
    
    target->piece= this;  //currentCell->piece;
    currentCell->piece=NULL;

    previousCell=currentCell;
    currentCell=target;
    
    onBoard=true;
    
    alreadyMoved=true;
    
    if (tRank>5){
        above5thRank=true;
    } else{
        above5thRank=false;
    }
    
    rank=tRank;
    col=tCol;
    return valid;
}

bool Piece::hasOpenColumn(){  //not the standard chess definition, only chcks the file is open from current cell forward
    bool openColumn=false;
    struct Cell* next;
    while ((next=(isBlackPiece?currentCell->b:currentCell->f))){
        if (!next->empty){
            openColumn=true;
        } else {
            openColumn=false;
            break;

        }

    }

    return openColumn;
}
bool Piece::hasHalfOpenColumn(){ // pending
    return false;
}
bool Piece::hasOpenRank(){ // pending
    return false;
}
bool Piece::hasOpenFRD(){ // pending
    return false;
}
bool Piece::hasOpenFLD(){ // pending
    return false;
}
bool Piece::hasOpenBRD(){ // pending
    return false;
}
bool Piece::hasOpenBLD(){ // pending
    return false;
}
bool Piece::isNextToKing(){
    return false;
}
bool Piece::isCoveringPieces(){ // pending
    return false;
}
bool Piece::isCoveringKing(){ // pending
    return false;
}
bool Piece::isBlockingCheck(){
    return false;
}


class Pawn:public Piece {

public:
    Pawn();
    void init(struct Cell *);
    void assess();
    bool isProtectingPieces();
    bool isAttackinglowerPiece();
    bool isAttackingSimilarPiece();
    bool isAttackingHigherPiece();
    void calculateAvailableCellsToMove();


};

Pawn::Pawn(){

}

void Pawn::init(struct Cell *initial){
    Piece::init(initial);
    //assess();
}

void Pawn::assess(){
    Piece:assess();
    /*
    protectingPiece=isProtectingPieces();
    attackinglowerPiece=isAttackinglowerPiece();
    attackingSimilarPiece=isAttackingSimilarPiece();
    attackingHigherPiece=isAttackingHigherPiece();
    calculateAvailableCellsToMove();
    */
}



bool Pawn::isProtectingPieces(){ 
    return false;
}
bool Pawn::isAttackinglowerPiece(){
    return false;
}
bool Pawn::isAttackingSimilarPiece(){
    return false;
}
bool Pawn::isAttackingHigherPiece(){
    return false;
}
void Pawn::calculateAvailableCellsToMove(){

}


class WPawn:public Pawn {

public:
    WPawn(struct Cell *);
    bool canReach(char , int);
    bool moveTo(char , int, bool);
    bool moveTo(char , int );
    bool enPassant=false;
    bool getEnPassant();
    void setEnPassant(bool);
};

WPawn::WPawn(struct Cell *c){
    Pawn::init(c);
    isBlackPiece=false;
}


bool WPawn::canReach(char tCol, int tRank){
    bool valid=false;
    if (currentCell==NULL){
        return valid;
    }
    char cCol  = currentCell->column;
    int cRank  = currentCell->row;
    struct Cell *next = currentCell;
    bool cBlack=currentCell->blackPiece;
    
    int side=(int)cCol - (int)tCol;  // negative -->R ,, positive -->L  
    int direction=(int)cRank - (int)tRank; //// negative -->F ,, positive -->B

    int fDistance=(int)tRank - (int)cRank;
    
    if (fDistance<=0 || fDistance>2){
        return valid;
    }
    if (fDistance==2 && cRank>2){
        return valid;

    }

    if (fDistance==2 && cRank==2 && side !=0){
        return valid;
    }
    

    //direction F 
    while (next->f !=NULL & side ==0 & direction <0 & !valid){
        next=next->f;
        if (next->column==tCol & next->row <= tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is empty
            valid=true;          
            break;
        }
        
    }


    //direction RF
    while (next->rf !=NULL & side <0 & direction <0 & !valid){
        next=next->rf;
        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by different  color
                valid=true;
                break;
            } 

        }
        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is empty, must be a passant
            valid=true;
            break;
        }
        
    }

    // side negative -->R ,, positive -->L  
    // direction negative -->F ,, positive -->B

    //direction LF 
    while (next->lf !=NULL & side >0 & direction < 0 & !valid){
        next=next->lf;
        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is different by same color
                valid=true;
                break;
            } 

        }
        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is empty )passant=
            valid=true;
            break;
        }
    }


    // if (valid)
        //valid=isCheckPinned(tCol, tRank);         ----------> PENDING --- IMPORTANT!!!!!!
    return valid;

}


bool WPawn::moveTo(char tCol, int tRank, bool capture){
    bool valid=false;

    if (capture){
       if (canReach(tCol,tRank)){

            valid=captureOn(tCol,tRank);
            return valid;
       } 
    }

    valid=moveTo(tCol,tRank);
    return valid;
}

bool WPawn::moveTo(char tCol, int tRank){
    bool valid=false;
    char cCol  = currentCell->column;
    int cRank  = currentCell->row;
    
    int side=(int)cCol - (int)tCol;  // negative -->R ,, positive -->L  
    int direction=(int)cRank - (int)tRank; //// negative -->F ,, positive -->B

    int fDistance=(int)tRank - (int)cRank;


    if (canReach(tCol,tRank)){
        if (fDistance==2 && cRank==2 && side ==0){
            setEnPassant(true);
        }
        valid=Piece::moveTo(tCol,tRank);
    }
 
    return valid;
}

bool WPawn::getEnPassant()
{
    return enPassant;
}

void WPawn::setEnPassant(bool b){
        enPassant=b;
}

bool Piece::captureEnPassant(char tCol, int tRank){
    bool valid=false;
    struct Cell *target=getCell(tCol, tRank);
    bool empty=target->empty;
    bool isTargetPieceBlack=target->blackPiece;

    if (isBlackPiece!=isTargetPieceBlack){
        valid=true;
    } else {
        return false;
    }
    
    if (empty){
        return false; ----Check pasant
    } else {
        currentCell->empty=true;
        target->empty=false;
        valid=true;
    }


    target->pieceType=currentCell->pieceType;
    currentCell->pieceType=' ';

    target->blackPiece=currentCell->blackPiece;
    currentCell->blackPiece=false;

    //---
    (target->piece)->onBoard=false;
    (target->piece)->rank=0;
    (target->piece)->col=' ';
    (target->piece)->previousCell=currentCell;
    (target->piece)->currentCell=NULL;
    //---
    
    target->piece= this;  //currentCell->piece;
    currentCell->piece=NULL;

    previousCell=currentCell;
    currentCell=target;
    
    onBoard=true;
    
    alreadyMoved=true;
    
    if (tRank>5){
        above5thRank=true;
    } else{
        above5thRank=false;
    }
    
    rank=tRank;
    col=tCol;
    return valid;
}



class BPawn:public Pawn {

public:
   BPawn(struct Cell *);
   bool enPassant;
   bool getEnPassant();
   void setEnPassant(bool b);
   bool canReach(char, int);
   bool moveTo(char , int, bool);
   bool moveTo(char , int );
};

BPawn::BPawn(struct Cell *c){
    Pawn::init(c);
    isBlackPiece=true;
}
bool BPawn::getEnPassant()
{
    return enPassant;
}

void BPawn::setEnPassant(bool b){
        enPassant=b;
}
//_______________________________

bool BPawn::canReach(char tCol, int tRank){
    bool valid=false;
    
    if (currentCell==NULL){
        return valid;
    }
    char cCol  = currentCell->column;
    int cRank  = currentCell->row;
    struct Cell *next = currentCell;
    bool cBlack=currentCell->blackPiece;
    
    int side=(int)cCol - (int)tCol;  // negative -->R ,, positive -->L  
    int direction=(int)cRank - (int)tRank; //// negative -->F ,, positive -->B

    int fDistance=(int)tRank - (int)cRank;
    
    if (fDistance>=0 || fDistance<-2){
        return valid;
    }
    if (fDistance==-2 && cRank<7){
        return valid;
    }

    if (fDistance==-2 && cRank==7 && side !=0){
        return valid;
    }
    

    //direction B 
    while (next->b !=NULL & side ==0 & direction >0 & !valid){
        next=next->b;
        if (next->column==tCol & next->row <= tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is occupied
            valid=true;
            break;
        }

    }


    //direction RB 
    while (next->rb !=NULL & side <0 & direction >0 & !valid){
        next=next->rb;
        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by other color
                valid=true;
                break;
            } 

        }
        
    }



    // side negative -->R ,, positive -->L  
    // direction negative -->F ,, positive -->B

    //direction LF 
    while (next->lf !=NULL & side >0 & direction < 0 & !valid){
        next=next->lf;
        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is different by same color
                valid=true;
                break;
            } 

        }
        
    }

//direction LB 
    while (next->lb !=NULL & side >0 & direction > 0 & !valid){
        next=next->lb;
        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 
        }
    }




    // if (valid)
        //valid=isCheckPinned(tCol, tRank);         ----------> PENDING --- IMPORTANT!!!!!!
    return valid;

}



bool BPawn::moveTo(char tCol, int tRank, bool capture){
    bool valid=false;
    if (capture){
       if (canReach(tCol,tRank)){
            valid=captureOn(tCol,tRank);
            return valid;
       } 
    }
    valid=moveTo(tCol,tRank);
    return valid;
}

bool BPawn::moveTo(char tCol, int tRank){
    bool valid=false;
    char cCol  = currentCell->column;
    int cRank  = currentCell->row;
    
    int side=(int)cCol - (int)tCol;  // negative -->R ,, positive -->L  
    int direction=(int)cRank - (int)tRank; //// negative -->F ,, positive -->B

    int fDistance=(int)tRank - (int)cRank;


    if (canReach(tCol,tRank)){
        if (fDistance==-2 && cRank==7 && side ==0){
            setEnPassant(true);
        }
        valid=Piece::moveTo(tCol,tRank);
    }
 
    return valid;



}


//__________________________


class King:public Piece {

public:
    King(struct Cell *);
    bool moveTo(char ,int , bool );
    bool moveTo(char ,int );
    bool canReach(char ,int);
    bool captureOn(char ,int );
    bool castle(char , int );
};

King::King(struct Cell *c){
    Piece::init(c);

}

bool King::moveTo(char tCol, int tRank, bool capture){
    bool valid=false;
    if (capture){
       if (canReach(tCol,tRank)){
            valid=captureOn(tCol,tRank);
            return valid;
       } 
    }
    valid=moveTo(tCol,tRank);
    return valid;
}

bool King::moveTo(char tCol, int tRank){
    bool valid=false;
    char cCol  = currentCell->column;
    int cRank  = currentCell->row;
    if (canReach(tCol,tRank)){
        valid=Piece::moveTo(tCol,tRank);
    }
    return valid;
}

bool King::castle(char tCol, int tRank){
    bool valid=false;
    char cCol  = currentCell->column;
    int cRank  = currentCell->row;
    //check if a black piece can reach e1, f1, g1
    valid= Piece::moveTo(tCol,tRank);
    return valid;
}

bool King::captureOn(char tCol, int tRank){
    bool valid=false;
    if (canReach(tCol,tRank)){
        valid=Piece::captureOn(tCol,tRank);
    } 
    return valid;
}

bool King::canReach(char tCol, int tRank){
    bool valid=false;
    char cCol  = currentCell->column;
    int cRank  = currentCell->row;
    if (isNextTo(tCol,tRank)){
        struct Cell *c=getCell(tCol, tRank);
        if (c->empty){ //reaching target  and target is empty
            valid=true;
        } else{
            if (currentCell->blackPiece != c->blackPiece){  // is occupied by different color
                valid=true;
            } 
        }
    }
    //valid=isSafeforKing(tCol, tRank);         ----------> PENDING --- IMPORTANT!!!!!!
    return valid;

}



class Queen:public Piece {

public:
    Queen(struct Cell *);
    bool canReach(char ,int);
    bool moveTo(char ,int , bool );
    bool moveTo(char ,int );
    bool captureOn(char ,int );

};

Queen::Queen(struct Cell *c){
    Piece::init(c);
}

bool Queen::canReach(char tCol, int tRank){
    bool valid=false;
    char cCol  = currentCell->column;
    int cRank  = currentCell->row;
    struct Cell *next = currentCell;
    bool cBlack=currentCell->blackPiece;
    
    int side=(int)cCol - (int)tCol;  // negative -->R ,, positive -->L  
    int direction=(int)cRank - (int)tRank; //// negative -->F ,, positive -->B
    
    //direction F 
    while (next->f !=NULL & side ==0 & direction <0 & !valid){
        next=next->f;
        if (next->column==tCol & next->row != tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 
        }
        
        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is occupied
                valid=true;
                break;
        }

    }

    //direction B 
    while (next->b !=NULL & side ==0 & direction >0 & !valid){
        next=next->b;
        if (next->column==tCol & next->row != tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 

        }

         if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is occupied
                valid=true;
                break;
        }
    

    }

    //direction R 
    while (next->r !=NULL & side <0 & direction == 0 & !valid){
        next=next->r;
        if (next->column!=tCol & next->row != tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 

        }

        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is occupied
                valid=true;
                break;
        }


    }

//direction L 
    while (next->l !=NULL & side >0 & direction == 0 & !valid){
        next=next->l;
        if (next->column!=tCol & next->row != tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 

        }

        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is occupied
                valid=true;
                break;
        }


    }


    //direction RF
    while (next->rf !=NULL & side <0 & direction <0 & !valid){
        next=next->rf;
        if (next->column!=tCol & next->row != tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 

        }

        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is occupied
                valid=true;
                break;
        }


    }

    //direction RB 
    while (next->rb !=NULL & side <0 & direction >0 & !valid){
        next=next->rb;
        if (next->column!=tCol & next->row != tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 

        }

        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is occupied
                valid=true;
                break;
        }


    }

    // side negative -->R ,, positive -->L  
    // direction negative -->F ,, positive -->B

    //direction LF 
    while (next->lf !=NULL & side >0 & direction < 0 & !valid){
        next=next->lf;
        if (next->column!=tCol & next->row != tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 

        }

        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is occupied
                valid=true;
                break;
        }


    }

//direction LB 
    while (next->lb !=NULL & side >0 & direction > 0 & !valid){
        next=next->lb;
        if (next->column!=tCol & next->row != tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 

        }

        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is occupied
                valid=true;
                break;
        }


    }



    //valid=isCheckPinned(tCol, tRank);         ----------> PENDING --- IMPORTANT!!!!!!
    return valid;

}

bool Queen::moveTo(char tCol, int tRank, bool capture){
    bool valid=false;
    if (capture){
       if (canReach(tCol,tRank)){
            valid=captureOn(tCol,tRank);
            return valid;
       } 
    }
    valid=moveTo(tCol,tRank);
    return valid;
}

bool Queen::moveTo(char tCol, int tRank){
    bool valid=false;
    char cCol  = currentCell->column;
    int cRank  = currentCell->row;
    if (canReach(tCol,tRank)){
        valid=Piece::moveTo(tCol,tRank);
    }
    return valid;
}

bool Queen::captureOn(char tCol, int tRank){
    bool valid=false;
    if (canReach(tCol,tRank)){
        valid=Piece::captureOn(tCol,tRank);
    } 
    return valid;
}



class Knight:public Piece {

public:
    Knight(struct Cell *);
    bool canReach(char ,int);
    bool moveTo(char ,int , bool );
    bool moveTo(char ,int );
    bool captureOn(char ,int );
};

Knight::Knight(struct Cell *c){
    Piece::init(c);
}

bool Knight::canReach(char tCol, int tRank){
    bool valid=false;
    char cCol  = currentCell->column;
    int cRank  = currentCell->row;
    struct Cell *next = currentCell;
    bool cBlack=currentCell->blackPiece;
    
    
    int side=(int)cCol - (int)tCol;  // negative -->R ,, positive -->L  
    int direction=(int)cRank - (int)tRank; //// negative -->F ,, positive -->B
    if (side==0 | direction==0){
        return valid;
    }

    int reach=abs(side)+abs(direction);

    next=getCell(tCol, tRank);

    if (reach==3 & !next->empty){
        if (cBlack!=next->blackPiece){  // is occupied by same color
            valid=true;
        }
    }

    if (reach==3 & next->empty){
        valid=true;
    }


    return valid;
}

bool Knight::moveTo(char tCol, int tRank, bool capture){
    bool valid=false;
    if (capture){
       if (canReach(tCol,tRank)){
            valid=captureOn(tCol,tRank);
            return valid;
       } 
    }
    valid=moveTo(tCol,tRank);
    return valid;
}

bool Knight::moveTo(char tCol, int tRank){
    bool valid=false;
    char cCol  = currentCell->column;
    int cRank  = currentCell->row;
    if (canReach(tCol,tRank)){
        valid=Piece::moveTo(tCol,tRank);
    }
    return valid;
}

bool Knight::captureOn(char tCol, int tRank){
    bool valid=false;
    if (canReach(tCol,tRank)){
        valid=Piece::captureOn(tCol,tRank);
    } 
    return valid;
}


class Rook:public Piece {
    

public:
    Rook(struct Cell *);
    bool moved=false;
    bool canReach(char ,int);
    bool moveTo(char ,int , bool );
    bool moveTo(char ,int );
    bool captureOn(char ,int );
    bool castle(char , int );
};

Rook::Rook(struct Cell *c){
    Piece::init(c);
}

bool Rook::canReach(char tCol, int tRank){
    bool valid=false;
    char cCol  = currentCell->column;
    int cRank  = currentCell->row;
    struct Cell *next = currentCell;
    bool cBlack=currentCell->blackPiece;
    
    int side=(int)cCol - (int)tCol;  // negative -->R ,, positive -->L  
    int direction=(int)cRank - (int)tRank; //// negative -->F ,, positive -->B
    
    //direction F 
    while (next->f !=NULL & side ==0 & direction <0 & !valid){
        next=next->f;
        if (next->column==tCol & next->row != tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 
        }

        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is occupied
                valid=true;
                break;
        }


    }

    //direction B 
    while (next->b !=NULL & side ==0 & direction >0 & !valid){
        next=next->b;
        if (next->column==tCol & next->row != tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 

        }
        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is occupied
                valid=true;
                break;
        }



    }

    //direction R 
    while (next->r !=NULL & side <0 & direction == 0 & !valid){
        next=next->r;
        if (next->column!=tCol & next->row == tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 

        }

        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is occupied
                valid=true;
                break;
        }



    }

//direction L 
    while (next->l !=NULL & side >0 & direction == 0 & !valid){
        next=next->l;
        if (next->column!=tCol & next->row == tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 

        }

        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is occupied
                valid=true;
                break;
        }

        
        
    }


    //valid=isCheckPinned(tCol, tRank);         ----------> PENDING --- IMPORTANT!!!!!!
    return valid;

}

bool Rook::moveTo(char tCol, int tRank, bool capture){
    bool valid=false;
    if (capture){
       if (canReach(tCol,tRank)){
            valid=captureOn(tCol,tRank);
            return valid;
       } 
    }
    valid=moveTo(tCol,tRank);
    return valid;
}

bool Rook::moveTo(char tCol, int tRank){
    bool valid=false;
    char cCol  = currentCell->column;
    int cRank  = currentCell->row;
    if (canReach(tCol,tRank)){
        valid=Piece::moveTo(tCol,tRank);
        moved=true;
    }
    return valid;
}

bool Rook::castle(char tCol, int tRank){
    bool valid=false;
    char cCol  = currentCell->column;
    int cRank  = currentCell->row;
    //check if a black piece can reach e1, f1, g1
    valid= Piece::moveTo(tCol,tRank);
    return valid;
}

bool Rook::captureOn(char tCol, int tRank){
    bool valid=false;
    if (canReach(tCol,tRank)){
        valid=Piece::captureOn(tCol,tRank);
    } 
    return valid;
}


class Bishop:public Piece {

public:
    Bishop(struct Cell *);
    bool canReach(char ,int);
    bool moveTo(char ,int , bool );
    bool moveTo(char ,int );
    bool captureOn(char ,int );
};

Bishop::Bishop(struct Cell *c){
    Piece::init(c);
}

bool Bishop::canReach(char tCol, int tRank){
    bool valid=false;
    char cCol  = currentCell->column;
    int cRank  = currentCell->row;
    struct Cell *next = currentCell;
    bool cBlack=currentCell->blackPiece;
    
    int side=(int)cCol - (int)tCol;  // negative -->R ,, positive -->L  
    int direction=(int)cRank - (int)tRank; //// negative -->F ,, positive -->B
        
    //direction RF
    while (next->rf !=NULL & side <0 & direction <0 & !valid){
        next=next->rf;
        if (next->column!=tCol & next->row != tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 

        }
        
        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is empty
            valid=true;
            break;
        }
        
    }

    //direction RB 
    while (next->rb !=NULL & side <0 & direction >0 & !valid){
        next=next->rb;
        if (next->column!=tCol & next->row != tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 

        }
        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is empty
            valid=true;
            break;
        }

    }

    // side negative -->R ,, positive -->L  
    // direction negative -->F ,, positive -->B

    //direction LF 
    while (next->lf !=NULL & side >0 & direction < 0 & !valid){
        next=next->lf;
        if (next->column!=tCol & next->row != tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 

        }
        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is empty
            valid=true;
            break;
        }

    }

//direction LB 
    while (next->lb !=NULL & side >0 & direction > 0 & !valid){
        next=next->lb;
        if (next->column!=tCol & next->row != tRank & !next->empty){ // path is blocked
            break;
        }

        if (next->column==tCol & next->row == tRank & !next->empty){ //reaching target  and target is occupied
            if (cBlack!=next->blackPiece){  // is occupied by same color
                valid=true;
                break;
            } 

        }
        if (next->column==tCol & next->row == tRank & next->empty){ //reaching target  and target is empty
            valid=true;
            break;
        }

    }



    //valid=isCheckPinned(tCol, tRank);         ----------> PENDING --- IMPORTANT!!!!!!
    return valid;

}

bool Bishop::moveTo(char tCol, int tRank, bool capture){
    bool valid=false;
    if (capture){
       if (canReach(tCol,tRank)){
            valid=captureOn(tCol,tRank);
            return valid;
       } 
    }
    valid=moveTo(tCol,tRank);
    return valid;
}

bool Bishop::moveTo(char tCol, int tRank){
    bool valid=false;
    char cCol  = currentCell->column;
    int cRank  = currentCell->row;
    if (canReach(tCol,tRank)){
        valid=Piece::moveTo(tCol,tRank);
    }
    return valid;
}

bool Bishop::captureOn(char tCol, int tRank){
    bool valid=false;
    if (canReach(tCol,tRank)){
        valid=Piece::captureOn(tCol,tRank);
    } 
    return valid;
}





class Board {

    struct Cell *fenArray[64];
    void initCells();
    void buildColumn(Cell* );
    void linkColumns(Cell* , Cell*);
    struct Cell* buildRows();
    struct Cell* getCell(char , int , bool );

    list<WPawn> wPawns;
    list<BPawn> bPawns;
    list<Knight> wKnights;
    list<Knight> bKnights;
    list<Rook> wRooks;
    list<Rook> bRooks;
    list<Bishop> wBishops;
    list<Bishop> bBishops;
    list<Queen> wQueens;
    list<Queen> bQueens;
    list<Piece> black;
    list<Piece> white;
    King *wKing;
    King *bKing;
    
    void buildFENArray();

    char* getChessPiece(char );
    bool whiteToMove=true;
    char wCastling='B';  //B=Both; K=king side,Q=Queenside
    char bCastling='b';  //b=Both; k=king side,q=Queenside
    char passant[2];
    char enPassantSide=' ';
    int halfMove=0;
    int fullMoves=1;

    

public:
    struct Cell* a1;
    struct Cell* a8;
    Board();
    std::string printBoard();
    friend ostream& operator<<(std::ostream& os, Board b) { return os << b.printBoard();   };
    int initBoard(std::string  ) ;
    int initBoard() ;
    string getFENString();
    int moveWhite(std::string);
    int moveBlack(std::string);
    int processWhiteMove(GameMove *);
    int processBlackMove(GameMove *);
    void initializeBlackPiece(struct Cell *, char);
    void initializeWhitePiece(struct Cell *, char);
    Queen *findWQueenTo(char , int, char ,int, bool);
    Rook  *findWRookTo(char , int, char ,int, bool);
    Bishop  *findWBishopTo(char , int, char ,int, bool);
    Knight  *findWKnightTo(char , int, char ,int, bool);
    WPawn  *findWPawnTo(char , int, char ,int, bool);
    Queen *findBQueenTo(char , int, char ,int, bool);
    Rook  *findBRookTo(char , int, char ,int, bool);
    Bishop  *findBBishopTo(char , int, char ,int, bool);
    Knight  *findBKnightTo(char , int, char ,int, bool);
    BPawn  *findBPawnTo(char , int, char ,int, bool);
    void updateWCastling(char , int, Rook *);
    void updateBCastling(char , int, Rook *);
    bool wKingCastling();
    bool bKingCastling();
    bool wQueenCastling();
    bool bQueenCastling();
    bool isABlackPiecePreventingKsideCastling();
    bool isAWhitePiecePreventingKsideCastling();
    bool isABlackPiecePreventingQsideCastling();
    bool isAWhitePiecePreventingQsideCastling();
    void setEnPassant(char , int , char);
    char getEnPassantSide();
    void setEnPassantSide(char );
};

Board::Board(){
    struct Cell* n=buildRows();
    a1=n; 
    initBoard("rnbqkbnr/ppppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ");
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
            buffer+=getChessPiece((n)->pieceType);
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
        if (fenArray[i]->pieceType!=' '){
            if (emptyCells==0){
                fenString+=fenArray[i]->pieceType;
            }else{
                aux<< emptyCells; 
                fenString+=aux.str();
                fenString+=fenArray[i]->pieceType;
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
// ferArr[0] --> a8  .....  fenArr[7]  --h8
// ferArr[8] --> a7  .....  fenArr[15] --h7
//   ......
// fenArr[48] -- a2 ......  fenArr[55] --H2
// fenArr[56] -- a1 ......  fenArr[63] --H1

    int Board::moveWhite(string mv){
        if (mv.length()>3){
        char initCol=mv[0];
        char initRow=mv[1];
        char targetCol=mv[2];
        char targetRow=mv[3];
        int initCelIdx;
        int targetCelIdx;
        struct Cell * initCel;
        struct Cell * targetCel;
        if ((initCol>='a' && initCol<='h') &&
            (targetCol>='a' && targetCol<='h') &&
            (initRow>='1' && initRow<='8') &&
            (targetRow>='1' && targetRow<='8') ){

            initCelIdx= ((int)(initCol-'a')) + ((int)('8'-initRow))*8;
            targetCelIdx=((int)(targetCol-'a')) + ((int)('8'-targetRow))*8;
            initCel=fenArray[initCelIdx];
            targetCel=fenArray[targetCelIdx];
            if ((!initCel->empty && (!initCel->blackPiece)) &&
                ((targetCel->empty) || (!targetCel->empty && (targetCel->blackPiece)))
                ){
                    targetCel->blackPiece=false;
                    targetCel->pieceType=initCel->pieceType;
                    targetCel->empty=false;
                    initCel->blackPiece=false;
                    initCel->pieceType=' ';
                    initCel->empty=true;
            } else {
                return 1;
            }
        } else {
            return 1;
        }


        } else {
            return 1;
        }
        return 0;


    }
    int Board::moveBlack(string mv){
        if (mv.length()>3){
        char initCol=mv[0];
        char initRow=mv[1];
        char targetCol=mv[2];
        char targetRow=mv[3];
        int initCelIdx;
        int targetCelIdx;
        struct Cell * initCel;
        struct Cell * targetCel;
        if ((initCol>='a' && initCol<='h') &&
            (targetCol>='a' && targetCol<='h') &&
            (initRow>='1' && initRow<='8') &&
            (targetRow>='1' && targetRow<='8')){

            initCelIdx= ((int)(initCol-'a')) + ((int)('8'-initRow))*8;
            targetCelIdx=((int)(targetCol-'a')) + ((int)('8'-targetRow))*8;
            initCel=fenArray[initCelIdx];
            targetCel=fenArray[targetCelIdx];
            if ((!initCel->empty && (initCel->blackPiece)) &&
                ((targetCel->empty) || (!targetCel->empty && (!targetCel->blackPiece)))
                ){
                    targetCel->blackPiece=true;
                    targetCel->pieceType=initCel->pieceType;
                    targetCel->empty=false;
                    initCel->blackPiece=false;
                    initCel->pieceType=' ';
                    initCel->empty=true;
            } else {
                return 1;
            }
        } else {
            return 1;
        }


        } else {
            return 1;
        }
        return 0;
    }

int Board::initBoard()  {
    return initBoard("rnbqkbnr/ppppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ");

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
                            (current)->empty=false;
                            (current)->pieceType=*it;
                            initializeWhitePiece(current, *it);
                            current=(current)->r;
                        }
                        if (blackPieces.find(*it) != string::npos ) {
                            (current)->blackPiece=true;
                            (current)->empty=false;
                            (current)->pieceType=*it;
                            initializeBlackPiece(current, *it);
                            current=(current)->r;
                        }
                        if (numbers.find(*it) != string::npos ){
                            aux<< *it; 
                            aux >> x;
                            while (x>0 & current!=NULL){
                                (current)->blackPiece=false;
                                (current)->empty=true;
                                (current)->pieceType=' ';
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

Queen   *Board::findWQueenTo(char oCol,int oRank,char tCol,int tRank,bool capture){
        Queen *q=NULL;
        char qCol;
        int qRank;
        list<Queen>::iterator i=wQueens.begin();
        while (i != wQueens.end()){
            qCol=(i)->col;
            qRank=(i)->rank;
            if ( ((i)->onBoard)){
                if ((qCol==oCol) && (qRank==oRank)){
                q=&*i;
                return q;
                }
            }
            ++i;
        }
        i=wQueens.begin();
        while (i != wQueens.end()){
            qCol=(i)->col;
            qRank=(i)->rank;
            if ((i)->onBoard){
                if ((qCol==oCol) && (i)->canReach(tCol, tRank) ){
                    q=&*i;
                    return q;
                }
            }
        ++i;
        }

        i=wQueens.begin();
        while (i != wQueens.end()){
            qCol=(i)->col;
            qRank=(i)->rank;
            if ( (i)->onBoard){
                if ( (i)->canReach(tCol, tRank) ){
                    q=&*i;
                    return q;
                }
            }
            ++i;
        }

        return q;
}

Rook   *Board::findWRookTo(char oCol,int oRank,char tCol,int tRank,bool capture){
        Rook *r=NULL;
        char rCol;
        int rRank;
        list<Rook>::iterator i=wRooks.begin();
        while (i != wRooks.end()){
            rCol=(i)->col;
            rRank=(i)->rank;
            if ((i)->onBoard){
                if ((rCol==oCol) && (rRank==oRank) ){
                    r=&*i;
                    return r;
                }
            }
            ++i;
        }
        i=wRooks.begin();
        while (i != wRooks.end()){
            rCol=(i)->col;
            rRank=(i)->rank;
            if ((i)->onBoard){
                if ((rCol==oCol) && (i)->canReach(tCol, tRank)){
                    r=&*i;
                    return r;
                }
            }
        ++i;
        }

        i=wRooks.begin();
        while (i != wRooks.end()){
            rCol=(i)->col;
            rRank=(i)->rank;
            if ((i)->onBoard){
                if ((i)->canReach(tCol, tRank)){
                    r=&*i;
                    return r;
                }
            }
        ++i;
        }

        return r;
}

Knight *Board::findWKnightTo(char oCol,int oRank,char tCol,int tRank, bool capture){
    Knight *k=NULL;
    char kCol;
    int kRank;
    list<Knight>::iterator i=wKnights.begin();
    while (i != wKnights.end()){
        kCol=(i)->col;
        kRank=(i)->rank;
        if ((i)->onBoard && (kCol==oCol) && (kRank==oRank) ){
                k=&*i;
                return k;
        }
        ++i;
    }
    i=wKnights.begin();
    while (i != wKnights.end()){
        kCol=(i)->col;
        kRank=(i)->rank;
        if ((i)->onBoard && (kCol==oCol) && (i)->canReach(tCol, tRank) ){
                k=&*i;
                return k;
        }
        ++i;
    }
    
    i=wKnights.begin();
    while (i != wKnights.end()){
        kCol=(i)->col;
        kRank=(i)->rank;
        if ((i)->onBoard && (kRank==oRank) && (i)->canReach(tCol, tRank) ){
                k=&*i;
                return k;
        }
        ++i;
    }

    i=wKnights.begin();
    while (i != wKnights.end()){
        kCol=(i)->col;
        kRank=(i)->rank;
        if ((i)->onBoard && (i)->canReach(tCol, tRank) ){
            k=&*i;
            return k;
        }
        ++i;
    }

    return k;
}

Bishop   *Board::findWBishopTo(char oCol,int oRank,char tCol,int tRank,bool capture){
        Bishop *b=NULL;
        char rCol;
        int rRank;
        list<Bishop>::iterator i=wBishops.begin();
        while (i != wBishops.end()){
            rCol=(i)->col;
            rRank=(i)->rank;
            if ( (i)->onBoard && (rCol==oCol) & (rRank==oRank) ){
                b=&*i;
                return b;
            }
            ++i;
        }
        i=wBishops.begin();
        while (i != wBishops.end()){
            rCol=(i)->col;
            rRank=(i)->rank;
            if ((i)->onBoard && (rCol==oCol) && (i)->canReach(tCol, tRank) ){
                b=&*i;
                return b;
            }
        ++i;
        }
        i=wBishops.begin();
        while (i != wBishops.end()){
            rCol=(i)->col;
            rRank=(i)->rank;
            if ((i)->onBoard && (i)->canReach(tCol, tRank) ){
                b=&*i;
                return b;
            }
        ++i;
        }
        return b;
}


//____________________________

Queen   *Board::findBQueenTo(char oCol,int oRank,char tCol,int tRank,bool capture){
        Queen *q=NULL;
        char qCol;
        int qRank;
        list<Queen>::iterator i=bQueens.begin();
        while (i != bQueens.end()){
            qCol=(i)->col;
            qRank=(i)->rank;
            if ((qCol==oCol) & (qRank==oRank) & ((i)->onBoard)){
                q=&*i;
                return q;
            }
            ++i;
        }
        i=bQueens.begin();
        while (i != bQueens.end()){
            qCol=(i)->col;
            qRank=(i)->rank;
            if ((qCol==oCol) & (i)->canReach(tCol, tRank) & ((i)->onBoard)){
                q=&*i;
                return q;
            }
        ++i;
        }

        i=bQueens.begin();
        while (i != bQueens.end()){
            qCol=(i)->col;
            qRank=(i)->rank;
            if ( (i)->canReach(tCol, tRank) & ((i)->onBoard)){
                q=&*i;
                return q;
            }
        ++i;
        }

        return q;
}

Rook   *Board::findBRookTo(char oCol,int oRank,char tCol,int tRank,bool capture){
        Rook *r=NULL;
        char rCol;
        int rRank;
        list<Rook>::iterator i=bRooks.begin();
        while (i != bRooks.end()){
            rCol=(i)->col;
            rRank=(i)->rank;
            if ((rCol==oCol) & (rRank==oRank) & ((i)->onBoard)){
                r=&*i;
                return r;
            }
            ++i;
        }
        i=bRooks.begin();
        while (i != bRooks.end()){
            rCol=(i)->col;
            rRank=(i)->rank;
            if ((rCol==oCol) & (i)->canReach(tCol, tRank) & ((i)->onBoard)){
                r=&*i;
                return r;
            }
        ++i;
        }

        i=bRooks.begin();
        while (i != bRooks.end()){
            rCol=(i)->col;
            rRank=(i)->rank;
            if ((i)->canReach(tCol, tRank) & ((i)->onBoard)){
                r=&*i;
                return r;
            }
        ++i;
        }

        return r;
}

Knight *Board::findBKnightTo(char oCol,int oRank,char tCol,int tRank, bool capture){
    Knight *k=NULL;
    char kCol;
    int kRank;
    list<Knight>::iterator i=bKnights.begin();
    
    while (i != bKnights.end()){
        kCol=(i)->col;
        kRank=(i)->rank;
        if (((i)->onBoard)  ){
            if  ( (kCol==oCol) & (kRank==oRank) ){
            k=&*i;
            return k;
             }
        }
        ++i;
    }
    i=bKnights.begin();
    while (i != bKnights.end()){
        kCol=(i)->col;
        kRank=(i)->rank;
        if (((i)->onBoard)  ){
            if  ( (i)->canReach(tCol, tRank) && (kCol==oCol)){
                k=&*i;
                return k;
            }
        }
        ++i;
    }
    
    i=bKnights.begin();
    while (i != bKnights.end()){
        kCol=(i)->col;
        kRank=(i)->rank;
        if (((i)->onBoard)  ){
            if  ( (i)->canReach(tCol, tRank) && (kRank==oRank)){
                k=&*i;
                return k;
            }
        }
        ++i;
    }

    i=bKnights.begin();
    while (i != bKnights.end()){
        kCol=(i)->col;
        kRank=(i)->rank;
        if (((i)->onBoard)  ){
            if  ( (i)->canReach(tCol, tRank)){
                k=&*i;
                return k;
            }
        }
        ++i;
    }

    return k;
}

Bishop   *Board::findBBishopTo(char oCol,int oRank,char tCol,int tRank,bool capture){
        Bishop *b=NULL;
        char rCol;
        int rRank;
        list<Bishop>::iterator i=bBishops.begin();
        while (i != bBishops.end()){
            rCol=(i)->col;
            rRank=(i)->rank;
            if ((i)->onBoard && (rCol==oCol) && (rRank==oRank) ){
                b=&*i;
                return b;
           }
            ++i;
        }
        i=bBishops.begin();
        while (i != bBishops.end()){
            rCol=(i)->col;
            rRank=(i)->rank;
            if ((i)->onBoard && (rCol==oCol) && (i)->canReach(tCol, tRank) ){
                b=&*i;
                return b;
            }
        ++i;
        }

        i=bBishops.begin();
        while (i != bBishops.end()){
            rCol=(i)->col;
            rRank=(i)->rank;
            if ((i)->onBoard && (i)->canReach(tCol, tRank) ){
                b=&*i;
                return b;
            }
        ++i;
        }

        return b;
}

WPawn *Board::findWPawnTo(char oCol, int oRank,char tCol, int tRank, bool capture){
        WPawn *p=NULL;
        char rCol;
        int rRank;
        Piece *pp;
        list<WPawn>::iterator i=wPawns.begin();
        while (i != wPawns.end()){
            rCol=(i)->col;
            rRank=(i)->rank;
            if ((i)->onBoard && (rCol==oCol) && (rRank==oRank) && (i)->canReach(tCol, tRank) ){
                pp = &*i;
                p=static_cast<WPawn *>(pp);   
                return p;
            }
            ++i;
        }
        i=wPawns.begin();
        while (i != wPawns.end()){
            rCol=(i)->col;
            rRank=(i)->rank;
            if ((i)->onBoard && (rCol==oCol) && (i)->canReach(tCol, tRank) ){
                pp = &*i;
                p=static_cast<WPawn *>(pp);   
                return p;
            }
        ++i;
        }
        i=wPawns.begin();
        while (i != wPawns.end()){
            if ((i)->onBoard && (i)->canReach(tCol, tRank) ){
                pp = &*i;
                p=static_cast<WPawn *>(pp);   
                return p;
            }
        ++i;
        }
        return p;
}

BPawn *Board::findBPawnTo(char oCol, int oRank,char tCol, int tRank, bool capture){
        BPawn *p=NULL;
        char rCol;
        int rRank;
        Piece *pp;
        list<BPawn>::iterator i=bPawns.begin();
        while (i != bPawns.end()){
            rCol=(i)->col;
            rRank=(i)->rank;
            if ((i)->onBoard && (rCol==oCol) && (rRank==oRank)){
                pp = &*i;
                p=static_cast<BPawn *>(pp);   
                return p;
            }
            ++i;
        }
        i=bPawns.begin();
        while (i != bPawns.end()){
            rCol=(i)->col;
            rRank=(i)->rank;
            if ((i)->onBoard && (rCol==oCol) && (i)->canReach(tCol, tRank)){
                pp = &*i;
                p=static_cast<BPawn *>(pp);   
                return p;
            }
        ++i;
        }
        i=bPawns.begin();
        while (i != bPawns.end()){
            if ((i)->onBoard && (i)->canReach(tCol, tRank)){
                pp = &*i;
                p=static_cast<BPawn *>(pp);   
                return p;
            }
        ++i;
        }
        return p;
}

//________________________



bool Board::isABlackPiecePreventingKsideCastling(){
    bool check=false;
    list<Piece>::iterator i=black.begin();
    Piece *pp;
    char type=' ';
    while (i != black.end()){
        type=i->type;
        pp = &*i;
        if (i->onBoard){
            switch (type){
                case 'p':
                    {
                    BPawn* p=static_cast<BPawn *>(pp);
                    check=((p)->canReach('e',1) || (p)->canReach('f',1) || (p)->canReach('g',1));
                    }
                    break;
                case 'r':
                    {
                    Rook* r=static_cast<Rook *>(pp);
                    check=((r)->canReach('e',1) || (r)->canReach('f',1) || (r)->canReach('g',1));
                    }
                    break;
                case 'n':
                    {Knight* n=static_cast<Knight *>(pp);
                    check=((n)->canReach('e',1) || (n)->canReach('f',1) || (n)->canReach('g',1));
                    }
                    break;
                case 'b':
                    {Bishop* b=static_cast<Bishop *>(pp);
                    check=((b)->canReach('e',1) || (b)->canReach('f',1) || (b)->canReach('g',1));
                    }
                    break;
                case 'q':
                    {Queen* q=static_cast<Queen *>(pp);
                    check=((q)->canReach('e',1) || (q)->canReach('f',1) || (q)->canReach('g',1));
                    }
                    break;
                case 'k':
                    {
                    King* k=static_cast<King *>(pp);
                    check=((k)->canReach('e',1) || (k)->canReach('f',1) || (k)->canReach('g',1));
                    }
                    break;
                default:
                    check=false;
                    break;                
            }
        }
        if (check){
            break;
        }
        ++i;
    }
    return check;
 }

 bool Board::isAWhitePiecePreventingKsideCastling(){
    bool check=false;
    list<Piece>::iterator i=white.begin();
    Piece *pp;
    char type=' ';
    while (i != white.end()){
        type=i->type;
        pp = &*i;
        if (i->onBoard){
            switch (type){
                case 'p':
                    {
                    WPawn* p=static_cast<WPawn *>(pp);
                    check=(p)->canReach('e',8) || (p)->canReach('f',8) || (p)->canReach('g',8);
                    }
                    break;
                case 'r':
                    {
                    Rook* r=static_cast<Rook *>(pp);
                    check=(r)->canReach('e',8) || (r)->canReach('f',8) || (r)->canReach('g',8);
                    }
                    break;
                case 'n':
                    {
                    Knight* n=static_cast<Knight *>(pp);
                    check=(n)->canReach('e',8) || (n)->canReach('f',8) || (n)->canReach('g',8);
                    }
                    break;
                case 'b':
                    {
                    Bishop* b=static_cast<Bishop *>(pp);
                    check=(b)->canReach('e',8) || (b)->canReach('f',8) || (b)->canReach('g',8);
                    }
                    break;
                case 'q':
                    {
                    Queen* q=static_cast<Queen *>(pp);
                    check=(q)->canReach('e',8) || (q)->canReach('f',8) || (q)->canReach('g',8);
                    }
                    break;
                case 'k':
                    {
                    King* k=static_cast<King *>(pp);
                    check=(k)->canReach('e',8) || (k)->canReach('f',8) || (k)->canReach('g',8);
                    }
                    break;
                default:
                    check=false;
                    break;                
            }
        }
        if (check)
            break;
        ++i;
    }
    return check;
 }

 bool Board::isABlackPiecePreventingQsideCastling(){
    bool check=false;
    list<Piece>::iterator i=black.begin();
    Piece *pp;
    char type=' ';
    while (i != black.end()){
        type=i->type;
        pp = &*i;
        if (i->onBoard){
            switch (type){
                case 'p':
                    {
                        BPawn* p=static_cast<BPawn *>(pp);
                    check=(p)->canReach('e',1) || (p)->canReach('d',1) || (p)->canReach('c',1);
                    }
                    break;
                case 'r':
                    {
                    Rook* r=static_cast<Rook *>(pp);
                    check=(r)->canReach('e',1) || (r)->canReach('d',1) || (r)->canReach('c',1);
                    }
                    break;
                case 'n':
                    {
                    Knight* n=static_cast<Knight *>(pp);
                    check=(n)->canReach('e',1) || (n)->canReach('d',1) || (n)->canReach('c',1);
                    }
                    break;
                case 'b':
                    {
                    Bishop* b=static_cast<Bishop *>(pp);
                    check=(b)->canReach('e',1) || (b)->canReach('d',1) || (b)->canReach('c',1);
                    }
                    break;
                case 'q':
                    {
                    Queen* q=static_cast<Queen *>(pp);
                    check=(q)->canReach('e',1) || (q)->canReach('d',1) || (q)->canReach('c',1);
                    }
                    break;
                case 'k':
                    {
                    King* k=static_cast<King *>(pp);
                    check=(k)->canReach('e',1) || (k)->canReach('d',1) || (k)->canReach('c',1);
                    }
                    break;
                default:
                    check=false;
                    break;                
            }
        }
        if (check)
            break;
        ++i;
    }
    return check;
 }

 bool Board::isAWhitePiecePreventingQsideCastling(){
    bool check=false;
    list<Piece>::iterator i=white.begin();
    Piece *pp;
    char type=' ';
    while (i != white.end()){
        type=i->type;
        pp = &*i;
        if (i->onBoard){
            switch (type){
                case 'p':
                    {
                    WPawn* p=static_cast<WPawn *>(pp);
                    check=(p)->canReach('e',8) || (p)->canReach('d',8) || (p)->canReach('c',8);
                    }
                    break;
                case 'r':
                    {
                    Rook* r=static_cast<Rook *>(pp);
                    check=(r)->canReach('e',8) || (r)->canReach('d',8) || (r)->canReach('c',8);
                    }
                    break;
                case 'n':
                    {
                    Knight* n=static_cast<Knight *>(pp);
                    check=(n)->canReach('e',8) || (n)->canReach('d',8) || (n)->canReach('c',8);
                    }
                    break;
                case 'b':
                    {
                    Bishop* b=static_cast<Bishop *>(pp);
                    check=(b)->canReach('e',8) || (b)->canReach('d',8) || (b)->canReach('c',8);
                    }
                    break;
                case 'q':
                    {
                    Queen* q=static_cast<Queen *>(pp);
                    check=(q)->canReach('e',8) || (q)->canReach('d',8) || (q)->canReach('c',8);
                    }
                    break;
                case 'k':
                    {
                    King* k=static_cast<King *>(pp);
                    check=(k)->canReach('e',8) || (k)->canReach('d',8) || (k)->canReach('c',8);
                    }
                    break;
                default:
                    check=false;
                    break;                
            }
        }
        if (check)
            break;
        ++i;
    }
    return check;
 }


bool Board::wKingCastling(){
    bool valid=false;
    char oCol='h';
    int oRank=1;
    char tCol='e';
    int tRank=1;
    char castlingKCol='g';
    int castlingKRank=1;
    char castlingRCol='f';
    int castlingRRank=1;
    bool capture=false;
    if (wCastling=='B' | wCastling=='K'){
        Rook *rook=findWRookTo(oCol,oRank,tCol,tRank,capture);
        if (!rook->moved){
        //check if a black piece can reach e1, f1, g1
            if (!isABlackPiecePreventingKsideCastling()){
                if (wKing->castle(castlingKCol, castlingKRank) & (rook->castle(castlingRCol, castlingRRank))){
                    valid=true;
                }
            };
        }

    } 
    return valid;
}

bool Board::bKingCastling(){
    bool valid=false;
    char oCol='h';
    int oRank=8;
    char tCol='e';
    int tRank=8;
    char castlingKCol='g';
    int castlingKRank=8;
    char castlingRCol='f';
    int castlingRRank=8;
    bool capture=false;
    if (bCastling=='b' | wCastling=='k'){
        Rook *rook=findBRookTo(oCol,oRank,tCol,tRank,capture);
        if (!rook->moved){
        //check if a black piece can reach e8, f8, g8
            if (!isAWhitePiecePreventingKsideCastling()){
                if (bKing->castle(castlingKCol, castlingKRank) & (rook->castle(castlingRCol, castlingRRank))){
                    valid=true;
                }
            };
        }

    } 
    return valid;
}

bool Board::wQueenCastling(){
    bool valid=false;
    char oCol='a';
    int oRank=1;
    char tCol='d';
    int tRank=1;
    char castlingKCol='c';
    int castlingKRank=1;
    char castlingRCol='d';
    int castlingRRank=1;
    bool capture=false;
    if (wCastling=='B' | wCastling=='Q'){
        Rook *rook=findWRookTo(oCol,oRank,tCol,tRank,capture);
        if (!rook->moved){
        //check if a black piece can reach e1, f1, g1
            if (!isABlackPiecePreventingQsideCastling()){
                if (wKing->castle(castlingKCol, castlingKRank) & (rook->castle(castlingRCol, castlingRRank))){
                    valid=true;
                }
            };
        }

    } 
    return valid;
}
bool Board::bQueenCastling(){
    bool valid=false;
    char oCol='a';
    int oRank=8;
    char tCol='d';
    int tRank=8;
    char castlingKCol='c';
    int castlingKRank=8;
    char castlingRCol='d';
    int castlingRRank=8;
    bool capture=false;
    if (bCastling=='b' | wCastling=='k'){
        Rook *rook=findBRookTo(oCol,oRank,tCol,tRank,capture);
        if (!rook->moved){
        //check if a black piece can reach e8, f8, g8
            if (!isAWhitePiecePreventingQsideCastling()){
                if (bKing->castle(castlingKCol, castlingKRank) & rook->castle(castlingRCol, castlingRRank)){
                    valid=true;
                }
            };
        }

    } 
    return valid;
}




 int Board::processWhiteMove(GameMove *gm){
    char pieceToMove = (gm)->getwPieceMoved();
    char oCol = (gm)->getwOriginColumn();
    int oRank = (gm)->getwOriginRank();
    char tCol = (gm)->getwTargetColumn();
    int tRank = (gm)->getwTargetRank();
    bool capture = (gm)->getwCapture();
    bool kCastling = (gm)->getwKCastling();
    bool qCastling = (gm)->getwQCastling();

    bool validMove=false;
    Rook *rook;
    Knight *knight;
    Bishop *bishop;
    Queen *queen;
    WPawn *pawn;
    bool moved=false;

    string test="KRNBQ";

    if (test.find(pieceToMove)!= string::npos){
        switch (pieceToMove){
            case 'K':
                validMove=wKing->moveTo(tCol,tRank,capture);
                if (validMove){
                    wCastling='n';
                    moved=true;
                }
            break;
            case 'Q':
                queen=findWQueenTo(oCol,oRank,tCol,tRank,capture);
                validMove=queen->moveTo(tCol,tRank,capture);
                if (validMove){
                    moved=true;
                }
            break;
            case 'R':
                rook=findWRookTo(oCol,oRank,tCol,tRank,capture);
                validMove=rook->moveTo(tCol,tRank,capture);
                if (validMove){
                    updateWCastling(oCol,oRank,rook);
                    moved=true;
                }
            break;
            case 'N':
                knight=findWKnightTo(oCol,oRank,tCol,tRank,capture);
                validMove=knight->moveTo(tCol,tRank,capture);
                if (validMove){
                    moved=true;
                }
            break;
            case 'B':
                bishop=findWBishopTo(oCol,oRank,tCol,tRank,capture);
                validMove=bishop->moveTo(tCol,tRank,capture);
                if (validMove){
                    moved=true;
                }
            break;
            default:
                validMove=false;
                moved=false;
            break;
        }
    } 

    if (kCastling & !moved){
        validMove=wKingCastling();
        if (validMove){
            moved=true;
        }
    }   

    if (qCastling & !moved){
        validMove=wQueenCastling();
        if (validMove){
            moved=true;
        }
    }   

    if (!moved){
        pawn=findWPawnTo(oCol,oRank,tCol,tRank,capture); //missing
        validMove=pawn->moveTo(tCol,tRank,capture);
        if (validMove){
            if (pawn->getEnPassant()){
                setEnPassant(tCol,tRank, 'W');
                pawn->setEnPassant(false);
            }
            moved=true;

        }
    }   

    return validMove;




}

void Board::setEnPassant(char col, int rank, char side){
                passant[0]=col;
                passant[1]=rank;
                enPassantSide=side;
}

char Board::getEnPassantSide(){
    return enPassantSide;
}

void  Board::setEnPassantSide(char c){
    enPassantSide=c;
}

int Board::processBlackMove(GameMove *gm){
    char pieceToMove = (gm)->getbPieceMoved();
    char oCol = (gm)->getbOriginColumn();
    int oRank = (gm)->getbOriginRank();
    char tCol = (gm)->getbTargetColumn();
    int tRank = (gm)->getbTargetRank();
    bool capture = (gm)->getbCapture();
    bool kCastling = (gm)->getbKCastling();
    bool qCastling = (gm)->getbQCastling();
    bool validMove=false;
    Rook *rook;
    Knight *knight;
    Bishop *bishop;
    Queen *queen;
    BPawn *pawn;
    bool moved=false;

    string test="KRNBQ";

    if (test.find(pieceToMove)!= string::npos){
        switch (pieceToMove){
            case 'K':
                validMove=bKing->moveTo(tCol,tRank,capture);
                if (validMove){
                    bCastling='n';
                    moved=true;
                }
            break;
            case 'Q':
                queen=findBQueenTo(oCol,oRank,tCol,tRank,capture);
                validMove=queen->moveTo(tCol,tRank,capture);
                if (validMove){
                    moved=true;
                }
            break;
            case 'R':
                rook=findBRookTo(oCol,oRank,tCol,tRank,capture);
                validMove=rook->moveTo(tCol,tRank,capture);
                if (validMove){
                    updateBCastling(oCol, oRank, rook);
                    moved=true;
                }
            break;
            case 'N':
                knight=findBKnightTo(oCol,oRank,tCol,tRank,capture);
                validMove=knight->moveTo(tCol,tRank,capture);
                if (validMove){
                    moved=true;
                }
            break;
            case 'B':
                bishop=findBBishopTo(oCol,oRank,tCol,tRank,capture);
                validMove=bishop->moveTo(tCol,tRank,capture);
                if (validMove){
                    moved=true;
                }
            break;
            default:
                validMove=false;
                moved-false;
            break;
        }
    } 

    if (kCastling & !moved){
        validMove=bKingCastling();
        if (validMove){
            moved=true;
        }
    }   

    if (qCastling & !moved){
        validMove=bQueenCastling();
        if (validMove){
            moved=true;
        }
    }   

    if (!moved){
        pawn=findBPawnTo(oCol,oRank,tCol,tRank,capture); 
        validMove=pawn->moveTo(tCol,tRank,capture);

        if (validMove){
            if (pawn->getEnPassant()){
                setEnPassant(tCol,tRank, 'B');
                pawn->setEnPassant(false);
            }
            moved=true;

        }
    }   

    return validMove;

}

void Board::updateWCastling(char oCol, int oRank,Rook *r){

    if ( oRank==1) {
        if (oCol=='a'){
            if (wCastling=='B'){
                wCastling='K';
            }
            if (wCastling=='K'){
                wCastling='n';
            }
        }  
        if (oCol=='h'){
            if (wCastling=='B'){
                wCastling='Q';
            }
            if (wCastling=='Q'){
                wCastling='n';
            }
        }  

    } 
}

void Board::updateBCastling(char oCol, int oRank,Rook *r){

    if ( oRank==8) {
        if (oCol=='a'){
            if (bCastling=='b'){
                bCastling='k';
            }
            if (bCastling=='k'){
                bCastling='n';
            }
        }  
        if (oCol=='h'){
            if (bCastling=='b'){
                bCastling='q';
            }
            if (bCastling=='q'){
                bCastling='n';
            }
        }  

    } 
}

void Board::initializeBlackPiece(struct Cell *current, char c){
    BPawn* p;
    Rook* r;
    Knight* n;
    Bishop* b;
    Queen* q;
    King* k;

    switch (c)  {
    case 'p':
        p = new BPawn(current);
        current->piece=p;
        p->isBlackPiece=true;
        p->onBoard=true;
        bPawns.push_back((BPawn ) *p);
        black.push_back( *p); 
        break;
    case 'r':
        r = new Rook(current);
        current->piece=r;
        r->isBlackPiece=true;
        r->onBoard=true;
        bRooks.push_back((Rook ) *r); 
        black.push_back( *r); 
        break;
    case 'n':
        n = new Knight(current);
        current->piece=n;
        n->isBlackPiece=true;
        n->onBoard=true;
        bKnights.push_back((Knight ) *n); 
        black.push_back( *n); 
        break;
    case 'b':
        b = new Bishop(current);
        current->piece=b;
        b->isBlackPiece=true;
        b->onBoard=true;
        bBishops.push_back((Bishop ) *b); 
        black.push_back( *b); 
        break;
    case 'q':
        q = new Queen(current);
        current->piece=q;
        q->isBlackPiece=true;
        q->onBoard=true;
        bQueens.push_back((Queen ) *q); 
        black.push_back( *q); 
        break;
    case 'k':
        k = new King(current);
        current->piece=k;
        k->onBoard=true;
        k->isBlackPiece=true;
        bKing=k; 
        black.push_back( *k); 
        break;
    default:
         break;
    }
}
void Board::initializeWhitePiece(struct Cell *current, char c){
    WPawn* p;
    Rook* r;
    Knight* n;
    Bishop* b;
    Queen* q;
    King* k;
    
    switch (c)  {
    case 'P':
        p = new WPawn(current);
        current->piece=p;
        p->isBlackPiece=false;
        p->onBoard=true;
        wPawns.push_back((WPawn ) *p); 
        white.push_back( *p);
        break;
    case 'R':
        r = new Rook(current);
        current->piece=r;
        r->onBoard=true;
        r->isBlackPiece=false;
        wRooks.push_back((Rook ) *r); 
        white.push_back( *r);
        break;
    case 'N':
        n = new Knight(current);
        current->piece=n;
        n->onBoard=true;
        n->isBlackPiece=false;
        wKnights.push_back((Knight ) *n); 
        white.push_back( *n);
        break;
    case 'B':
        b = new Bishop(current);
        current->piece=b;
        b->onBoard=true;
        b->isBlackPiece=false;
        wBishops.push_back((Bishop ) *b); 
        white.push_back( *b);
        break;
    case 'Q':
        q = new Queen(current);
        current->piece=q;
        q->onBoard=true;
        q->isBlackPiece=false;
        wQueens.push_back((Queen ) *q); 
        white.push_back( *q);
        break;
    case 'K':
        k = new King(current);
        current->piece=k;
        k->onBoard=true;
        k->isBlackPiece=false;
        wKing=k; 
        white.push_back( *k);
        break;
    default:
         break;
    }
}