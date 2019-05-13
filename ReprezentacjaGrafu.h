#pragma once
#include <iostream>
#include <fstream>
#define MAXWARTOSC 2147483647
using namespace std;

class ReprezentacjaGrafu
{
    public:
    virtual void wczytajParametry()=0;
    virtual void inicjuj()=0;
    virtual void pobierzDane()=0;
    virtual void wyznaczNajlepszeDojscia()=0;
    virtual void wyswietl()=0;
    virtual void odczytZPliku()=0;
    virtual void zapiszWynikdoPliku()=0;
    virtual ~ReprezentacjaGrafu() {}


};


