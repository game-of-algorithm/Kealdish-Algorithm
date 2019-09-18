#include <iostream>
#include <stack>
using std::cout;
using std::endl;
using std::stack;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
};

/**
 * 1. 先序遍历
 */

void preorder_recursive(TreeNode *root) {
    if (root == nullptr)
    {
        return;
    }

    cout<<root->val<<endl;
    
    preorder_recursive(root->left);
    preorder_recursive(root->right);
}

void preorder_nonrecursive(TreeNode *root) {
    if (root == nullptr)
    {
        return;
    }

    stack<TreeNode *> stack;
    stack.push(root);

    while (!stack.empty())
    {
        TreeNode *node = stack.top();
        cout<<node->val<<endl;
        stack.pop();

        if (node->right != nullptr)
        {
            stack.push(node->right);
        }

        if (node->left != nullptr)
        {
            stack.push(node->left);
        }
        
    }
    
}

/**
 * 2. 中序遍历
 */

void inorder_recursive(TreeNode *root) {
    if (root == nullptr)
    {
        return;
    }

    inorder_recursive(root->left);
    cout<<root->val<<endl;
    inorder_recursive(root->right);
    
}

void inorder_noncursive(TreeNode *root) {
    if (root == nullptr)
    {
        return;
    }

    stack<TreeNode *> stack;
    
    TreeNode *node = root;
    // 先处理左子树，后处理右子树

    while (node != nullptr || !stack.empty())
    {
        // 先处理左子树，将左子树按序压入栈中
        while (node != nullptr)
        {
            stack.push(node);
            node = node->left;
        }
        
        node = stack.top();
        stack.pop();
        cout<<node->val<<endl;
        node = node->right; // 处理右子树

    }
    
}

/**
 * 后序遍历
 */

void postOrder_recursive(TreeNode *root) {
    if (root == nullptr)
    {
        return;
    }

    postOrder_recursive(root->left);
    postOrder_recursive(root->right);
    cout<<root->val<<endl;
    
}

void postOrder_nonrecursive(TreeNode *root) {
    if (root == nullptr)
    {
        return;
    }

    stack<TreeNode *> stack;

    stack.push(root);

    while (!stack.empty())
    {
        TreeNode *node = stack.top();
        stack.pop();

        if (node->left == nullptr && node->right == nullptr)
        {
            cout<<node->val<<endl;
        } else {
            stack.push(node);

            if (node->right != nullptr)
            {
                stack.push(node->right);
            }

            if (node->left != nullptr)
            {
                stack.push(node->left);
            }
            
        }
        
    }
    
    
}