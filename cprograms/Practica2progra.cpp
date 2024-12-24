//Tomas Alberto Alegria Martinez
//281870
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct Lista{
    int id;
    char producto[15];
    int existencia;
    int precio;    
};

struct Lista pasardatos(ifstream& archivo, int id);
void original();
int main(){
    ifstream archivo("./productos.txt",ios::binary);
    if(!archivo){
        cout<<endl<<"No se pudo abrir el archivo correctamente."<<endl;
        return 1;
    }
    cout<<endl<<"Dame el id del producto que deseas eliminar: ";
    int id;
    cin>>id;
    Lista borrar;
    borrar= pasardatos(archivo, id);
    cout<<"El producto eliminado fue:  "<<borrar.producto<<endl;
    original();
    ifstream original("productos.txt");

    if(!original){
        cout<<endl<<"No se pudo abrir el archivo correctamente. "<<endl;
    }
    original.seekg(0, ios::beg);

    string lineas;
    cout<<endl<<"Archivo Actualizado: "<<endl;
    while(!original.eof()){ 
        while(getline(original,lineas)){
             cout<<lineas<<endl;
        }
    }
    
    original.close();
    return 0;
}

struct Lista pasardatos(ifstream& archivo, int id){
    ofstream copia("Copia.txt",ios::binary);
    if(!copia){
        cout<<endl<<"No se pudo abrir el archivo copia correctamente. "<<endl;
    }
    //Lista registro2= {0," ",9999,8888};
    //char test [40];
    
    //copia.write((char *) &registro, sizeof(struct Lista));

    //copia.close();
    //ifstream copia2("Copia.txt",ios::binary); 
    //if(!copia2){
        //cout<<endl<<"No se pudo abrir el archivo correctamente. "<<endl;
    //}
    ///if(copia2.read((char *)&registro2,sizeof(Lista)))
       //cout<<"--"<<test<<endl;
    /*while(archivo.read((char *)&registro,sizeof(Lista))){
        if(registro.id!=0){
            if(registro.id==id){
                cout<<"Se encontro el dato."<<endl;
                borrar.id=registro.id;
                strncpy(borrar.producto, registro.producto, 50);
                borrar.existencia=registro.existencia;
                borrar.precio=registro.precio;
            }
            else
            copia<<registro.id<<registro.producto<<registro.existencia<<registro.precio<<endl;

        }
    }*/
    // Leer el archivo caracter por caracter y contar las líneas
    string linea;
    int lineas=0;
    while(getline(archivo,linea)){
        lineas++;
    }
    archivo.close();
    ifstream archivo2("productos.txt");
    archivo2.seekg(0, ios::beg);
    Lista registro[lineas];
    Lista borrar={0,"",0,0};
    while (!archivo2.eof())
    {
        for(int i=0; i<=lineas-1;i++){ 
            archivo2 >> registro[i].id;
            archivo2 >> registro[i].producto;
            archivo2 >> registro[i].existencia;
            archivo2 >> registro[i].precio;
        }
    }

    copia.seekp(0, ios::beg);
    int f = 0;
    while (f<lineas)
    {
        if(registro[f].id==id){
            borrar.id= registro[f].id;
            strncpy(borrar.producto, registro[f].producto, 15);            
            borrar.existencia= registro[f].existencia;
            borrar.precio= registro[f].precio;
        }
        else{ 
        copia << registro[f].id<<"          ";
        copia << registro[f].producto<<"           ";
        copia << registro[f].existencia << "        ";
        copia << registro[f].precio << endl;
        }
        f++;
    }

    archivo2.close();
    copia.close();
    return borrar;

}

void original(){
    int lineas=0;
    ifstream copia("Copia.txt",ios::binary);
    ofstream archivo("productos.txt",ios::binary|ios::trunc);//Se elimina todo lo que tenia el archivo, para pasarle la lista con los productos ya eliminados
    if(!(copia&&archivo)){
        cout<<"No se puede abrir el archivo"<<endl;

    }
   
    else{
        
        copia.seekg(0,copia.end);//final del archivo
        long size= copia.tellg(); //Obtiene cantidad de bytes del archivo
        copia.seekg(0);//inicio del archivo
        char *buffer=new char[size];// Se crea un espacio con el tamaño que tiene el archivo
        copia.read(buffer,size);//lee el contenido del archivo
        archivo.write(buffer,size);//paso puntero y cantidad
        delete[]buffer;
        copia.close();
        archivo.close();

    }
    

}