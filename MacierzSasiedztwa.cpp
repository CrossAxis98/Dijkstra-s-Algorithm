#include "MacierzSasiedztwa.h"


MacierzSasiedztwa::MacierzSasiedztwa(int iloscWierzcholk)
{
iloscWierzcholkow=iloscWierzcholk;
tablicaKosztowDojscia= new int [iloscWierzcholkow];
    tablicaPoprzednikow= new int [iloscWierzcholkow];
    czyPozaChmura=new bool [iloscWierzcholkow];

    kopiec=new int[iloscWierzcholkow];
    pozycjawKopcu=new int [iloscWierzcholkow];

    macierz=new int *[iloscWierzcholkow];
    for(int i=0; i<iloscWierzcholkow; i++)
    {
        macierz[i]=new int [iloscWierzcholkow];
    }


}

void MacierzSasiedztwa::inicjuj()
{
dlugoscKopca=iloscWierzcholkow;

for(int i=0; i<iloscWierzcholkow; i++)
    {
        tablicaKosztowDojscia[i]=MAXWARTOSC;
        tablicaPoprzednikow[i]=-1;
        czyPozaChmura[i]=false;
       kopiec[i]=pozycjawKopcu[i]=i;
       for(int j=0; j<iloscWierzcholkow; j++)
        macierz[i][j]=0;
    }
    }



void MacierzSasiedztwa::wczytajParametry()
{
    cin>>iloscKrawedzi>>iloscWierzcholkow>>startWierzcholek;
}

void MacierzSasiedztwa::pobierzDane()
{
for(int i=0; i<iloscKrawedzi; i++)
{
cin>>wierzcholekPoczatkowy>>wierzcholekDocelowy>>wagaKrawedziLaczacej;
macierz[wierzcholekPoczatkowy][wierzcholekDocelowy]=wagaKrawedziLaczacej;
}
}

void MacierzSasiedztwa::wyznaczNajlepszeDojscia()
{
tablicaKosztowDojscia[startWierzcholek]=0;
int zmienna(0);
    zmienna=kopiec[0];
    kopiec[0]=kopiec[startWierzcholek];
    kopiec[startWierzcholek]=zmienna;

    pozycjawKopcu[startWierzcholek]=0;
    pozycjawKopcu[0]=startWierzcholek;



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
for(int i=0; i<iloscWierzcholkow; i++)
{
if((macierz[najmniejszy][i]!=0)&&(!czyPozaChmura[i])&&(tablicaKosztowDojscia[i]>(tablicaKosztowDojscia[najmniejszy]+macierz[najmniejszy][i])))
{
tablicaKosztowDojscia[i]=tablicaKosztowDojscia[najmniejszy]+macierz[najmniejszy][i];
tablicaPoprzednikow[i]=najmniejszy;
}
  for(dziecko=pozycjawKopcu[i]; dziecko; dziecko=rodzic)
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

void MacierzSasiedztwa::wyswietl()
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


void MacierzSasiedztwa::odczytZPliku()
{
fstream plik;
plik.open("dane.txt", ios::in);
if(plik.good()==true)
{

    plik>>iloscKrawedzi>>iloscWierzcholkow>>startWierzcholek;


    for(int i=0; i<iloscKrawedzi; i++)
{
plik>>wierzcholekPoczatkowy>>wierzcholekDocelowy>>wagaKrawedziLaczacej;
macierz[wierzcholekPoczatkowy][wierzcholekDocelowy]=wagaKrawedziLaczacej;
}
 plik.close();
 }
 else
 cout<<"Brak dostepu do pliku!!!"<<endl;


}

void MacierzSasiedztwa::zapiszWynikdoPliku()
{
fstream plik;
    plik.open("wynikiZMacierzySasiedztwa.txt", ios::out);
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


MacierzSasiedztwa::~MacierzSasiedztwa()
{
delete [] tablicaKosztowDojscia;
    delete [] tablicaPoprzednikow;
    delete [] czyPozaChmura;

    delete [] kopiec;
    delete [] pozycjawKopcu;
for(int i = 0; i < iloscWierzcholkow; i++) delete [] macierz[i];
  delete [] macierz;



}
