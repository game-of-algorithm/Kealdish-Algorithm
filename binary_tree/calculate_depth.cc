/**
 * 计算树的深度
 */

#include <iostream>
using std::max;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
};

int calculate_depth(TreeNode *root) {
    if (root == nullptr)
    {
        return 0;
    }
    
    return max(calculate_depth(root->left), calculate_depth(root->right)) + 1;
}
