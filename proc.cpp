#include <string>
#include <iostream>

using namespace std;

int main() {
    for (int i = 0; i < 10; ++i) {
        cout << "Run \\#" << to_string(i + 1) << " & ";
        for (int j = 0; j < 3; ++j) {
            int n;
            cin >> n;
            cout << n;
            if (j == 2) cout << " \\\\\n";
            else cout << " & ";
        }
    }

    return 0;
}