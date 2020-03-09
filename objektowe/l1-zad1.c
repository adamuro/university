#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.141592

enum Figury {
	typ_kwadrat = 0, typ_trojkat = 1, typ_kolo = 2
};

typedef struct Figura {
	float x;
	float y;
	float dlugosc;
	int typfig;
} Figura;

Figura* nowy_kwadrat (float x, float y, float dlugosc) {
	if(dlugosc <= 0) {
		printf("Niepoprawna dlugosc boku.\n");
		return NULL;
	}
	Figura* kwadrat = malloc(sizeof(Figura));
	kwadrat->x = x;
	kwadrat->y = y;
	kwadrat->dlugosc = dlugosc;
	kwadrat->typfig = typ_kwadrat;
	return kwadrat;
}

Figura* nowy_trojkat (float x, float y, float dlugosc) {
	if(dlugosc <= 0) {
		printf("Niepoprawna dlugosc boku.\n");
		return NULL;
	}
	Figura* trojkat = malloc(sizeof(Figura));
	trojkat->x = x;
	trojkat->y = y;
	trojkat->dlugosc = dlugosc;
	trojkat->typfig = typ_trojkat;
	return trojkat;
}

Figura* nowe_kolo (float x, float y, float promien) {
	if(promien <= 0) {
		printf("Niepoprawna dlugosc promienia.\n");
		return NULL;
	}
	Figura* kolo = malloc(sizeof(Figura));
	kolo->x = x;
	kolo->y = y;
	kolo->dlugosc = promien;
	kolo->typfig = typ_kolo;
	return kolo;
}

float pole(Figura *f) {
	float pole;

	switch(f->typfig) {
		case typ_kwadrat:
			return f->dlugosc * f->dlugosc;
		case typ_trojkat:
			return f->dlugosc * f->dlugosc * sqrt(3.0) / 4;
		case typ_kolo:
			return PI * f->dlugosc * f->dlugosc;
		default:
			printf("Nieznany typ figury.\n");
			break;
	}
	return 0;
}

void przesun(Figura *f, float x, float y) {
	f->x += x;
	f->y += y;
}

float sumapol(Figura **f, int size) {
	float suma = 0;
	
	for(int i = 0; i < size; i++) {
		suma += pole(f[i]);
	}
}


int main() {
	Figura *kwadrat = nowy_kwadrat(2, 4, 1.5);
	Figura *kolo = nowe_kolo(-2.5, 1, 4);
	Figura *trojkat = nowy_trojkat(0, 1, 3);

	printf("pole kwadratu: %f\n", pole(kwadrat));
	printf("pole kola: %f\n", pole(kolo));
	printf("pole trojkata: %f\n", pole(trojkat));

	Figura *tab[3] = {kwadrat, kolo, trojkat};
	printf("%f\n", sumapol(tab, 3));

	return 0;
}