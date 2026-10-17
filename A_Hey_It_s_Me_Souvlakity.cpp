#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

        
    int testCases;
    cin  >> testCases;

    while (testCases--) {
        int length;
        string binaryString;
        cin >>   length >> binaryString;

        vector<int> onePositions;
        for (int index =0; index < length; ++index) {
            if (binaryString[index] ==  '1') {
                onePositions.push_back(index);
            }
        }

        if (onePositions.size() <= 1) {
            cout << 0 << '\n';
            continue;
        }

        if (onePositions.size()  == 2) {
            cout << 1 << '\n';
            continue;
        }

        cout << onePositions.back() - onePositions.front() << '\n';
    }

    return 0;
}