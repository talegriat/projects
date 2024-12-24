//Tomas Alberto Alegria Martinez
//281870

//Programa en el cual calcularas la circunferencia, area y volumen de un circulo, para lo cual
//podras ingresar el radio y/o diametro.Utiliza funciones y creacion de nuevos tipos(enum,struct y union)

#include <iostream>
#include <cmath>

using namespace std;

enum Opcion { RADIO, DIAMETRO };

struct Circulo {
    float radio;
    float diametro;
};

float calcularCircunferencia(const Circulo &circulo); 

float calcularArea(const Circulo &circulo);
float calcularVolumen(const Circulo &circulo, float altura);


int main() {
    Circulo circulo;
    float altura;
    Opcion opcion;

    cout << "¿Deseas ingresar el radio o el diámetro? (0 para radio, 1 para diámetro): ";
    int opcionInt;
    cin >> opcionInt;

    // Convertir la entrada del usuario en una opción enum
    if(opcionInt == 0){
        opcion=RADIO;
    }
    else{
        opcion=DIAMETRO;
    }

    if (opcion == RADIO) {
        cout << "Ingresa el radio del círculo: ";
        cin >> circulo.radio;
        circulo.diametro = 2 * circulo.radio;
    } else {
        cout << "Ingresa el diámetro del círculo: ";
        cin >> circulo.diametro;
        circulo.radio = circulo.diametro / 2;
    }

    cout << "Ingresa la altura para calcular el volumen: ";
    cin >> altura;

    cout << "Circunferencia: " << calcularCircunferencia(circulo) << endl;
    cout << "Área: " << calcularArea(circulo) << endl;
    cout << "Volumen: " << calcularVolumen(circulo, altura) << endl;

    return 0;
}
float calcularCircunferencia(const Circulo &circulo) {
    return 2 * M_PI * circulo.radio;
}

float calcularArea(const Circulo &circulo) {
    return M_PI * pow(circulo.radio, 2);
}

float calcularVolumen(const Circulo &circulo, float altura) {
    return calcularArea(circulo) * altura;
}