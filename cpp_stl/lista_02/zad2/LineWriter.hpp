#include <iostream>
#include <memory>

class LineWriter {
  public:
    LineWriter(std::shared_ptr<std::ofstream> ofstream);
    void write(std::string text);

  private:
    std::shared_ptr<std::ofstream> ofstream;
};