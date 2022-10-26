#include <fenix.hxx>
#include <cstdio>

int main() {
    using namespace fx;
    String s = "Hello, World!";

    printf("S Value: %s\n", (const char *) (s + s + s));
    return 0;
}
