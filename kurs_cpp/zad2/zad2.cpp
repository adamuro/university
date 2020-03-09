#include "zad2.hpp"

/* ------------------ WEKTOR ------------------ */

wektor::wektor (double x, double y): dx(x), dy(y) {}
wektor::wektor (const wektor &w): dx(w.dx), dy(w.dy) {}

// Globalna do dodawania wektorów wedle wytycznych.
wektor suma_wektorow (const wektor &w1, const wektor &w2) {
	return wektor(w1.dx + w2.dx, w1.dy + w2.dy);
}

/* ------------------ PUNKT ------------------ */

punkt::punkt (double x_, double y_): x(x_), y(y_) {}
punkt::punkt (const punkt &p, const wektor &w): x(p.x + w.dx), y(p.y + w.dy) {}
punkt::punkt (const punkt &p): x(p.x), y(p.y) {}

/* ------------------ PROSTA ------------------ */

prosta::prosta (const punkt &p1, const punkt &p2) {
	if(p1.x == p2.x && p1.y == p2.y) {
		std::invalid_argument exception("Podane punkty sa takie same.");
		throw exception;
	}
	a = p2.y - p1.y;
	b = p1.x - p2.x;
	c = p2.x * p1.y - p1.x * p2.y;

	double czynnik_norm = 1 / (sqrt(a * a + b * b));

	a *= czynnik_norm;
	b *= czynnik_norm;
	c *= czynnik_norm;
}
prosta::prosta (const wektor &w) {
	if(w.dx == 0 && w.dy == 0) {
		std::invalid_argument exception("Podano wektor zerowy.");
		throw exception;
	}
	a = w.dx;
	b = w.dy;
	c = -(a * a + b * b);

	double czynnik_norm = 1 / (sqrt(a * a + b * b));

	a *= czynnik_norm;
	b *= czynnik_norm;
	c *= czynnik_norm;

}
prosta::prosta (double a_, double b_, double c_) {
	if(a_ == 0 && b_ == 0) {
		std::invalid_argument exception("Wspolczynniki a i b sa rowne 0.");
		throw exception;
	}
	a = a_;
	b = b_;
	c = c_;

	double czynnik_norm = 1 / (sqrt(a * a + b * b));
	
	a *= czynnik_norm;
	b *= czynnik_norm;
	c *= czynnik_norm;
}
prosta::prosta (const prosta &p, const wektor &w) {
	double wektor_norm = 1 / sqrt(w.dx * w.dx + w.dy * w.dy);

	a = p.a;
	b = p.b;
	c = p.c - w.dx * p.a * wektor_norm + w.dy * wektor_norm;

	double czynnik_norm = 1 / (sqrt(a * a + b * b));

	a *= czynnik_norm;
	b *= czynnik_norm;
	c *= czynnik_norm;
}
double prosta::get_a () {
	return a;
}
double prosta::get_b () {
	return b;
}
double prosta::get_c () {
	return c;
}
bool prosta::czy_wektor_prostopadly (const wektor &w) {
	return (w.dx == a && w.dy == b);
}
bool prosta::czy_wektor_rownolegly (const wektor &w) {
	return (w.dx == -b && w.dy == a);
}
bool prosta::czy_punkt_na_prostej (const punkt &p) {
	return (a * p.x + b * p.y + c == 0);
}

/* ------------------ GLOBALNE ------------------ */

bool czy_proste_rownolegle (prosta &p1, prosta &p2) {
	return (p1.get_a() * p2.get_b() - p2.get_a() * p1.get_b() == 0);
}
bool czy_proste_prostopadle (prosta &p1, prosta &p2) {
	return (p1.get_a() * p2.get_a() + p1.get_b() * p2.get_b() == 0);
}
punkt przeciecie_prostych (prosta &p1, prosta &p2) {
	double d = p1.get_a() * p2.get_b() - p2.get_a() * p1.get_b();
	double x = (p1.get_b() * p2.get_c() - p2.get_b() * p1.get_c()) / d;
	double y = -1 * (p1.get_a() * p2.get_c() - p2.get_a() * p1.get_c()) / d;
	return punkt(x, y);
}