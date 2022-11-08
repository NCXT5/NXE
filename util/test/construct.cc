#include <nxe/util>

int main() {
    using namespace nxe::util;
    Array<int> x;
    Array<int> y(10);

    const int d[2] = {1, 2};
    Array<int> z(d, 2);

    if (x.len() != 0) {
        return 1;
    }

    return 0;
}
