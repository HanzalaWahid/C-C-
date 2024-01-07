#include <iostream>
using namespace std;

void printReversedPyramid(const string &hello) {
    for (int i = hello.length() - 1; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            cout << hello[j];
        }
        cout << "\n";
    }
}

int main() {
    string hello = "Python";

    // Call the function to print the reversed pyramid pattern
    printReversedPyramid(hello);

    // Call it again if needed
    printReversedPyramid(hello);

    return 0;
}
