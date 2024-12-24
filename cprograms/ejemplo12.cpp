#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ofstream file("test1.txt",ios::app);//generamos una referencia a un archivo llamado
                                        //la carpeta del output de VSCODE en modo salida secuencial
    
    if(!file){
        cout<<"No se pudo abrir el archivo...";
        exit(1);
    }

    file << "Hola ";
    file << "Mundo"<<endl;
    file.close();
    return 0;

    

}