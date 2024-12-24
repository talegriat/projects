//Comparacion de llamada por valor, llamada por referencia con punteros y 
//llamada por referencia con referencias

#include<iostream>

using namespace std;

//prototipos
int squarebyvalue(int a);
void squarebypointer(int *bptr);
void squarebyreference(int &);

int main(){
    int x=2, y=3, z=4;
    cout<<"x= "<<x<<" Antes de SquareByValue"<<endl<<"Valor devuelto por SquareByValue: "<<squarebyvalue(x)<<
    "\nx= "<<x<<" Despues de SquereByValue"<<endl<<endl;

    squarebypointer(&y);
    cout<<"y= "<<y<<" despues de SquareByPointer "<<endl;
    cout<<"z= "<<z<<"Antes de SquareByReference"<<endl;
    squarebyreference(z);
    cout<<"z= "<<z<<" despues de SquareByPointer "<<endl;

}

int squarebyvalue(int a){
    return a*=a;
    //Argumento de la llamada no modificado
}

void squarebypointer(int *bptr){
    *bptr *= *bptr;//Argumento de la llamada modificado
}

void squarebyreference(int &cref){
    cref *=cref; //Argumento de la llamada modificado
}

