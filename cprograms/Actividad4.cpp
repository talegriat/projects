//Tomas Alberto Alegria Martinez
//28170

//Programa en el cual usas los argumentos del main para pasarle al programa dos datos 
//del tipo cadenas de caracteres y despues de que las ingreses las concatenaras para imprimirlas 
//en la misma llamada desde la consola del DOS

#include<iostream>

using namespace std;


int main(int argc, char* argv[]){

    string cadena1= argv[1];
    string cadena2= argv[2];
    //en el argv[0] se guarda el nombre del programa
    string resultado = cadena1 + cadena2;  //se concatenan las cosa cadenas de caracteres

    cout<<endl<<"Cadenas concatenadas: "<<resultado<<endl;





return 0;
}

