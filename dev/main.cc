#include <nxe/util>
#include <iostream>

void p(nxe::util::Array<int> arr) {
    for (auto &x : arr)
        printf("Element: %d\n", x);
    printf("---\n");
}

int main() {
    nxe::util::Array<int> arr;

    arr.sAdd(1);
    arr.sAdd(2);
    arr.sAdd(3);
    arr.sAdd(4);

    p(arr);
    arr.kill(0);
    p(arr);

    return 0;
}
