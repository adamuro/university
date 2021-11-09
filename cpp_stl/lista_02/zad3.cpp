#include <iostream>
#include <memory>

int main(int argc, char const *argv[]) {
  std::weak_ptr<uint32_t> weak;

  if (true) {
    std::shared_ptr<uint32_t> shared_ptr(new uint32_t(24));

    weak = shared_ptr;
    std::cout << weak.expired() << std::endl;

    std::shared_ptr<uint32_t> shared = weak.lock();
    std::cout << *shared << std::endl;
  }

  if (weak.expired()) {
    std::cout << "Expired" << std::endl;
  }


  return 0;
}
