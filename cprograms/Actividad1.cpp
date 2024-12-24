//Tomas Alberto Alegria Martinez
//281870

//Genera un programa que te permita introducir tu edad y la edad de un amigo. Una vez que tengas ambas edades deberas compararlas para desplegar un mensaje diciendo si eres más joven
//que tu amigo, si eres mas viejo que tu amigo o si tienen la misma edad

#include<iostream>

using namespace std;
//prototipo
void comparar(int edad, int amigo);
int main(){
    int edad,amigo;
    cout<<"Actividad 1"<<endl<<endl;
    cout<<"Dame tu edad: ";
    cin>>edad;
    cout<<endl<<"Dame la edad de tu amigo: ";
    cin>>amigo;
    comparar(edad, amigo);
return 0;
}
void comparar(int edad, int amigo){
    if(edad==amigo){
        cout<<endl<<"Tienen la misma edad"<<endl;
    }
    else{
        if(edad>amigo){
            cout<<endl<<"Eres mayor que tu amigo"<<endl;
        }
        else{
            cout<<endl<<"Eres menor que tu amigo"<<endl;
        }
    }
}