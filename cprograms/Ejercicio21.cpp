//Tomas Alberto Alegria Martinez
//281870
//Uso del puntero this para referenciar un objeto
#include <iostream>

using namespace std;

class Prueba{
    public:
        Prueba(int =0);
        void imprime()const;

    private:
        int x;
};
//Constructores de los metodos
Prueba:: Prueba(int a){
    x=a;
}

void Prueba::imprime()const{
    cout<<"x= "<<x<<endl<<"this->x= "<<this->x<<endl<<"(*this).x= "<<(*this).x<<endl;
}


int main(){
cout<<"Dame un numero: ";
int num;
cin>>num;
Prueba test(num);
test.imprime();
return 0;
}