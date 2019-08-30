/**
 * 按层遍历。编写一个方法 printLevel() ，接受一个结点 Node 作为参数，按照层级顺序打印以该结点为根的
 * 子树。提示：使用队列。
 */

#include <deque>
#include <iostream>
using std::deque;
using std::cout;

struct TreeNode
{
    TreeNode *left;
    TreeNode *right;
    int val;
};

void print_level(TreeNode *root) {
    if (root == nullptr)
    {
        return;
    }

    deque<TreeNode *> dq;

    dq.push_back(root);
    
    while (!dq.empty())
    {
        TreeNode *node = dq.front();
        cout << node->val << ' ';
        dq.pop_front();

        if (node->left != nullptr)
        {
            dq.push_back(node->left);
        }

        if (node->right != nullptr)
        {
            dq.push_back(node->right);
        }
        
    }
    
}
