#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class RectangleOverlap_BruteForce {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        int left = max(rec1[0], rec2[0]);
        int right = min(rec1[2], rec2[2]);
        int bottom = max(rec1[1], rec2[1]);
        int top = min(rec1[3], rec2[3]);
        return left < right && bottom < top;
    }
};

class RectangleOverlap_Better {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        return !(rec1[2] <= rec2[0] || rec2[2] <= rec1[0] ||
                 rec1[3] <= rec2[1] || rec2[3] <= rec1[1]);
    }
};

class RectangleOverlap_Optimal {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        bool separatedHorizontally = rec1[2] <= rec2[0] || rec2[2] <= rec1[0];
        bool separatedVertically = rec1[3] <= rec2[1] || rec2[3] <= rec1[1];
        return !separatedHorizontally && !separatedVertically;
    }
};

int main() {
    vector<int> rec1 = {0, 0, 2, 2}, rec2 = {1, 1, 3, 3};
    RectangleOverlap_BruteForce bf; cout << (bf.isRectangleOverlap(rec1, rec2) ? "true" : "false") << endl;
    RectangleOverlap_Better btr; cout << (btr.isRectangleOverlap(rec1, rec2) ? "true" : "false") << endl;
    RectangleOverlap_Optimal opt; cout << (opt.isRectangleOverlap(rec1, rec2) ? "true" : "false") << endl;
    return 0;
}
