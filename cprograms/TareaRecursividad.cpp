//Tomas Alberto alegria Martinez
//Practica 1 de recursividad


#include <iostream>
#define Col 5

using namespace std;
int menu();
int division(int a, int b);
int invertir(int n);
int sumar_dig(int n);
int sumVec(int v[],int n);
int multiplicar(int vec[],int tam);
int sacar_mcd(int a,int b);
bool negativo(int n);
bool positivo(int n);
int sumMat(int fila, int col, int orden, int **mat);







int main(){
menu();
return 0;
}


int menu(){
    int opc;
    do{

    
    cout<<"Elija alguna de los siguientes ejercicios: "<<endl;
    cout<<endl<<"1. Funcion recursiva que permita hacer la divisio por restas sucesivas...";
    cout<<endl<<"2. Funcion recursiva que permita invertir un numero...";
    cout<<endl<<"3. Funicon que permita sumar los digitos de un número...";
    cout<<endl<<"4. Funcion que permita sumar los elementos de un vector...";
    cout<<endl<<"5. Funcion que permita multiplicar los elementos de un vector...";
    cout<<endl<<"6. Funcion que calcule el Maximo comun divisor de dos números...";
    cout<<endl<<"7. funcion que determine si un numero es positivo...";
    cout<<endl<<"8. Funcion que permita sumar los elementos de una matriz...";
    cout<<endl<<"9. Salir";
    cout<<endl<<"Respuesta: ";
    cin>>opc;
    switch(opc){
        case 1: 
            break;
        case 2: 
            break;
        case 3: 
            break;
        case 4: 
            break;    
        case 5: 
            break;
        case 6: 
            break;
        case 7: 
            break;
        case 8: 
        
            break;
        
}
 }while(opc>0&&opc<9);

}

int division(int a, int b){
    if(b>a){
        return 0;
    }
    else
        return division(a-b,b)+1;
}


//Programar una funcion recursiva que permita invertir un numero 123,321
int invertir(int n){
    if(n<10){
        return n;
    }
    else{
        return(n%10) + invertir (n/10)*10;
    }
}


//Programar unafuncion recursiva que permita sumar los digitos dde un numero.
int sumar_dig(int n){
    if(n==0){
        return n;
    }
    else{
        return sumar_dig(n/10) + (n%10);
    }
}


//Programar una funcion recursiva que permita sumar los elementos de un vector
int sumVec(int vec[],int n){
    if(n==0){
        return vec[n];
    }
    else{
        return sumVec(vec,n-1) + vec[n];
    }
}


//Programar una funcion rexursiva que permita multiplicar los elementos de un vector.
int multiplicar(int vec[],int tam){
    if(tam==0){
        return(vec[0]);
    }

    return(vec[tam]*multiplicar(vec,tam-1));
}


//Programar una funcion recursiva que calcule el Maximo comun divisor de dos numeros
int sacar_mcd(int a,int b){
    if(b==0){
        return a;
    }
    else {
        return sacar_mcd(b,a%b);
    }
}



//Programar una funcio recursiva que determine si un numero es positivo
bool positivo(int n){
    if(n>0){
        return true;
    }
    else{
        return negativo(n);
    }
}
bool negativo(int n){
    if(n<0){
        return false;
    }
    else{
        return positivo(n);
    }
}


//Programar una funcion recursiva que permitasumar los elementos de una matriz
int sumMat(int fila, int col, int orden, int **mat) {
    if (fila == 0 && col == 0) {
        return mat[0][0];
    } else {
        if (col < 0) {
            return sumMat(fila - 1, orden - 1, orden, mat);
        } else {
            return mat[fila][col] + sumMat(fila, col - 1, orden, mat);
        }
    }
}


