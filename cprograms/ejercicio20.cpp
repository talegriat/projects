#include <iostream>

using namespace std;

class caja{

    //no podemos asignar atributos con valores especificos
    double largo;
    double ancho;
    double alto;

    public:
        caja(double lar, double an, double alt){
            largo=lar;
            ancho=an;
            alto=alt;

        }
        double volumen(){
            return largo*ancho*alto;
        }
};

int main(){
    caja unaCaja(1.45,0.98,2.54);

    cout<<endl<<"El volumen de la caja es: "<<unaCaja.volumen()<<endl;

    return 0;
}