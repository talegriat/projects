//metodo lectura

#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

int main(){

cout<<"Dame el nombre del archivo: ";
fflush(stdin);
string nom;
getline(cin,nom);
fflush(stdin);

    ifstream ifile(nom.c_str());
    if(ifile){
        cout<<"Error al abrir el archivo..."<<endl;
        exit(1);

    }
    string palabra;
    getline(ifile,palabra);
    ifile>>palabra;
    cout<<" Ya leimos la palabra"<<endl;
    cout<<palabra<<endl;

    ifile.close();

    return 0;
}