//registro de usuarios de un banco
#include <iostream>
#include <fstream>
#include<cstring>

using namespace std;
fstream archivo;
struct cliente{
    int numCuenta;
    char nombre[50];
    float monto;

};
//prototipos
void creastruct();
int menu();
void escribirRegistro();
int capturaCuenta();
void leerRegistro();
void mostrarRegistro();
void Borrar_Cliente(int num);
bool verificacion_cuenta(int cuenta);




int main(){
    int resp,opc;
    int Numc;
    archivo.open("banco.dat",ios::binary|ios::in|ios::out);//archivo de entrada,salida y binario
    if(!archivo){
        cout<<"No se pudo abrir el archivo........"<<endl;
        cout<<"Deseas crear la estructura de los clientes: "<<endl;
        cout<<"Si(1) no(2)"<<endl;
        cin>>resp;
        if(resp==2) return 1;
        creastruct();
        archivo.open("banco.dat",ios::binary|ios::in|ios::out);//archivo de entrada,salida y binario
        do{
            opc=menu();
            switch(opc){
                case 1: escribirRegistro();
                    break;
                case 2: 
                    leerRegistro();
                    break;
                case 3:
                    mostrarRegistro();
                    break;
                case 4:
                    archivo.close();
                    creastruct();
                    archivo.open("banco.dat",ios::binary|ios::in|ios::out);//archivo de entrada,salida y binario
                    break;
                case 5:
                    Borrar_Cliente();
                    break;
                case 6:
                    cout<<endl<<"Fin del programa.................."<<endl;
                    break;
                default:
                    cout << "Opción no válida. Por favor, elige una opción válida." << endl;
                break;
            }

        }while(opc!=6);
        archivo.close();
        return 0;
           
    }

return 0;
}
//funciones
int menu(){
    int op;
    cout<<endl;
    cout<<endl<<"Menu para problar los archivos binarios";
    cout<<endl<<"1. Escribir un registro...";
    cout<<endl<<"2. Leer un registro... ";
    cout<<endl<<"3. Mostrar un resgistro";
    cout<<endl<<"4. Crear de nuevo la estructura...";
    cout<<endl<<"5. Salir";
    cout<<endl<<"Que opcion quieres:  ";
    fflush(stdin);
    cin>>op;
    return op;
}

void creastruct(){
    archivo.open("banco.dat",ios::binary|ios::out);
    cliente blank={0,"",0};//registro en blanco
    for(int i=0;i<10;i++){
        archivo.write((char *)&blank,sizeof(cliente));
    }

    cout<<endl<<"creamos la estructura de 10 clientes en nuestros en el archivo";
    archivo.close();
    
}

void escribirRegistro(){
    cliente registro;
    bool band;
    cout<<endl<<"Registro de datos"<<endl;
    int cuenta = capturaCuenta();
    band=verificacion_cuenta(cuenta);
    if(band){
        cout<<endl<<"Esta cuenta ya se encuentra ocupada.";

    }
    else{ 
    cout<<"Dame un nombre: ";
    cin.getline(registro.nombre,40);
    cout<<endl<<"Dame el monto de la cuenta: "<<endl;
    cin>>registro.monto;
    registro.numCuenta=cuenta;
    archivo.seekp((cuenta-1)*sizeof(cliente),ios::beg);//beg para el inicio
    archivo.write((char *)&registro,sizeof(cliente));
    cout<<endl<<"El registro se guardo exitosamente";
    }
}
int capturaCuenta(){
    int cuenta;
    do{
        cout<<endl<<"Ingresa cuenta: ";
        fflush(stdin);
        cin>>cuenta;
        if(cuenta<1||cuenta>10){
            cerr<<endl<<"ERROR, cuentas validas solo entre 1 y 10";

        }
    }while(cuenta<1||cuenta>10);
    fflush(stdin);
    return cuenta;

}
void leerRegistro(){
    cliente blank ={0,"",0};
    cliente registro;

    registro=blank;//limpia la variable de registro
    cout<<endl<<"Consulta de cuentas"<<endl;
    int cuenta= capturaCuenta();
    archivo.seekg((cuenta -1)* sizeof(cliente));
    archivo.read((char *)&registro,sizeof(cliente));
    if(strlen(registro.nombre)==0){
        cout<<endl<<"Registro en blanco"<<endl;

    }
    else{
        cout<<endl<<"Datos del cliente..."<<endl;
        cout<<endl<<"Nombre: "<<registro.nombre<<"Monto: "<<registro.monto<<endl;


    }

}
void mostrarRegistro(){
    cliente registro;
    cout<<endl<<"Leyendo secuencialmente el archivo binario";
    archivo.clear();//
    archivo.seekg(0);
    cout<<endl;
    while(archivo.read((char *)(&registro),sizeof(cliente))){
        if(registro.numCuenta!=0){
            cout<<endl;
            cout<<endl<<"Cuenta: "<<registro.numCuenta;
            cout<<endl<<"Nombre: "<<registro.nombre;
            cout<<endl<<"Monto:  "<<registro.monto;


        }
    }
    archivo.clear();
    archivo.seekg(0);
}

void Borrar_Cliente(){
    int cuenta;
cout<<"Borrar cuenta"<<endl;
   cuenta= capturaCuenta();
  cliente blank ={0,"",0};
   archivo.seekg((cuenta -1)* sizeof(cliente));
   archivo.write((char *)&blank,sizeof(cliente));
   cout<<"Cuenta Borrada"<<endl;
   archivo.seekg(0);
   archivo.clear();

}
bool verificacion_cuenta(int cuenta){
    bool band=false;
    cliente registro;
    while(archivo.read((char *)(&registro),sizeof(cliente))){
        if(registro.numCuenta==cuenta){
            band=true;//ya esta registrada
            break;
        }
    }
    
    return band;
}