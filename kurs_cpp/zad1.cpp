#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

bool isPrime(int64_t num) {
	if(num == 2) {
		return 1;
	}
	if(num == 0 || num == 1 || num % 2 == 0) {
		return 0;
	}
	for(int64_t i = 3; i * i <= num; i += 2) {
		if(num % i == 0)
			return 0;
	}
	return 1;
}

int64_t stringToInt(std::string str) {
	int64_t result = 0;
	int64_t i = (str[0] == '-') ? 1 : 0;
	
	if(str[i] == '0' && str.length() != 1) {
		std::string exception = "Liczba zaczyna sie od zera.";
		throw exception;
	}
	for(; i < str.length(); i++) {
		if(str[i] < '0' || str[i] > '9') {
			std::string exception = "Argument nie jest liczba.";
			throw exception;
		}
		result *= 10;
		result += str[i] - '0';
	}
	if(str[0] == '-') {
		result *= -1;
	}
	return result;
} 

std::vector<int64_t> getPrimeFactors(int64_t num) {
	std::vector<int64_t> primeFactors;

	if(num == -1 || num == 0 || num == 1) {
		primeFactors.push_back(num);
		return primeFactors;
	}
	else if(num < 0) {
		if(num % 2 == 0) {
			primeFactors.push_back(-1);
			primeFactors.push_back(2);
			num /= 2;
			num *= -1;
		}
		else {
			primeFactors.push_back(-1);
			num *= -1;
		}
	}
	int64_t numAbs = (num < 0) ? -1 * num : num;
	for(int64_t i = 2; i * i <= numAbs; i++) {
		while(num % i == 0) {
			primeFactors.push_back(i);
			num /= i;
		}
	}
	if(isPrime(num))
		primeFactors.push_back(num);

	return primeFactors;
}

void printPrimeFactors(std::vector<int64_t> primeFactors, int64_t num) {
	int64_t factorsProduct = 1;

	std::cout << num << " = ";

	for(int64_t factor : primeFactors) {
		std::cout << factor;
		factorsProduct *= factor;
		if(factorsProduct != num) {
			std::cout << " * ";
		}
	}
	std::cout << std::endl;
}

int main (int argc, char *argv[]) {
	if(argc == 1) {
		std::cerr << "Program sluzy do rozkladu liczb na czynniki pierwsze." << std::endl;
		std::cerr << "Nalezy podac przynajmniej jedna liczbe calkowita jako argument wywolania." << std::endl;
		return 0;
	}

	for(int i = 1; i < argc; i++) {
		int64_t argument;
		try {
			argument = stringToInt(argv[i]);
			std::vector<int64_t> primeFactors = getPrimeFactors(argument);
			printPrimeFactors(primeFactors, argument);
		}
		catch(std::string exception) {
			std::cerr << exception << std::endl;
		}
	}
	return 0;
}