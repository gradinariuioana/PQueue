#include <iostream>
#include "PQueue.h"
#include <string>
using namespace std;

int main()
{
    //exemplu pe double:
    int i;
    PQueue <double> c, d;
    for (i=0; i<10; i++)
        c.Adaugare(i/2.0, i), d.Adaugare(i+i/5.0, i+20);
    cout<<"Valoare element de prioritate maxima "<<c.getpmax()<<endl;
    c.Eliminare();
    cout<<"\nValoare element de prioritate maxima dupa eliminare \n"<<c.getpmax();
    priority <double> y;
    y=c.getvalmax();
    cout<<"\nValoare maxima \n"<<y.val;
    int z=c.numar_elemente();
    cout<<"\nNumar elemente: \n "<<z;
    PQueue <double> e(c);
    cout<<"\ne(c) \n "<<e;
    c=c+d;
    cout<<"\nSuma: c+d \n "<<c;
    PQueue <double> t;
    t=++(c);
    cout<<"\nt=++c \n "<<t;
    PQueue <double> f;
    f=--(c);
    cout<<"\nf=--c \n c:"<<c<<"\n f:"<<f;
    f.Eliminare();
    f.Eliminare();
    f.Eliminare();
    f.Eliminare();
    cout<<"\nf dupa 4 eliminari: \n"<<f;
    PQueue <double>g;
    g=e=f;
    cout<<"\ng=e=f \n"<<g.numar_elemente()<<"\n"<<g;

    //exemplu pe char-uri
    /*
    PQueue <char> c, d;
    for (int i=0; i<10; i++)
        c.Adaugare('a'+i, i), d.Adaugare('z'-i, i+10);
    cout<<c<<endl<<d<<endl;
    c=c+d;
    cout<<c;
    PQueue<char>f;
    f=--(c);
    cout<<endl<<f<<endl;
    f.Eliminare();
    f.Eliminare();f.Eliminare();f.Eliminare();
    cout<<"\nf dupa 4 eliminari: \n"<<f<<endl;
    PQueue <char>g;
    g=f;
    cout<<"\ng=e=f \n"<<g.numar_elemente()<<"\n"<<g;
    */

    //exemplu pe string-uri
    /*
    PQueue <string> c;
    cin>>c;
    cout<<c;
    */

    return 0;
}
