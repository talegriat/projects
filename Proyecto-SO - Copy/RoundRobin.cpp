#include <iostream>
#include "variables_funciones.hpp"

using namespace std;


proceso *agregar_proceso(proceso *lista_procesos){      //creacion de la lista de procesos no creados
    proceso *new_proceso=NULL, *proceso_copia=NULL;
    if(lista_procesos==NULL){
        lista_procesos=crea();
        id_global++;

        lista_procesos->id=id_global;
        lista_procesos->tam = 1+rand()%tam_max_proceso;
        lista_procesos->numero_cuantos = 1+rand()%tam_max_cuantos_por_proceso;
        lista_procesos->siguiente_proceso=NULL; 
    }else{

        new_proceso=crea();
        id_global++;                    //se incrementa el id global para numero de proceso

        new_proceso->id=id_global;  
        new_proceso->tam = 1+rand()%tam_max_proceso;
        new_proceso->numero_cuantos = 1+rand()%tam_max_cuantos_por_proceso;
        new_proceso->siguiente_proceso=NULL;
        
        proceso_copia=lista_procesos;
        while(proceso_copia->siguiente_proceso!=NULL){
            proceso_copia=proceso_copia->siguiente_proceso;
        }
        proceso_copia->siguiente_proceso=new_proceso;
    }
    return lista_procesos;
}


proceso *agrega_proceso_round_robin(proceso *lista_RR_c){

    proceso *copia_para_desplazar=lista_procesos, *copia2_para_desplazar=NULL;
    proceso *copia_proceso;
    bool bandera=false;

    while(copia_para_desplazar!=NULL){
        bandera=true;
        raiz=recorre_izquierda(raiz);
        if(verificar_procesos(raiz, copia_para_desplazar)){ //Primero la pregunta es que si se debe agregar a la lista de round robin 
            //vamos a enviar copia_para_desplazar
            bandera=false;
            copia2_para_desplazar=copia_para_desplazar->siguiente_proceso;
            cout<<endl<<"Entra ...";
            cout<<"[ "<<copia_para_desplazar->id<<" , "<<copia_para_desplazar->tam<<" , "<<copia_para_desplazar->numero_cuantos<<" ] ";
            
            //system("pause"); cout<<"Proceso: "<<copia_para_desplazar->id;

            copia_proceso=crea();           //se crea un nuevo proceso como auxiliar el cual sera mandado a round robin
            copia_proceso->id=copia_para_desplazar->id; 
            copia_proceso->numero_cuantos=copia_para_desplazar->numero_cuantos; 
            copia_proceso->siguiente_proceso=NULL; 
            copia_proceso->tam=copia_para_desplazar->tam; 
        
            lista_RR_c=inserta_Lista_RR(lista_RR_c, copia_proceso);//funcion para insertar en cola circular a round robin
            lista_procesos=elimina_proceso_ID(lista_procesos, copia_para_desplazar->id);    //se elimina de la lista de procesos con el id de proceso
            numero_procesos_memoria++;  /*Prueba ++++++*/

        }

        if(bandera)
            copia_para_desplazar=copia_para_desplazar->siguiente_proceso;
        else
            copia_para_desplazar=copia2_para_desplazar;
        

    }
        recorre2(lista_RR_c);
        for(int i=0 ; i<numero_procesos_memoria ; i++){ /*Prueba ++++++*/
            lista_RR_c=atender_proceso(lista_RR_c);
        }    
    return lista_RR_c;
}


proceso *elimina_proceso_ID(proceso *p, int id){
	proceso *q=p,*t;
	if(p==NULL){
		cout<<endl<<"Lista vacia no hay proceso a eliminar"<<endl;
	}else{
		while(q->id!=id){
			t=q;
			q=q->siguiente_proceso;
		}//fin while

		if(p==q){
			p=p->siguiente_proceso;
		}else{
			t->siguiente_proceso=q->siguiente_proceso;
		}
        
		//quita(q);
    }

	return(p);
}


proceso *inserta_Lista_RR(proceso *lista, proceso *copia){
    proceso *lista_copia=NULL;
    if(lista==NULL){
        lista=copia;
        lista->siguiente_proceso=lista; 

    }else{
        copia->siguiente_proceso=lista;
        lista_copia=lista;
        while(lista_copia->siguiente_proceso!=lista){
            lista_copia=lista_copia->siguiente_proceso;
        }
        lista_copia->siguiente_proceso=copia;


    }
    return lista;
}


void recorre2(proceso *lista_RR){
	proceso *proceso_copia=NULL;
    cout<<endl<<"Cargados en lista RR para ser procesados ------------------------------------------ Num. Procesos en memoria: "<<numero_procesos_memoria<<endl;

	if(lista_RR==NULL){
		cout<<endl<<"Lista vacia, nada que mostrar"<<endl;
	}else{
		proceso_copia=lista_RR;
	    do{
            cout<<"* [ "<<proceso_copia->id<<" , "<<proceso_copia->tam<<" , "<<proceso_copia->numero_cuantos<<" ]"<<endl;
	    	proceso_copia=proceso_copia->siguiente_proceso;
		}while(proceso_copia!=lista_RR);
	}

    //Sleep(velocidad_programa);
}


proceso *atender_proceso(proceso *lista_RR_c ){
    //variable definida por el usuario durante la ejecución

    cout<<endl<<"Procesando "; //Sleep(velocidad_programa);cout<<".";Sleep(velocidad_programa);cout<<".";Sleep(velocidad_programa);cout<<".";
    cout<<"[ "<<lista_RR_c->id<<" , "<<lista_RR_c->tam<<" , "<<lista_RR_c->numero_cuantos<<" ]";
    lista_RR_c->numero_cuantos=lista_RR_c->numero_cuantos-cuantos_por_exe;
    cout<<" -> "<<"[ "<<lista_RR_c->id<<" , "<<lista_RR_c->tam<<" , "<<lista_RR_c->numero_cuantos<<" ]";

    if((lista_RR_c->numero_cuantos)<=0){      //cada que se ingrese se recorrera la lista por medio del algoritmo de descarga
        cout<<endl<<endl<<"Descargando proceso"<<endl;
        lista_RR_c=descargar_proceso_RR_ID(lista_RR_c, raiz);
        //system("pause");
        numero_procesos_memoria--;
    }else{ //de lo contrario al no recorrerse por medio del algoritmo se cambiara por este else
        lista_RR_c=lista_RR_c->siguiente_proceso;       //se cambia al siguiente proceso a ejecutar, el cual es indicado como inicio
        //tambien se cambia con la finalidad de que cuando se requiera ingresar un proceso en la lista de RR, ahí sera el inicio de la lista
    }

    return lista_RR_c;
}


proceso *descargar_proceso_RR_ID(proceso *lista_RR_c, Buddy *raiz){
    int id;
    id=lista_RR_c->id;
    cout<<endl<<"Descargando ";
    cout<<"-";//Sleep(velocidad_programa);cout<<"-";Sleep(velocidad_programa);cout<<"-";
    cout<<"-> "<<"[ "<<lista_RR_c->id<<" , "<<lista_RR_c->tam<<" , "<<lista_RR_c->numero_cuantos<<" ] "<<endl;

    proceso *lista_RR_c_copia=lista_RR_c, *aux=NULL;
	if(lista_RR_c==NULL){
		cout<<endl<<"Lista vacia no hay proceso a eliminar"<<endl;
	}else{
        //cout<<"Eliminando... .  .   ."<<endl;
		if(lista_RR_c_copia->siguiente_proceso!=lista_RR_c){
			lista_RR_c=lista_RR_c->siguiente_proceso;
            aux=lista_RR_c;
            while(aux->siguiente_proceso!=lista_RR_c_copia){
                aux=aux->siguiente_proceso;
            }
            //salto de nodo
            aux->siguiente_proceso=lista_RR_c;
            delete[]lista_RR_c_copia;

		}else{
			lista_RR_c=NULL;
		}
        
        
        
        //aux->siguiente_proceso=lista_'YU6JHRR_c;//evaluando
		//quita(lista_RR_c_copia);
	}
    raiz=recorre_izquierda(raiz);
    raiz=eliminarproceso(raiz, id);
    cout<<endl<<"Reorganizando la memoria:"<<endl;
    Reorganizar=true;
    while(Reorganizar){
        raiz=reorganizar(raiz);
    }
    cout<<"Acabo de reorganizar, imprimiendo"<<endl;
    raiz=recorre_izquierda(raiz);
    imprimir_m(raiz);
	return (lista_RR_c);
}