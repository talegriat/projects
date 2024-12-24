//Tomas alberto Alegria Martinez
//ejemplo 13

#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ofstream ofile;
    ofile.open("test13.txt");    
    if(!ofile){
        cout<<"No se pudo abrir el archivo...";
        exit(1);
    }

    
    ofile << "Hola Putos"<<endl;
    ofile.close();
    return 0;

}