#include <iostream>
#include <deque>
#include <algorithm>

class Person {
public:
  std::string name;
  std::string surname;
  uint16_t age;
  float height; // [m]
  float weight; // [kg]

  Person(std::string _name, std::string _surname, uint16_t _age, float _height, float _weight)
  : name(_name), surname(_surname), age(_age), height(_height), weight(_weight) {}

  float bmi() {
    return weight / (height * height);
  }

  void print() {
    std::cout << name << " " << surname << ", lat " << age << ", waga: " << weight << "kg, wzrost: " << height << "m, bmi: " << bmi() << std::endl;
  }
};

void sortByBmi(std::deque<Person> &people) {
  std::sort(people.begin(), people.end(), [](Person p1, Person p2) {
    return p1.bmi() < p2.bmi();
  });
}

void loseWeight(std::deque<Person> &people) {
  std::for_each(people.begin(), people.end(), [](Person &p) {
    p.weight = p.weight * 0.9;
  });
}

void groupLightAndHeavy(std::deque<Person> &people) {
  std::partition(people.begin(), people.end(), [](Person &p) {
    return p.weight > 100.0;
  });
}

void middleHeight(std::deque<Person> &people) {
  std::nth_element(people.begin(), people.begin() + 5, people.end(), [](Person &p1, Person &p2) {
    return p1.height > p2.height;
  });
}

void shuffleParts(std::deque<Person> &people) {
  std::random_shuffle(people.begin(), people.begin() + 4);
  std::random_shuffle(people.end() - 4, people.end());
}

void printPeople(std::deque<Person> &people) {
  for (Person &p : people) {
    p.print();
  }
  std::cout << std::endl;
}

auto youngestAndEldest(std::deque<Person> &people) {
  return std::minmax_element(people.begin(), people.end(), [](Person &p1, Person &p2) {
    return p1.age < p2.age;
  });
}

int main(int argc, char const *argv[]) {
  std::deque<Person> people {
    Person("Robert", "Lewandowski", 33, 1.88, 82.0),
    Person("Damian", "Lis", 45, 1.83, 114.0),
    Person("Mariusz", "Pudzianowski", 45, 1.79, 122.0),
    Person("Sara", "Sudoł", 21, 1.66, 54.0),
    Person("Adam", "Małysz", 43, 1.73, 64.0),
    Person("Malwina", "Sikora", 38, 1.84, 111.0),
    Person("Robert", "Makłowicz", 52, 1.67, 72.0),
    Person("Mirosława", "Brzezińska", 78, 1.65, 58.0),
    Person("Tytus", "Szyluk", 29, 1.82, 75.0),
    Person("Dobromił", "Mazur", 54, 1.92, 103.0),
    Person("Witold", "Tacikiewicz", 27, 1.86, 78.0)
  };

  std::cout << "a) posortuj osoby według współczynnika BMI (funkją porównującą niech będzie lambda)" << std::endl;
  sortByBmi(people);
  printPeople(people);

  std::cout << "b) osoby odchudziły się na obozie sportowym i straciły 10% swojej pierwotnej wagi (funkją modyfikującą niech będzie lambda)" << std::endl;
  loseWeight(people);
  printPeople(people);

  std::cout << "c) podziel osoby na dwie grupy: ciężkie z wagą powyżej 100[kg] i lekkie z wagą niewiększą niż 100[kg] (użyj lambdy jako predykatu)" << std::endl;
  groupLightAndHeavy(people);
  printPeople(people);

  std::cout << "d) ustaw osobę o środkowym w tej populacji wzroście na pozycji 5 (pośrodku listy)" << std::endl;
  middleHeight(people);
  printPeople(people);

  std::cout << "e) losowo poprzestawiaj między sobą pierwsze 5 osób a potem ostatnie 5 osób" << std::endl;
  shuffleParts(people);
  printPeople(people);

  std::cout << "f) wypisz osobę najstarszą i najmłodszą na standardowym wyjściu (nie korzystaj z sortowania danych)" << std::endl;
  auto yae = youngestAndEldest(people);
  std::cout << "Najmłodsza osoba: ";
  yae.first->print();
  std::cout << "Najstarsza osoba: ";
  yae.second->print();

  return 0;
}
