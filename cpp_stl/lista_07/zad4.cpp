#include <iostream>
#include <fstream>
#include <random>

std::string generateText(int words, std::vector<double> lettersFrequencies) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::binomial_distribution<int> binomial(11);
  std::discrete_distribution<int> discrete(lettersFrequencies.begin(), lettersFrequencies.end());
  std::string text;

  for (int i = 0; i < words; i++) {
    std::string word;
    int wordLength = binomial(mt) + 1;

    for (int i = 0; i < wordLength; i++) {
      word += (char) discrete(mt) + 'a';
    }
    text += word + " ";
  }

  return text;
}


int main(int argc, char const *argv[]) {
  const std::vector<double> lettersFrequencies {812, 149, 271, 432, 1202, 230, 203, 592, 731, 10, 69, 398, 261, 695, 768, 182, 11, 602, 628, 910, 288, 111, 209, 17, 211, 7};

  int wordsNumber = std::stoi(argv[1]);
  std::string fileName = argv[2];
  std::ofstream outputFile;
  outputFile.open(fileName);
  outputFile << generateText(wordsNumber, lettersFrequencies) << std::endl;
  outputFile.close();

  return 0;
}
