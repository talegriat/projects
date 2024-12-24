#include <iostream>
#include "variables_funciones.hpp"
using namespace std;
//Se define el tamaño para memoria
int Definir_Tamano_Memoria(){
    int opc;
    int tam_p=0;
    do{
    cout<<endl<<"TAMAÑO DE MEMORIA"<<endl<<endl;
    cout<<"Selecciona el Tamaño de memoria deseas utilizar: "<<endl;
    cout<<"1. 1MB"<<endl;
    cout<<"2. 4MB"<<endl;
    cout<<"3. 8MB"<<endl;
    fflush(stdin);
    cin>>opc;
    switch(opc){
        case 1: 
            cout<<"Se escogio 1MB"<<endl;
            tam_p = 1024;
            break;
        case 2:
            cout<<"Se escogio 4MB"<<endl;
                tam_p=4096;
                break;
        case 3:
            cout<<"Se escogio 8MB"<<endl;
            tam_p= 8192;
            break;
        default:
            cout<<"La respuesta es incorrecta"<<endl;
            break;
    }

    }while(opc<1||opc>3);
    return tam_p;
}

bool verificar_procesos(Buddy *raiz, proceso *procesos){
    bool verificar=false;
    if(procesos->tam > tam_memoria){
        verificar=false;//No se puede almacenar porque el tamaño del proceso es superior a el tamaño de la memoria

    }
    else{//si no es mayor al espacio de la memoria, entonces es menor o igual al tamaño de la memoria
        if(procesos->tam>raiz->espacio){
            Recorre_BOOL=recorre_bool(raiz, procesos->tam, procesos->id);
            if(Recorre_BOOL==true){
                raiz=recorre(raiz, procesos);
                verificar=true;
            }
            else{//no cabe en las divisiones de memoria actuales
                Recorre_BOOL=false;
                verificar=false;
            }
           
        }
        else{
            if(procesos->tam > raiz->espacio/2){//si el tamaño del proceso es mayor a la mitad del tamaño de la memoria utilizada
                if(raiz->id==0){
                    raiz->id=procesos->id;
                    raiz->mem_proceso=procesos->tam;
                    raiz->cuantos=procesos->numero_cuantos;
                    Imprime_buddy(raiz, procesos);
                    raiz=recorre_izquierda(raiz);
                    imprimir_m(raiz);
                    verificar=true;//si se puede almacenar, el proceso entra correctamente en el espacio de memoria y el espacio de memoria se encuentra vacio
                }
                else{
                    //el proceso cabe correctamente en el espaccio pero este se encuentra ocupado
                    Recorre_BOOL=recorre_bool(raiz, procesos->tam, procesos->id);
                    if(Recorre_BOOL==true){//si existe un espacio disponible dentro de la memoria que pueda almacenar el proceso
                        raiz=recorre(raiz, procesos);
                        verificar=true;
                    }
                    else{//no hay ningun espacio disponible que pueda almacenar el proceso
                        Recorre_BOOL=false;
                        verificar=false;
                    }
                }
            }
            else{
                //significa que es mas pequeño que la memoria actualmente dividida, se tiene que dividir otra vez
                if(raiz->espacio==32){//si la division tiene el minimo tamaño posible se queda igual
                    if(raiz->id==0){
                        raiz->id=procesos->id;
                        raiz->mem_proceso=procesos->tam;
                        raiz->cuantos= procesos->numero_cuantos;
                        Imprime_buddy(raiz, procesos);
                        raiz=recorre_izquierda(raiz);
                        imprimir_m(raiz);
                        verificar=true;
                    }
                    else{//es el minimo espacio posible, pero se encuentra ocupada
                        Recorre_BOOL=recorre_bool(raiz, procesos->tam, procesos->id);
                        if(Recorre_BOOL==true){//si existe un espacio disponible dentro de la memoria para almacenar el proceso
                            raiz=recorre(raiz, procesos); 
                            verificar=true;
                        }
                        else{//no existe espacio disponible dentro de la memoria para almacenar el proceso
                            Recorre_BOOL=false;
                            verificar=false;
                        }
                        

                    }
                }
                else{//se puede dividir
                    if(raiz->id==0){//se verifica si el espacio esta vacio
                        raiz=dividir_memoria(raiz,raiz->espacio, procesos);//con esta fucionse divide la memoria hasta que se encuentre el tam de memoria adecuado
                        //Imprime_buddy(raiz, procesos->tam, procesos->id, procesos->numero_cuantos);
                        verificar=true;
                    }
                    else{//se tiene que recorrer
                        Recorre_BOOL=recorre_bool(raiz, procesos->tam, procesos->id);
                        if(Recorre_BOOL==true){
                            raiz=recorre(raiz,procesos);
                            verificar=true;
                         }
                        else{//no existe espaico dispobible dentro de la memoria para almacenar el proceso
                        Recorre_BOOL=false;
                            verificar=false;
                        }
                         
                    }
                }
            }
        }
    }
    return verificar;
}

bool recorre_bool(Buddy *raiz, int tamano, int id)//recorre la lista y regresa un true si es que existe memoria disponible para almacenar el proceso
{
    bool recorreb=false;
    if(raiz->id!=0){//significa que la division de memoria en la que se encuentra esta ocupada
        if(raiz->der!=NULL){//sigue llamandose la funcion recursiva mientras no se llegue al final de la memoria
            return (recorre_bool(raiz->der, tamano, id));
        }
        else{//se llega al final de la memoria y todos los espacios de esta se encuentran ocupados
            raiz=recorre_izquierda(raiz);
            recorreb=false;
            
        }
    }
    else{//la division de memoria en la que se encuentra no esta ocupada
        if(tamano<=raiz->espacio){//regresa un true si es que el proceso cabe en el tamaño de la division de memoria
            raiz=recorre_izquierda(raiz);
            recorreb=true;
        }
        else{
            if(raiz->der!=NULL)//se vuelve a llamar la funcion mientras no se llegue al final de la memoria
            {
                return (recorre_bool(raiz->der, tamano, id));
            }
            else{
                raiz=recorre_izquierda(raiz);
                recorreb=false;
                //regresa un false, ya que puesto a que el espacio de memoria no se encuentra ocupado, no tiene el espacio suficiente para almacenar el proceso
            }
        }
    }
    return recorreb;
}
Buddy *recorre(Buddy *raiz, proceso *procesos){//recorre la lista buscando un tamaño de memoria disponible para almacenar el proceso
    if(raiz->id!=0){
        if(raiz->der!=NULL){//se sigue recorriendo mientras haya espacios a la derecha
            return (recorre(raiz->der, procesos));
        }
        else{//todos los espacios estan ocupados
            cout<<endl<<"No hay espacios disponibles"<<endl; 
        }
    }
    else{//la division de memoria en la que se encuentra no esta ocupada
        if(procesos->tam <=raiz->espacio){//se verifica si el proceso cabe en la division de memoria
            if(procesos->tam <raiz->espacio/2){ //En caso de que quepa, se verifica si se necesita dividir
                raiz=dividir_memoria(raiz,raiz->espacio, procesos);
            }
            else{
                raiz->id=procesos->id;
                raiz->cuantos=procesos->numero_cuantos;
                raiz->mem_proceso=procesos->tam;
                Imprime_buddy(raiz,procesos);
                raiz=recorre_izquierda(raiz);
                imprimir_m(raiz);

            }
        }
        
        else{//el proceso no cabe en la division de memoria que no se encuentra ocupada
            if(raiz->der!=NULL){
                return (recorre(raiz->der, procesos));
            }
        }

    }
    raiz=recorre_izquierda(raiz);
    return raiz;
}
Buddy *recorre_izquierda(Buddy *raiz){//recorre la raiz a la izquierda para que se pueda verificar el almacenamiento correctamente
    while(raiz->izq!=NULL){
        raiz=raiz->izq;
    }
    return raiz;
}
Buddy *eliminarproceso(Buddy*raiz, int id){//se elimina el id del proceso del espacio de memoria
    if (raiz == nullptr) {
        cout << "Árbol vacío, no se puede eliminar el proceso." << endl;
        return nullptr;
    }

    // Buscar el nodo con el ID específico
    if (raiz->id != id) {
        // El ID no se encuentra en este nodo, buscar en los subárboles
        if (raiz->der != nullptr) {
            return  eliminarproceso(raiz->der, id);
        } else {
            cout << "No se encontró el ID del proceso." << endl;
        }
    } else {
        // Encontrado el nodo con el ID, eliminar el proceso
        cout << "Eliminando ID de la memoria." << endl;
        raiz->id = 0;
        raiz->cuantos = 0;
        raiz->mem_proceso = 0;

        // Recorrer hacia la izquierda para actualizar la raíz
        raiz = recorre_izquierda(raiz);
    }

    return raiz;
}
//reorganizar la memoria cada que se elimine un proceso
Buddy *reorganizar(Buddy *&raiz){//busca reordenar la memoria
    Buddy*actual=raiz;
    if(raiz==nullptr||raiz->der==nullptr){
        Reorganizar=false;
    }
    else{
        
        if(raiz->espacio==raiz->der->espacio&&raiz->id==0&&raiz->der->id==0){ 
            raiz->der->espacio=raiz->der->espacio*2;
            if(raiz->izq!=nullptr){
                raiz->izq->der=raiz->der;
                raiz->der->izq=raiz->izq;
                cout<<"Se elimina el nodo"<<endl;
                            //eliminar_nodo(temp);
            }
            else{
                raiz=raiz->der;
                raiz->izq=nullptr;
                cout<<"Se elimina el nodo"<<endl;
                //eliminar_nodo(temp);
            }
            delete actual;
            Reorganizar=true;
        }
        else{//o no son del mismo tamaño o uno esta ocupado
                delete actual;
                if(raiz->espacio!=raiz->der->espacio){
                    return reorganizar(raiz->der);
                }
                    
                else{
                    return reorganizar(raiz->der->der);
                }       
        }
    }
    return raiz;

}



Buddy *dividir_memoria(Buddy *espacio, int tamR, proceso *procesos){
    Buddy *nuevoEspacio = nullptr;

    if (procesos->tam <= espacio->espacio / 2 && espacio->espacio / 2 >= 32) {
        // Crear un nuevo nodo en la memoria dinámica
        if(espacio->izq!=nullptr){
            nuevoEspacio = crear_Buddy();
            nuevoEspacio->der = espacio;
            nuevoEspacio->izq=espacio->izq;
            espacio->izq = nuevoEspacio;
            nuevoEspacio->izq->der=nuevoEspacio;
            nuevoEspacio->espacio = tamR/2;
            espacio->espacio = tamR/2;
        }
        else{
            nuevoEspacio=crear_Buddy();
            nuevoEspacio->der=espacio;
            nuevoEspacio->izq=espacio->izq;
            espacio->izq=nuevoEspacio;
            nuevoEspacio->espacio=tamR/2;
            espacio->espacio=tamR/2;
        }
        
        // Llamar recursivamente para continuar con la división
        return dividir_memoria(nuevoEspacio, tamR/2,procesos);
    } else {
        espacio->id = procesos->id;
        espacio->cuantos=procesos->numero_cuantos;
        espacio->mem_proceso=procesos->tam;
        Imprime_buddy(espacio, procesos);
        espacio=recorre_izquierda(espacio);
        imprimir_m(espacio);
    }
    // Si no se crea un nuevo espacio, simplemente devolver el espacio existente
    return espacio;
    
}


void Imprime_buddy(Buddy *raiz, proceso *procesos){
    cout<<endl<<"["<<procesos->id<<",("<<procesos->tam<<")"<<raiz->espacio<<","<<procesos->numero_cuantos<<"]:"<<endl;
}
Buddy *crear_Buddy(){

    Buddy *myBuddy = (Buddy*)calloc(1, sizeof(Buddy));

    return (myBuddy);
}
void eliminar_nodo(Buddy *aux){//el nodo se elimina al momento de reorganizar las divisiones en la memoria
	aux->der=nullptr;
    aux->izq=nullptr;
    delete[]aux;
    //[]aux;
}
void imprimir_m(Buddy *raiz){
    if(raiz!=NULL){
        cout<<"["<<raiz->id<<","<<"("<<raiz->mem_proceso<<")"<<raiz->espacio<<","<<raiz->cuantos<<"]";
        fflush(stdout);
        imprimir_m(raiz->der);
    }
}
