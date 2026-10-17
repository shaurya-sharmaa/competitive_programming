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

        vector<long long> numbers(elementCount);
        for (auto &value : numbers) {
            cin >> value;
        }

        int pivotIndex = max_element(numbers.begin(), numbers.end()) - numbers.begin();
        long long currentValue = numbers[pivotIndex];

        auto sweep = [&](vector<long long> &segment) {
            long long capacity = numbers[pivotIndex];

            for (long long value : segment) {
                if (value >= capacity) {
                    capacity = value;
                    currentValue |= value;
                    continue;
                }

                vector<long long> candidates = {value, capacity};
                for (int bit = 0; bit < 31; ++bit) {
                    if ((capacity >> bit) & 1LL) {
                        long long candidate = ((capacity >> (bit + 1)) << (bit + 1)) | ((1LL << bit) - 1);
                        if (candidate >= value) {
                            candidates.push_back(candidate);
                        }
                    }
                }

                long long best = value;
                for (long long candidate : candidates) {
                    if ((currentValue | candidate) > (currentValue | best) ||
                        ((currentValue | candidate) == (currentValue | best) && candidate > best)) {
                        best = candidate;
                    }
                }

                currentValue |= best;
                capacity = best;
            }
        };

        vector<long long> leftSegment;
        leftSegment.reserve(pivotIndex + 1);
        for (int index = pivotIndex; index >= 0; --index) {
            leftSegment.push_back(numbers[index]);
        }

        vector<long long> rightSegment;
        rightSegment.reserve(elementCount - pivotIndex - 1);
        for (int index = pivotIndex + 1; index < elementCount; ++index) {
            rightSegment.push_back(numbers[index]);
        }

        sweep(leftSegment);
        sweep(rightSegment);

        cout << currentValue << '\n';
    }

    return 0;
}