#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;

    while (testCases--) {
        int elementCount;
        cin >> elementCount;

        vector<int> numbers(elementCount);
        for (auto &value : numbers) {
            cin >> value;
        }

        int oddCount = count_if(numbers.begin(), numbers.end(), [](int value) {
            return value % 2 != 0;
        });
        int evenCount = elementCount - oddCount;

        bool shouldLose = (evenCount == 1 && oddCount == 1) || (evenCount == 0 && oddCount == 3);
        cout << (shouldLose ? "Larpity" : "Moggity") << '\n';
    }

    return 0;
}