#include <iostream>
#include <vector>
using namespace std;

class DistinctSubsequences_BruteForce {
public:
    int countWays (string& s, string& t, int i, int j) {
        if(j == (int) t.size()) return 1;
        if(i == (int) s.size()) return 0;

        int skip = countWays(s, t, i+1, j);
        int take = 0;
        if(s[i] == t[j]) 
            take = countWays(s, t, i+1, j+1);

        return skip + take;
    }

    int numDistinct(string s, string t) {
        return countWays(s, t, 0, 0);
    }
};

class DistinctSubsequences_Better {
public:
    vector<vector<int>> memo;
    int countWays(string& s, string& t, int i, int j) {
        if(j == (int) t.size()) return 1;
        if(i == (int) s.size()) return 0;
        if(memo[i][j] != -1) return memo[i][j];

        int skip = countWays(s, t, i+1, j); int take = 0;
        if(s[i] == t[j]) 
            take = countWays(s, t, i+1, j+1);

        memo[i][j] = skip + take;
        return memo[i][j];
    }

    int numDistinct(string s, string t) {
        memo = vector<vector<int>>(s.size(), vector<int>(t.size(), -1));
        return countWays(s, t, 0, 0);
    }
};

class DistinctSubsequences_Optimal {
public:
    int numDistinct(string s, string t) {
        int n = s.size(); int m = t.size();
        vector<int> dp(m+1, 0);
        dp[0] = 1;

        for(int i=1; i<=n; i++) {
            for(int j=m; j >= 1; j--) {
                if(s[i-1] == t[j-1]) {
                    dp[j] += dp[j-1];
                }
            }
        }
        return dp[m];
    }
};

int main(){
    string s = "rabbbit", t = "rabbit";
    DistinctSubsequences_BruteForce dss_bf; cout << dss_bf.numDistinct(s, t) << endl;
    DistinctSubsequences_Better dss_btr; cout << dss_btr.numDistinct(s, t) << endl;
    DistinctSubsequences_Optimal dss_opt; cout << dss_opt.numDistinct(s, t) << endl;
    return 0;
}