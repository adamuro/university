#include <iostream>
#include <initializer_list>
#include <utility>

class stos {
public:
	stos ();
	stos (int poj);
	stos (std::initializer_list<std::string> init);
	stos (const stos &s);
	stos& operator= (stos &s);
	stos (stos &&s);
	stos& operator= (stos &&s);

	void wloz (std::string);
	std::string sciagnij ();
	std::string sprawdz ();
	int rozmiar ();
	stos odwroc ();
private:
	int pojemnosc;
	int ile;
	std::string *tablica;
};