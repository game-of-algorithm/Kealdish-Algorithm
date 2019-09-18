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

// 先将结点的左子树一直遍历一直压栈，到树底部后开始弹栈。
// 先输出左子节点，如果右子节点为空或者已经访问过右子节点则输出自身，继续弹栈。
// 否则，压入右子节点，并继续压左子树。
void postOrder_nonrecursive(TreeNode *root) {
    
    if (root == nullptr)
    {
        return;
    }

    stack<TreeNode *> stack;
    TreeNode *lastVisitedNode = nullptr;
    TreeNode *node = root;
    
    stack.push(node);
    node = node->left;

    while (!stack.empty())
    {
        while (node != nullptr)
        {
            stack.push(node);
            node = node->left;
        }
        
        node = stack.top();
        stack.pop();

        cout<<node->val<<endl;
        lastVisitedNode = node;

        node = stack.top();

        if (node->right == nullptr || node->right == lastVisitedNode)
        {
            stack.pop();
            cout<<node->val<<endl;
            lastVisitedNode = node;
        } else {
            node = node->right;
        }
    }
    
    
    
}