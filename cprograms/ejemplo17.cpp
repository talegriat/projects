//copia el contenido de un archivo a otro
#include<iostream>
#include <fstream>

using namespace std;

int main(){
    ifstream ifile("test3.txt",ios::binary);
    ofstream ofile("test4.txt",ios::binary);

    if(!(ifile && ofile)){
        cout<<"No se pudo abrir alguno de los archivos..."<<endl;
        exit(1);

    }
ifile.seekg(0,ios::end);//se ubica en el final del archivo
    //(0,ifile.end)
    long tam= ifile.tellg();//es para la distancia
    ifile.seekg(0);//para ponerse en el inicio del archiov

    char *buff= new char[tam];//se crea un espacio con el tamaño
    ifile.read(buff,tam);//paso puntero y cantidad

    ofile.write(buff,tam);
    delete[]buff;
    ofile.close();
    ifile.close();
    return 0;


}