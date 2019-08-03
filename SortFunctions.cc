/**
 * 选择排序
 * 
 * 在待排序区中找到数组中最小的元素，与待排序区队首元素位置进行交换，变成有序区。
 * 
 */

#include <vector>
#include <algorithm>
using std::vector;
using std::swap;

void chooseSort(vector<int> vt) {
    
    for (int i = 0; i < vt.size(); i++)
    {
        int minIndex = i;

        for (int j = i; j < vt.size(); j++)
        {
            if (vt[j] < vt[minIndex])
            {
                minIndex = j;
            }
            
        }

        if (minIndex != i)
        {
            swap(vt[minIndex], vt[i]);
        }
        
    }
    
}

/**
 * 插入排序
 * 
 * 取待排序区队首元素插入到有序区中合适的位置，再循环往复。
 */

void insertSort(vector<int> vt) {

    for (int i = 0; i < vt.size(); i++)
    {
        int cur = vt[i];
        for (int j = 0; j < i; j++)
        {
            if (cur < vt[j])
            {
                for (int k = i - 1; k >= j; k--)
                {
                    vt[k+1] = vt[k];
                }
                
                vt[j] = cur;
                break;
            }
            
        }
        
    }
    
}

/**
 * 希尔排序
 * 
 * 将数组不断拆分为不同步长的小的数组，然后在小数组中使用插入排序
 */

void shellSort(vector<int> vt) {
    // 数组长度
    int n = vt.size();

    // 步长
    int h = n / 3 + 1;
    
    while (h >= 1)
    {
        for (int i = h; i < n; i++)
        {
            int e = vt[i];
            int j;

            // 对 vt[i], vt[i-h], vt[i-2h] ... 进行插入排序
            for (int j = i; j >= h && e < vt[j-h] ; j-=h)
            {
                vt[j] = vt[j-h];
            }
            
            vt[j] = e;
        }
        
        h = h / 3 + 1;
    }

}

/**
 * 归并排序
 * 
 * 通过递归将两个有序的数组合并成更大的数组
 * 
 */

void mergeVector(vector<int> a, int first, int mid, int last, int *temp)  
{  
    int i = first, j = mid + 1;  
    int m = mid,   n = last;  
    int k = 0;  
      
    while (i <= m && j <= n)  
    {  
        if (a[i] <= a[j])  
            temp[k++] = a[i++];  
        else  
            temp[k++] = a[j++];  
    }  
      
    while (i <= m)  
        temp[k++] = a[i++];  
      
    while (j <= n)  
        temp[k++] = a[j++];  
      
    for (i = 0; i < k; i++)  
        a[first + i] = temp[i];  
}

void mergesort(vector<int> a, int first, int last, int *temp)  
{  
    if (first < last)  
    {  
        int mid = (first + last) / 2;  
        mergesort(a, first, mid, temp);    //左边有序  
        mergesort(a, mid + 1, last, temp); //右边有序  
        mergeVector(a, first, mid, last, temp); //再将二个有序数列合并  
    }  
}

bool MergeSort(vector<int> a)  
{
    int n = a.size();
    int *p = new int[n];  
    if (p == NULL)  
        return false;  
    mergesort(a, 0, a.size() - 1, p);  
    delete[] p;  
    return true;  
}

/**
 * 2.1.2 在选择排序中，一个元素最多能被交换多少次？平均可能被交换多少次？
 * 
 * 一个元素最多能被交换 N 次。举例：9 1 2 3 4 5 6 7 8 8
 * 
 * (0 + 1 + 2 + 3 + ... + N) / N + 1 = N/2
 *  平均可能被交换 N/2 次
 */

/**
 * 2.1.6 在所有主键相同时，选择排序和插入排序谁更快？
 * 
 * 选择排序比较次数为 N-1 + ... + N / 2 + ... + 2 + 1 = N / 2 * (N - 1)，交换次数为 0，总计为 N * (N - 1) / 2
 * 插入排序执行次数为比较 N - 1 次，交换 0 次（从有序区尾部开始比较）
 * 插入排序更快
 */

/**
 * 2.1.7 对于逆序数组，选择排序和插入排序谁更快？
 * 
 * 选择排序比较次数为 N-1 + ... + N / 2 + ... + 2 + 1 = N / 2 * (N - 1)，交换次数为 N / 2，总计为 N * N / 2
 * 插入排序比较次数为 0 + 1 + 2 + ... + N - 1 = (N - 1) / 2 * N，交换次数为 0 + 1 + 3 + 4 + ... + N = (N + 1)(N + 1) / 2 - 2
 * 
 * 选择排序更快
 */

/**
 * 2.1.14 说说你会如何将一副扑克牌排序，限制条件是只能查看最上面的两张牌，交换最上面的两张牌，或是将最上面的两张牌放到最下面。
 * 
 * 选择排序。记下每次排序起始的号码，比较最上面的两张牌，将大的放到最上面，然后放到最下面。如此循环，直到再次遇到记下的那张牌，
 * 意味着一轮循环结束。
 * 将最小的那张牌交换到最上面，再放到最下面，变成有序区，并记下有序区的数字。
 * 再次循环，找出待序区的最小牌，再放到最下面。
 * 一直循环往复，直到有序区变满。
 */

/**
 * 2.1.19 希尔排序的最坏情况。用 1 到 100 构造一个含有 100 个元素的数组并用希尔排序和递增序列 1 4 13 40 对其排序，使比较的次数尽可能多。
 */

/**
 * 100,92,84,76,68,60,52,44,36,28,21,14,7,
 * 99,91,83,75,67,59,51,43,35,27,20,13,6,
 * 98,90,82,74,66,58,50,42,34,26,19,12,5,
 * 97,89,81,73,65,57,49,41,33,25,18,11,4,
 * 96,88,80,72,64,56,48,40,32,24,17,10,3,
 * 95,87,79,71,63,55,47,39,31,23,16,9,2,
 * 94,86,78,70,62,54,46,38,30,22,15,8,1,
 * 93,85,77,69,61,53,45,37,29
 */

/**
 * 2.1.20 希尔排序的最好情况。最好情况是什么？证明你的结论。
 * 
 * 最好情况是比较次数的量级是 O(N)，最好的情况是正序序列。
 * 
 */

/**
 * 2.2.4 是否当且仅当两个输入的子数组都有序时，原地归并的抽象方法才能得到正确结果吗？证明结论或出个反例。
 * 
 * 是的，归并排序并不会改变原输入数组中元素的前后相对位置，如果子数组在归并前无序，那么归并后仍将无序。
 * 
 */


/**
 * 2.2.7 证明归并排序的比较次数是单调递增的（即对于 N > 0 ，C(N+!) > C(N) ）
 * 
 * 由命题 F 得出数组长度为 N 时比较次数为 C(N) = NlgN,该函数是单调递增函数，因而，比较次数也是单调递增的。
 */

/**
 * 2.2.17 实现对链表的自然排序
 */

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

/**
 * 找到链表的中间节点
 */
ListNode *findMiddle(ListNode *head)
{
    ListNode *middle = head;
    ListNode *fastNode = head->next;
    while(fastNode != NULL && fastNode->next != NULL)
    {
        middle = middle->next;
        fastNode = fastNode->next->next;
    }
    return middle;
}

/**
 * 合并两个有序的链表
 */
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
    if (l1 == NULL)
        return l2;
    if (l2 == NULL)
        return l1;

    ListNode *pre = new ListNode(0);
    ListNode *head = pre;

    while (l1 != NULL && l2 !=NULL)
    {
        if(l1->val > l2->val)
        {
            head->next = l2;
            l2 = l2->next;            
        }
        else
        {
            head->next = l1;
            l1 = l1->next; 
        }
        head = head->next;
    }

    if (l1 == NULL)
    {
        head->next = l2;
    }

    if (l2 == NULL)
    {
        head->next = l1;
    }

    return pre->next;
}

/**
 * 递归合并排序
 */
ListNode *sortList(ListNode *head) 
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    ListNode *middle = findMiddle(head);
    ListNode *right = sortList(middle->next);
    middle->next = NULL;
    ListNode *left = sortList(head);
    return mergeTwoLists(left, right);
}

/**
 * 2.1.20 间接排序。编写一个不改变数组的归并排序，它返回一个 int[] 数组 perm，其中 perm[i] 的值是原数组中第 i 小的元素的位置。
 */

vector<int> merge(vector<int> leftVt, vector<int> rightVt) {
    vector<int> vt;

    int l = 0;
    int r = 0;

    while (l < leftVt.size() && r < rightVt.size())
    {
        if (leftVt[l] < rightVt[r])
        {
            vt.push_back(leftVt[l++]);
        } else {
            vt.push_back(rightVt[r++]);
        }
        
    }

    if (l < leftVt.size())
    {
        vt.push_back(leftVt[l++]);
    }
    
    if (r < rightVt.size())
    {
        vt.push_back(rightVt[r++]);
    }
    
    return vt;
}

vector<int> sortList(vector<int> vt, int start, int end) {
    if (start < end)
    {
        int mid = (start + end) / 2;
        vector<int> tmp1 = sortList(vt, start, mid);
        vector<int> tmp2 = sortList(vt, mid + 1, end);
        return merge(tmp1, tmp2);
    } else {
        vector<int> temp;
        temp.push_back(vt[start]);
        return temp;
    }
    
}


