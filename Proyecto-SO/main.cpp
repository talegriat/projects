//Proyecto de sistemas operativos
#include <iostream>
#include <cstdlib>
#include <ctime>
//#include <windows.h>
#include "RoundRobin.cpp"
#include "SystemBuddy.cpp"

using namespace std;



int main(){
    //system("cls");
    srand(time(NULL));
    tam_memoria=Definir_Tamano_Memoria();
    raiz=crear_Buddy();
    raiz->espacio=tam_memoria;
    cout<<"Salida Inicial: "<<endl;
    cout<<"[0,"<<raiz->espacio<<",0]"<<endl;
    velocidad_programa=700;
    for(int i=0; i<50; i++){

    //do{
        //*int n_procesos = 1+rand()%2;
        
        int n_procesos = 1;
        tam_max_cuantos_por_proceso=12;
        tam_max_proceso=1024;


        for(int i=0 ; i<n_procesos ; i++){
            lista_procesos=agregar_proceso(lista_procesos);
        }
        recorre2(lista_round_robin);

        lista_round_robin=agrega_proceso_round_robin(lista_round_robin);



        //Sleep(velocidad_programa);
        //system("cls");
    //}while(true);
    }
    return 0;
}

proceso *crea(){
    proceso *myProceso = (proceso*)calloc(1, sizeof(proceso));
    return (myProceso);
} 

void quita(proceso *aux){
    delete  aux;
} 


void recorre(proceso *lista_procesos){
    proceso *proceso_copia=lista_procesos;
    cout<<endl<<"Cargados en lista de procesos para ser introducidos en RR------------------------------------------"<<endl;

    if(lista_procesos==NULL){
        cout<<endl<<"Lista vacia, no hay elementos a mostrar!";
    }else{
        while(proceso_copia!=NULL){
            cout<<"[ "<<proceso_copia->id<<" , "<<proceso_copia->tam<<" , "<<proceso_copia->numero_cuantos<<" ]"<<endl;
            proceso_copia=proceso_copia->siguiente_proceso;
            
        }
    }
}
