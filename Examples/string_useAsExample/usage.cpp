// демонстрация использования объекта класса STRING

#include <iostream.h>
#include "string.cpp"

int main()
{

char ch[]="char array";

STRING a;
STRING b(10,'z');
STRING c(ch);

a="a string";

cout<<"a: "<<a<<"  length: "<<a.Len()<<endl;
cout<<"b: "<<b<<"  length: "<<b.Len()<<endl;
cout<<"c: "<<c<<"  length: "<<c.Len()<<endl;

cout<<"enter a string(a): ";
cin>>a;
cout<<"a+b: "<<a+b<<endl;




return 0;
}

