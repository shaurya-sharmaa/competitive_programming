#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    mt19937_64 rng(static_cast<unsigned long long>(chrono::steady_clock::now().time_since_epoch().count()));
    const int INF = 1e9;

    int testCases;
    cin >> testCases;

    while (testCases--) {
        int nodeCount, edgeCount;
        cin >> nodeCount >> edgeCount;

        vector<unsigned long long> xorPrefix(nodeCount + 2, 0);
        for (int index = 0; index < edgeCount; ++index) {
            int left, right;
            cin >> left >> right;
            unsigned long long randomHash = rng();
            xorPrefix[left] ^= randomHash;
            xorPrefix[right + 1] ^= randomHash;
        }

        vector<pair<unsigned long long, int>> valueByPosition(nodeCount);
        unsigned long long currentXor = 0;
        for (int position = 1; position <= nodeCount; ++position) {
            currentXor ^= xorPrefix[position];
            valueByPosition[position - 1] = {currentXor, position};
        }

        sort(valueByPosition.begin(), valueByPosition.end());

        vector<int> bestRangeEnd(nodeCount + 2, INF), maxRightIndex(nodeCount + 2, 0);
        for (int index = 0; index < nodeCount;) {
            int rightIndex = index;
            while (rightIndex + 1 < nodeCount && valueByPosition[rightIndex + 1].first == valueByPosition[index].first) {
                ++rightIndex;
            }

            if (rightIndex > index) {
                for (int k = index; k < rightIndex; ++k) {
                    int left = valueByPosition[k].second;
                    int right = valueByPosition[k + 1].second - 1;
                    bestRangeEnd[left] = min(bestRangeEnd[left], right);
                }
                maxRightIndex[valueByPosition[index].second] = max(maxRightIndex[valueByPosition[index].second], valueByPosition[rightIndex].second);
            }
            index = rightIndex + 1;
        }

        vector<int> nextSegmentEnd(nodeCount + 2, INF), dp(nodeCount + 2, 0), segmentEnd(nodeCount + 2, 0), prefixMax(nodeCount + 2, 0);
        for (int position = nodeCount - 1; position >= 0; --position) {
            nextSegmentEnd[position] = min(nextSegmentEnd[position + 1], bestRangeEnd[position + 1]);
        }
        for (int position = nodeCount; position >= 0; --position) {
            if (nextSegmentEnd[position] == INF) {
                dp[position] = 0;
                segmentEnd[position] = position;
            } else {
                dp[position] = 1 + dp[nextSegmentEnd[position]];
                segmentEnd[position] = segmentEnd[nextSegmentEnd[position]];
            }
        }

        for (int position = 1; position <= nodeCount; ++position) {
            prefixMax[position] = max(prefixMax[position - 1], maxRightIndex[position]);
        }

        int currentDepth = dp[0];
        if (currentDepth == 0) {
            cout << 0 << '\n';
            continue;
        }

        vector<int> selectedPoints;
        bool foundSolution = false;
        if (currentDepth % 2 == 0) {
            int rightMin = nextSegmentEnd[0];
            for (int position = 1; position <= rightMin && !foundSolution; ++position) {
                if (1 + dp[position] == currentDepth && segmentEnd[position] >= prefixMax[position]) {
                    int currentPoint = position;
                    selectedPoints.push_back(currentPoint);
                    while (nextSegmentEnd[currentPoint] != INF) {
                        currentPoint = nextSegmentEnd[currentPoint];
                        selectedPoints.push_back(currentPoint);
                    }
                    foundSolution = true;
                }
            }
        }

        if (!foundSolution) {
            int currentPoint = 0;
            while (nextSegmentEnd[currentPoint] != INF) {
                currentPoint = nextSegmentEnd[currentPoint];
                selectedPoints.push_back(currentPoint);
            }
            selectedPoints.push_back(0);
            if (currentDepth % 2 == 0) {
                selectedPoints.push_back(nodeCount);
            }
        }

        sort(selectedPoints.begin(), selectedPoints.end());
        int pairCount = selectedPoints.size() / 2;
        string output = to_string(pairCount) + '\n';
        for (int index = 0; index < pairCount; ++index) {
            output += to_string(selectedPoints[index] + 1) + " " + to_string(selectedPoints[index + pairCount]) + '\n';
        }

        cout << output;
    }

    return 0;
}