//Tomas Alberto Alegria Martinez
//281870
#include <iostream>
#include <fstream>

using namespace std;

struct alcohol{
    int cantidad;
    float precio;
    char nombre[15];
};

int contarlineas();
void creararch(int lineas);
int main(){ 
    int lineas;
    lineas=contarlineas();
    creararch(lineas);

}

int contarlineas(){
    ifstream archivo("booze.txt");
    string linea;
    int lineas;
    while(getline(archivo,linea)){
        lineas++;
    }
    return lineas;
    archivo.close();

}
void creararch(int lineas){
    ifstream archivo("booze.txt", ios::binary);
    ofstream ofile("stock.txt", ios::binary| ios::trunc);
    if(!(archivo&&ofile)){
        cout<<"No se pudo abrir alguno de los archivos."<<endl;
        
    }
    archivo.seekg(0,ios::beg);
    alcohol reg[lineas];
    while(!archivo.eof()){
        for(int i=0;i<lineas; i++){
            archivo >> reg[i].cantidad;
            archivo >> reg[i].precio;
            archivo>> reg[i].nombre;
        }
    }
    float value;
    float total;
    ofile.seekp(0, ios::beg);
    int f = 0;
    ofile<< "Quantity   "<<"Price   "<<"Value   "<<"Description"<<endl;
    while (f<lineas)
    {
        value= reg[f].cantidad*reg[f].precio;
        total+=value;
        ofile << reg[f].cantidad<<"     ";
        ofile << reg[f].precio<<"           ";
        ofile << value << "        ";
        ofile << reg[f].nombre << endl;
        f++;
    }
    ofile<<"Total:      $"<<total<<endl;
    archivo.close();
    ofile.close();

}