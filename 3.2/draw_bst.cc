/**
 * 绘图。为二叉查找树添加一个方法 draw()，按照正文中的样式将树绘制出来。
 */

/**
 * 
  2
 /a\
1aaa3
 *
 */

#include <iostream>
#include <vector>
#include <string>
using std::cout;
using std::vector;
using std::string;
using std::to_string;
using std::endl;

int min_x = 0;

struct TreeNode
{
    TreeNode *left;
    TreeNode *right;
    int val;
    int x;
};

struct Symbol {
    string val;
    int x;
};

void dfs(TreeNode *node, vector<vector<TreeNode *> > &vt, vector<vector<Symbol *> > &sym_vt, int h) {
    if (node == nullptr)
    {
        return ;
    }

    if (h >= vt.size())
    {
        vector<TreeNode *> sub_vt;
        sub_vt.push_back(node);
    } else {
        vt[h].push_back(node);
    }
    
    if (node->left != nullptr)
    {
        Symbol *left = new Symbol();
        left->val = "/";
        left->x = node->x - 1;

        if (h >= sym_vt.size())
        {
            vector<Symbol *> sub_vt;
            sub_vt.push_back(left);
        } else {
            sym_vt[h].push_back(left);
        }

        node->left->x = node->x - 2;
        min_x = node->left->x;
        dfs(node->left, vt, sym_vt, h + 1);
    }
    
    if (node->right != nullptr)
    {
        Symbol *right = new Symbol();
        right->val = "\\";
        right->x = node->x + 1;

        if (h >= sym_vt.size())
        {
            vector<Symbol *> sub_vt;
            sub_vt.push_back(right);
        } else {
            sym_vt[h].push_back(right);
        }
        node->right->x = node->x + 2;
        dfs(node->right, vt, sym_vt, h + 1);
    }
    
}

void draw(TreeNode *root) {
    
    if (root == nullptr)
    {
        return;
    }

    vector<vector<TreeNode *> > vt;
    vector<vector<Symbol *> > sym_vt;
    dfs(root, vt, sym_vt, 0);
    
    for (int k = 0; k < vt.size(); k++)
    {
        vector<TreeNode *> arr = vt[k];
        vector<Symbol *> symbols = sym_vt[k];

        int n1 = arr.back()->x - min_x;
        int n2 = symbols.back()->x - min_x;
        vector<string> str_vt(n1, " ");
        vector<string> symb_vt(n2, " ");

        for (int i = 0; i < arr.size(); i++)
        {
            TreeNode *node = arr[i];
            str_vt[node->x - min_x] = to_string(node->val);
        }

        for (int i = 0; i < symbols.size(); i++)
        {
            Symbol *sym = symbols[i];
            symb_vt[sym->x - min_x] = sym->val;
        }

        for (string s : str_vt)
        {
            cout<<s;
        }

        cout<<endl;

        for (string s : symb_vt)
        {
            cout<<s;
        }

        cout<<endl;
    }
    
}