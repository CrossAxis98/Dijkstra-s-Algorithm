#include <iostream>
#include "ReprezentacjaGrafu.h"
#include "ListaSasiedztwa.h"
#include "MacierzSasiedztwa.h"
#define iloscWierzcholkow 10

using namespace std;

void wylosujIZapiszDoPliku(int,int,int);

int main()
{

int krawedzie((iloscWierzcholkow*(iloscWierzcholkow-1))), wierzcholki(iloscWierzcholkow), startowy(0);

wylosujIZapiszDoPliku(krawedzie, wierzcholki, startowy);

 MacierzSasiedztwa ms(wierzcholki);
 ListaSasiedztwa ls(wierzcholki);

ReprezentacjaGrafu *tab[]={&ls, &ms};

for(auto &i: tab)
{

    i->inicjuj();
    i->odczytZPliku();
    i->wyznaczNajlepszeDojscia();
    i->wyswietl();
 }


  return 0;
}



void wylosujIZapiszDoPliku(int liczbaKrawedzi, int liczbaWierzcholkow, int startowyWierzholek)
{
    fstream plik;
    plik.open("dane.txt", ios::out);
    int waga(0), a(0), b(0);
    bool **flagi;
    flagi=new bool* [liczbaWierzcholkow];
    int ileBrakujeKrawedzi(liczbaKrawedzi);
    for(int i=0; i<liczbaWierzcholkow; i++)
        flagi[i]=new bool[liczbaWierzcholkow];
    for(int i=0; i<liczbaWierzcholkow; i++)
        for(int j=0; j<liczbaWierzcholkow; j++)
            {
            flagi[i][j]=false;
            }
    if(plik.good()==true)
    {plik<<liczbaKrawedzi<<" "<<liczbaWierzcholkow<<" "<<startowyWierzholek<<endl;
    for(int i=0; i<liczbaWierzcholkow-1; i++)
    {
    waga=rand()%9+1;
    plik<<i<<" "<<i+1<<" "<<waga<<endl;
    flagi[i][i+1]=true;
    ileBrakujeKrawedzi--;
    }
    waga=rand()%9+1;
    plik<<liczbaWierzcholkow-1<<" "<<0<<" "<<waga<<endl;
    flagi[liczbaWierzcholkow-1][0]=true;
    ileBrakujeKrawedzi--;
    int liczba(0);
    while(ileBrakujeKrawedzi)
    {

    a=rand()%liczbaWierzcholkow;
    b=rand()%liczbaWierzcholkow;
    waga=rand()%9+1;
    if((a!=b)&&(flagi[a][b]==false))
    {
    ileBrakujeKrawedzi--;
    plik<<a<<" "<<b<<" "<<waga<<endl;
    flagi[a][b]=true;
    }
    liczba++;

    }
    plik.close();
    }
    else
    cout<<"nie mozna otworzyc pliku!!";

for(int i=0; i<liczbaWierzcholkow; i++) delete [] flagi[i];

delete [] flagi;
}
