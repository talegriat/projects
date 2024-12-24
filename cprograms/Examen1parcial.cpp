//Tomas Alberto Alegria Martinez
//ascendente de menor a mayor


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;
void insertionsort();



int main(){
    insertionsort();
    

    return 0;
}

void insertionsort(){
    cout<<endl<<"Cuantos numeros deseas almacenar: ";
    int num;
    cin>>num;
    int *vec;
    
    vec=new int[num];
    for(int i=0; i<num; i++){
        cout<<endl<<"Dame el numero que deseas ingresar: ";
        cin>>vec[i];
    }

int x;
int j;
int i=1;

while(i< num){
    x=vec[i];
    j=i-1;
    while(j>=0 && vec[j]>x){
        vec[j+1]=vec[j];
        j=j-1;
    }
    vec[j+1]=x;
    i++;
}

ofstream ofile("ordenados.txt", ios::app);
    if(!(ofile)){
        cout<<"No se pudo abrir alguno de los archivos..."<<endl;
        exit(1);
    }
    else{
        ofile<<"Datos Ordenados"<<endl;
        for(int h=0; h<num; h++){
            ofile<<vec[h]<<endl;
        }
        ofile.close();
        
    }
delete[]vec;
}