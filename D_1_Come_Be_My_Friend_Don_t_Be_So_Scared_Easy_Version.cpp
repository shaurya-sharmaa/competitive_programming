#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;

    while (testCases--) {
        int totalNodes, edgeCount;
        cin >> totalNodes >> edgeCount;

        for (int index = 0; index < edgeCount; ++index) {
            int left, right;
            cin >> left >> right;
        }

        if (totalNodes == 1) {
            cout << 0 << '\n';
            continue;
        }

        int pairCount = (totalNodes + 1) / 2;
        string output = to_string(pairCount) + '\n';

        for (int pairStart = 1; pairStart <= pairCount; ++pairStart) {
            output += to_string(pairStart) + " " + to_string(pairStart + pairCount - 1) + '\n';
        }

        cout << output;
    }

    return 0;
}