#include <iostream>

using namespace std;

void display(char *);
void display(string);
void display(string, string);
void modifyString( string);
void modifyString( string *);


int main(){
    string str1;
    char str[100];

    cout<<"enter a string: ";
    getline(cin,str1);

    cout<<"enter another string: ";
    cin.get(str,100,'\n');

    display(str1);
    display(str);

    modifyString(&str1);

    display("after chagnes: ", str1);

    return 0;
}

void display(char s[]){

    cout<< "Entered char array is: "<< s << endl;

}

void display(string s){

    cout<< "Entered string is: "<< s << endl;

}

void display(string s, string s2){

    cout<< s << ": "<< s2 << endl;

}

void modifyString(string s){
    string str="The original string: ";

    s=str+s;
    s+=" -- has been modified, but just internaly";

    cout<< "inside modify string "<< s <<endl;
}

void modifyString(string *s){
    string str="The original string: ";

    *s=str+*s;
    *s+=" -- has been modified";

    cout<< "inside modify string "<< *s <<endl;
}
