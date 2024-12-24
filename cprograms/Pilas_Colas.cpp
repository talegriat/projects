//Tomas Alberto Alegria Martinez y Ricardo Ramirez Torres
//Tarea 1: Pilas y colas
#include<iostream>
#include<cstring>
#include<string>
#include <string.h>

using namespace std;


//Prototipos 
//menu
void pilas_menu();

//pilas
bool pila_vacia(char pila, int Tope);
bool pila_llena(char pila, int Max,int Tope);
void Push(char *pila, int Tope, int Max, char dato);
char Pop(char *pila, int Tope);
void Conv_A_Posfijo(char *pila,int n);
int prioridad(char simbolo);
//colas



int main(){
    pilas_menu();

}

bool pila_vacia(char pila[], int Tope){
    bool band;
    if(Tope==0){
        band=true;//vacia
    }
    else
        band=false;
    return band;
}


bool pila_llena(char pila[], int Max,int Tope){
    bool band;
    if(Tope==Max){
        band=true;//llena
    
    }
    else
        band=false;
    return band;
}


void Push(char *pila, int Tope, int Max, char dato){
    bool band;
    band=pila_llena(pila,Max,Tope);
    if(band){
        cout<<"Desbordamiento-Pila llena"<<endl;
    }
    else{
        Tope++;
        pila[Tope]=dato;
    }
}


char Pop(char *pila, int Tope){
    int band;
    char dato;
    band=pila_vacia(pila,Tope);
    if(band){
        cout<<"Subdesbordamiento-Pila vacia"<<endl;
    }
    else{
        dato=pila[Tope];
        Tope--;
    }
    return dato;
}
void pilas_menu(){
    int opc;
    string expresion;
    int tamaño;
    int n;
    do{
        cout<<endl<<"     Pilas";
        cout<<endl<<"1.   Push";
        cout<<endl<<"2.   Pop";
        cout<<endl<<"3.   Pila vacia";
        cout<<endl<<"4.   Pila llena";
        cout<<endl<<"5.   Conversion a Posfija";
        cout<<endl<<"6.   Conversion a Prefija";
        cout<<endl<<"7.   Salir";
        cout<<endl<<"Opcion: ";
    fflush(stdin);
    cin>>opc;
    }while(opc<1||opc>3);

        switch(opc){
        case 1: break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5:   
                        cout<<"Dame la expresion que deseas convertir: ";
                        getline(cin,expresion);
                        n=0; 
                        tamaño = expresion.length(); //para saber la cantidad de caracteres que se encuentran en la cadena
                        
                        char *Ele= new char [tamaño+1];
                        strcpy(Ele,expresion.c_str());
                        n=tamaño+1;
                        
                        Conv_A_Posfijo(Ele,n);
                        delete[]Ele;
                        break; 

        case 6:  
                        cout<<"Dame la expresion que deseas convertir: ";
                        getline(cin,expresion);
                        n=0; 
                        tamaño = expresion.length(); //para saber la cantidad de caracteres que se encuentran en la cadena
                        
                        char *El = new char [tamaño + 1];
                        strcpy(El,expresion.c_str());
                        n=tamaño+1;
                        Conv_prefija(El,n);
                        delete[]El;
                    
                    break;

    }
    


}


void Conv_A_Posfijo(char *El,int n){
    int tope=0;
    char dato ;   
    int cont = n;
    int izq=0;
    char pila[n];
    char epos[n];
    int en=0;
    char simbolo;
    bool band;
    int orden;
    int ordenp;


    while(cont>=0){
        dato=El[izq];
        El[izq]=' ';
        izq++;
        cont--;
        if(dato='('){
            if(pila_llena(pila,n,tope)==false){
                Push(pila,tope,n,dato);
            }
            else{
                cout<<endl<<"La pila esta llena"<<endl;
                break;
            }
        }
        else{
            if(dato=')'){
                while(pila[tope]!='('){
                    dato=Pop(pila,tope);
                    epos[en]=dato;
                    en++;
                }
                dato=Pop(pila,tope);

            }
            else{
                if(dato=='*'||dato=='^'||dato=='/'||dato=='+'||dato=='-'){//operadores
                    band=pila_vacia(pila,tope);
                    orden=prioridad(dato);
                    ordenp=prioridad(pila[tope]);
                    while(band=false&&orden<ordenp){
                        //falta la prioridad del operador
                        simbolo=Pop(pila,tope);
                        epos[en]=simbolo;
                        en++;
                        band=pila_vacia(pila,tope);
                    }
                        Push(pila,tope,n,dato);

                }
                else{
                    //Esun operando
                    epos[en]=dato;
                    en++;
                }



            }
        }


    }
    while(band=false){
        dato=Pop(pila,tope);
        epos[en]=dato;
        en++;
        band=pila_vacia(pila,tope);
    }
    cout<<"La expresion convertida a posfija es: "<<endl;
    for(int i=0; i<n;i++){
        cout<<epos[i];
    }
    
}


void Conv_prefija(char *El,int n){
    int tope=0;
    char dato ;   
    int cont = n;
    int izq=0;
    char pila[n];
    char epre[n];
    int en=0;
    char simbolo;
    bool band;
    int orden;
    int ordenp;


    while(cont>=0){
        dato=El[cont];
        El[cont]=' ';
        cont--;
        if(dato=')'){
            if(pila_llena(pila,n,tope)==false){
                Push(pila,tope,n,dato);
            }
            else{
                cout<<endl<<"La pila esta llena"<<endl;
                break;
            }
        }
        else{
            if(dato='('){
                while(pila[tope]!=')'){
                    dato=Pop(pila,tope);
                    epre[en]=dato;
                    en++;
                }
                dato=Pop(pila,tope);

            }
            else{
                if(dato=='*'||dato=='^'||dato=='/'||dato=='+'||dato=='-'){//operadores
                    band=pila_vacia(pila,tope);
                    orden=prioridad(dato);
                    ordenp=prioridad(pila[tope]);
                    while(band=false&&orden>ordenp){
                        simbolo=Pop(pila,tope);
                        epre[en]=simbolo;
                        en++;
                        band=pila_vacia(pila,tope);
                    }
                        Push(pila,tope,n,dato);

                }
                else{
                    //Esun operando
                    epre[en]=dato;
                    en++;
                }



            }
        }


    }
    while(band=false){
        dato=Pop(pila,tope);
        epre[en]=dato;
        en++;
        band=pila_vacia(pila,tope);
    }
    cout<<"La expresion convertida a prefija es: "<<endl;
    for(int i=n-1; i>=0;i--){
        cout<<epre[i];
    }
}

int prioridad(char simbolo){
    int orden;
    switch(simbolo){
        case '^':
            orden=1;
            break;
        case '/':
            orden=2;
            break;
        case '*':
            orden=2;
            break;
        case '-':
            orden=3;
            break;
        case '+':
            orden=3;
            break;
        default: 
            orden=4;
            break;
        
    }
    return orden;
}
