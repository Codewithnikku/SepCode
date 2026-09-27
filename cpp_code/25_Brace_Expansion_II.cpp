#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cctype>
using namespace std;

class BraceExpansion_II {

public:

    string s;
    int n;
    int idx = 0;

    set<string> performUnion() {
        set<string> result;

        while (true) {
            set<string> temp = performConcat();

            result.insert(begin(temp), end(temp));

            if (idx < n && s[idx] == ',')
                idx++;
            else
                break;
        }

        return result;
    }

    set<string> performConcat() {
        set<string> result = {""};

        while (idx < n && (s[idx] == '{' || isalpha(s[idx]))) {
            set<string> temp = getUnit();

            set<string> concatResult;

            for (const string& left : result) {
                for (const string& right : temp) {
                    concatResult.insert(left + right);
                }
            }

            result = concatResult;
        }

        return result;
    }

    set<string> getUnit() {

        set<string> result;

        if (isalpha(s[idx])) {
            result.insert(string(1, s[idx]));
            idx++;
        }
        else if (s[idx] == '{') {
            idx++;

            result = performUnion();

            idx++;
        }

        return result;
    }

    vector<string> braceExpansionII(string expression) {

        s = expression;
        n = expression.length();
        idx = 0;

        set<string> st = performUnion();

        vector<string> result(begin(st), end(st));

        return result;
    }
};