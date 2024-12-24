//Listas enlazadas
#include <iostream>
#include <iomanip>
#include<cstdlib>
#include<math.h>

using namespace std;

//structs
struct TNodo{
    int info;
    TNodo *liga;
};


//prototipos
TNodo *crea();
void *quita(TNodo);
TNodo *insertaInicio(TNodo *, int dato);
TNodo *insertaFinal(TNodo *, int dato);
void recorre(TNodo *p);

int main(){
    TNodo *p=NULL;
    int op,dato;
    do{
        cout<<endl<<"1. Inserta al inicio";
        cout<<endl<<"2. Inserta al final";
        cout<<endl<<"3. Inserta antes de una referencia";
        cout<<endl<<"4. Inserta despues de una referencia";
        cout<<endl<<"5. Recorre la lista";
        cout<<endl<<"6. Salir";
        cout<<endl<<"Selecciona tu opcion: ";
        cin>>op;
        switch(op){
            case 1: 
                cout<<endl<<"Dato a insertar: ";
                cin>>dato;
                p=insertaInicio(p,dato);
                cout<<endl<<"Dato insertado"<<endl;
                
                break;
            case 2: 
                cout<<endl<<"Dato a insertar: ";
                cin>>dato;
                p=insertaFinal(p,dato);
                cout<<endl<<"Dato insertado"<<endl;
               
                break;
            case 3: 

                break;
            case 4: 
            break;
            case 5: 
                cout<<endl<<"Datos en lista"<<endl;
                recorre(p);
                cout<<endl;
                break;
            case 6: 
            break;
            default: 
            break;
        }

    }while(op!=6);
}

TNodo *crea(){
    return (new TNodo);
}
void *quita(TNodo *aux){
    delete  aux;
}
TNodo *insertaInicio(TNodo *p, int dato){
    TNodo *q=NULL;
    TNodo *t=NULL;
    if(p==NULL){
        p=crea();
        p->info=dato;
        p->liga=NULL; //*p
    }else{
        q=crea();
        q->info=dato;
        q->liga=p;
        p=q;
    }
    return p;
}
TNodo *insertaFinal(TNodo *p, int dato){
    TNodo *q=NULL, *t=NULL;
    if(p==NULL){
        p=crea();
        p->info=dato;
        p->liga=NULL; //*p
    }else{
        q=crea();
        q->info=dato;
        q->liga=NULL;
        t=p;
        while(t->liga!=NULL){
            t=t->liga;
        }
        t->liga=q;
    }
    return p;
}
void recorre(TNodo *p){
    TNodo *t=p;
    if(p==NULL){
        cout<<endl<<"Lista vacia, no hay elementos a mostrar!"<<endl;
    }else{
        while(t!=NULL){
            cout<<"["<<t->info<<"]";
            t=t->liga;
        }
    }
}