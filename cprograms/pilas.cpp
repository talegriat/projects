//Tomas Alberto Alegria Martinez y Ricardo Ramirez Torres
//Tarea 1: Pilas y colas
// Corrección de código
#include <iostream>
#include <cstring>
#include <string>
#include <string.h>
#include <stdio.h>

using namespace std;

// Prototipos
void pilas_menu(void);
bool pila_vacia(char pila[], int Tope);
bool mpila_vacia(char pila[], int Tope);
int operacion(int x, int y, char simb);
bool pila_llena(char pila[], int Max, int Tope);
bool mpila_llena(char pila[], int Max, int Tope);
int Push(char *pila, int Tope, int Max, char dato);
int mPush(char *pila, int Tope, int Max, char dato);
char Pop(char *pila, int Tope);
char mPop(char *pila, int Tope);
void Conv_A_Posfijo(char *pila, int n);
void Conv_prefija(char *pila, int n);
int prioridad(char simbolo);
void exp_A_prefija(char *pila, int n);
void mostrarmenu(char *exp, int n);

int main()
{
    pilas_menu();
    return 0;
}



bool pila_vacia(char pila[], int Tope){
    bool band;
    if(Tope==-1){
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


int Push(char *pila, int Tope, int Max, char dato){
    bool band;
    band=pila_llena(pila,Max,Tope);
    if(band){
        cout<<"Desbordamiento-Pila llena"<<endl;
    }
    else{
            Tope++;
            pila[Tope]=dato;
            

    }
     return Tope;
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
    int tamano;
    int n;
    
        cout<<endl<<"     Pilas";
       cout<<endl<<"1.    Mostrar menu con las funciones basicas(Push,Pop,Pila llena y Pila vacia)";
        cout<<endl<<"2.   Conversion a Posfija";
        cout<<endl<<"3.   Conversion a Prefija";
        cout<<endl<<"4.   Salir";
        cout<<endl<<"Opcion: ";
        fflush(stdin);
        cin>>opc;
     
    

        switch(opc){
        case 1:{ 
             cout<<endl<<"Dada una expresion: ";
             getline(cin,expresion);
             fflush(stdin);
             n=0; 
             tamano = expresion.length(); //para saber la cantidad de caracteres que se encuentran en la cadena
             char *Exp= new char [tamano];
             strcpy(Exp,expresion.c_str());
             n=tamano;
             cout<<endl<<"Esta sera almacenada dentro de un vector, para despues ser usada por la pila";
             cout<<endl;
             mostrarmenu(Exp,n);
             }

        break;
       
        case 2:{    
            fflush(stdin);
            cout<<"Dame la expresion que deseas convertir: ";
            fflush(stdin);
            getline(cin,expresion);
            fflush(stdin);
            n=0; 
            tamano = expresion.length(); //para saber la cantidad de caracteres que se encuentran en la cadena
            char *Exp= new char [tamano];
            strcpy(Exp,expresion.c_str());
            n=tamano;
            exp_A_prefija(Exp,n);
            delete[]Exp;
            break;
            } 
        case 3:{   
            fflush(stdin);
            cout<<"Dame la expresion que deseas convertir: ";
            fflush(stdin);
            getline(cin,expresion);
            fflush(stdin);
            n=0; 
            tamano = expresion.length(); //para saber la cantidad de caracteres que se encuentran en la cadena
            char *Exp= new char [tamano];
            strcpy(Exp,expresion.c_str());
            n=tamano;
            exp_A_prefija(Exp,n);
            delete[]Exp;
            break;
            }
        default: 
            break;

    }
    


}


void Conv_A_Posfijo(char *El,int n){
    int tope=-1;
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


    while(cont>0){
        dato=El[izq];
        El[izq]=' ';
        izq++;
        cont--;
        if(dato=='('){
            if(pila_llena(pila,n,tope)==false){
                tope=Push(pila,tope,n,dato);
            }
            else{
                cout<<endl<<"La pila esta llena"<<endl;
                break;
            }
        }
        else{
            if(dato==')'){
                while(pila[tope]!='('){
                    dato=Pop(pila,tope);
                    tope--;
                    epos[en]=dato;
                    en++;
                }
                dato=Pop(pila,tope);
                tope--;

            }
            else{
                if(dato=='*'||dato=='^'||dato=='/'||dato=='+'||dato=='-'){//operadores
                    band=pila_vacia(pila,tope);
                    orden=prioridad(dato);
                    ordenp=prioridad(pila[tope]);
                    while(band==false && orden>=ordenp){
                        
                        simbolo=Pop(pila,tope);
                        tope--;
                        epos[en]=simbolo;
                        en++;
                        band=pila_vacia(pila,tope);
                        ordenp=prioridad(pila[tope]);
                    }
                        tope=Push(pila,tope,n,dato);

                }
                else{
                    //Esun operando
                    epos[en]=dato;
                    en++;
                }



            }
        }


    }
    band=false;
    while(band==false){
        dato=Pop(pila,tope);
        tope--;
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
    int tope=-1;
    char dato ;   
    int cont = n-1;
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
        if(dato==')'){
            if(pila_llena(pila,n,tope)==false){
                tope=Push(pila,tope,n,dato);
            }
            else{
                cout<<endl<<"La pila esta llena"<<endl;
                break;
            }
        }
        else{
            if(dato=='('){
                while(pila[tope]!=')'){
                    dato=Pop(pila,tope);
                    tope--;
                    epre[en]=dato;
                    en++;
                }
                dato=Pop(pila,tope);
                tope--;
            }
            else{
                if(dato=='*'||dato=='^'||dato=='/'||dato=='+'||dato=='-'){//operadores
                    band=pila_vacia(pila,tope);
                    orden=prioridad(dato);
                    ordenp=prioridad(pila[tope]);
                    while(band==false && orden>ordenp){
                        simbolo=Pop(pila,tope);
                        tope--;
                        epre[en]=simbolo;
                        en++;
                        band=pila_vacia(pila,tope);
                        ordenp=prioridad(pila[tope]);
                    }
                        tope=Push(pila,tope,n,dato);

                }
                else{
                    //Esun operando
                    epre[en]=dato;
                    en++;
                }



            }
        }


    }
    band=false;
    while(band==false){
        dato=Pop(pila,tope);
        tope--;
        epre[en]=dato;
        en++;
        band=pila_vacia(pila,tope);
    }
    cout<<"La expresion convertida a prefija es: "<<endl;
    for(int i=n; i>=0;i--){
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

void exp_A_prefija(char *Exp, int n){
int tope=-1;
bool band=false;
int cont= n;
int contnum;
int izq=0;
char pila[n];
char dato;
char datox;
char op;
int dato1;
int dato2;

char operador[3];
int res;
char put;

while(band==false){ 
        dato=Exp[izq];
        Exp[izq]=' ';
        izq++;
        cont--;
        if(dato=='*'||dato=='^'||dato=='/'||dato=='+'||dato=='-'){
            tope=Push(pila,tope,n,dato);
            contnum=0;
        }
        else{//es un numero
            contnum++;
            tope=Push(pila,tope,n,dato);
            if(contnum==2){
                for(int i=0;i<3;i++){
                datox=Pop(pila,tope);
                tope--;
                operador[i]=datox;
                }
                dato1=(operador[0]-'0');
                dato2=(operador[1]-'0');
                op=operador[2];
                res=operacion(dato1,dato2,op);
                fflush(stdin);
                put=(res+'0');
                tope=Push(pila,tope,n,put);
                contnum=contnum-1;
            }
            
        }
    band=pila_llena(pila,n,tope);

}

     
}

int operacion(int x,int y,char simb){
    int res;
    switch(simb){
        case '^':
            res=y^x;
            break;
        case '/':
            res=y/x;
            break;
        case '*':
            res=y*x;
            break;
        case '-':
            res=y-x;
            break;
        case '+':
            res=y+x;
            break;
    }
    return res ;
}
void mostrarmenu(char *exp, int n){
    cout<<endl<<"Primero se crea la pila, la cual tendra el tamaño que tenga el vector con la expresion dada:"<<endl;
    cout<<"Pila con tamaño "<<n<<endl;
    cout<<endl<<"Ahora tenemos que declarar la variable de tope, la cual empieza con el valor de -1 pq hasta el momento la pila de encuentra vacia";
    char pila[n];
    int tope=-1;
    int dato;
    int cont=0;
     int opc;
    do{ 
    cout<<endl<<"Elija la opcion que desee usar: "<<endl;
    cout<<endl<<"1. Push";
    cout<<endl<<"2. Pop";
    cout<<endl<<"3. Pila_llena";
    cout<<endl<<"4. Pila_vacia";
    cout<<endl<<"5. Salir";
    cout<<endl<<"Opcion: ";
    cin>>opc;
    bool band;
    switch(opc){
        case 1:{ 
            cout<<endl<<"Se va a introducir el primer valor del vector"<<endl;
            dato=exp[cont];
            cont++;
            mPush(pila,tope,n,dato);
            break;
             }
        case 2:{ 
            cout<<endl<<"Se va a quitar un elemento de la pila, el que se encuentre en tope"<<endl;
            dato= mPop(pila,tope);
            tope--;
            cout<<endl<<"el valor que se quito de la pila fue el siguiente: "<<dato<<endl;
            break;
             }
        case 3:{
            cout<<endl<<"Ahora se va checar si es que la pila se encuentra llena"<<endl;
            band=mpila_llena(pila,n,tope);
            if(band){
                cout<<endl<<"Pila llena devolvio true, lo que significa que la pila esta llena. No se pueden agregar mas datos"<<endl;

            }
            else{
                cout<<endl<<"Pila llena devolvio false, lo que significa que la pila no esta llena. Se pueden agregar mas valores"<<endl;

            }
            break;
             }
        case 4:{ 
            cout<<endl<<"Se va a checar si es que la pila se encuentra vacia";
            band=mpila_vacia(pila,tope);
            if(band){
                cout<<endl<<"Pila vacia devolvio true, lo que significa que la pila esta vacia. No se pueden quitar valores de la pila";
                
            }
            else{
                cout<<endl<<"Pila vacia devolvio false, lo que significa que la pila no esta vacia. Se pueden quitar valores";
            }
            break;
            }


    }
     }while(opc>0 && opc<5);
}

int mPush(char *pila, int Tope, int Max, char dato){
    cout<<endl<<"Estado Actual de la pila: "<<endl;
    for(int i=Tope;i>-1;i--){
        cout<<pila[i]<<" ";
    }
    cout<<endl<<"Se crea un bool para definir si es que se pueden poner mas valores, para esto se llama a pila llena"<<endl;
    bool band;
    band=pila_llena(pila,Max,Tope);
    if(band){
        cout<<"La pila esta llena, no se pueden agregar mas datos";
        cout<<endl;
        cout<<"Desbordamiento-Pila llena"<<endl;
        cout<<endl<<"Estado Actual de la pila: "<<endl;
        for(int i=Tope;i>-1;i--){
        cout<<pila[i]<<" ";
        }

    }
    else{
            cout<<endl<<"La pila no esta llena, se pueden agregar datos";
            Tope++;
            pila[Tope]=dato;
            cout<<endl<<"Estado Actual de la pila: "<<endl;
            for(int i=Tope;i>-1;i--){
            cout<<pila[i]<<" ";
            }
    }
     return Tope;
}

char mPop(char *pila, int Tope){
    cout<<endl<<"Estado Actual de la pila: "<<endl;
    for(int i=Tope;i>-1;i--){
        cout<<pila[i]<<" ";
    }
    cout<<endl<<"Se crea un bool para definir si es que se pueden quitar valores, para esto se llama a pila vacia"<<endl;
    int band;
    char dato;
    band=pila_vacia(pila,Tope);
    if(band){
        cout<<endl<<"Pila vacia es verdadero, no se pueden quitar valores"<<endl;
        cout<<"Subdesbordamiento-Pila vacia"<<endl;
        cout<<endl<<"Estado Actual de la pila: "<<endl;
        for(int i=Tope;i>-1;i--){
        cout<<pila[i]<<" ";
        }

    }
    else{
        cout<<endl<<"Pila vacia es falso, se pueden quitar valores"<<endl;
        dato=pila[Tope];
        Tope--;
        cout<<endl<<"Estado Actual de la pila: "<<endl;
        for(int i=Tope;i>-1;i--){
        cout<<pila[i]<<" ";
        }
    }
    return dato;
}

bool mpila_vacia(char *pila, int Tope){
    cout<<endl<<"Se verifica si es que la pila se encuentra vacia"<<endl;
    cout<<endl<<"Estado Actual de la pila: "<<endl;
    for(int i=Tope;i>-1;i--){
        cout<<pila[i]<<" ";
    }

    cout<<endl<<"Primero se crea una variable bool, la cual se regresa a la funcion llamada para saber si es que esta vacia o no"<<endl;
    cout<<"Para saber si la pila esta vacia tenemos que saber el valor que tiene el tope de la pila, si es -1 significa que esta vacia, cualquier otro valor mayor significa que la pila tiene valores"<<endl;
    cout<<"valor de la pila: "<<Tope<<endl;

    
    bool band;
    if(Tope==-1){
        band=true;//vacia
        cout<<"Tope es igual a -1, la variable esta vacia"<<endl;
    }
    else{
        cout<<endl<<"El valor de tope es mayor a -1, la pila no esta vacia"<<endl;
        band=false;
        cout<<"Estado Actual de la pila: "<<endl;
        for(int i=Tope;i>-1;i--){
        cout<<pila[i]<<" ";
        }
    }
        
    return band;
}


bool mpila_llena(char *pila, int Max,int Tope){
    cout<<endl<<"Se verifica si es que la pila se encuentra llena"<<endl;
    cout<<endl<<"Estado Actual de la pila: "<<endl;
    for(int i=Tope;i>-1;i--){
        cout<<pila[i]<<" ";
    }

    cout<<endl<<"Primero se crea una variable bool, la cual se regresa a la funcion llamada para saber si es que esta llena o no"<<endl;
    cout<<"Para saber si la pila esta llena tenemos que saber el valor que tiene el tope de la pila, si es igual a Max significa que esta llena, cualquier otro valor menor significa que la pila no esta llena"<<endl;
    cout<<"valor de la pila: "<<Tope<<endl;
    bool band;
    if(Tope==Max){
        cout<<"El valor de tope es igual al de Max, la pila esta llena"<<endl;
        band=true;//llena
        cout<<endl<<"Estado Actual de la pila: "<<endl;
    for(int i=Tope;i>-1;i--){
        cout<<pila[i]<<" ";
    }

    
    }
    else{
        cout<<endl<<"El valor de tope es menor que Max, la pila no esta llena"<<endl;
        band=false;
        cout<<endl<<"Estado Actual de la pila: "<<endl;
        for(int i=Tope;i>-1;i--){
        cout<<pila[i]<<" ";
        }
        
    }
        
    return band;

}


