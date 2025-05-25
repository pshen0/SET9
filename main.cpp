#include "StringSortTester.h"
#include "StringGenerator.h"

int main() {
    StringGenerator generator;
    generator.generateAll();
    StringSortTester tester;
    tester.runTests();
    return 0;
}




