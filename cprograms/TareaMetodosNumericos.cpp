//Tomas Alberto Alegria Martinez 
//Tarea: Introduccion a los metodos numericos
#include<iostream>
#include <math.h>
using namespace std;
void fraccBin(double n);

int main(){
    //1
    double n;
    int limite;
    double x;
    double y;
    n=0.1;
    fraccBin(n);
    n=0.125;
    fraccBin(n);


}

void fraccBin(double n){
    //1- Convierta los siguientes numeros en fracciones bunarias de la forma 0.d1d2..dndos.
    //a) 0.1
    double R;
    int  d[10];
    double f;
    int entero;
    double decimal;
    //modf para separar parte entera y decimal 

    f=n;
    for(int i=0; i<10; i++){
        R=f*2;
        entero=(int) R;
        d[i]=entero;
        if(entero==1){
            f=R-entero;
        }
        else{
            f=f*2;
        }
        

    }
    cout<<"Respuesta: 0.";
    for(int i=0; i<10; i++){
        cout<<d[i];
    }
    cout<<endl;
   
}

