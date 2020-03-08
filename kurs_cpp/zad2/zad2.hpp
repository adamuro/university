#include <iostream>

#ifndef zad2_hpp
#define zad2_hpp

class wektor {
public:
	wektor () = default;
	wektor (double x, double y);
	wektor (const wektor &w);
	~wektor ();

	const double dx;
	const double dy;
};

wektor suma_wektorow (const wektor &w1, const wektor &w2);

class punkt {
public:
	punkt () = default;
	punkt (double x_, double y_);
	punkt (const punkt &p, const wektor &w);
	punkt (const punkt &p);
	~punkt ();

	const double x;
	const double y;
};

class prosta {
public:
	prosta (const punkt &p1, const punkt &p2);
	prosta (const wektor &w);
	prosta (double a_, double b_, double c_); // a i b nie moga byc 0 jednoczesnie
	prosta (const prosta &p, const wektor &w);
	prosta () = default;
	~prosta ();

	bool czy_wektor_prostopadly (const wektor &w);
	bool czy_wektor_rownolegly (const wektor &w);
	bool czy_punkt_na_prostej (const punkt &p);

	double get_a ();
	double get_b ();
	double get_c ();
private:
	double a;
	double b;
	double c;
};

bool czy_proste_rownolegle (const prosta &p1, const prosta &p2);
punkt przeciecie_prostych (const prosta &p1, const prosta &p2);

#endif