#include <iostream>
#include <filesystem>

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cerr << "Nie podano żadnej nazwy folderu" << std::endl;
  }

  for (int i = 1; i < argc; i++) {
    std::string dirName = argv[i];
    std::filesystem::path path = std::filesystem::path(dirName);

    if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
      for (auto entry : std::filesystem::directory_iterator(path)) {
        std::cout << entry.path().filename() << std::endl;
      }
    } else {
      std::cout << "Folder " << dirName << " nie istnieje" << std::endl;
    }
  }

  return 0;
}
