#include "stos.hpp"

stos::stos () {
	pojemnosc = 1;
	ile = 0;
	tablica = new std::string[pojemnosc];
}

stos::stos (int poj) : stos () {
	if(poj <= 100) {
		pojemnosc = poj;
		tablica = new std::string[pojemnosc];
	}
	else {
		std::invalid_argument exception("Wybrana pojemnosc jest za duza.\nMaksymalna pojemnosc stosu: 100.");
		throw exception;
	}
}

stos::stos (std::initializer_list<std::string> init) : stos () {
	pojemnosc = init.size();
	tablica = new std::string[pojemnosc];

	for(std::string s: init) {
		tablica[ile++] = s;
	}
}

stos::stos (const stos &s) {
	std::cout << "Konstruktor kopiujacy." << std::endl;
	pojemnosc = s.pojemnosc;
	ile = s.ile;
	tablica = s.tablica;
}

stos& stos::operator= (stos &s) {
	std::cout << "Przypisanie kopiujace." << std::endl;
	pojemnosc = s.pojemnosc;
	ile = s.ile;
	tablica = s.tablica;
	return *this;
}

stos::stos (stos &&s) :
	pojemnosc(std::exchange(s.pojemnosc, 0)),
	ile(std::exchange(s.ile, 0)),
	tablica(std::move(s.tablica)) {
		std::cout << "Konstruktor przenoszący." << std::endl;
	}

stos& stos::operator= (stos &&s) {
	std::cout << "Przypisanie przenoszące." << std::endl;
	pojemnosc = std::exchange(s.pojemnosc, 0);
	ile = std::exchange(s.ile, 0);
	tablica = std::move(s.tablica);

	return *this;
}

void stos::wloz (std::string element) {
	if(ile < pojemnosc) {
		tablica[ile] = element;
		ile++;
	}
	else {
		std::length_error exception("Stos jest pelny.");
		throw exception;
	}
}
	
std::string stos::sciagnij () {
	if(ile > 0) {
		ile--;
		std::string out = tablica[ile];
		return out;
	}
	else {
		std::length_error exception("Stos jest pusty.");
		throw exception;
	}
}
	
std::string stos::sprawdz () {
	if(ile > 0) {
		return tablica[ile - 1];
	}
	else {
		std::length_error exception("Stos jest pusty.");
		throw exception;
	}
}

int stos::rozmiar () {
	return ile;
}

stos stos::odwroc () {
	stos out = stos(pojemnosc);
	for(int i = ile - 1; i >= 0; i--) {
		out.wloz(tablica[i]);
	}
	return out;
}