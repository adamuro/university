#include "wyrazenie.hpp"
#include <cmath>

/* Liczba */
liczba::liczba (double wartosc_): wartosc(wartosc_) {}
double liczba::oblicz () {
	return wartosc;
}
std::string liczba::opis () {
	return std::to_string(wartosc);
}
/* Zmienna */
zmienna::zmienna (std::string nazwa_): nazwa(nazwa_) {}
std::vector<std::pair<std::string, double>> zmienna::wartosci_zmiennych;
double zmienna::oblicz () {
	for(std::pair<std::string, double> &wartosc_zm: zmienna::wartosci_zmiennych) {
		if(std::get<std::string>(wartosc_zm) == nazwa) {
			return std::get<double>(wartosc_zm);
		}
	}
	throw std::invalid_argument("Zmienna " + nazwa + " nie ma przypisanej wartosci");
}
std::string zmienna::opis () {
	return nazwa;
}
void zmienna::dodaj_wartosc (std::string nazwa, double wartosc) {
	for(std::pair<std::string, double> &wartosc_zm: wartosci_zmiennych) {
		if(std::get<std::string>(wartosc_zm) == nazwa) {
			std::get<double>(wartosc_zm) = wartosc;
			return;
		}
	}
	wartosci_zmiennych.push_back(std::pair<std::string, double> (nazwa, wartosc));
}
void zmienna::usun_wartosc (std::string nazwa) {
	for(int i = 0; i < wartosci_zmiennych.size(); i++) {
		if(std::get<std::string>(wartosci_zmiennych[i]) == nazwa) {
			wartosci_zmiennych.erase(wartosci_zmiennych.begin() + i);
			return;
		}
	}
}
double zmienna::sprawdz_wartosc (std::string nazwa_) {
	for(std::pair<std::string, double> &wartosc_zm: wartosci_zmiennych) {
		if(std::get<std::string>(wartosc_zm) == nazwa_) {
			return std::get<double>(wartosc_zm);
		}
	}
	throw std::invalid_argument("Zmienna " + nazwa_ + " nie ma przypisanej wartosci");
}
/* Stała */
stala::stala (std::string nazwa_, double wartosc_): 
	nazwa(nazwa_), wartosc(wartosc_) {}

double stala::oblicz () {
	return wartosc;
}
std::string stala::opis () {
	return nazwa;
}
pi::pi (): stala("pi", 3.14159) {}
e::e (): stala("e", 2.71828) {}
fi::fi (): stala("fi", 1.61803) {}
/* Operator 1-argumentowy */
operator1arg::operator1arg (std::string nazwa_, wyrazenie *argument_): 
	nazwa(nazwa_), argument(argument_) {}

operator1arg::~operator1arg () {
	delete argument;
}
std::string operator1arg::opis () {
	return nazwa + "(" + argument->opis() + ")";
}
sin::sin (wyrazenie *argument_): 
	operator1arg("sin", argument_)  {}
double sin::oblicz () {
	return std::sin(argument->oblicz());
}

cos::cos (wyrazenie *argument_): 
	operator1arg("cos", argument_)  {}
double cos::oblicz () {
	return std::cos(argument->oblicz());
}

bezwzgl::bezwzgl (wyrazenie *argument_): 
	operator1arg("abs", argument_)  {}
double bezwzgl::oblicz () {
	return std::abs(argument->oblicz());
}

przeciw::przeciw (wyrazenie *argument_): 
	operator1arg("-", argument_)  {}
double przeciw::oblicz () {
	return -1 * argument->oblicz();
}

exp::exp (wyrazenie *argument_): 
	operator1arg("exp", argument_)  {}
double exp::oblicz () {
	return std::exp(argument->oblicz());
}

odwrot::odwrot (wyrazenie *argument_): 
	operator1arg("1/", argument_)  {}
double odwrot::oblicz () {
	return 1 / argument->oblicz();
}

ln::ln (wyrazenie *argument_): 
	operator1arg("ln", argument_)  {}
double ln::oblicz () {
	return std::log(argument->oblicz());
}
/* Operator 2-argumentowy */
operator2arg::operator2arg (std::string nazwa_, wyrazenie *argument_l, wyrazenie *argument_p):
	nazwa(nazwa_), argument_lewy(argument_l), argument_prawy(argument_p) {}
operator2arg::~operator2arg () {
	delete argument_lewy;
	delete argument_prawy;
}
std::string operator2arg::opis () {
	return "(" + argument_lewy->opis() + nazwa + argument_prawy->opis() + ")";
}

dodaj::dodaj (wyrazenie *argument_l, wyrazenie *argument_p):
	operator2arg("+", argument_l, argument_p) {}
double dodaj::oblicz () {
	return argument_lewy->oblicz() + argument_prawy->oblicz();
}

odejmij::odejmij (wyrazenie *argument_l, wyrazenie *argument_p):
	operator2arg("-", argument_l, argument_p) {}
double odejmij::oblicz () {
	return argument_lewy->oblicz() - argument_prawy->oblicz();
}

mnoz::mnoz (wyrazenie *argument_l, wyrazenie *argument_p):
	operator2arg("*", argument_l, argument_p) {}
double mnoz::oblicz () {
	return argument_lewy->oblicz() * argument_prawy->oblicz();
}

dziel::dziel (wyrazenie *argument_l, wyrazenie *argument_p):
	operator2arg("/", argument_l, argument_p) {}
double dziel::oblicz () {
	if(argument_prawy->oblicz() == 0) {
		throw std::domain_error("Proba dzielenia przez zero.");
	}
	return argument_lewy->oblicz() / argument_prawy->oblicz();
}

logarytm::logarytm (wyrazenie *argument_l, wyrazenie *argument_p):
	operator2arg("log", argument_l, argument_p) {}
double logarytm::oblicz () {
	return std::log(argument_prawy->oblicz()) / std::log(argument_lewy->oblicz());
}
std::string logarytm::opis () {
	return nazwa + "(" + argument_lewy->opis() + ")" "(" + argument_prawy->opis() + ")";
}

modulo::modulo (wyrazenie *argument_l, wyrazenie *argument_p):
	operator2arg("%", argument_l, argument_p) {}
double modulo::oblicz () {
	return (int)argument_lewy->oblicz() % (int)argument_prawy->oblicz();
}

potega::potega (wyrazenie *argument_l, wyrazenie *argument_p):
	operator2arg("^", argument_l, argument_p) {}
double potega::oblicz () {
	return std::pow(argument_lewy->oblicz(), argument_prawy->oblicz());
}
