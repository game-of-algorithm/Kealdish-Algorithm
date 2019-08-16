/**
 * 大根堆排序
 */

#include<iostream>
using namespace std; 
void heapSort(int a[], int n);
void maxHeap(int a[], int n);
void buildMaxHeap(int a[], int n);
 
int size;
int main()
{
	int a[] = { 9, 12, -3, 0, 6, 8, 15, 7 };
	size= sizeof(a) / 4;
	heapSort(a, size);
	for (int i = 0; i < 8; i++)
		cout << a[i] << " ";
	return 0;
}

void heapSort(int a[], int n)
{
	int i;
	buildMaxHeap(a, n);
	for (i = size; i>1; i--)
	{
		swap(a[0], a[i-1]);
	    size = size - 1;
		maxHeap(a, 1);
	}
 
}

void buildMaxHeap(int a[], int n)
{
	int i = n / 2;
	for (i; i > 0; i--)
		maxHeap(a, i);
 
}

void maxHeap(int a[], int n)
{
	int leftChild, rightChild, largest;
	leftChild = 2 * n;
	rightChild = 2 * n + 1;

	int q = sizeof(a);
	if (leftChild <= size && a[leftChild-1] > a[n-1])
		largest = leftChild;
	else
		largest = n;
	if (rightChild <= size&&a[rightChild-1] > a[largest-1])
		largest = rightChild;

	if (largest != n)
	{
		swap(a[n-1], a[largest-1]);
		maxHeap(a, largest);
	}
}

/**
 * 2.4.16 对于 N = 32，构造数组使得堆排序使用的比较次数最多以及最少。
 */

/**
 * 最好情况只需要一个所有键值完全相同的数组即可。比如 32 个 1.
 * 
 * 比较次数为 90 次
 * 
 * 反向来看，对于一个已经构建好的大堆，在缩小堆排序数组时要想比较次数最多就需要交换次数最多，
 * 要交换次数最多，就需在堆顶元素与堆尾元素交换后下沉最多，要想下沉最多可以在堆顶元素与堆尾元素交换时让堆尾元素是堆中的最小元素。
 * 按照这个方法就可以构建一个比较次数最多的大堆。反过来操作就可以得到一个比较次数最少的大堆。
 * 
 */

public class WorstHeap {
    
};




/**
 * 2.4.29 同时面向最大和最小元素的优先队列。设计一个数据类型，支持如下操作：插入元素、删除最大元素、
 * 删除最小元素（所需时间均为对数级），以及找到最大元素、找到最小元素（所需时间均为常数级别）。
 */

/**
 * 用一个最大堆和一个最小堆，每个堆都保存了所有元素，且相同元素之间有指针相连。
 * 
 * 插入元素时需要构建两个完全相同的元素分别插入到两个堆中。
 * 找到最小元素和找到最大元素只需要分别返回最大堆和最小堆的堆顶元素即可。
 * 以删除最小元素为例，先对最小堆进行 DelMin() 操作，再通过指针找到对应最大堆的元素并删除。
 * 
 * 下面介绍删除堆中任意元素的算法。
 * 首先将待删除元素与堆中最后一个元素交换，让堆的大小减一。
 * 随后对交换后的元素先进行 Swim 再进行 Sink，移动到正确的位置上。
 * 
 */
