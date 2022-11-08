#include <nxe/util.h>
#include <iostream>

int main() {
    using namespace nxe::util;
    Array<String> words = String("Hello normal world").split(" ");
    for (int i = 0; i < words.len(); i++) {
        std::cout << words.access(i).rev() << "-";
    }
    std::cout << std::endl;
    return 0;
}
