#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class NSNOLS_Better {
public:
    int numberOfSets(int n, int k) {
        const long long MOD = 1e9 + 7;
        vector<long long> dp(k + 1), sum(k + 1);
        dp[0] = 1; sum[0] = 1;

        for (int i = 1; i < n; i++) {
            vector<long long> ndp(k + 1);
            ndp[0] = 1;

            for (int j = 1; j <= k; j++) {
                ndp[j] = (dp[j] + sum[j - 1]) % MOD;
            }

            dp = ndp;
            for (int j = 0; j <= k; j++) {
                sum[j] = (sum[j] + dp[j]) % MOD;
            }
        }

        return dp[k];
    }
};

class NSNOLS_optimal {
public:
    static const long long MOD = 1000000007;

    long long power(long long a, long long b) {
        long long res = 1;

        while (b) {
            if (b & 1)
                res = res * a % MOD;

            a = a * a % MOD;
            b >>= 1;
        }

        return res;
    }

    int numberOfSets(int n, int k) {
        int N = n + k - 1; int R = 2 * k;
        vector<long long> fact(N + 1);
        fact[0] = 1;

        for (int i = 1; i <= N; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        long long numerator = fact[N];
        long long denominator = fact[R] * fact[N - R] % MOD;
        long long inverse = power(denominator, MOD - 2);

        return numerator * inverse % MOD;
    }
};


int main() {
    int n = 4; int k = 2;
    NSNOLS_Better btr;
    NSNOLS_Better opt;
    cout << "Output: " << btr.numberOfSets(n, k) << endl;
    cout << "Output: " << opt.numberOfSets(n, k) << endl;
}