#include <iostream>
#include "wyrazenie.hpp"

int main () {
	wyrazenie *w1 =
	new dziel(
		new mnoz(
			new odejmij(
				new zmienna("x"),
				new liczba(1)),
			new zmienna("x")),
		new liczba(2));

	wyrazenie *w2 =
	new dziel(
		new dodaj(
			new liczba(3),
			new liczba(5)),
		new dodaj(
			new liczba(2),
			new mnoz(
				new zmienna("x"),
				new liczba(7))));

	wyrazenie *w3 = 
	new odejmij(
		new dodaj(
			new liczba(2),
			new mnoz(
				new zmienna("x"),
				new liczba(7))),
		new dodaj(
			new mnoz(
				new zmienna("y"),
				new liczba(3)),
			new liczba(5)));

	wyrazenie *w4 = 
	new dziel(
		new cos(
			new mnoz(
				new dodaj(
					new zmienna("x"),
					new liczba(1)),
				new zmienna("x"))),
		new potega(
			new e(),
			new potega(
				new zmienna("x"),
				new liczba(2))));

	std::cout << "w1: " << w1->opis() << std::endl;
	std::cout << "w2: " << w2->opis() << std::endl;
	std::cout << "w3: " << w3->opis() << std::endl;
	std::cout << "w4: " << w4->opis() << std::endl;
	std::cout << std::endl <<
	"    x    |" << 
	"    w1    |" << 
	"     w2    |" << 
	"    w4    " << std::endl;
	for(double i = 0; i <= 1; i += 0.01) {
		zmienna::dodaj_wartosc("x", i);
		printf("%4lf | %4lf | %5lf | %7lf\n", 
			zmienna::sprawdz_wartosc("x"), w1->oblicz(), w2->oblicz(), w4->oblicz());
	}
}