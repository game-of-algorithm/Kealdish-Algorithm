// 2.3.3 对于长度为 N 的数组，在快排中最大的元素最多会被交换多少次？

/**
 * N / 2
 * 在快速排序中，一个元素要被交换，有以下两种情况
 * 1.该元素是枢轴，在切分的最后一步被交换
 * 2.该元素位于枢轴错误的一侧，需要被交换到另一侧去
 * 
 * 所以，尽量让最大元素在每次切分时都满足第二步。
 * 
 */

// 2.3.9 请说明快排在处理只有两种主键值的数组行为，以及在处理只有三种主键值的行为。

/**
 * 切分时，枢轴左侧都是小于（或等于）枢轴的，右侧都是大于（或等于）枢轴的
 * 
 * 只有两种主键值时，第一次切分之后，某一侧的元素将全部相同（如果枢轴选了较大的，那么右侧将全部相同，反之则左侧全部相同）
 * 
 * 只有三种主键值时，和一般快速排序类似。
 */

// 2.3.15 螺丝和螺帽。假设有 N 个螺丝和 N 个螺帽混在一堆，你需要快速将它们配对。一个螺帽只会匹配一个螺丝，一个螺丝只会匹配一个螺帽。
// 你可以试着把一个螺丝和一个螺帽拧在一起看看谁大了，但不能直接比较两个螺丝或者两个螺帽。给出一个解决这个问题的有效方法。

/**
 * 1）将螺丝螺帽分开，分成两个数组。
 * 2）选一个螺丝（也可以螺帽，之后反过来就行），以此螺丝为pivot，将螺帽分两组。
 * 3）以步骤2中的螺丝对应的螺帽为pivot，将螺丝分为两组
 * 4）经过步骤2和3，螺丝螺帽已经被分为大小两个组，然后递归地进行步骤2，3即可
 */

#include <memory>
#include <ctime>
#include <random>
#include <iostream>

class Nuts_And_Bolts {
	
    // 螺母
	struct Nut
	{
		Nut(int s);
		int size;
	};
    
    // 螺丝
	struct Bolt
	{
		Bolt(int s);
		int size;
	};

	friend bool operator<(const Nuts_And_Bolts::Nut & n, const Nuts_And_Bolts::Bolt & b);
	friend bool operator>(const Nuts_And_Bolts::Nut & n, const Nuts_And_Bolts::Bolt & b);
	friend bool operator==(const Nuts_And_Bolts::Nut & n, const Nuts_And_Bolts::Bolt & b);
	friend bool operator<(const Nuts_And_Bolts::Bolt & b, const Nuts_And_Bolts::Nut & n);
	friend bool operator>(const Nuts_And_Bolts::Bolt & b, const Nuts_And_Bolts::Nut & n);
	friend bool operator==(const Nuts_And_Bolts::Bolt & b, const Nuts_And_Bolts::Nut & n);

    std::allocator<Bolt> bolt_alloc;
	std::allocator<Nut> nut_alloc;
public:
	Nuts_And_Bolts(int n); // n个螺丝和n个螺帽一一配对,假设已经分成两堆，从小到大排列
	~Nuts_And_Bolts();
	void shuffle(); // 将螺丝和螺帽分别打乱
	void show(); // 按在数组中的顺序组成pair并打印出来
	Bolt* bolts; // Bolts
	Nut* nuts; // Nuts堆
	int size; // 等于n	
};
 
void sort(Nuts_And_Bolts& nb);

Nuts_And_Bolts::bool operator<(const Nuts_And_Bolts::Nut & n, const Nuts_And_Bolts::Bolt & b)
{
	return n.size<b.size;
}
 
Nuts_And_Bolts::bool operator>(const Nuts_And_Bolts::Nut & n, const Nuts_And_Bolts::Bolt & b)
{
	return n.size>b.size;
}
 
Nuts_And_Bolts::bool operator==(const Nuts_And_Bolts::Nut & n, const Nuts_And_Bolts::Bolt & b)
{
	return n.size == b.size;
}
 
Nuts_And_Bolts::void sort_impl(Nuts_And_Bolts& nb, int lo, int hi)
{
	if (lo >= hi)
		return;
	//以bolts[lo]为pivot，对nuts排序
	//双指针，两头向中间扫描并交换的快排
	int beg = lo;
	int end = hi;
	auto pivot_b = nb.bolts[lo];
	using std::swap;
	
    while (true) {

		while (beg <= hi&&nb.nuts[beg] < pivot_b) {
			++beg;
		}

		while (end >= lo&&nb.nuts[end] > pivot_b) {
			--end;
		}

		if (beg > end) { //将在lo中存放的匹配的nut放到合适的位置
			swap(nb.nuts[lo], nb.nuts[--beg]);
			break;
		}

		if (beg == end) {
			break;
		}

		if (nb.nuts[beg] == pivot_b || nb.nuts[end] == pivot_b) {//如果遇见了匹配的nut
			if (nb.nuts[beg] == pivot_b) { 
                //将匹配的nuts暂时放到lo
				if (beg == lo) {
                    //如果beg本来就是lo就会导致死循环
					++beg;
				}
				else {
					swap(nb.nuts[lo], nb.nuts[beg]);
				}
			}
			else {
				swap(nb.nuts[end], nb.nuts[lo]);
			}
			//b eg，end不移动以待下一轮处理
		}
		else {// 如果没有遇见匹配的nut
			swap(nb.nuts[beg], nb.nuts[end]);
			++beg;
			--end;
		}
	}

	// 通过pivot_b将nuts排完了序
	// 现在通过pivot_n将bolt排序
	auto pivot_n = nb.nuts[beg];
	beg = lo;
	end = hi;
	while (true) {

		while (beg <= hi&&nb.bolts[beg] < pivot_n) {
			++beg;
		}

		while (end >= lo&&nb.bolts[end] > pivot_n) {
			--end;
		}

		if (beg > end) {//将在lo中存放的匹配的nut放到合适的位置
			swap(nb.bolts[lo], nb.bolts[--beg]);
			break;
		}

		if (beg == end) {
			break;
		}

		if (nb.bolts[beg] == pivot_n || nb.bolts[end] == pivot_n) {//如果遇见了匹配的nut
			if (nb.bolts[beg] == pivot_n) {//将匹配的nuts暂时放到lo
				if (beg == lo) {//如果beg本来就是lo就会导致死循环
					++beg;
				}
				else {
					swap(nb.bolts[lo], nb.bolts[beg]);
				}
			}
			else {
				swap(nb.bolts[end], nb.bolts[lo]);
			}
			//beg，end不移动以待下一轮处理
		}
		else {//如果没有遇见匹配的nut
			swap(nb.bolts[beg], nb.bolts[end]);
			++beg;
			--end;
		}
	}
	//现在bolts也排了序
	//beg是匹配的位置
	sort_impl(nb, lo, beg - 1);
	sort_impl(nb, beg + 1, hi);
}
 
Nuts_And_Bolts::void sort(Nuts_And_Bolts & nb)
{
	nb.shuffle();//打乱以保证快排效率
	sort_impl(nb, 0, nb.size - 1);
}
 
Nuts_And_Bolts::bool operator<(const Nuts_And_Bolts::Bolt & b, const Nuts_And_Bolts::Nut & n)
{
	return b.size < n.size;
}
 
Nuts_And_Bolts::bool operator>(const Nuts_And_Bolts::Bolt & b, const Nuts_And_Bolts::Nut & n)
{
	return b.size > n.size;
}
 
Nuts_And_Bolts::bool operator==(const Nuts_And_Bolts::Bolt & b, const Nuts_And_Bolts::Nut & n)
{
	return b.size == n.size;
}
 
// 初始化
Nuts_And_Bolts::Nut::Nut(int s) :size(s)
{
}

// 初始化
Nuts_And_Bolts::Bolt::Bolt(int s) : size(s)
{
}
 
Nuts_And_Bolts::Nuts_And_Bolts(int n)
{
	bolts = bolt_alloc.allocate(n);
	nuts = nut_alloc.allocate(n);
	for (int i = 0; i < n; ++i) {//从0到n-1，螺丝螺帽一一配对，已经从小到大排序好
		bolt_alloc.construct(bolts + i, i);
		nut_alloc.construct(nuts + i, i);
	}	
	size = n;
}

// 析构函数
Nuts_And_Bolts::~Nuts_And_Bolts()
{
	for (int i = 0; i < size; ++i) {
		bolt_alloc.destroy(bolts + i);
		nut_alloc.destroy(nuts + i);
	}
	bolt_alloc.deallocate(bolts, size);
	nut_alloc.deallocate(nuts, size);
}
 
// 乱序
void Nuts_And_Bolts::shuffle()
{
	static std::default_random_engine rgen(time(nullptr));
	static std::uniform_int_distribution<> dis;
	using std::swap;
	for (int i = 0; i < size; ++i) {
		swap(bolts[i], bolts[dis(rgen, decltype(dis)::param_type(0, i))]);
		swap(nuts[i], nuts[dis(rgen, decltype(dis)::param_type(0, i))]);
	}
}
 
void Nuts_And_Bolts::show()
{
	for (int i = 0; i < size; ++i) {
		std::cout << " ( " << bolts[i].size << " , " << nuts[i].size << " ) " << std::endl;
	}
	std::cout << std::endl;
}
 
// 2.3.17 哨兵。修改算法 2.5 ，去掉内循环 while 中的边界检查。由于切分元素本身就是一个哨兵，左侧边界的检查是多余的。
// 要去掉另一个检查，可以在打乱数组后将数组的最大元素放在 a[length - 1] 中。该元素永远不会移动（除非和相等的元素交换），
// 可以在所有包含它的子数组中成为哨兵。

#include <vector>
#include <algorithm>
using std::vector;
using std::shuffle;
using std::swap;

void sort(vector<int> a) {

    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(a.begin(), a.end(), g);

    int maxIndex = 0;

    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] > a[maxIndex])
        {
            maxIndex = i;
        }
        
    }

    swap(a[maxIndex], a[a.size() - 1]);
    
    subSort(a, 0, a.size() - 1);
}

void subSort(vector<int> a, int l, int h) {
    if (l >= h)
    {
        return;
    }
    
    int j = parttion(a, l, h);
    subSort(a, l, j - 1);
    subSort(a, j + 1, h);
}

int partition(vector<int> a, int l, int h) {
    int i = l, j = h + 1;

    int value = a[l];

    while (true)
    {
        while (a[++i] < value) ;
        while (a[--j] > value) ;

        if (i > j) break;

        swap(a[i], a[j]);
    }
    
    swap(a[l], a[j]);
    return j;
}

// 2.3.20 非递归的快速排序。实现一个非递归的快速排序，使用一个循环来将弹出栈的子数组切分并将结果子数组重新压入栈。
// 注意：先将较大的子数组压入栈，这样就可以保证栈最多只会有 lgN 个元素。

#include <stack>
#include <algorithm>
using std::stack;
using std::swap;

void QuickSortNonRecursive(int arr[],int length)
{
    stack<int> stack; // 先存大再存小，取得时候就可以先取小再取大，此处的大小指的是数组索引
    stack.push(length-1);
    stack.push(0);
    int low, high;

    while(!stack.empty())
    {
        low = stack.top();
        stack.pop();
        high = stack.top();
        stack.pop();

        if(low >= high) continue;

        int i = low;
        int j = high;
        int value = arr[low];

        while(i < j)// i==j 循环结束
        {
            while(arr[j] > value) j--;// 右边的都大于 value
            swap(arr[j], arr[i]);
            while(arr[i]<value) i++;// 左边的都小于 value
            swap(arr[i], arr[j]);
        }

        // 开始存储左右两侧待处理的数据，为了先处理左侧先保存右侧数据
        lowHigh.push(high);
        lowHigh.push(i+1);
        // 左侧
        lowHigh.push(i-1);
        lowHigh.push(low);
        
    }
    
}

// 2.3.24 取样排序。实现一个快速排序，取样大小为 2^k - 1。首先将取样得到的元素排序，然后将递归函数中使用样品的中位数切分。
// 分为两部分的其余样品元素无需再次排序并分别应用于原数组的两个子数组。这种算法被称为取样排序。

/**
 * 
 * 在打乱输入数组之后，取前 2^k-1 个元素作为取样数组，用快排对其排序。
 * 然后把取样数组的后半部分放到整个数组的末尾。
 * 这样操作的结果是输入数组分为了四个部分：
 * 有序的取样数组、取样数组的中位数、无序的剩余数组、有序的取样数组。
 * 中位数则位于第一部分的末尾，我们将其作为枢轴对剩余数组进行切分，数组变为：
 * 有序的取样数组、小于中位数的部分、枢轴、大于中位数的部分、有序的取样数组
 * 接下来我们再对第一个部分取半，放到中位数之前；对最后一部分取半，放到中位数之后：
 * 0 ~ 1/4 取样数组、小于中位数、1/4 ~ 1/2 取样数组、枢轴、1/2~3/4 取样数组、大于中位数、3/4~1 取样数组
 * 你会发现枢轴前后又分别变回了初始条件，递归执行上述操作，便能对整个数组排序。
 * 注意当取样数组用完的时候，直接变回普通的快排。
 * 
 */

#include <vector>
#include <cmath>
using std::vector;
using std::pow;
using std::shuffle;
using std::swap;

static int k = 8;

void sampleSort(vector<int> a) {
    // 如果数组长度小于 2^(k+1) 使用常规快排
    if (a.size() < pow(2, k + 1)) {
        sort(a);
        return;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(a.begin(), a.end(), g);

    int sampleH = pow(2, k) - 2;
    // 利用快速排序对取样数组进行排序
    subSort(a, 0, sampleH);
    // 找到取样数组的中位数
    int sampleMedian = samplehi / 2;
    // 将取样数组后半部分放到数组末尾
    int i = samplehi, j = a.size() - 1;
            
    while (i != sampleMedian)
        swap(a[i--], a[j--]);
    
    // 根据取样数组进行排序
    subSort(a, 0, sampleMedian, j, a.Length - 1);
}

// 用快速排序对数组 a 的 lo ~ hi 范围排序。
void sampleSubsort(vector<int> a, int sampleL, int l, int h, int sampleH) {

    if (h <= l) {
        return;
    }

    int j = samplePartition(a, l, h);

    // 将前部的有序取样数组取半，后半部分放在枢轴前面。
    if (l - sampleL > 1)
    {
        // p 应该始终指向有序部分的最后一项
        // v 应该始终指向有序部分的前面一项
        int p = l - 1, v = j - 1;
        for (int i = 0; i < (l - sampleL) / 2; i++)
        {
            swap(a[p--], a[v--]);
        }

        sampleSubsort(a, sampleL, p, v, j - 1);
    } else {
        // 取样数组已经用完，退化为普通 Quicksort
        sort(a, sampleL, j - 1);
    }
    
    // 将尾部有序取样数组取半，前半部分放在枢轴后面。
    if (samplehi - h > 1)
    {
        // p 应该始终指向有序部分的前面一项
        // v 应该始终指向有序部分的最后一项
        int p = h, v = j;
        for (int i = 0; i < (sampleH - h) / 2; i++)
        {
            swap(a[++p], a[++v]);
        }
        sampleSubsort(a, j + 1, v, p, sampleH);
    }
    else
    {
        // 取样数组已用完，退化为普通 Quicksort
        sort(a, j + 1, sampleH);
    }
}

int samplePartition(vector<int> a, int l, int h) {
    int i = l, j = h + 1;
    int v = a[l];

    while (true)
    {
        while (a[++i] < v) {
            if (i == h)
            {
                break;
            }
        }
        
        while (a[--j] > v) {
            if (i == l)
            {
                break;
            }
        }
        
        if (i >= j)
        {
            break;
        }
        
        swap(a[i], a[j]);
    }

    swap(a[l], a[j]);
    return j;
}






