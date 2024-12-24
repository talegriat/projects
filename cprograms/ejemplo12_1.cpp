//Tomas alberto Alegria Martinez
//ejemplo 13
#include <iostream>
#include <fstream>
using namespace std;

int main(){
    fstream file(test2.txt, ios::app|ios::out);//ios::trunc es para borrar el archivo y lo vuelve a reescribir, el app sirve para generar lineas
    if(!file){
        cout<<"No se pudo abrir el archivo...";
        exit(1);
    }

    file << "Hola ";
    file << "Mundo"<<endl;
    file.close();
    return 0;
}