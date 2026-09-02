#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class CUPA_I_BruteForce {
public:
    bool feasible(vector<int>& nums1, int target) {
        int n = nums1.size();
        for(int i=0; i<n; i++) {
            bool found = (nums1[i] % 2 == target);
            if(!found) {
                for(int j=0; j<n; j++) {
                    if(j==i) continue;
                    int diff = nums1[i] - nums1[j];
                    int p = ((diff % 2) + 2) % 2;
                    if(p == target) { found = true; break; }
                }
            }
            if(!found) return false;
        }
        return true;
    }

    bool uniformArray(vector<int>& nums1) {
        return feasible(nums1, 0) || feasible(nums1, 1);
    }
};

class CUPA_I_better {
public:
    bool uniformArray(vector<int>& nums1) {
        int oddCount = 0; 
        for(int x : nums1)
            if(x % 2 != 0) oddCount++;
        bool feasibleEven = (oddCount == 0) || (oddCount >= 2);
        bool feasibleOdd = (oddCount >= 1);

        return feasibleEven || feasibleOdd;
    }
};

class CUPA_I_optimal {
public:
    bool uniformArray(vector<int>& nums1) {
        int n = nums1.size(); vector<int> nums2(n);
        bool allOdd = all_of(nums1.begin(), nums1.end(), [](int x) {return x % 2 != 0; });
        bool allEven = all_of(nums1.begin(), nums1.end(), [](int x) {return x % 2 == 0; });

        if(allOdd || allEven) { nums2 = nums1; }
        else {
            int oddIdx = -1; int evenIdx = -1;
            for(int i=0; i<n; i++) {
                if(nums1[i] % 2) oddIdx = i; else evenIdx = i;
            }
            for(int i=0; i<n; i++) {
                int j = (nums1[i] % 2) ? evenIdx : oddIdx;
                nums2[i] = nums1[i] - nums1[j];
            }
        }
        return true;
    }
};

int main(){
    vector<int> nums1 = {2, 3};
    CUPA_I_BruteForce solver_bf;
    cout << (solver_bf.uniformArray(nums1) ? "true" : "false") << endl;
    CUPA_I_better solver_btr;
    cout << (solver_btr.uniformArray(nums1) ? "true" : "false") << endl;
    CUPA_I_optimal solver_opt;
    cout << (solver_opt.uniformArray(nums1) ? "true" : "false") << endl;
    return 0;
}