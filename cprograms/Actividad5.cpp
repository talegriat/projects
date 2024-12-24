//Tomas Alberto Alegria Martinez
//281870
#include<iostream>
#include <fstream>
#include <string.h>

using namespace std;

void abrir();
void escribir(char* argc);

    int main(int argc, char *argv[]){
    char nom[30];
    if(atoi(argv[1])){

    }

}

void abrir(){
    ifstream archivo("/home/talegria/cprograms/Texto.txt");
    if(archivo){
        cout<<"Error al abrir el archivo..."<<endl;
        exit(1);

    }
    string palabra;
    getline(archivo,palabra);
    archivo>>palabra;
    cout<<palabra<<endl;

    archivo.close();
}
void escribir(char*argc){
    ofstream ofile;
    ofile.open("Texto.txt");    
    if(!ofile){
        cout<<"No se pudo abrir el archivo...";
        exit(1);
    }

    
    ofile <<argc<<endl;
    ofile.close();

}