#include <iostream>
#include "zad2.hpp"

int main () {
	// Konstruktory
	wektor w1 = wektor(1, 3);
	wektor w2 = wektor(-2, 2);
	punkt p1 = punkt(0, 1);
	punkt p2 = punkt(p1, w1);
	prosta *pr1 = new prosta(p1, p2);
	prosta *pr2 = new prosta (2, 2, 1);
	prosta *pr3 = new prosta (*pr1, w1);
	// Suma wektorow
	wektor suma_w = suma_wektorow(w1, w2);
	std::cout << "suma wektorow [1, 3] + [-2, 2]: [" << suma_w.dx << ", " << suma_w.dy << "]" << std::endl;
	// Gettery
	std::cout << "pr1: a: "<< pr1->get_a() << " b: " << pr1->get_b() << " c: " << pr1->get_c() << std::endl;
	// Funkcje globalne: prosta prostopadla do wektora, przechodzaca przez punkt
	std::cout << "czy porstopadla do wektora: " << pr1->czy_wektor_prostopadly(w1) << std::endl;
	std::cout << "czy punkt na prostej: " << pr1->czy_punkt_na_prostej(p1) << std::endl;
	// Punkt przeciecia prostych
	punkt pkt_przeciecia = przeciecie_prostych(*pr1, *pr2);
	std::cout << "punkt przeciecia: (" << pkt_przeciecia.x << ", " << pkt_przeciecia.y << ")" << std::endl;
	// Przesuniecie prostej o wektor i sprawdzenie rownoleglosci
	std::cout << "przesuniecie pr1 o wektor [1, 3]: a:" << pr3->get_a() << " b: " << pr3->get_b() << " c: " << pr3->get_c() << std::endl;
	std::cout << "czy_proste_rownolegle: " << czy_proste_rownolegle(*pr1, *pr3) << std::endl;

	delete pr1;
	delete pr2;
	delete pr3;

	return 0;
}