//Tomas Alberto Alegria Martinez
//281870

//Realizar un programa en el cual uses los argumanetos del main para pasarle dos argumentos.
//El primero sera de control, pudiendo ser los números 1 o 2, en donde el 1 solo abrira el archivo
//haciendo una salida de los datos leidos en el archivo por medio de cout, ignorando el segundo argumento
//Si el primer argumento resultara ser el 2 entonces se abrira el archivo en modo escritura y colocaras el 
//segundo argumento dentro del archivo. Si el usuario ingresa cualquier otra cosa que no sean las variabes 
//de control el programa no debera realizar ninguna accion

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

// Prototipos
void abrirarch();
void escribir(string cadena);

int main(int argc, char* argv[]) {
    if (argc < 3) {
        return 1;
    }
    int dato1 = atoi(argv[1]);
    string cadena2 = argv[2];
    if (dato1 == 1) {
        abrirarch();
    } else if (dato1 == 2) {
        escribir(cadena2);
    } else {
        cout << "Los datos ingresados en el primer argumento no son válidos, deben ser 1 o 2" << endl;
    }

    return 0;
}

void abrirarch() {
    ifstream archivo("Textoact5.txt");
    if (!archivo) {
        cout << "Error al abrir el archivo..." << endl;
        exit(1);
    }
    string palabra;
    getline(archivo, palabra);
    cout << palabra << endl;

    archivo.close();
}

void escribir(string cadena) {
    ofstream ofile;
    ofile.open("Textoact5.txt", ios::app);
    if (!ofile) {
        cout << "No se pudo abrir el archivo..." << endl;
        exit(1);
    }
    ofile << cadena; // Usamos << para escribir la cadena en el archivo

    ofile.close();
}

