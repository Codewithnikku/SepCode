#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <unordered_map>
using namespace std;

class TNS_TargetSum_BruteForce {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size(), answer = INT_MAX;
        vector<pair<int, int>> valid;
        for (int start = 0; start < n; start++) {
            int sum = 0;
            for (int end = start; end < n; end++) {
                sum += arr[end];
                if (sum == target) valid.push_back({start, end});
            }
        }
        for (auto first : valid)
            for (auto second : valid)
                if (first.second < second.first || second.second < first.first)
                    answer = min(answer, first.second - first.first + second.second - second.first + 2);
        return answer == INT_MAX ? -1 : answer;
    }
};

class TNS_TargetSum_Better {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size(), answer = INT_MAX;
        vector<int> best(n, INT_MAX);
        unordered_map<int, int> first;
        first[0] = -1;
        int prefix = 0, shortest = INT_MAX;
        for (int i = 0; i < n; i++) {
            prefix += arr[i];
            if (first.count(prefix - target)) {
                int start = first[prefix - target] + 1;
                int length = i - start + 1;
                if (start > 0 && best[start - 1] != INT_MAX)
                    answer = min(answer, best[start - 1] + length);
                shortest = min(shortest, length);
            }
            best[i] = shortest;
            if (!first.count(prefix)) first[prefix] = i;
        }
        return answer == INT_MAX ? -1 : answer;
    }
};

class TNS_TargetSum_Optimal {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size(), answer = INT_MAX;
        vector<int> best(n + 1, INT_MAX);
        unordered_map<int, int> last;
        last[0] = 0;
        int prefix = 0;
        for (int i = 1; i <= n; i++) {
            prefix += arr[i - 1];
            best[i] = best[i - 1];
            if (last.count(prefix - target)) {
                int start = last[prefix - target], length = i - start;
                if (best[start] != INT_MAX)
                    answer = min(answer, best[start] + length);
                best[i] = min(best[i], length);
            }
            last[prefix] = i;
        }
        return answer == INT_MAX ? -1 : answer;
    }
};

int main() {
    vector<int> arr = {3, 2, 2, 4, 3}; int target = 3;
    TNS_TargetSum_BruteForce bf; cout << bf.minSumOfLengths(arr, target) << endl;
    TNS_TargetSum_Better btr; cout << btr.minSumOfLengths(arr, target) << endl;
    TNS_TargetSum_Optimal opt; cout << opt.minSumOfLengths(arr, target) << endl;
    return 0;
}
