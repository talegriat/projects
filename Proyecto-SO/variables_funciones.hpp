#ifndef VARIABLES_FUNCIONES_HPP
#define VARIABLES_FUNCIONES_HPP

#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;


    /*  ---------------Constantes/Restricciones---------------*/
    int tam_memoria; ///indica el tamaño predefinido para la prueba, el cual se define en el main
    int tam_minimo_split = 32; //tiene la funcionalidad para indicar el tam minimo en el que se particionara la memoria

    /*  ---------------Configuracion de parametros---------------*/
    int tam_max_proceso;                  //limite de tamaño maximo de la memoria del proceso 
    int tam_max_cuantos_por_proceso;       //limite de tamaño maximo de los cuantos  
    int velocidad_programa;     //velocidad para el programa
    int cuantos_por_exe=2; //numero de cuantos restador por cada vez que entre al procesador


    /*  ---------------Struct para procesos---------------*/
    struct proceso{
        int numero_cuantos=0;
        int id=0;     
        int tam=0;
        proceso *siguiente_proceso=NULL;
    };
    /*  ---------------Struct para memoria "buddy"---------------*/
    struct Buddy{
        int espacio=0;
        int id=0;
        Buddy *izq=NULL,*der=NULL;
        int cuantos=0;
        int mem_proceso=0;
    };
    Buddy *impresion=NULL;
    bool Recorre_BOOL; //bool para verificar si se encuentra un espacio disponible para almacenar un proceso dentro de la memoria
    struct lista{//lista de espacios de memoria disponibles
        Buddy *divisiones;
        lista *der=NULL;
    };
    //funciones para SystemBuddy
    bool Reorganizar;
    Buddy *raiz=NULL;
    int Definir_Tamano_Memoria();
    bool verificar_procesos(Buddy *raiz, proceso *procesos);
    bool recorre_bool(Buddy *raiz, int tamano, int id);//recorre la lista y regresa un true si es que existe memoria dispobible para almacenar el proceso
    Buddy *recorre(Buddy *raiz, proceso *procesos);
    Buddy *recorre_izquierda(Buddy *raiz);
    Buddy *eliminarproceso(Buddy *raiz, int id);//se elimina el id de el proceso deseado
    Buddy *reorganizar(Buddy *&raiz);//reorganiza la memoria cada que se elimine un proceso
    Buddy *dividir_memoria(Buddy *espacio, int tamR, proceso *procesos);//divide la memoria en bloques mas pequeños para poder almacenar el proceso
    void Imprime_buddy(Buddy *raiz, proceso *procesos);
    Buddy *crear_Buddy();
    void eliminar_nodo(Buddy *aux);
    void imprimir_m(Buddy *raiz);
    int suma=0;
    Buddy *temp=NULL;
    





    /*  ---------------Requerido para hacer estadisticas ---------------*/
    int tam_total_procesos;               //contador
    int id_global = 0;                    //incrementador para id de procesos
    int numero_procesos = 0;              //contador del numero de procesos

    int numero_procesos_memoria=0;        //indica el numero de procesos que estan actualmente en la memoria


    proceso *lista_procesos = NULL;              //Lista de procesos en la fila
    proceso *lista_round_robin = NULL;           //Lista circular para procesos en round robin

    
//para round robin
    proceso *agrega_proceso_round_robin(proceso *lista_round_robin);
    proceso *elimina_proceso_ID(proceso *p, int id);
    proceso *inserta_Lista_RR(proceso *p, proceso *copia);
    void recorre2(proceso *lista_round_robin);
    proceso *atender_proceso(proceso *lista_RR_c );
    proceso *descargar_proceso_RR_ID(proceso *lista_RR_c, Buddy *raiz);


    //para main
    proceso *agregar_proceso(proceso *lista_procesos);
    proceso *crea();
    void quita(proceso *);
    void recorre(proceso *lista_procesos);
   
#endif
