#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Ulamek {
	int licznik;
	int mianownik;
} Ulamek;

int NWW (int a, int b) {
	int n1 = a, n2 = b;
	while(n1 != n2) {
		if(n1 < n2)
			n1 += a;
		else
			n2 += b;
	}
	return n1;
}

int NWD(int a, int b) {
	return (a == 0) ? b : NWD(b % a, a);
}

Ulamek* nowy_ulamek (int licznik, int mianownik) {
	if(mianownik < 0) {
		licznik *= -1;
		mianownik *= -1;
	}
	int nwd = NWD(abs(licznik), mianownik);
	licznik /= nwd;
	mianownik /= nwd;

	Ulamek* nowy = malloc(sizeof(Ulamek));
	nowy->licznik = licznik;
	nowy->mianownik = mianownik;
	return nowy;
}

Ulamek* dodaj (Ulamek *u1, Ulamek *u2) {
	int wsp_mianownik = u1->mianownik;
	if(u1->mianownik != u2->mianownik) {
		wsp_mianownik = NWW(u1->mianownik, u2->mianownik);
		u1->licznik *= wsp_mianownik / u1->mianownik;
		u2->licznik *= wsp_mianownik / u2->mianownik;
		u1->mianownik = u2->mianownik = wsp_mianownik;
	}
	int suma_licznikow = u1->licznik + u2->licznik;
	return nowy_ulamek(suma_licznikow, wsp_mianownik);
}

Ulamek* odejmij (Ulamek *u1, Ulamek *u2) {
	int wsp_mianownik = u1->mianownik;
	if(u1->mianownik != u2->mianownik) {
		wsp_mianownik = NWW(u1->mianownik, u2->mianownik);
		u1->licznik *= wsp_mianownik / u1->mianownik;
		u2->licznik *= wsp_mianownik / u2->mianownik;
		u1->mianownik = u2->mianownik = wsp_mianownik;
	}
	int roznica_licznikow = u1->licznik - u2->licznik;
	return nowy_ulamek(roznica_licznikow, wsp_mianownik);
}

Ulamek* pomnoz (Ulamek *u1, Ulamek *u2) {
	int iloczyn_licznikow = u1->licznik * u2->licznik;
	int iloczyn_mianownikow = u1->mianownik * u2->mianownik;
	return nowy_ulamek(iloczyn_licznikow, iloczyn_mianownikow);
}

Ulamek* podziel (Ulamek *u1, Ulamek *u2) {
	int iloraz_licznika = u1->licznik * u2->mianownik;
	int iloraz_mianownika = u1->mianownik * u2->licznik;
	return nowy_ulamek(iloraz_licznika, iloraz_mianownika);
}

/*
void dodaj (Ulamek *u1, Ulamek *u2) {
	int wsp_mianownik = u1->mianownik;
	if(u1->mianownik != u2->mianownik) {
		wsp_mianownik = NWW(u1->mianownik, u2->mianownik);
		u1->licznik *= wsp_mianownik / u1->mianownik;
		u2->licznik *= wsp_mianownik / u2->mianownik;
		u1->mianownik = u2->mianownik = wsp_mianownik;
	}
	int suma_licznikow = u1->licznik + u2->licznik;
	Ulamek* suma_ulamkow = nowy_ulamek(suma_licznikow, wsp_mianownik);
	u2 -> licznik = suma_ulamkow -> licznik;
	u2 -> mianownik = suma_ulamkow -> mianownik;
	free(suma_ulamkow);
}

void odejmij (Ulamek *u1, Ulamek *u2) {
	int wsp_mianownik = u1->mianownik;
	if(u1->mianownik != u2->mianownik) {
		wsp_mianownik = NWW(u1->mianownik, u2->mianownik);
		u1->licznik *= wsp_mianownik / u1->mianownik;
		u2->licznik *= wsp_mianownik / u2->mianownik;
		u1->mianownik = u2->mianownik = wsp_mianownik;
	}
	int roznica_licznikow = u1->licznik - u2->licznik;
	Ulamek* roznica_ulamkow = nowy_ulamek(roznica_licznikow, wsp_mianownik);
	u2 -> licznik = suma_ulamkow -> licznik;
	u2 -> mianownik = suma_ulamkow -> mianownik;
	free(roznica_ulamkow);
}

void pomnoz (Ulamek *u1, Ulamek *u2) {
	int iloczyn_licznikow = u1->licznik * u2->licznik;
	int iloczyn_mianownikow = u1->mianownik * u2->mianownik;
	Ulamek iloczyn_ulamkow = nowy_ulamek(iloczyn_licznikow, iloczyn_mianownikow);
	u2 -> licznik = iloczyn_ulamkow -> licznik;
	u2 -> mianownik = iloczyn_ulamkow -> mianownik;
	free(iloczyn_ulamkow);
}

void podziel (Ulamek *u1, Ulamek *u2) {
	int iloraz_licznikow = u1->licznik * u2->mianownik;
	int iloraz_mianownikow = u1->mianownik * u2->licznik;
	Ulamek iloraz_ulamkow = nowy_ulamek(iloraz_licznikow, iloraz_mianownikow);
	u2 -> licznik = iloraz_ulamkow -> licznik;
	u2 -> mianownik = iloraz_ulamkow -> mianownik;
	free(iloraz_ulamkow);
}
*/
int main () {
	Ulamek *u1;
	Ulamek *u2;
	Ulamek *u;
	u1 = nowy_ulamek(2, -4);
	u2 = nowy_ulamek(14, 2);
	u = pomnoz(u1, u2);
	printf("%d %d\n", u->licznik, u->mianownik);
	return 0;
}