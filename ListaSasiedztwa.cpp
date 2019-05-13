#include "ListaSasiedztwa.h"




ListaSasiedztwa::ListaSasiedztwa(int iloscWierzcholk)
{
    iloscWierzcholkow=iloscWierzcholk;
    tablicaKosztowDojscia= new int [iloscWierzcholkow];
    tablicaPoprzednikow= new int [iloscWierzcholkow];
    czyPozaChmura=new bool [iloscWierzcholkow];

    kopiec=new int[iloscWierzcholkow];
    pozycjawKopcu=new int [iloscWierzcholkow];

    graf=new lista *[iloscWierzcholkow];

}

void ListaSasiedztwa::inicjuj()
{
dlugoscKopca=iloscWierzcholkow;
for(int i=0; i<iloscWierzcholkow; i++)
    {
        tablicaKosztowDojscia[i]=MAXWARTOSC;
        tablicaPoprzednikow[i]=-1;
        czyPozaChmura[i]=false;
        graf[i]=NULL;
        kopiec[i]=pozycjawKopcu[i]=i;
    }

}

void ListaSasiedztwa::wczytajParametry()
{
    cin>>iloscKrawedzi>>iloscWierzcholkow>>startWierzcholek;
}

void ListaSasiedztwa::pobierzDane()
{
for(int i=0; i<iloscKrawedzi; i++)
    {
        cin>>wierzcholekStartowy>>wierzcholekDocelowy>>wagaKrawedziLaczacej;
        element=new lista;
        element->numerWezla=wierzcholekDocelowy;
        element->wagaKrawedzi=wagaKrawedziLaczacej;
        element->nastepny=graf[wierzcholekStartowy];
        graf[wierzcholekStartowy]=element;
    }
}

void ListaSasiedztwa::wyznaczNajlepszeDojscia()
{
tablicaKosztowDojscia[startWierzcholek]=0;
 int zmienna(0);
    zmienna=kopiec[0];
    kopiec[0]=kopiec[startWierzcholek];
    kopiec[startWierzcholek]=zmienna;

    pozycjawKopcu[startWierzcholek]=0;
    pozycjawKopcu[0]=startWierzcholek;

    int najmniejszy, rodzic, lewy, prawy, mniejszyPotomek, mniejszyKoszt, dziecko;

    for(int i=0; i<iloscWierzcholkow; i++)
    {
        najmniejszy=kopiec[0];

        kopiec[0]=kopiec[--dlugoscKopca];
        pozycjawKopcu[kopiec[0]]=rodzic=0;

        while(true)
        {
            lewy=2*rodzic+1;
            prawy=lewy+1;
            if(lewy>=dlugoscKopca) break;
            mniejszyKoszt=tablicaKosztowDojscia[kopiec[lewy]];
            mniejszyPotomek=lewy;
            if((prawy<dlugoscKopca)&&(mniejszyKoszt>tablicaKosztowDojscia[kopiec[prawy]]))
            {
                mniejszyKoszt=tablicaKosztowDojscia[kopiec[prawy]];
                mniejszyPotomek=prawy;
            }
            if(tablicaKosztowDojscia[kopiec[rodzic]]<=mniejszyKoszt) break;

            zmienna=kopiec[rodzic];
            kopiec[rodzic]=kopiec[mniejszyPotomek];
            kopiec[mniejszyPotomek]=zmienna;

            pozycjawKopcu[kopiec[rodzic]]=rodzic;
            pozycjawKopcu[kopiec[mniejszyPotomek]]=mniejszyPotomek;
            rodzic=mniejszyPotomek;
        }
        czyPozaChmura[najmniejszy]=true;

        for(element=graf[najmniejszy]; element; element=element->nastepny)
            if(!czyPozaChmura[element->numerWezla]&&(tablicaKosztowDojscia[element->numerWezla]>tablicaKosztowDojscia[najmniejszy]+element->wagaKrawedzi))
            {
                tablicaKosztowDojscia[element->numerWezla]=tablicaKosztowDojscia[najmniejszy]+element->wagaKrawedzi;
                tablicaPoprzednikow[element->numerWezla]=najmniejszy;

                for(dziecko=pozycjawKopcu[element->numerWezla]; dziecko; dziecko=rodzic)
                {
                    rodzic=dziecko/2;
                    if(tablicaKosztowDojscia[kopiec[rodzic]]<=tablicaKosztowDojscia[kopiec[dziecko]]) break;
                    zmienna=kopiec[rodzic];
                    kopiec[rodzic]=kopiec[dziecko];
                    kopiec[dziecko]=zmienna;

                    pozycjawKopcu[kopiec[rodzic]]=rodzic;
                    pozycjawKopcu[kopiec[dziecko]]=dziecko;
                }
            }
    }
}

void ListaSasiedztwa::wyswietl()
{
    stos=new int [iloscWierzcholkow];
    int wskaznikStosu(0), j;


    for(int i=0; i<iloscWierzcholkow; i++)
    {
        cout<<i<<" Poprzednicy: ";

        for(j=i; j>-1; j=tablicaPoprzednikow[j]) stos[wskaznikStosu++]=j;

    while(wskaznikStosu)
        cout<<stos[--wskaznikStosu]<<" ";

    cout<<"Koszt: "<<tablicaKosztowDojscia[i]<<endl;
    }
     delete [] stos;



}


void ListaSasiedztwa::odczytZPliku()
{
fstream plik;
plik.open("dane.txt", ios::in);
if(plik.good()==true)
{

    plik>>iloscKrawedzi>>iloscWierzcholkow>>startWierzcholek;
    for(int i=0; i<iloscKrawedzi; i++)
    {
        plik>>wierzcholekStartowy>>wierzcholekDocelowy>>wagaKrawedziLaczacej;

        element=new lista;
        element->numerWezla=wierzcholekDocelowy;
        element->wagaKrawedzi=wagaKrawedziLaczacej;
        element->nastepny=graf[wierzcholekStartowy];
        graf[wierzcholekStartowy]=element;
    }

 plik.close();
 }
 else
 cout<<"Brak dostepu do pliku!!!"<<endl;

}

void ListaSasiedztwa::zapiszWynikdoPliku()
{
fstream plik;
    plik.open("wynikiZListySasiedztwa.txt", ios::out);
    if(plik.good()==true)
    {
    stos=new int [iloscWierzcholkow];
    int wskaznikStosu(0), j;


    for(int i=0; i<iloscWierzcholkow; i++)
    {
        plik<<i<<" Poprzednicy: ";

        for(j=i; j>-1; j=tablicaPoprzednikow[j]) stos[wskaznikStosu++]=j;

    while(wskaznikStosu)
        plik<<stos[--wskaznikStosu]<<" ";

    plik<<"Koszt: "<<tablicaKosztowDojscia[i]<<endl;
    }
     delete [] stos;

    plik.close();
    }
    else
    cout<<"Blad zapisow wynikow do pliku!!!";



}


ListaSasiedztwa::~ListaSasiedztwa()
{
delete [] tablicaKosztowDojscia;
    delete [] tablicaPoprzednikow;
    delete [] czyPozaChmura;

    delete [] kopiec;
    delete [] pozycjawKopcu;
    lista *doUsuwania;

    for(int i=0; i<iloscWierzcholkow; i++)
    {
        element=graf[i];

        while(element)
        {
            doUsuwania=element;
            element=element->nastepny;
            delete doUsuwania;
        }
    }

    delete [] graf;



}


