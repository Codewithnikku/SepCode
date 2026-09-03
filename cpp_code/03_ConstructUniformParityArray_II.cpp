#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

class CUPA_II_BruteForce
{
public:
    bool feasible(vector<int> &nums1, int target)
    {
        int n = nums1.size();
        for (int i = 0; i < n; i++)
        {
            bool found = (((nums1[i] % 2) + 2) % 2 == target);
            if (!found)
            {
                for (int j = 0; j < n; j++)
                {
                    if (j = i)
                        continue;
                    int diff = nums1[i] - nums1[j];
                    if (diff < 1)
                        continue;
                    if (diff % 2 == target)
                    {
                        found = true;
                        break;
                    }
                }
            }
            if (!found)
                return false;
        }
        return true;
    }

    bool uniformArray(vector<int> &nums1)
    {
        return feasible(nums1, 0) || feasible(nums1, 1);
    }
};

class CUPA_II_Better
{
public:
    bool uniformArray(vector<int> &nums1)
    {
        long long smallestOdd = LLONG_MAX;
        for (int x : nums1)
            if (x % 2 != 0)
                smallestOdd = min(smallestOdd, (long long)x);
        for (int target = 0; target <= 1; target++)
        {
            bool ok = true;
            for (int x : nums1)
            {
                if (x % 2 == target)
                    continue; // direct works
                if (smallestOdd != LLONG_MAX && smallestOdd < x)
                    continue; // can flip via smallestOdd
                ok = false;
                break;
            }
            if (ok)
                return true;
        }
        return false;
    }
};

class CUPA_II_Optimal
{
public:
    bool uniformArray(vector<int> &nums1)
    {
        int minVal = INT_MAX;
        bool hasOdd = false;
        for(int x : nums1) {
            minVal = min(minVal, x);
            if(x % 2 != 0) hasOdd = true;
        }
        bool minIsOdd = (minVal % 2 != 0);
        return minIsOdd || !hasOdd;
    }
};

int main()
{
    vector<int> nums1 = {1, 2, 3};
    CUPA_II_BruteForce solver_bf;
    CUPA_II_Better solver_btr;
    CUPA_II_Optimal solver_opt;
    cout << (solver_bf.uniformArray(nums1) ? "true" : "false") << endl;
    cout << (solver_btr.uniformArray(nums1) ? "true" : "false") << endl;
    cout << (solver_opt.uniformArray(nums1) ? "true" : "false") << endl;
    return 0;
}