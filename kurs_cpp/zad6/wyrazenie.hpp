#ifndef WYRAZENIE_HPP
#define WYRAZENIE_HPP

#include <iostream>
#include <utility>
#include <vector>
/* Wyrażenie */
class wyrazenie {
public:
	virtual double oblicz () = 0;
	virtual std::string opis () = 0;
};
/* Liczba */
class liczba : public wyrazenie {
public:
	liczba (double wartosc_);
	
	double oblicz () override;
	std::string opis () override;
private:
	const double wartosc;
};
/* Zmienna */
class zmienna : public wyrazenie {
public:
	zmienna (std::string nazwa_);

	double oblicz () override;
	std::string opis () override;
	
	static void dodaj_wartosc (std::string nazwa, double wartosc);
	static void usun_wartosc (std::string nazwa);
	static double sprawdz_wartosc (std::string nazwa);
private:
	static std::vector<std::pair<std::string, double>> wartosci_zmiennych;
	const std::string nazwa;
};
/* Stała */
class stala : public wyrazenie {
public:
	stala (std::string nazwa_, double wartosc_);
	double oblicz () override;
	std::string opis () override;
protected:
	const std::string nazwa;
	const double wartosc;
};
class pi : public stala {
public:
	pi ();
};
class e : public stala {
public:
	e ();
};
class fi : public stala {
public:
	fi ();
};
/* Operator 1-argumentowy */
class operator1arg : public wyrazenie {
public:
	operator1arg (std::string nazwa_, wyrazenie *argument_);
	~operator1arg ();

	std::string opis () override;
protected:
	const std::string nazwa;
	wyrazenie *argument;
};
class sin : public operator1arg {
public:
	sin (wyrazenie *argument_);
	double oblicz () override;
};
class cos : public operator1arg {
public:
	cos (wyrazenie *argument_);
	double oblicz () override;
};
class bezwzgl : public operator1arg {
public:
	bezwzgl (wyrazenie *argument_);
	double oblicz () override;
};
class przeciw : public operator1arg {
public:
	przeciw (wyrazenie *argument_);
	double oblicz () override;
};
class exp : public operator1arg {
public:
	exp (wyrazenie *argument_);
	double oblicz () override;
};
class odwrot : public operator1arg {
public:
	odwrot (wyrazenie *argument_);
	double oblicz () override;
};
class ln : public operator1arg {
public:
	ln (wyrazenie *argument_);
	double oblicz () override;
};
/* Operator 2-argumentowy */
class operator2arg : public wyrazenie {
public:
	operator2arg (std::string nazwa_, wyrazenie *argument_l, wyrazenie *argument_p);
	~operator2arg ();

	std::string opis () override;
protected:
	const std::string nazwa;
	wyrazenie *argument_lewy;
	wyrazenie *argument_prawy;
};
class dodaj : public operator2arg {
public:
	dodaj (wyrazenie *argument_l, wyrazenie *argument_p);
	double oblicz () override;
};
class odejmij : public operator2arg {
public:
	odejmij (wyrazenie *argument_l, wyrazenie *argument_p);
	double oblicz () override;
};
class mnoz : public operator2arg {
public:
	mnoz (wyrazenie *argument_l, wyrazenie *argument_p);
	double oblicz () override;
};
class dziel : public operator2arg {
public:
	dziel (wyrazenie *argument_l, wyrazenie *argument_p);
	double oblicz () override;
};
class logarytm : public operator2arg {
public:
	logarytm (wyrazenie *argument_l, wyrazenie *argument_p);
	double oblicz () override;
	std::string opis () override;
};
class modulo : public operator2arg {
public:
	modulo (wyrazenie *argument_l, wyrazenie *argument_p);
	double oblicz () override;
};
class potega : public operator2arg {
public:
	potega (wyrazenie *argument_l, wyrazenie *argument_p);
	double oblicz () override;
};
#endif