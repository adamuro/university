#include "LineWriter.hpp"

#include <fstream>

LineWriter::LineWriter(std::shared_ptr<std::ofstream> ofstream) {
  this->ofstream = ofstream;
}

void LineWriter::write(std::string text) {
  *ofstream << text << std::endl;
}