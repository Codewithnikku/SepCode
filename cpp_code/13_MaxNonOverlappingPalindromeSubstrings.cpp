#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class MNOPS_BruteForce {
public:
    int dfs(string& s, int start, int k) {
        if (start >= (int)s.size()) return 0;
        int answer = dfs(s, start + 1, k);
        for (int end = start + k - 1; end < (int)s.size(); end++) {
            bool palindrome = true;
            for (int left = start, right = end; left < right; left++, right--)
                if (s[left] != s[right]) palindrome = false;
            if (palindrome) answer = max(answer, 1 + dfs(s, end + 1, k));
        }
        return answer;
    }

    int maxPalindromes(string s, int k) {
        return dfs(s, 0, k);
    }
};

class MNOPS_Better {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();
        vector<vector<bool>> palindrome(n, vector<bool>(n, false));
        for (int length = 1; length <= n; length++)
            for (int left = 0; left + length <= n; left++) {
                int right = left + length - 1;
                palindrome[left][right] = s[left] == s[right] &&
                    (length <= 2 || palindrome[left + 1][right - 1]);
            }
        vector<int> dp(n + 1);
        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i - 1];
            if (i >= k)
                for (int start = 0; start <= i - k; start++)
                    if (palindrome[start][i - 1])
                        dp[i] = max(dp[i], dp[start] + 1);
        }
        return dp[n];
    }
};

class MNOPS_Optimal {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();
        vector<int> dp(n + 1);
        for (int center = 0; center < n; center++) {
            for (int left = center, right = center; left >= 0 && right < n && s[left] == s[right]; left--, right++)
                if (right - left + 1 >= k) dp[right + 1] = max(dp[right + 1], dp[left] + 1);
            for (int left = center - 1, right = center; left >= 0 && right < n && s[left] == s[right]; left--, right++)
                if (right - left + 1 >= k) dp[right + 1] = max(dp[right + 1], dp[left] + 1);
            if (center + 1 < n) dp[center + 1] = max(dp[center + 1], dp[center]);
        }
        return dp[n];
    }
};

int main() {
    string s = "abaccdbbd"; int k = 3;
    MNOPS_BruteForce bf; cout << bf.maxPalindromes(s, k) << endl;
    MNOPS_Better btr; cout << btr.maxPalindromes(s, k) << endl;
    MNOPS_Optimal opt; cout << opt.maxPalindromes(s, k) << endl;
    return 0;
}
