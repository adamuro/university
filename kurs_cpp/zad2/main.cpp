#include <iostream>
#include "zad2.hpp"

int main () {
	//punkt *p = new punkt(1,1);
	wektor *w = new wektor(1,2);
	//punkt *pp = new punkt(*p, *w);
	prosta *q = new prosta(*w);
	std::cout << q->czy_wektor_prostopadly(*w) << std::endl;
	return 0;
}