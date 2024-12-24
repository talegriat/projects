//Tomas Alberto Alegria Martinez
//281870
#include <iostream>
#include <fstream>

using namespace std;

struct productos{
    int id;
    string nomarticulo;
    double precio; 
    int existencia;
};
int contarlineas();

int main(){
    int lineas;
    lineas=contarlineas();
    productos *arreglos= new productos[lineas];
    ifstream archivo("articulos.txt",ios::binary);
    if(!archivo){
        cout<<"El archivo no se pudo abrir. "<<endl;
    }
    for(int i=0; i<lineas; i++){
        archivo>>arreglos[i].id;
        archivo>>arreglos[i].nomarticulo;
        archivo>>arreglos[i].precio;
        archivo>>arreglos[i].existencia;
    }
    cout<<"Imprimir arreglo: "<<endl;
    cout<<"Id   Nombre del articulo   Precio    Existencia"<<endl;
    for(int i=0; i<lineas;i++){
        cout<<arreglos[i].id<<"       ";
        cout<<arreglos[i].nomarticulo<<"        ";
        cout<<arreglos[i].precio<<"         ";
        cout<<arreglos[i].existencia<<endl;
    }
    archivo.close();
    delete[]arreglos;
    return 0;
}
int contarlineas(){
    ifstream archivo("articulos.txt");
    string linea;
    int lineas;
    while(getline(archivo,linea)){
        lineas++;
    }
    return lineas;
    archivo.close();
}
