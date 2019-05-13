#pragma once
#include "ReprezentacjaGrafu.h"


class MacierzSasiedztwa: public ReprezentacjaGrafu
{
 int iloscKrawedzi, iloscWierzcholkow, startWierzcholek;
 int *tablicaKosztowDojscia, *tablicaPoprzednikow, *kopiec, *pozycjawKopcu;
    bool *czyPozaChmura;
    int **macierz;
    int dlugoscKopca, wierzcholekPoczatkowy, wierzcholekDocelowy, wagaKrawedziLaczacej;
    int najmniejszy, rodzic, lewy, prawy, mniejszyPotomek, mniejszyKoszt, dziecko;
    int *stos;




 public:
    MacierzSasiedztwa(int);
    void inicjuj();
    void wczytajParametry();
    void pobierzDane();
    void wyznaczNajlepszeDojscia();
    void wyswietl();
    void odczytZPliku();
    void zapiszWynikdoPliku();
    ~MacierzSasiedztwa();



};
