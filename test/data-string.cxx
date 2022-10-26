#include <fenix.hxx>
#include <cstdio>

using namespace fx;

int main() {
    String s = "Hello World";
    String s2 = "Hello World";

    String d = "Bye World";

    if (s != s2) {
        printf("S is not equal to S2\n");
        return 1;
    }

    if (!(s == s2)) {
        printf("S is not equal to S2\n");
        return 1;
    }

    if (s == d) {
        printf("S is equal to D\n");
        return 1;
    }

    if (!(s != d)) {
        printf("S is equal to D\n");
        return 1;
    }

    if (s.length != 11) {
        printf("S length is not 11\n");
        return 1;
    }

    if (s2.length != 11) {
        printf("S2 length is not 11\n");
        return 1;
    }

    if (d.length != 9) {
        printf("D length is not 9\n");
        return 1;
    }

    String sum = s + " " + d;
    printf("Sum: %s\n", (const char *) sum);

    if (sum != "Hello World Bye World") {
        printf("Sum is not equal to \"Hello World Bye World\"\n");
        return 1;
    }

    if (sum.length != 21) {
        printf("Sum length is not 21\n");
        return 1;
    }

    return 0;
}
