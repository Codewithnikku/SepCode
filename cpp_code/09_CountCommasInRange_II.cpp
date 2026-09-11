#include <iostream>
using namespace std;

class CountCommasInRange_II_BruteForce {
public:
    string withCommas(long long x) {
        string raw = to_string(x);
        string result;
        int len = raw.size();
        for (int i = 0; i < len; i++) {
            if (i > 0 && (len - i) % 3 == 0)
                result += ','; 
            result += raw[i];
        }
        return result;
    }

    long long countCommas(long long n) {
        long long total = 0;
        for (long long x = 1; x <= n; x++) {
            for (char c : withCommas(x)) {
                if (c == ',')
                    total++;
            }
        }
        return total;
    }
};

class CountCommasInRange_II_Better {
public:
    int numDigits(long long x) {
        int d = 0;
        while (x > 0) { d++; x /= 10; }
        return d;
    }

    long long countCommas(long long n) {
        long long total = 0;
        for (long long x = 1; x <= n; x++) {
            int d = numDigits(x);
            total += (d - 1) / 3; 
        }
        return total;
    }
};

class CountCommasInRange_II_Optimal {
public:
    long long countCommas(long long n) {
        long long total = 0;
        long long low = 1, high = 9; 
        int d = 1;
        while (low <= n) {
            long long upper = min(high, n);
            long long count = upper - low + 1; 
            long long commas = (d - 1) / 3; 
            total += count * commas;
            low = high + 1; 
            high = high * 10 + 9;
            d++;
        }
        return total;
    }
};

int main() {
    long long n = 1002;
    CountCommasInRange_II_BruteForce bf; cout << bf.countCommas(n) << endl;
    CountCommasInRange_II_Better btr; cout << btr.countCommas(n) << endl;
    CountCommasInRange_II_Optimal opt; cout << opt.countCommas(n) << endl;
    return 0;
}