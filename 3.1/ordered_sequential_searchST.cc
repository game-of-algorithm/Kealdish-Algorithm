/**
 * 3.1.3 开发一个符号表的实现 OrderedSequentialSearchST，使用有序链表来实现我们的有序符号表 API
 */

#include <string>
using std::string;

struct Node {
    string key;
    int val;
    Node *prev;
    Node *next;

    Node() {
        key = "";
        val = 0;
        prev = nullptr;
        next = nullptr;
    }
};

class OrderedSequentialSearchST {
public:
    OrderedSequentialSearchST() {
        n = 0;
        first = nullptr;
        last = nullptr;
    }

    bool contains(string key) {
        Node *tmp = first;
        while (tmp != nullptr && less(key, tmp->key))
        {
            tmp = tmp->next;
        }
        if (tmp != nullptr && tmp->key == key) {
            return true;
        }

        return false;
    }

    bool empty() {
        return n == 0;
    }

    void put(string key, int val) {
        delete(key);

        Node *tmp = new Node();
        tmp->key = key;
        tmp->val = val;

        Node *left;
        Node *right = first;
        while (right != nullptr && less(right->key, tmp->key))
        {
            left = right;
            right = right->next;
        }
        
        insert(left, right, tmp);

        if (left == nullptr)
        {
            first = tmp;
        }

        if (right == nullptr)
        {
            last = tmp;
        }
        
        n++;
        
    }

    string maxKey() {
        return last == nullptr ? "" : last->key;
    }

    string minKey() {
        return first == nullptr ? "" : first->key;
    }

    // 小于 Key 的键的数量
    int rank(string key) {
        int count = 0;
        Node *tmp = first;
        while (tmp != nullptr && less(tmp->key, key))
        {
            tmp = tmp->next;
            count++;
        }
        return count;
    }

    // 获得排名为 k 的键
    string select(int k) {
        if (k >= n)
        {
            return "";
        }
        
        node *tmp = first;
        for (int i = 0; i < k; i++)
        {
            tmp = tmp->next;
        }
        
        return tmp->key;
    }

    void delete(string key) {
        node *tmp = first;
        while (tmp != nullptr && tmp->key != key)
        {
            tmp = tmp->next;
        }
        
        if (tmp == nullptr)
        {
            return;
        }
        
        delete(tmp);
    }

    void deleteMax() {
        if (n > 0) {
            delete(last);
        }
    }

    void deleteMin() {
        if (n > 0)
        {
            delete(first);
        }
        
    }

    int get(string key) {
        Node *node = first;
        while (node != nullptr && greater(key, node->key))
        {
            node = node->next;
        }

        if (node != nullptr && node->key == key)
        {
            return node->val;
        }
        
        return 0;
        
    }

private:
    Node *first;
    Node *last;
    int n;

    void delete(Node *&node) {
        Node *prev = node->prev;
        Node *next = node->next;

        if (prev == nullptr)
        {
            this->first = next;
        } else {
            prev.next = next;
        }

        if (next == nullptr)
        {
            this->last = prev;
        }
        
        this->n--;
    }

    bool less(string key1, string key2) {
        return key1 < key2;
    }

    bool greater(string key1, string key2) {
        return key1 > key2;
    }

    void insert(Node *node1, Node *node2, Node *node3) {
        node3->prev = node1;
        node3->next = node2;

        if (node1 != nullptr)     
        {
            node1->next = node3;
        }
        
        if (node2 != nullptr )
        {
            node2->next = node3;
        }
        
    }
};