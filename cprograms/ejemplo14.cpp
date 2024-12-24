//tomas alberto Alegria Martinez
//metodo lectura

#include<iostream>
#include<fstream>

using namespace std;

int main(){
    ifstream ifile("test13.txt");
    if(ifile){
        cout<<"Error al abrir el archivo..."<<endl;
        exit(1);

    }
    string palabra;
    ifile>>palabra;
    cout<<" Ya leimos la palabra"<<endl;
    cout<<palabra<<endl;
    ifile.close();




    return 0;
}