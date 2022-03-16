#include <iostream>
using namespace std;

int random_generator(int m, int n, int c);

int main() {
    cout << "Random number generator" << endl;
    cout << "Variant 1" << random_generator(37, 3, 64) << endl;
    cout << "Variant 2" << random_generator(25173, 13849, 65537);
    return 0;
}

int random_generator(int m, int n, int c) {
    int S = 1;
    for (int i = 0; i <= n; i++) {
        S = (m * S + i) % c;
    }
}