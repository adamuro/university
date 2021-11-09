#include <iostream>
#include <fstream>

#include "LineWriter.hpp"

void ofstream_deleter(std::ofstream *ofstream) {
  *ofstream << "Zamykam plik" << std::endl;

  ofstream->close();

  delete ofstream;

}

int main(int argc, char const *argv[]) {
  std::shared_ptr<std::ofstream> ofstream_ptr(new std::ofstream("out.txt"), ofstream_deleter);

  LineWriter *lw1 = new LineWriter(ofstream_ptr);
  LineWriter *lw2 = new LineWriter(ofstream_ptr);

  lw1->write("Jeden");
  lw2->write("Dwa");

  delete lw1;
  
  lw2->write("Trzy");

  delete lw2;

  return 0;
}
