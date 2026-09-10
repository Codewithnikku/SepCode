#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <unordered_map>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class CNEAS_BruteFrorce
{
public:
    pair<int, int> sumAndCount(TreeNode *node)
    {
        if (!node)
            return {0, 0};
        auto l = sumAndCount(node->left);
        auto r = sumAndCount(node->right);
        return {node->val + l.first + r.first, 1 + l.second + r.second};
    }
    int count = 0;
    void visitEveryNode(TreeNode *node)
    {
        if (!node)
            return;
        auto subtree = sumAndCount(node);
        if (subtree.first / subtree.second == node->val)
            count++;
        visitEveryNode(node->left);
        visitEveryNode(node->right);
    }
    int averageOfSubtree(TreeNode *root)
    {
        count = 0;
        visitEveryNode(root);
        return count;
    }
};

class CNEAS_Better
{
public:
    unordered_map<TreeNode *, pair<int, int>> memo; // node -> (subtree sum, subtree count)
    pair<int, int> computeAndStore(TreeNode *node)
    {
        if (!node)
            return {0, 0};
        auto l = computeAndStore(node->left);
        auto r = computeAndStore(node->right);
        pair<int, int> result = {node->val + l.first + r.first, 1 + l.second + r.second};
        memo[node] = result; // store it for the second pass to reuse
        return result;
    }
    int averageOfSubtree(TreeNode *root)
    {
        memo.clear();
        computeAndStore(root);
        int count = 0;
        function<void(TreeNode *)> checkAll = [&](TreeNode *node)
        {
            if (!node)
                return;
            auto subtree = memo[node];
            if (subtree.first / subtree.second == node->val)
                count++;
            checkAll(node->left);
            checkAll(node->right);
        };
        checkAll(root);
        return count;
    }
};

class CNEAS_Optimal
{
public:
    int count = 0;
    pair<int, int> dfs(TreeNode *node)
    {
        if (!node)
            return {0, 0};
        auto l = dfs(node->left);
        auto r = dfs(node->right);
        int sum = node->val + l.first + r.first;
        int cnt = 1 + l.second + r.second;
        if (sum / cnt == node->val)
            count++; 
        return {sum, cnt};
    }
    int averageOfSubtree(TreeNode *root)
    {
        count = 0;
        dfs(root);
        return count;
    }
};

int main()
{
    TreeNode *n0 = new TreeNode(0); TreeNode *n1 = new TreeNode(1);
    TreeNode *n6 = new TreeNode(6); TreeNode *n8 = new TreeNode(8, n0, n1);
    TreeNode *n5 = new TreeNode(5, nullptr, n6);TreeNode *root = new TreeNode(4, n8, n5);

    CNEAS_BruteFrorce bf; cout << bf.averageOfSubtree(root) << endl;
    CNEAS_Better btr; cout << btr.averageOfSubtree(root) << endl;
    CNEAS_Optimal opt; cout << opt.averageOfSubtree(root) << endl;
    return 0;
}