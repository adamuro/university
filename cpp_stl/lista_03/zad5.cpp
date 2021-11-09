#include <iostream>
#include <random>
#include <chrono>

template<int size>
class Matrix {
  private:
    double *matrix;

  public:
    Matrix() {
      matrix = new double[size * size];

      std::random_device rd;
      std::mt19937 mt(rd());
      std::uniform_real_distribution<double> dist(0.5, 2.0);

      for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
          matrix[i * size + j] = dist(mt);
    }

    void square() {
      double *squared = new double[size * size];
      for (int i = 0; i < size * size; i++)
        squared[i] = 0;

      for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
          for (int k = 0; k < size; k++)
            squared[i * size + j] += matrix[i * size + k] * matrix[k * size + j];

      delete[] matrix;
      matrix = squared;
    }

    void printSquareTime(int iterations = 1) {
      std::cout << "Mnożenie macierzy rozumiaru " << size << " x " << size <<
      std::endl << "Liczba iteracji: " << iterations << std::endl;

      auto start = std::chrono::high_resolution_clock::now();

      for (int i = 0; i < iterations; i++)
        square();

      auto end = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>((end - start) / iterations);

      std::cout << "Czas trwania jednej iteracji: " << duration.count() << " milisekund." << std::endl;
    }
};


int main(int argc, char const *argv[]) {
  Matrix<100> m100;
  Matrix<1000> m1000;
  Matrix<10000> m10000;

  m100.printSquareTime(25);
  m1000.printSquareTime();
  m10000.printSquareTime();

  return 0;
}
