#include <iostream>
#include "stos.hpp"

void wypiszStos (stos s) {
    while(s.rozmiar() > 0) {
        std::cout << s.sciagnij() << " ";
    }
}

void utworzStosLista () {
    std::string str1;
    std::string str2;
    std::string str3;

    std::cin >> str1 >> str2 >> str3;
    stos s = {str1, str2, str3};

    std::cout << std::endl << "Udalo sie utworzyc stos:" << std::endl;
    wypiszStos(s);
}

int main()
{
    bool running = 1;

    while(running)
    {
        int rozmiar;

        std::cout
        << "Program testowy." << std::endl
        << "Podaj rozmiar testowego stosu: ";

        std::cin >> rozmiar;

        stos* testStos = new stos(rozmiar);
        bool test = 1;

        while(test) {
            int wybor;
            std::cout << std::endl
            << "Wybierz opcje:" << std::endl
            << "1) Wstaw element" << std::endl
            << "2) Usun element" << std::endl
            << "3) Sprawdz ilosc elementow stosu" << std::endl
            << "4) Wypisz caly stos" << std::endl
            << "5) Wypisz odwrocony stos" << std::endl
            << "6) Test tworzenia stosu za pomoca listy 3 stringow" << std::endl
            << "7) Powrot do wyboru rozmiaru stosu" << std::endl
            << "8) Zakoncz prace z programem" << std::endl
            << std::endl
            << "Wybierz numer operacji: ";

            std::cin >> wybor;

            std::string input;

            switch (wybor) {
            case 1:
                std::cout << "Podaj element do wstawienia: ";
                std::cin >> input;
                try {
                	testStos->wloz(input); 
                }
                catch (std::length_error exception) {
                	std::cerr << "Nie udalo sie dodac elementu: " << exception.what();
                }
            	break;
            case 2:
	            try {
	            	std::string element = testStos->sciagnij();
	                std::cout 
	                << "Element zostal usuniety" << std::endl
	                << "Usunięty element: " << element << std::endl;
	            }
	            catch (std::length_error exception) {
	            	std::cerr << "Nie udalo sie usunac elementu: " << exception.what();
	            }
            	break;
            case 3:
                std::cout << "Ilosc elementow: " << testStos->rozmiar() << std::endl;
            	break;
            case 4:
                std::cout << "Stos:" << std::endl;
                wypiszStos(*testStos);
            	break;
            case 5:
                std::cout << "Stos został odwrócony:" << std::endl;
                wypiszStos(testStos->odwroc());
            	break;
            case 6:
                std::cout << "Podaj stringi: " << std::endl;
                utworzStosLista();
            	break;
            case 7:
                delete testStos;
                test = 0;
            	break;
            case 8:
                delete testStos;
                test = 0;
                running = 0;
            	break;
            default:
                std::cout << "Wybierz opcje 1-8." << std::endl;
            	break;
            }
        }
    }

    // Przykladowe polecenia wywolujace poszczegolne kostruktory i przypisania.

    std::cout 
    << "Wywolania poszczegolnych konstruktorow i przypisan:"
    << std::endl;

    stos przyklad = stos();
	stos przypPrzenoszace = stos();
	std::exchange(przypPrzenoszace, przyklad); // Konstruktor i przypisanie przenoszące
	stos konstrPrzenoszacy(std::move(przyklad)); // Konstruktor przenoszący
	stos konstrKopiujacy = przyklad; // Konstruktor kopiujący
	stos przypKopiujace;
	przypKopiujace = przyklad; // Przypisanie kopiujace


    return 0;
}