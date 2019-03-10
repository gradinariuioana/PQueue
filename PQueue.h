#ifndef PQUEUE_H
#define PQUEUE_H
#include <iostream>
using namespace std;

template <class Ctype> struct priority
{
    Ctype val;
    int prioritate;
};


template <class PQtype> class PQueue
{
public:
    PQueue();
    PQueue(const PQueue <PQtype> &p);
    template <class T> friend istream & operator>>(istream &c, PQueue <T> &p);
    template <class T> friend ostream & operator<<(ostream &c, PQueue <T> &p);
    void Adaugare(PQtype valoare, int prioritate);
    void Eliminare();
    void heapify(priority <PQtype> x);
    PQtype getpmax();
    priority <PQtype> getvalmax();
    int numar_elemente();
    PQueue <PQtype> & operator+ (const PQueue <PQtype> &p1);
    PQueue <PQtype> & operator= (const PQueue <PQtype> &p);
    PQueue <PQtype> operator++ ();
    PQueue <PQtype> operator-- ();
    ~PQueue();

protected:

private:
    priority <PQtype> *coada;
    int nrelem;
    int dimensiune_maxima;
};

//constructor
template <class PQtype>
PQueue <PQtype>::PQueue()
{
    nrelem=0;
    dimensiune_maxima=10;
    coada=new priority <PQtype> [10];
}

//constructor de copiere (cu parametru)
template <class PQtype>
PQueue <PQtype>::PQueue(const PQueue &p)
{
    this->nrelem=p.nrelem;  //modific numarul de elemente
    this->dimensiune_maxima=p.dimensiune_maxima;  //si dimensiunea maxima
    priority <PQtype> *aux=new priority <PQtype> [nrelem];  //creez o noua coada
    delete[] coada;  //sterg veche coada
    coada=aux;  //apoi mut coada la adresa celei noi (aux)
    for (int i=0; i<nrelem; i++)
    {
        coada[i].prioritate=p.coada[i].prioritate;  //copiez informatiile din PQueue-ul parametru
        coada[i].val=p.coada[i].val;
    }
}

//supraincarcarea operatorului de citire
template <class PQtype>
istream& operator>>(istream &c, PQueue <PQtype> &p)
{
    int prio;
    PQtype value;
    while(c>>value>>prio)  //cat timp se citesc valori cu prioritati,
        p.Adaugare(value, prio);  //acestea sunt adaugate in PQueue
    return c;
}

//supraincarcarea operatorului de afisare
template <class PQtype>
ostream & operator<<(ostream &c, PQueue <PQtype> &p)
{
    for (int i=0; i<p.nrelem; i++)
        cout<<p.coada[i].val<<" "<<p.coada[i].prioritate<<"     ";
    return c;
}

//functie de adaugare a unui element (valoare cu prioritate) in PQueue
template <class PQtype>
void PQueue <PQtype>::Adaugare(PQtype valoare, int prior)
{
    nrelem++;
    if (nrelem>=dimensiune_maxima)  //daca am depasit dimensiunea maxima a cozii,
    {
        priority <PQtype> *aux=new priority <PQtype> [dimensiune_maxima+3];  //aceasta va creste cu 3
        dimensiune_maxima+=3;
        for (int i=0; i<dimensiune_maxima; i++)
        {
            aux[i]=coada[i];
        }
        delete[] coada;
        coada=aux;
    }
    coada[nrelem-1].val=valoare;  //noul element este adaugat pe ultima pozitie,
    coada[nrelem-1].prioritate=prior;
    int i=nrelem-1;
    while (i>0 && prior>coada[(i-1)/2].prioritate)  //apoi va fi adus pe locul cel bun prin compararea recursiva a prioritatilor fiilor cu cele ale tatilor
    {
        swap(coada[i], coada[(i-1)/2]);
        i=(i-1)/2;
    }
}

//Functie de heapify
template <class PQtype>
void PQueue <PQtype> ::heapify(priority <PQtype> x)
{
    int i;
    for (int j=0; j<nrelem; j++)
        if (coada[j].prioritate==x.prioritate && coada[j].val==x.val)  //caut elementul x in coada
            i=j;
    int mx=i;
    int s=2*i+1;  //retin indicele fiului stang
    int d=2*i+2;  //si cel al fiului drept ai lui x
    if(s<nrelem && coada[s].prioritate>coada[mx].prioritate )  //retin daca unul dintre fii are prioritate mai mare
        mx=s;
    if(d<nrelem && coada[d].prioritate>coada[mx].prioritate)
        mx=d;
    if(mx!=i)  //daca unul dintre fii are prioritate mai mare, atunci interschimb x cu fiul maxim si apoi reapelez recursiv functia cu fiul
    {
        swap(coada[i], coada[mx]);
        heapify(coada [mx]);
    }
    else
    {
        if(s<nrelem)  //altfel, reapelez functia cu fiul cel mai mare
            heapify(coada [s]);
        if (d<nrelem)
            heapify(coada [d]);
    }
}

//Eliminarea prioritatii maxime din coada
template <class PQtype>
void PQueue <PQtype>::Eliminare()
{
    swap(coada[0], coada[nrelem-1]);  //elementul de prioritate maxima este dus pe ultima pozitie,
    nrelem--;  //eliminat,
    heapify(coada[0]);  //apoi se reface structura de heap cu functia de heapify
}

//Functie de determinare a valorii elementului cu prioritate maxima
template <class PQtype>
PQtype PQueue <PQtype>::getpmax ()
{
    return coada[0].val;  //elementul de prioritate maxima se afla pe pozitia 0
}

//Functie de determinare a elementului de valoare maxima din coada
template <class PQtype>
priority <PQtype> PQueue <PQtype>::getvalmax()
{
    PQtype mx=coada[0].val;
    int elmx=0;
    for (int i=1; i<nrelem; i++)
        if (coada[i].val>mx)
        {
            mx=coada[i].val;
            elmx=i;
        }
    return coada[elmx];
}

//Functie de returnare a numarului de elemente
template <class PQtype>
int PQueue <PQtype> ::numar_elemente ()
{
    return nrelem;
}
//Supraincarcarea operatorului +
template <class PQtype>
PQueue <PQtype> & PQueue <PQtype> ::operator+ (const PQueue <PQtype> &p1)
{
    PQueue <PQtype> *r=new PQueue <PQtype>;  //este creata o noua PQueue
    for (int i=0; i<this->nrelem; i++)
    {
        r->Adaugare(this->coada[i].val, this->coada[i].prioritate);  //Sunt pe rand adaugate toate elementele primei PQueue
    }
    for (int i=0; i<p1.nrelem; i++)
    {
        r->Adaugare(p1.coada[i].val, p1.coada[i].prioritate);  //Apoi cele din cea de-a doua PQueue
    }
    return *r;
}


//Supraincarcarea operatorului ++
template <class PQtype>
PQueue <PQtype> PQueue <PQtype>::operator++ ()
{
    for (int i=0; i<nrelem; i++)  //prioritatea fiecarui element creste cu 1
        coada[i].prioritate++;
    PQueue <PQtype> r(*this);
    return r;
}


//Supraincarcarea operatorului --
template <class PQtype>
PQueue <PQtype> PQueue <PQtype>::operator-- ()
{
    for (int i=0; i<nrelem; i++)
        coada[i].prioritate--;  //prioritatea fiecarui element scade cu 1
    int k=0, i=0;
    while (i<nrelem)
    {
        while (coada[i].prioritate<=0)  //trec peste elementele de prioritate mai mica sau egala cu 0
            i++;
        if (i<nrelem)
        {
            coada[k]=coada[i];  //elementele cu prioritate pozitiva se copiaza prin suprascriere la stanga
            k++;
        }
        i++;
    }
    nrelem=k;  //actualizez numarul de elemente cu prioritate pozitiva
    heapify(coada[0]);  //apelez functia de heapify pentru a reface structura de heap
    PQueue <PQtype> r(*this);
    return r;
}

//supraincarcarea operatorului de copiere
template <class PQtype>
PQueue <PQtype>& PQueue <PQtype>::operator=(const PQueue <PQtype> &p)
{
    nrelem=p.nrelem;  //this preia numarul de elemente si dimensiunea maxima a PQueue-ului parametru
    dimensiune_maxima=p.dimensiune_maxima;
    priority <PQtype>*aux=new priority <PQtype> [nrelem];  //este creata o noua coada, apoi copiate toate elem. cozii parametru
    delete[] coada;
    coada=aux;  //coada lui this se va afla la aceeasi adresa cu noua coada
    for (int i=0; i<nrelem; i++)
    {
        coada[i].prioritate=p.coada[i].prioritate;
        coada[i].val=p.coada[i].val;
    }
    return *this;
}

//Destructor
template <class PQtype>
PQueue <PQtype>::~PQueue()
{
    delete[] coada;
}

#endif // PQUEUE_H
