//listas simples

#include<iostream>
#include<cstdlib>
#include<math.h>

using namespace std;

struct tnodo{
	int info;
	tnodo*liga;
	
};

tnodo *crea();
void quita(tnodo*aux);
tnodo *insertaprin(tnodo *p,int dato);
tnodo *insertafin(tnodo *p,int dato);
void recorre(tnodo *p);
tnodo *insertaAntes(tnodo *p, int Dato,int ref);

void elimina_antes(tnodo*p, int ref);




int main(){
	int dato;
	tnodo *p=NULL;
	int op;
	int ref;
	do{
		cout<<endl<<"1......INSERTA AL INICIO ";
		cout<<endl<<"2......INSERTA AL FINAL ";
		cout<<endl<<"3......INSERTA ANTES DE UNA REFERENCIA";
		cout<<endl<<"4......INSERTA DESPUES DE UNA REFERENCIA ";
		cout<<endl<<"5......RECORRE LA LISTA ";
		cout<<endl<<"6......Elimina primero";
		cout<<endl<<"7......Elimina final";
		cout<<endl<<"8......Elimina nodo con informacion x";
		cout<<endl<<"9......Elimina nodo antes de una referencia";
		cout<<endl<<"10.....Elimina nodo despues de una referencia";
		cout<<endl<<"11.....Salir";




		cout<<endl<<"Selecciona una opcion: ";
		cin>>op;
		switch(op){
			case 1:
				cout<<endl<<"Dato a insertar: ";
				cin>>dato;
				
				p=insertaprin(p,dato);
				cout<<endl<<"dato insertado";
				
				break;
			case 2:
				cout<<endl<<"Dato a insertar: ";
				cin>>dato;
				
				p=insertafin(p,dato);
				cout<<endl<<"dato insertado";
				break;
				
			case 3:
			cout<<endl<<"Dato a insertar: ";
			cin>>dato;
			cout<<endl<<"Antes de cual referencia: ";
			cin>>ref;
			p=insertaAntes(p,dato,ref);
			cout<<endl<<"Dato a insertar";
			cout<<endl;	
				break;
			case 4:
				break;
			case 5:
				cout<<"DATOS DE LA LISTA: "<<endl;
				
				recorre(p);
				cout<<endl;
				break;
			case 6:
				break;

				
			
		}
	}while(op!=6);
	
	
}



void recorre(tnodo *p){
	tnodo *t=p;
	if(p==NULL){
		cout<<endl<<"la lista esta vacia  no hay elementos que mostrar"<<endl;
		
		
	}else{
		while(t!=NULL){
			cout<<"["<<t->info<<"]";
			t=t->liga;
			
		}
	}
}

tnodo *crea(){
	tnodo *aux=NULL;
	aux=new tnodo;
	return aux;
	
}
void quita(tnodo*aux){
	delete aux;
}

tnodo *insertaprin(tnodo *p,int dato){
	
	tnodo *q=NULL,*t=NULL;
	if(p==NULL){
		p=crea();
		p->info=dato;
		p->liga=NULL;
		
	}else{
		q=crea();
		q->info=dato;
		q->liga=p;
		p=q;
		
	}
	return p;
	
	
}
tnodo *insertafin(tnodo *p,int dato){
	tnodo *q=NULL,*t=NULL;
	if(p==NULL){
		p=crea();
		p->info=dato;
		p->liga=NULL;
		
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

tnodo *insertaAntes(tnodo *p, int dato,int ref){
	tnodo *q=NULL, *r=NULL,*t=NULL;
	bool band=true;
	q=p;
	if(p==NULL){
		cout<<"Lista vacia, no hay referencia"<<endl;

	}else{
		while(q->info!=ref && band==true){
			if(q->liga!=NULL){
				t=q;
				q=q->liga;
			}else{
				band=false;
			}//fin if
		}//fin de while
		if(band==true){
		r=crea();
		r->info=dato;
		if(q==p){
			r->liga=p;
			p=r;
		}//fin if
		else{
		t->liga=r;
		r->liga=q;
		}
		cout<<endl<<"Dato insertado"<<endl;
		}//fin else
		else{
		cout<<endl<<"Referencia no encontrada,nodo no insertado"<<endl;
 		}
 	}
		return(p);
}

void elimina_antes(tnodo*p, int referencia){
    tnodo*q=p,*t,*r;
    bool band=true;

    if(p==NULL){
        cout<<endl<<"ERROR: Lista vacia, la referencia no existe"<<endl;
    }else{
        if(p->info==referencia){
            cerr<<endl<<"ERROR: No existe un nodo antes de la referencia"<<endl;
        }else{
            while(q->info!=referencia||band==true){
                if(q->liga==NULL){
                    band=false;
                }else{
                    r=t;
                    t=q;
                    q=q->liga;
                }
            }
            if(band==true){
                if(p->liga==q){
                    p=p->liga;
                }
				else{
					r->liga=q;
				}
				quita(t);
				cout<<endl<<"Nodo eliminado"<<endl;
            }else{
				cout<<endl<<"Referencia no encontrada, nodo no eliminado"<<endl;
			}//fin if

        }
    }
	return(p);
}