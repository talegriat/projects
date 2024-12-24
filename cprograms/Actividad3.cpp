//Tomas Alberto Alegria Martinez
//281870

//Programa que te permita obtener las calificaciones de un estudiante. Tendras que preguntar cuantos alumnos y calificaciones capturaras
//hay que hacer uso de arreglos y estructuras dinamicas

#include <iostream>

using namespace std;


struct Estudiante {
    string nombre;
    int numCalificaciones;
    float *calificaciones;
};

void capturarCalificaciones(Estudiante &estudiante); 
float calcularPromedio(const Estudiante &estudiante);

int main() {
    int num;

    cout << "¿Cuántos estudiantes desea ingresar? ";
    cin >> num;

    Estudiante *estudiantes = new Estudiante[num];

    for (int i = 0; i < num; ++i) {
        capturarCalificaciones(estudiantes[i]);
    }

    cout << "\nResumen de calificaciones:\n";

    for (int i = 0; i < num ; ++i) {
        cout << "Estudiante: " << estudiantes[i].nombre << endl;
        cout << "Calificaciones: ";
        for (int j = 0; j < estudiantes[i].numCalificaciones; ++j) {
            cout << estudiantes[i].calificaciones[j] << ", ";
        }
        cout << "\nPromedio: " << calcularPromedio(estudiantes[i]) <<endl<<endl;
    }

    delete[] estudiantes;

    return 0;
}
void capturarCalificaciones(Estudiante &estudiante) {
    cout << "Ingrese el nombre del estudiante: ";
    cin >> estudiante.nombre;

    cout << "¿Cuántas calificaciones desea capturar para " << estudiante.nombre << "? ";
    cin >> estudiante.numCalificaciones;

    estudiante.calificaciones = new float[estudiante.numCalificaciones];

    for (int i = 0; i < estudiante.numCalificaciones; ++i) {
        cout << "Ingrese la calificación #" << (i + 1) << ": ";
        cin >> estudiante.calificaciones[i];
    }
}

float calcularPromedio(const Estudiante &estudiante) {
    if (estudiante.numCalificaciones == 0) {
        return 0.0;
    }

    float suma = 0.0;
    for (int i = 0; i < estudiante.numCalificaciones; ++i) {
        suma += estudiante.calificaciones[i];
    }

    return suma / estudiante.numCalificaciones;
}

