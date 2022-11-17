#include <iostream>

using namespace std;

int avg[3] = {0};

int main() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 3; ++j) {
            int n;
            cin >> n;
            avg[j] += n;
        }
    }
    for (int j = 0; j < 3; ++j) {
        cout << avg[j] / 10.0;
    }
}