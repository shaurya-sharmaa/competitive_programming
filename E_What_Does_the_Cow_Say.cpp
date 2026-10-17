#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;

    while (testCases--) {
        int length, maxAdditionalBrackets;
        string expression;
        cin >> length >> maxAdditionalBrackets >> expression;

        vector<int> openGroups(1, 0), closeGroups(1, 0);

        int index = 0;
        while (index < length) {
            int groupEnd = index;
            while (groupEnd < length && expression[groupEnd] == '(') {
                ++groupEnd;
            }
            openGroups.push_back(groupEnd - index);
            index = groupEnd;

            while (groupEnd < length && expression[groupEnd] == ')') {
                ++groupEnd;
            }
            closeGroups.push_back(groupEnd - index);
            index = groupEnd;
        }

        int segmentCount = static_cast<int>(openGroups.size()) - 1;

        vector<int> openPrefix(segmentCount + 1, 0);
        vector<int> closePrefix(segmentCount + 1, 0);
        vector<int> balance(segmentCount + 1, 0);
        vector<int> segmentValue(segmentCount + 1, 0);

        for (int segment = 1; segment <= segmentCount; ++segment) {
            openPrefix[segment] = openPrefix[segment - 1] + openGroups[segment];
            closePrefix[segment] = closePrefix[segment - 1] + closeGroups[segment];
            balance[segment] = openPrefix[segment] - closePrefix[segment];
            segmentValue[segment] = openPrefix[segment] - closePrefix[segment - 1];
        }

        vector<int> nextSmaller(segmentCount + 1, segmentCount);
        vector<int> monotonicStack;

        for (int segment = segmentCount - 1; segment >= 0; --segment) {
            while (!monotonicStack.empty() && balance[monotonicStack.back()] >= balance[segment]) {
                monotonicStack.pop_back();
            }

            if (!monotonicStack.empty()) {
                nextSmaller[segment] = monotonicStack.back();
            }

            monotonicStack.push_back(segment);
        }

        int segmentTreeSize = 1;
        while (segmentTreeSize < segmentCount) {
            segmentTreeSize <<= 1;
        }

        vector<int> segmentTree(2 * segmentTreeSize, 0);
        for (int segment = 1; segment <= segmentCount; ++segment) {
            segmentTree[segmentTreeSize + segment - 1] = segmentValue[segment];
        }
        for (int node = segmentTreeSize - 1; node > 0; --node) {
            segmentTree[node] = max(segmentTree[node << 1], segmentTree[node << 1 | 1]);
        }

        auto rangeQuery = [&](int left, int right) {
            int result = 0;
            left += segmentTreeSize;
            right += segmentTreeSize + 1;

            while (left < right) {
                if (left & 1) {
                    result = max(result, segmentTree[left++]);
                }
                if (right & 1) {
                    result = max(result, segmentTree[--right]);
                }
                left >>= 1;
                right >>= 1;
            }

            return result;
        };

        int answer = 0;

        for (int segment = 0; segment < segmentCount; ++segment) {
            long long limit = static_cast<long long>(closePrefix[segment]) + maxAdditionalBrackets;

            int boundary = static_cast<int>(
                upper_bound(closePrefix.begin() + segment,
                            closePrefix.end(), limit)
                - closePrefix.begin())
                - 1;

            int rightmost = min({segmentCount, nextSmaller[segment], boundary + 1});

            if (segment + 1 <= rightmost) {
                answer = max(answer, rangeQuery(segment, rightmost - 1) - balance[segment]);
            }
        }

        for (int segment = 1; segment <= segmentCount && closePrefix[segment - 1] <= maxAdditionalBrackets; ++segment) {
            answer = max(answer, maxAdditionalBrackets + segmentValue[segment]);
        }

        cout << min(answer, length / 2) << '\n';
    }

    return 0;
}