#include <iostream>
#include "tabbit.hpp"

int main () {
	tab_bit a(10);
	a[1] = 1;
	a[5] = 1;
	tab_bit b(15);
	b[5] = 1;
	b[12] = 1;

	tab_bit lub = a | b;
	tab_bit i = a & b;
	tab_bit x_or = a ^ b;
	tab_bit zaprz = !a;

	std::cout << "a: " << a <<
	std::endl << "b: " << b <<
	std::endl << "a | b: " << lub <<
	std::endl << "a & b: " << i <<
	std::endl << "a ^ b: " << x_or <<
	std::endl << "!a: " << zaprz <<
	std::endl;

    return 0;
}