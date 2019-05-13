#pragma once
#include "ReprezentacjaGrafu.h"




struct lista
{
    lista *nastepny;
    int wagaKrawedzi, numerWezla;
};

class ListaSasiedztwa: public ReprezentacjaGrafu
{
    int iloscKrawedzi, iloscWierzcholkow, startWierzcholek;
    lista **graf;
    int *tablicaKosztowDojscia, *tablicaPoprzednikow, *kopiec, *pozycjawKopcu;
    bool *czyPozaChmura;
    int dlugoscKopca, wierzcholekStartowy, wierzcholekDocelowy, wagaKrawedziLaczacej;
    lista *element;
    int *stos;

    public:
    ListaSasiedztwa(int);
    void inicjuj();
    void wczytajParametry();
    void pobierzDane();
    void wyznaczNajlepszeDojscia();
    void wyswietl();
    void odczytZPliku();
    void zapiszWynikdoPliku();
    ~ListaSasiedztwa();

};



