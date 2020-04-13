#ifndef TABBIT_HPP
#define TABBIT_HPP

#include <iostream>
#include <fstream>
#include <cstdint>

class tab_bit
{
	typedef uint64_t slowo; // komorka w tablicy
	static const int rozmiarSlowa = 64; // rozmiar slowa w bitach
	class ref {
	public:
        ref (const tab_bit &tb, int i);
        ref (tab_bit &tb, int i, bool b);
        operator bool ();
        ref & operator= (bool b) noexcept;
        ref & operator= (ref &reference);
    private:
        slowo *komorka;
        int indeks_bitu;
    }; // klasa pomocnicza do adresowania bitów
protected:
	int dl; // liczba bitów
	slowo *tab; // tablica bitów
public:
	explicit tab_bit (int rozm); // wyzerowana tablica bitow [0...rozm]
	explicit tab_bit (uint64_t tb); // tablica bitów [0...rozmiarSlowa]
	                             // zainicjalizowana wzorcem
	tab_bit (const tab_bit &tb); // konstruktor kopiujący
	tab_bit (tab_bit &&tb); // konstruktor przenoszący
	tab_bit & operator = (const tab_bit &tb); // przypisanie kopiujące
	tab_bit & operator = (tab_bit &&tb); // przypisanie przenoszące
	~tab_bit (); // destruktor
private:
	bool czytaj (int i) const; // metoda pomocnicza do odczytu bitu
	bool pisz (int i, bool b); // metoda pomocnicza do zapisu bitu
public:
	bool operator[] (int i) const; // indeksowanie dla stałych tablic bitowych
	ref operator[] (int i); // indeksowanie dla zwykłych tablic bitowych
	inline int rozmiar () const {
		return dl;
	} // rozmiar tablicy w bitach
public:
	tab_bit operator | (tab_bit& tb1);
    tab_bit& operator |= (tab_bit& tb);
    tab_bit operator & (tab_bit& tb);
    tab_bit& operator &= (tab_bit& tb);
    tab_bit operator ^ (tab_bit& tb);
    tab_bit& operator ^= (tab_bit& tb);
    tab_bit operator !();
	// operatory bitowe: | i |=, & i &=, ^ i ^= oraz !
public:
	friend std::istream & operator >> (std::istream &we, tab_bit &tb);
	friend std::ostream & operator << (std::ostream &wy, const tab_bit &tb);
	// zaprzyjaźnione operatory strumieniowe: << i >>
};

#endif