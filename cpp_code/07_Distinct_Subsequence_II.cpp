#include <iostream>
#include <vector>
#include <set>
using namespace std;

class DistinctSubseq_II_BruteForce {
public:
    set<string> seen;
    void gen(string& s, int i, string cur) {
        if(i == (int)s.size()) {
            if(!cur.empty()) seen.insert(cur);
            return;
        }

        gen(s, i+1, cur);
        gen(s, i+1, cur+s[i]);
    }

    int distinctSubseqII(string s) {
        seen.clear(); gen(s, 0, "");
        long long MOD = 1000000007;
        return (int) ((long long) seen.size() % MOD);
    }
};

class DistinctSubseq_II_Better {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1000000007;
        vector<long long> endCount(26, 0);

        for(char ch : s) {
            long long total = 0;
            for(int c=0; c < 26; c++) total = (total + endCount[c]) % MOD;
            long long newVal = (total + 1) % MOD;
            endCount[ch - 'a'] = newVal;
        }

        long long answer = 0;
        for(int c=0; c<26; c++) answer = (answer + endCount[c]) % MOD;
        return (int) answer;
    }
};

class DistinctSubseq_II_Optimal {
public:
    int distinctSubseqII(string s) {
        int n = s.size(); int MOD = 1e9 + 7;
        vector<int> dp(n, 1);
        vector<int> countEndWith(26, 0);
        int sum = 0;
        for(int i=0; i<n; i++) {
            int idx = s[i] - 'a';
            dp[i] = (1 + sum - countEndWith[idx] + MOD) % MOD;
            sum = (sum + dp[i]) % MOD;
            countEndWith[idx] = (countEndWith[idx] + dp[i]) % MOD;
        }
        return sum;
    }
};

int main(){
    string s = "abc";
    DistinctSubseq_II_BruteForce bf; cout << bf.distinctSubseqII(s) << endl;
    DistinctSubseq_II_Better btr; cout << btr.distinctSubseqII(s) << endl;
    DistinctSubseq_II_Optimal opt; cout << opt.distinctSubseqII(s) << endl;
    return 0;
}