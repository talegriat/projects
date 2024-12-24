//Tomas Alberto Alegria Martinez
//281870
//Practica de vectores dinamicos
#include<iostream>
#include <stdlib.h>
using namespace std;
void ruletarusa(int n);
void baraja(int n);
void shuffle(int *vec, int n);
void interseccion(int vec1[8],int vec2[10]);

int main(){
srand(time(NULL));
cout<<"Dame un tamano para el vector dinamico: "<<endl;
int num;
cin>>num;
cout<<"Ruleta Rusa: "<<endl;
ruletarusa(num);

cout<<"Dame un tamaño para la baraja: ";
int bar;
cin>>bar;
baraja(bar);
int vec1[8]={2,4,12,9,2,15,4,2};
int vec2[10]={4,6,8,10,5,7,1,13,14,24};
interseccion(vec1,vec2);



return 0;


}
void ruletarusa(int n){
    int *vec;
    vec= new int[n];
    float porc;
    int v;
    porc= float(n)*(0.30);
    v=int(porc);
    cout<<v<<endl;
    int t;
    int unos=0;
    for(int j=0; j<n; j++){
        vec[j]= 0;
    }

    while(unos<v){
    t=rand()%(n-1);
    if(vec[t]==0){
        vec[t]=1;
        unos++;
    }
    }
   for(int i=0; i<n; i++){
    cout<<vec[i]<<",";
   }
   cout<<endl;
   delete[]vec;
}

void baraja(int n){
int *vect;
vect=new int[n];
for(int i=0; i<n; i++){
    vect[i]=i+1;
}
shuffle(vect,n);
for(int i=0; i<n; i++){
    cout<<vect[n]<<" ";
}
cout<<endl<<endl;
delete[]vect;
}
void interseccion(int vec1[8],int vec2[10]){
    int cont=0;
    int k=0;
    for(int i=0; i<8; i++){
        for(int j=0; i<10; j++){
            if(vec1[i]==vec2[j]){
                k++;
            }
        }
    }
    int *vec;
    vec=new int[k];
    for(int i=0; i<10; i++){
        for(int j=0; j<8; j++){
            if(vec1[i]==vec2[j]){
                vec[cont]=vec1[i];
                cont++;
            }
        }
    }

for(int i=0; i<k; i++){
    cout<<vec[i]<<",";
}

}

void shuffle(int *vec, int n){
    if(n>1){
        for(int i=0; i<n-1;i++){
            int k= i+rand()/(RAND_MAX/(n-i)+1);
            int j=vec[i];
            vec[k]=vec[i];
            vec[i]=j;
        } 
    }
}