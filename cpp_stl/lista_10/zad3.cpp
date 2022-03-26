#include <iostream>
#include <filesystem>
#include <sstream>
#include <chrono>
#include <ctime>

// https://stackoverflow.com/a/61067330
template <typename TP>
std::time_t to_time_t(TP tp) {
  using namespace std::chrono;
  auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
  return system_clock::to_time_t(sctp);
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cerr << "Nie podano żadnej nazwy pliku" << std::endl;
  }

  for (int i = 1; i < argc; i++) {
    std::string fileName = argv[i];

    if (std::filesystem::exists(fileName)) {
      std::cout << "- " << fileName << " - znaleziono" << std::endl;
      auto path = std::filesystem::path(fileName);
      std::cout << "Ścieżka kanoniczna: " << std::filesystem::canonical(path) << std::endl;
      std::time_t lastWriteTime = to_time_t(std::filesystem::last_write_time(path));
      std::cout << "Data ostatniej modyfikacji: " << std::put_time(std::localtime(&lastWriteTime), "%c") << std::endl;
      if (!std::filesystem::is_directory(path)) {
        std::cout << "Rozmiar: " << std::filesystem::file_size(path) << "B" << std::endl;
      }
    } else {
      std::cout << fileName << " - nie znaleziono" << std::endl;
    }
  }
  return 0;
}
