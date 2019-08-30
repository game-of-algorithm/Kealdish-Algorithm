/**
 * 编写一个方法 isBST() ，接受一个结点 Node 作为参数。
 * 若该结点是一个二叉查找树的根节点则返回 true，否则返回 false。
 * 
 * 1. 判断结点数是否与预期相符，保证不会存在环
 * 2. 判断根节点左子树的所有节点是否都小于根节点，根节点右子树的所有节点是否都大于根节点
 * 3. 判断其中是否含有等值的结点。
 */

#include <iostream>
#include <vector>
using std::vector;

struct TreeNode
{
    TreeNode *left;
    TreeNode *right;
    int val;
};

int cal_bst_count(TreeNode *node) {
    
    if (node == nullptr)
    {
        return 0;
    }
    
    return 1 + cal_bst_count(node->left) + cal_bst_count(node->right);
}

// 1
bool is_binary_tree(TreeNode *root, int n) {

    int count = cal_bst_count(root);
    
    return count == n;
}

// 2
bool is_ordered(TreeNode *node) {

    if (node == nullptr)
    {
        return true;
    }

    if (node->left != nullptr && node->left->val >= node->val)
    {
        return false;
    }
    
    if (node->right != nullptr && node->right->val <= node->val)
    {
        return false;
    }
    
    return is_ordered(node->left) && is_ordered(node->right);

}

bool check_duplicates_helper(TreeNode *node, vector<int> &vt) {
    if (node == nullptr)
    {
        return true;
    }
    
    if (vt[node->val] > 0)
    {
        return false;
    } else {
        vt[node->val]++;
    }
    
    return check_duplicates_helper(node->left, vt) && check_duplicates_helper(node->right, vt);
}

// 3
bool has_no_duplicates(TreeNode *node, int n) {

    vector<int> vt(n, 0);
    return check_duplicates_helper(node, vt);
}

bool isBST(TreeNode *root, int n) {
    if (root == nullptr)
    {
        return false;
    }

    if (!is_binary_tree(root, n))
    {
        return false;
    }
    
    if (!is_ordered(root))
    {
        return false;
    }
    
    if (!has_no_duplicates(root, n))
    {
        return false;
    }
    
    return true;
}