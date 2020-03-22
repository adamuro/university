// Adam Turowski, zad. 3

#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::string bin2rom (int x) {
	if(x <= 0 || x >= 4000) {
		std::invalid_argument exception("Liczba spoza zakresu 1-3999");
		throw exception;
	}
	std::string output = "";
	const std::vector<std::pair<int, std::string>> rzym = {
		{1000, "M"},
		{900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
		{90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"},
		{9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
	};
	for(const std::pair<int, std::string> &convert: rzym) {
		while(std::get<int>(convert) <= x) {
			x -= std::get<int>(convert);
			output += std::get<std::string>(convert);
		}
	}
	return output;
}

int main (int argc, char** argv) {
	if(argc == 1) {
		std::cerr << "Program sluzy do przeksztalcania liczb arabskich z zakresu 1-3999 na rzymskie." << std::endl;
		std::cerr << "Nalezy podac przynajmniej jedna liczbe calkowita jako argument wywolania." << std::endl;
		exit(1);
	}
	for(int i = 1; i < argc; i++) {
		try {
			std::string arg = argv[i];
			int num = std::stoi(arg);
			std::cout << bin2rom(num) << std::endl;
		}
		catch (std::invalid_argument exception) {
			std::clog << "Niepoprawny argument: " << exception.what() << std::endl;
		}
		catch (std::out_of_range exception) {
			std::clog << "Blad zakresu: " << exception.what() << std::endl;
		}
	}
}