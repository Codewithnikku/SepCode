#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class SBI_II_BruteForce {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int mx = INT_MIN;
            for (int a = 0; a <= i; a++) mx = max(mx, nums[a]); 

            int mn = INT_MAX;
            for (int b = i; b < n; b++) mn = min(mn, nums[b]); 
            
            if ((long long)mx - mn <= k) return i;
        } 
        return -1;
    }
};

class SBI_II_Better {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> prefixMax(n), suffixMin(n);
        prefixMax[0] = nums[0];
        for (int i = 1; i < n; i++)
            prefixMax[i] = max(prefixMax[i - 1], nums[i]);
        suffixMin[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--)
            suffixMin[i] = min(suffixMin[i + 1], nums[i]);
        for (int i = 0; i < n; i++) {
            if ((long long)prefixMax[i] - suffixMin[i] <= k)
                return i;
        }
        return -1;
    }
};

class SBI_II_Optimal {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> suffixMin(n); suffixMin[n-1] = nums[n-1];
        for(int i=n-2; i>=0; i--) 
            suffixMin[i] = min(suffixMin[i+1], nums[i]);
        int rngMax = INT_MIN;
        for(int i=0; i<n; i++) {
            rngMax = max(rngMax, nums[i]);
            if((long long) rngMax - suffixMin[i] <= k) return i;
        }
        return -1;
    }
};

int main(){
    vector<int> nums = {5, 0, 1, 4}; int k = 3;
    SBI_II_BruteForce sbi_bf; cout << sbi_bf.firstStableIndex(nums, k) << endl;
    SBI_II_Better sbi_btr; cout << sbi_btr.firstStableIndex(nums, k) << endl;
    SBI_II_Optimal sbi_opt; cout << sbi_opt.firstStableIndex(nums, k) << endl;
    return 0;
}