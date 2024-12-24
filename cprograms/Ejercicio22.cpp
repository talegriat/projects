//tomas Alberto alegria Martinez
//281870
//Circunferencia
#include<iostream>
#include <math.h>
using namespace std;

//clases
class circunferencia{
    //atributos
    private:
        float radio;
    //metodos o el comportamiento
    public:
        float calcularArea();
        float getRadio();//retorna el valor del radio
        void setRadio(float radio);//Obtener el valor del radio


};

//Constructores
float circunferencia :: calcularArea(){
    float area;
    area=M_PI * this->radio * this->radio;
    return area;
}

float circunferencia:: getRadio(){
    return this->radio;
}
void circunferencia:: setRadio(float radio){
    this->radio= radio;

}

int main(){
    circunferencia circulo;
    float area,rad;
    cout<<"Dame el valor del radio: ";
    cin>>rad;
    circulo.setRadio(rad);
    area=circulo.calcularArea();
    cout<<endl<<"El area es: "<<area<<endl;
    cout<<endl<<"El radio es: "<<circulo.getRadio();

    return 0;
    
}