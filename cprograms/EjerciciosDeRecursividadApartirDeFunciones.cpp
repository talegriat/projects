//Tomas Alberto Alegria Martinez
//281870
//Dadas las siguientes funciones recursivas, implementelas en programacion
//fecha de entrega
#include<iostream>
#include <cmath>
#include <cstring>
#define TAM 10

using namespace std;

//prototipos
int fib(int n);
int euc(int n,int m);
//la funcion de akerman num usada en la teoria computacional
int ak(int m, int n);
int particion(int m, int n);
int triangulopascal(int n, int k);
//investigar e implementar las torres de hanoi
int Torresh(int elementos, char A, char B, char C);
float Capital(float m, float x, int n);
char cadena(char cad[], int n);
int elevado(int a, int b);
int buscar(int vec[TAM], int n, int x);







int main(){
    int opcion;
    do {
        cout << "Menú de opciones:" << endl;
        cout << "1. Calcular el n-ésimo número de Fibonacci" << endl;
        cout << "2. Calcular el máximo común divisor (MCD) usando el algoritmo de Euclides" << endl;
        cout << "3. Calcular la función de Ackermann" << endl;
        cout << "4. Calcular las particiones de un número" << endl;
        cout << "5. Calcular un valor en el Triángulo de Pascal" << endl;
        cout << "6. Resolver las Torres de Hanoi" << endl;
        cout << "7. Calcular el capital con interés compuesto" << endl;
        cout << "8. Invertir una cadena de caracteres" << endl;
        cout << "9. Calcular A elevado a la B" << endl;
        cout << "10. Buscar un valor en un arreglo" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int n;
                cout << "Ingrese el valor de n: ";
                cin >> n;
                int resultado = fib(n);
                cout << "El resultado de Fibonacci para " << n << " es: " << resultado << endl;
                break;
            }
            case 2: {
                int n, m;
                cout << "Ingrese el valor de n: ";
                cin >> n;
                cout << "Ingrese el valor de m: ";
                cin >> m;
                int resultado = euc(n, m);
                cout << "El MCD de " << n << " y " << m << " es: " << resultado << endl;
                break;
            }
            case 3: {
                int m, n;
                cout << "Ingrese el valor de m: ";
                cin >> m;
                cout << "Ingrese el valor de n: ";
                cin >> n;
                int resultado = ak(m, n);
                cout << "El resultado de la función de Ackermann para m=" << m << " y n=" << n << " es: " << resultado << endl;
                break;
            }
            case 4: {
                int m, n;
                cout << "Ingrese el valor de m: ";
                cin >> m;
                cout << "Ingrese el valor de n: ";
                cin >> n;
                int resultado = particion(m, n);
                cout << "El número de particiones de " << m << " en sumandos de hasta " << n << " es: " << resultado << endl;
                break;
            }
            case 5: {
                int n, k;
                cout << "Ingrese el valor de n: ";
                cin >> n;
                cout << "Ingrese el valor de k: ";
                cin >> k;
                int resultado = triangulopascal(n, k);
                cout << "El valor en el Triángulo de Pascal para n=" << n << " y k=" << k << " es: " << resultado << endl;
                break;
            }
            case 6: {
                int numElementos;
                cout << "Ingrese el número de elementos: ";
                cin >> numElementos;
                int movimientos = Torresh(numElementos, 'A', 'B', 'C');
                cout << "Se realizaron " << movimientos << " movimientos en las Torres de Hanoi." << endl;
                break;
            }
            case 7: {
                float m, x;
                int n;
                cout << "Ingrese el capital inicial (m): ";
                cin >> m;
                cout << "Ingrese la tasa de interés (x en %): ";
                cin >> x;
                cout << "Ingrese el número de años (n): ";
                cin >> n;
                float capitalFinal = Capital(m, x, n);
                cout << "El capital final después de " << n << " años es: " << capitalFinal << endl;
                break;
            }
            case 8: {
                string Cadena;
                cout << "Ingrese una cadena de caracteres: ";
                cin.ignore(); // Ignorar el salto de línea pendiente.
                getline(cin, Cadena);
                int n = Cadena.length();
                char cad[n + 1];
                strcpy(cad, Cadena.c_str());
                cadena(cad, n);
                cout << "La cadena invertida es: " << cad << endl;
                break;
            }
            case 9: {
                int a, b;
                cout << "Ingrese el valor de A: ";
                cin >> a;
                cout << "Ingrese el valor de B: ";
                cin >> b;
                int resultado = elevado(a, b);
                cout << "El resultado de " << a << " elevado a la " << b << " es: " << resultado << endl;
                break;
            }
            case 10: {
                int vec[TAM], n, x;
                cout << "Ingrese el tamaño del arreglo: ";
                cin >> n;
                cout << "Ingrese los elementos del arreglo en orden decreciente:" << endl;
                for (int i = 0; i < n; i++) {
                    cin >> vec[i];
                }
                cout << "Ingrese el valor a buscar: ";
                cin >> x;
                int encontrado = buscar(vec, n, x);
                if (encontrado != -1) {
                    cout << "El valor " << x << " se encuentra en la posición " << encontrado << " del arreglo." << endl;
                } else {
                    cout << "El valor " << x << " no se encuentra en el arreglo." << endl;
                }
                break;
            }
            case 0:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);

    return 0;
}


int fib(int n){
    if(n==0||n==1){
        return n;
    }
    else{
        return fib(n-1)+fib(n-2);
    }
}
int euc(int n, int m){
    if(n==0){
        return m;
    }
    else{
        return euc(n,m%n);
    }
}
int ak(int m,int n){

    if(m==0){
        return n+1;
    }
    
}

//la funcion particion nos permite conocer todas las formas en las cuales un entero positivo puede ser descompuesto
int particion(int m, int n){
    if(m==1){
        return 1;
    }
    if(n==1){
        return 1;
    }
    if(m<n){
        return particion(m,m);
    }
    if(m==n){
        return 1+particion(m,m-1);
    }
    if(m>n){
        return particion(m,n-1)+particion(m-n,n);
    }
}

int triangulopascal(int n, int k){
    if(k==0||n==k){
        return 1;
    }
    if(n>k>0){
        return triangulopascal(n-1,k)+triangulopascal(n-1,k-1);
    }
}


int Torresh(int elementos, char A, char B, char C){
    static int movimiento =0;
    if(elementos > 0){
        Torresh(elementos -1,A,B,C);
        cout<<"Se movio el disco"<<elementos<<"de "<<A<<"a "<<C;
        movimiento++;
        Torresh(elementos -1, B,A,C);
    }
    return movimiento;
    
    

}


//Determinar el capital que se tendra al cabo de n años.
float Capital(float m, float x, int n){
    if(n==0){
        return m;
    }
    else{
        return Capital(m+(m*(float(x/100))), x, n-1);
    }
}

//programa que invierta el orden de una cadena de caracteres
char cadena(char cad[], int n){
    for(int i=n-1; i>-1; i--){
        return cad[i];
    }

}



//Funcion recursiva que busque un valor x en un arreglo unidimensional de enteros, ordenado
// en forma decreciente
int buscar(int vec[TAM], int n, int x){
      if(n == 0){ 
        return -1; // No se encontró el valor en el arreglo.
    }
    if(vec[n-1] == x){
        return n-1; // Se encontró el valor en la posición 'n-1' del arreglo.
    }
    else{
        return buscar(vec, n-1, x);
    }
}


//Funcion recursiva que calcule A elevado a la B
int elevado(int a, int b){
    if(a<=0 || b<0 ){
        return 1;
    }
    else{
        if(b==0){
            return 1;//cualquier valor elevado a la cero es 1
        }
        else{
            return a*elevado(a,b-1);
        }
    }
}




