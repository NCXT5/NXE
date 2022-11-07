#include <nxe/util>
#include <iostream>

int main() {
    nxe::util::Array<int> arr;

    arr.sAdd(1);
    arr.sAdd(2);
    arr.sAdd(3);
    arr.sAdd(4);

    auto x = arr.access(100);
    auto t = x.rev();

    return 0;
}
