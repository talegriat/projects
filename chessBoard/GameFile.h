#include <stdlib.h>
#include <string> 
#include <fstream>  
#include <list>
#include <regex>
#include <iostream>    
using namespace std;
#define BLACK true
#define WHITE false

class GameMove {
    string match;               //Match   						0
    string fullMove;            //Full Move						1
    string fullMoveNumber;      //Full Move number				2
    int moveNumber=0;           //Move Number					3
    char dummy=' ';             //Format character				4
    string fullwMove;           //Full white move				5
    string wMove;               //White move					6
    char wPieceMoved=' ';       //Piece Moved [RNBKQ]			7
    string wOriginCell;        //origin Cell					8
    char wOriginColumn='z';     //origin Column					9
    int wOriginRank=0;          //Origin rank					10
    char wCapture='-'  ;        //Capture? (x)					11
    string wTargetCell;         //Target Cell					12
    char wTargetColumn='z';     //Target Column					13
    int wTargetRank=0;          //target rank					14
    char wPromoteTo='P';        //CoronarPor  "=Q|R|N|B"    	15
    string wCastling;           //enroque  O-O-O or O-O 	    16
    char wCheck='-';            //Check or mate	+ or #			17
    string fullbMove;           //Full black move				18
    string bMove;               //Black move					19
    char bPieceMoved=' ';       //Piece Moved					20
    string bOriginCell;        //origin Cell					21
    char bOriginColumn='z';     //origin Column					22
    int bOriginRank=0;          //Origin rank					23
    char bCapture='-'  ;        //Capture?						24
    string bTargetCell;         //Target Cell					25
    char bTargetColumn='z';     //Target Column					26
    int bTargetRank=0;          //target rank					27
    char bPromoteTo='P';        //CoronarPor  "=Q|R|N|B"    	28
    string bCastling;           //enroque  O-O-O or O-O 		29
    char bCheck='-';            //Check or mate	+ or #			30
    string fullResult;          //Full result					31
    string winResult;           //White/black win 1-0 or 0-1	32
    string draw;                //Draw 1/2-1/2                  33
    

public:
    void setMatch(string );
    void setMoveNumber(string );
    void setMoveNumber(int );
    void setFullwMove(string );
    void setwMove(string);
    void setwPieceMoved(string );
    void setwPieceMoved(char);
    void setwOriginCell(string );
    void setwOriginColumn(string );
    void setwOriginColumn(char );
    void setwOriginRank(string );
    void setwOriginRank(int );
    void setwCapture(string );
    void setwCapture(char );
    void setwTargetCell(string );
    void setwTargetColumn(string );
    void setwTargetColumn(char );
    void setwTargetRank(string );
    void setwTargetRank(int );
    void setwPromoteTo(string );
    void setwPromoteTo(char );
    void setwCastling(string );
    void setwCheck(string );
    void setwCheck(char );
    void setFullbMove(string );
    void setbMove(string );
    void setbPieceMoved(string );
    void setbPieceMoved(char  );
    void setbOriginCell(string );
    void setbOriginColumn(string );
    void setbOriginColumn(char );
    void setbOriginRank(string );
    void setbOriginRank(int );
    void setbCapture(string );
    void setbCapture(char );
    void setbTargetCell(string );
    void setbTargetColumn(string );
    void setbTargetColumn(char );
    void setbTargetRank(string );
    void setbTargetRank(int );
    void setbPromoteTo(string );
    void setbPromoteTo(char );
    void setbCastling(string );
    void setbCheck(string );
    void setbCheck(char );
    void setFullResult(string );
    void setWinResult(string );
    void setDraw(string );
    string getWhiteMove();
    string getBlackMove();
    int getMoveNumber();
    string getFullResult( );
    char getwPieceMoved();
    char getwOriginColumn();
    int getwOriginRank();
    char getwTargetColumn();
    int getwTargetRank();
    bool getwCapture();
    bool getwKCastling();
    bool getwQCastling();
    char getbPieceMoved();
    char getbOriginColumn();
    int getbOriginRank();
    char getbTargetColumn();
    int getbTargetRank();
    bool getbCapture();
    bool getbKCastling();
    bool getbQCastling();
    char getwPromoteTo();
    char getbPromoteTo();
    GameMove();
};

GameMove::GameMove(){

}
char GameMove::getwPromoteTo(){
    return wPromoteTo;
}

char GameMove::getbPromoteTo(){
    return bPromoteTo;
}

char GameMove::getwPieceMoved(){
    return wPieceMoved;
}
char GameMove::getwOriginColumn(){
    return wOriginColumn;
}
int GameMove::getwOriginRank(){
    return wOriginRank;
}
char GameMove::getwTargetColumn(){
    return wTargetColumn;
}
int GameMove::getwTargetRank(){
    return wTargetRank;
}
bool GameMove::getwCapture(){
    if (wCapture=='x'){
        return true;
    } 
    return false;
}
bool GameMove::getwKCastling(){
    if (wCastling=="O-O"){
        return true;
    } 
    return false;
}
bool GameMove::getwQCastling(){
    if (wCastling=="O-O-O"){
        return true;
    } 
    return false;
}
char GameMove::getbPieceMoved(){
    return bPieceMoved;
}
char GameMove::getbOriginColumn(){
    return bOriginColumn;
}
int GameMove::getbOriginRank(){
    return bOriginRank;
}
char GameMove::getbTargetColumn(){
    return bTargetColumn;
}
int GameMove::getbTargetRank(){
    return bTargetRank;
}
bool GameMove::getbCapture(){
    if (bCapture=='x'){
        return true;
    } 
    return false;
}
bool GameMove::getbKCastling(){
    if (bCastling=="O-O"){
        return true;
    } 
    return false;
}
bool GameMove::getbQCastling(){
    if (bCastling=="O-O-O"){
        return true;
    } 
    return false;
}

//---------------------------------------

string GameMove::getFullResult( ){
    return  fullResult;
}

string GameMove::getWhiteMove(){
    return wMove;
}

string GameMove::getBlackMove(){
    return bMove;
}

int GameMove::getMoveNumber(){
    return moveNumber;
}

void GameMove::setMatch(string s){
    match="Empty";
    if (!s.empty()) {
        match=s;
    }

}

//Move Number					3
void GameMove::setMoveNumber(string s){
        int x=0;
        stringstream aux;
        aux<<s;                         
        aux>>x;
        setMoveNumber(x);
}           

void GameMove::setMoveNumber(int x){
    if (x>0){
        moveNumber=x;
    }
}           

//Full white move				5
void GameMove::setFullwMove(string s){
    fullwMove="";
    if (!s.empty()) {
        fullwMove=s;
    }

    
}

//White move					6
void GameMove::setwMove(string s){
    wMove="";
    if (!s.empty()) {
        wMove=s;
    }

}

//Piece Moved [RNBKQ]			7
void GameMove::setwPieceMoved(string s){
    wPieceMoved=' ';
    if (!s.empty()) {
    setwPieceMoved(s[0]);
    }
}

void GameMove::setwPieceMoved(char c){
    string test="RNBQK";
    if (test.find(c)!= string::npos){
        wPieceMoved=c;
    } else {
        wPieceMoved=' ';
    }
}

//origin Cell					8
void GameMove::setwOriginCell(string s){
    wOriginCell ="";
    if (!s.empty()) {
        wOriginCell=s;
    }    
}

//origin Column					9
void GameMove::setwOriginColumn(string s){
    wOriginColumn=' ';
    if (!s.empty()) {
    setwOriginColumn(s[0]);
    }
}

//origin Column					9
void GameMove::setwOriginColumn(char c){
    string test="abcdefgh";
    if (test.find(c)!= string::npos){
        wOriginColumn=c;
    } else {
        wOriginColumn=' ';
    }
}

//Origin rank					10
void GameMove::setwOriginRank(string s){
    int x=0;
    stringstream aux;
    aux<<s;                          
    aux>>x;
    setwOriginRank(x);
}

void GameMove::setwOriginRank(int i){
    if (i>0 && i<9){
        wOriginRank=i;
    }
}

//Capture? (x)					11
void GameMove::setwCapture(string s){
    wCapture=' ';
    if (!s.empty()) {
        setwCapture(s[0]);
    }
}

//Capture? (x)					11
void GameMove::setwCapture(char c){
    string test="RNBQK";
    if (c =='x'){
        wCapture=c;
    } else {
        wCapture=' ';
    }        
}                         

//Target Cell					12
void GameMove::setwTargetCell(string s){
    wTargetCell ="";
    if (!s.empty()) {
        wTargetCell=s;
    }    
}


//Target Column					13
void GameMove::setwTargetColumn(string s){
    wTargetColumn=' ';
    if (!s.empty()) {
    setwTargetColumn(s[0]);
    }
}

//Target Column					13
void GameMove::setwTargetColumn(char c){
    string test="abcdefgh";
    if (test.find(c)!= string::npos){
        wTargetColumn=c;
    } else {
        wTargetColumn=' ';
    }
}


//target rank					14
void GameMove::setwTargetRank(string s){
    int x=0;
    stringstream aux;
    aux<<s;                          
    aux>>x;
    setwTargetRank(x);
}

//target rank					14
void GameMove::setwTargetRank(int i){
    if (i>0 && i<9){
        wTargetRank=i;
    }
}


//CoronarPor  "=Q|R|N|B"    	15
void GameMove::setwPromoteTo(string s){
    char c =s[1];
    setwPromoteTo(c);
  
}

void GameMove::setwPromoteTo(char c){
    string test="RNBQ";

    if (test.find(c)!= string::npos){
        wPromoteTo=c;
    } else {
        wPromoteTo=' ';
    }
   
}                      

//enroque  O-O-O or O-O 	    16
void GameMove::setwCastling(string s){
    wCastling=' ';
    if (!s.empty()) {
        wCastling=s;
    }
}                         

//Check or mate	+ or #			17
void GameMove::setwCheck(string s){
    char c =s[0];
    setwCheck(c);
}

void GameMove::setwCheck(char c){
     string test="+#";

    if (test.find(c)!= string::npos){
        wCheck=c;
    } else {
        wCheck=' ';
    }   
}

//Full black move				18
void GameMove::setFullbMove(string s){
    fullbMove="";
    if (!s.empty()) {
        fullbMove=s;
    }
}

//Black move					19
void GameMove::setbMove(string s){
    bMove="";
    if (!s.empty()) {
        bMove=s;
    }
}

//Piece Moved					20
void GameMove::setbPieceMoved(string s){
    bPieceMoved=' ';
    if (!s.empty()) {
    setbPieceMoved(s[0]);
    }
}

void GameMove::setbPieceMoved(char c){
    string test="RNBQK";
    if (test.find(c)!= string::npos){
        bPieceMoved=c;
    } else {
        bPieceMoved=' ';
    }
}

//origin Cell					21

void GameMove::setbOriginCell(string s){
    bOriginCell ="";
    if (!s.empty()) {
        bOriginCell=s;
    }    
}

//origin Column					22
void GameMove::setbOriginColumn(string s){
    bOriginColumn=' ';
    if (!s.empty()) {
    setbOriginColumn(s[0]);
    }
}

void GameMove::setbOriginColumn(char c){
    string test="abcdefgh";
    if (test.find(c)!= string::npos){
        bOriginColumn=c;
    } else {
        bOriginColumn=' ';
    }
}

//Origin rank					23
void GameMove::setbOriginRank(string s){
    int x=0;
    stringstream aux;
    aux<<s;                          
    aux>>x;
    setbOriginRank(x);
}

void GameMove::setbOriginRank(int i){
    if (i>0 && i<9){
        bOriginRank=i;
    }
}

//Capture?						24
void GameMove::setbCapture(string s){
    bCapture=' ';
    if (!s.empty()) {
        setbCapture(s[0]);
    }
}

void GameMove::setbCapture(char c){
    string test="RNBQK";
    if (c =='x'){
        bCapture=c;
    } else {
        bCapture=' ';
    }        
}                         

//Target Cell					25
void GameMove::setbTargetCell(string s){
    bTargetCell ="";
    if (!s.empty()) {
        bTargetCell=s;
    }    
}


//Target Column					26
void GameMove::setbTargetColumn(string s){
    bTargetColumn=' ';
    if (!s.empty()) {
    setbTargetColumn(s[0]);
    }
}

void GameMove::setbTargetColumn(char c){
    string test="abcdefgh";
    if (test.find(c)!= string::npos){
        bTargetColumn=c;
    } else {
        bTargetColumn=' ';
    }
}


//target rank					27
void GameMove::setbTargetRank(string s){
    int x=0;
    stringstream aux;
    aux<<s;                          
    aux>>x;
    setbTargetRank(x);
}

void GameMove::setbTargetRank(int i){
    if (i>0 && i<9){
        bTargetRank=i;
    }
}


//CoronarPor  "=Q|R|N|B"    	28
void GameMove::setbPromoteTo(string s){
    char c =s[1];
    setbPromoteTo(c);
}

void GameMove::setbPromoteTo(char c){
    string test="RNBQ";

    if (test.find(c)!= string::npos){
        bPromoteTo=c;
    } else {
        bPromoteTo=' ';
    }
   
}                      

//enroque  O-O-O or O-O 		29
void GameMove::setbCastling(string s){
    bCastling=' ';
    if (!s.empty()) {
        bCastling=s;
    }
}                         

//Check or mate	+ or #			30
void GameMove::setbCheck(string s){
    char c =s[0];
    setbCheck(c);
}

void GameMove::setbCheck(char c){
     string test="+#";

    if (test.find(c)!= string::npos){
        bCheck=c;
    } else {
        bCheck=' ';
    }   
}

//Full result					31
void GameMove::setFullResult(string s){
    if (!s.empty()) {
        fullResult=s;
    }
    
}                             

//White/black win 1-0 or 0-1	32
void GameMove::setWinResult(string s){
    
}                              

void GameMove::setDraw(string s){
    
}            



class GameFile {
public:
    char movesString[2000];
    int movesStringSize=0;
    int current=0;
    int totalGames=0;
    list<GameMove> gameMoves;
    char * gamesList[2000];
    //GameFile();
    void processFile(string);
    char *moveList();
    void parseMoves(char *);
    list<GameMove> getGameMoves();
    bool hasMoreGames();
    list<GameMove> getNextGameMoves();
    string currentGame();

};

string GameFile::currentGame(){
    string s="Current Game -- ";
    string z;
    stringstream x;
    x<<current;
    x>>z;
    s=s+z+" -- ";
    s+=gamesList[current];
    
    return s;
}

list<GameMove> GameFile::getNextGameMoves(){
    list<GameMove> gM;
    if (current<totalGames){
        parseMoves(gamesList[current++]);
        return gameMoves;
    } else
    return gM;
}

bool GameFile::hasMoreGames(){
    if (current<totalGames)
        return true;
    return false;
}

void GameFile::processFile(string fileName){
    fstream inFile;
    int i=0;
    std::string strx;
    char * stry;
    inFile.open(fileName);
    if (!inFile.is_open()) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    while (getline(inFile, strx) && i<2000) {
        if((strx.find('[')== string::npos) &&(strx.find("     ")== string::npos ) &&(strx.length()>0) ){
            stry=(char *) malloc (2000 * sizeof *stry);
            strx.copy(movesString,strx.length(),0);
            movesString[strx.length()]='\0';
            movesStringSize=strx.length();
            strx.copy(stry,strx.length(),0);
            stry[strx.length()]='\0';
            gamesList[i++]=stry;
            totalGames=i;
        }
        
    }    
}

//char *GameFile::moveList(){
//    return movesString;
//}

void GameFile::parseMoves(char * movesStr){
    string moves=movesStr;
    gameMoves.clear();
    regex str_pgnExpr ("(((\\d+)(\\.)) ((([PNBRQK]?)(([a-h]?)([1-8]?)?)([x]?)(([a-h])([1-8]))(=[NBRQ]+)?|(O\\-O\\-O|O\\-O))(\\+|\\#)?)(  )?((([PNBRQK]?)(([a-h]?)([1-8]?)?)([x]?)(([a-h])([1-8]))(=[NBRQ]+)?|(O\\-O\\-O|O\\-O))?(\\+|\\#)?))( )?|(([10][\\-][10])|(1\\/2[\\-]1\\/2))*"); 
    smatch m;
    int i=0;


    while (moves.length()!=0 ) {
        regex_search (moves,m,str_pgnExpr);
        GameMove* gm=new GameMove();
        string match=m[0];
        int lengthMatch=match.length();
        gm->setMatch(m[0]);                  //Match   						0
        gm->setFullResult(m[33]);                  //Full result					31
        gm->setWinResult(m[34]);                   //White/black win 1-0 or 0-1	32
        gm->setDraw(m[35]);                        //Draw 1/2-1/2                  33   
        //string fullMove;                  //Full Move						1
        //string fullMoveNumber;            //Full Move number				2

        gm->setMoveNumber(m[3]);           
        //char dummy=' ';                   //Format character				4
        gm->setwPromoteTo(m[15]);            //CoronarPor  "=Q|R|N|B"    	15
        gm->setwCastling(m[16]);             //enroque  O-O-O or O-O 	    16
        gm->setwCheck(m[17]);                //Check or mate	+ or #			17
        gm->setwCapture(m[11]);              //Capture? (x)					11
        gm->setwPieceMoved(m[7]);            //Piece Moved [RNBKQ]			7
        gm->setwOriginColumn(m[9]);           //origin Column					9
        gm->setwOriginRank(m[10]);           //Origin rank					10
        gm->setwOriginCell(m[8]);           //origin Cell					8
        gm->setwTargetColumn(m[13]);         //Target Column					13
        gm->setwTargetRank(m[14]);           //target rank					14
        gm->setwTargetCell(m[12]);          //Target Cell					12
        gm->setwMove(m[6]);                  //White move					6
        gm->setFullwMove(m[5]);              //Full white move				5



        gm->setbPromoteTo(m[29]);            //CoronarPor  "=Q|R|N|B"    	28
        gm->setbCastling(m[30]);             //enroque  O-O-O or O-O 		29
        gm->setbCheck(m[31]);                //Check or mate	+ or #			30
        gm->setbCapture(m[25]);              //Capture?						24
        gm->setbPieceMoved(m[21]);           //Piece Moved					20
        gm->setbOriginColumn(m[23]);         //origin Column					22
        gm->setbOriginRank(m[24]);           //Origin rank					23
        gm->setbOriginCell(m[22]);          //origin Cell					21
        gm->setbTargetColumn(m[27]);         //Target Column					26
        gm->setbTargetRank(m[28]);           //target rank					27
        gm->setbTargetCell(m[26]);           //Target Cell					25
        gm->setbMove(m[20]);                 //Black move					20
        gm->setFullbMove(m[19]);             //Full black move				19
        
        gameMoves.push_back((GameMove)*gm);
        moves=moves.substr(lengthMatch);



    }
}

