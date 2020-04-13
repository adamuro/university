#include "tabbit.hpp"

tab_bit::tab_bit (int rozm) {
	if(rozm <= 0) {
		throw std::invalid_argument("Podany rozmiar jest mniejszy lub równy zero.");
	}

	int liczba_komorek;
	if(rozm % 64 == 0) {
		liczba_komorek = rozm / rozmiarSlowa;
	}
	else {
		liczba_komorek = rozm / rozmiarSlowa + 1;
	}
	tab = new slowo [liczba_komorek] {0};
	dl = rozm;
}

tab_bit::tab_bit (uint64_t tb) {
	this->~tab_bit();
	tab = new slowo [1];
	tab[0] = tb;
	dl = rozmiarSlowa;
}

tab_bit::tab_bit (const tab_bit &tb) {
	dl = tb.dl;
	tab = tb.tab;
}

tab_bit::tab_bit (tab_bit &&tb):
	dl(std::move(tb.dl)),
	tab(std::move(tb.tab)) {}

tab_bit & tab_bit::operator = (const tab_bit &tb) {
	dl = tb.dl;
	tab = tb.tab;
	return *this;
}

tab_bit & tab_bit::operator = (tab_bit &&tb) {
	dl = std::move(tb.dl);
	tab = std::move(tb.tab);
}

tab_bit::~tab_bit () {
	delete [] tab;
}

bool tab_bit::czytaj (int i) const {
	if(i >= dl) {
		throw std::range_error("Podany indeks jest wiekszy od rozmiaru tablicy.");
	}
	if(i < 0) {
		throw std::range_error("Podany indeks jest mniejszy od zera.");
	}
	ref referencja = ref(*this, i);
	return (bool)referencja;
}
bool tab_bit::pisz (int i, bool b) {
	ref referencja = ref(*this, i);
	referencja = b;
}
bool tab_bit::operator[] (int i) const {
	return czytaj(i);
}
tab_bit::ref tab_bit::operator[] (int i) {
	return ref(*this, i);
}

tab_bit::ref::ref (const tab_bit &tb, int i) {
    int indeks;
	if(i % 64 == 0) {
		indeks = i / 64;
	}
	else {
		indeks = i / 64 + 1;
	}
	komorka = &tb.tab[indeks];
	indeks_bitu = i % 64;
}

tab_bit::ref::operator bool() {
	uint64_t maska = 1;
    return maska & (*komorka >> (63 - indeks_bitu));
}

tab_bit::ref& tab_bit::ref::operator = (bool b) noexcept {
    uint64_t maska = 1;
    if(b) {
    	*komorka |= maska << (63 - indeks_bitu);
    }
    else {
    	*komorka &= ~(maska << (63 - indeks_bitu));
    }
}

tab_bit::ref& tab_bit::ref::operator= (ref &r) {
    bool b = (bool)r;
    uint64_t maska = 1;
    if(b) {
    	*komorka |= maska << (63 - indeks_bitu);
    }
    else {
    	*komorka &= ~(maska << (63 - indeks_bitu));
    }
    return *this;
}

tab_bit tab_bit::operator | (tab_bit& tb) {
	int rozm = (dl > tb.dl) ? dl : tb.dl;
	tab_bit temp = tab_bit(rozm);

	for(int i = 0; i < rozm; i++) {
		if(i < dl && (*this)[i] == 1) {
			temp[i] = 1;
		}
		else if(i < tb.dl && tb[i] == 1) {
			temp[i] = 1;
		}
	}
	return temp;
}
tab_bit& tab_bit::operator |= (tab_bit& tb) {
	tab_bit temp = *this | tb;
	this->~tab_bit();
	*this = temp;

	return *this;
}
tab_bit tab_bit::operator & (tab_bit& tb) {
	int rozm = (dl > tb.dl) ? dl : tb.dl;
	tab_bit temp = tab_bit(rozm);

	for(int i = 0; i < rozm; i++) {
		if(i < dl && i < tb.dl) {
			if((*this)[i] == 1 && tb[i] == 1) {
				temp[i] = 1;
			}
		}
	}
	return temp;
}
tab_bit& tab_bit::operator &= (tab_bit& tb) {
	tab_bit temp = *this & tb;
	this->~tab_bit();
	*this = temp;

	return *this;
}
tab_bit tab_bit::operator ^ (tab_bit& tb) {
	int rozm = (dl > tb.dl) ? dl : tb.dl;
	tab_bit temp = tab_bit(rozm);

	for(int i = 0; i < rozm; i++) {
		if(i < dl && i < tb.dl) {
			if((*this)[i] == 1 && tb[i] == 0) {
				temp[i] = 1;
			}
			else if((*this)[i] == 0 && tb[i] == 1) {
				temp[i] = 1;
			}
			else {
				temp[i] = 0;
			}
		}
		else if(i < dl && (*this)[i] == 1) {
			temp[i] = 1;
		}
		else if(i < tb.dl && tb[i] == 1) {
			temp[i] = 1;
		}
	}
	return temp;
}
tab_bit& tab_bit::operator ^= (tab_bit& tb) {
	tab_bit temp = *this ^ tb;
	this->~tab_bit();
	*this = temp;

	return *this;
}
tab_bit tab_bit::operator !() {
	tab_bit temp(dl);
	for(int i = 0; i < dl; i++) {
		if((*this)[i] == 0) {
			temp[i] = 1;
		}
		else {
			temp[i] = 0;
		}
	}
	return temp;
}

std::istream& operator >> (std::istream &strumien_we, tab_bit &tb){
    std::string wejscie;
    strumien_we >> wejscie;
    
    for(int i = 0; i < wejscie.length() && i < tb.rozmiar(); i++){
        tb[i] = (bool)(wejscie[i] - '0');
    }
    return strumien_we;
}

std::ostream& operator << (std::ostream &strumien_wy, const tab_bit &tb){
    std::string wyjscie = "";
    
    for(int i = 0; i < tb.rozmiar(); i++){
        if((bool)tb[i]) {
        	wyjscie += "1";
        }
        else {
        	wyjscie += "0";
        }
    }
    strumien_wy << wyjscie;
    return strumien_wy;
}