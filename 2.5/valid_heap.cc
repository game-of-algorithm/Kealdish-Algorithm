/*
	稳定的优先队列。实现一个稳定的优先队列。
*/

/*
	借助另一个数组，记录优先队列同样位置的数的插入次序，优先队列数组中发生交换操作时，也需要同步交换插入次序数组的位置。
*/

#include <iostream>
#include <vector>
using namespace std; 
void heapSort(int a[], int n);
void maxHeap(int a[], int n);
void buildMaxHeap(int a[], int n);

int size;
vector<int> vt;
void heapSort(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		vt.push_back(i);
	}
	
	int i;
	buildMaxHeap(a, n);
	for (i = size; i>1; i--)
	{
		swap(a[0], a[i-1]);
		swap(vt[0], a[i-1]);
	    size = size - 1;
		maxHeap(a, 1);
	}
 
}

void buildMaxHeap(int a[], int n)
{
	for (int i = n / 2; i > 0; i--)
		maxHeap(a, i);
}

void maxHeap(int a[], int n)
{
	int leftChild, rightChild, largest;
	leftChild = 2 * n;
	rightChild = 2 * n + 1;

	if (leftChild <= size && a[leftChild - 1] > a[n - 1])
		largest = leftChild;
	else
		largest = n;
	if (rightChild <= size && a[rightChild - 1] >= a[largest - 1]) {
		
		if (a[rightChild - 1] == a[largest - 1])
		{
			largest = vt[rightChild - 1] < vt[largest - 1] ? rightChild : largest;
		} else
		{
			largest = rightChild;
		}
		
	}

	if (largest != n)
	{
		swap(a[n - 1], a[largest - 1]);
		swap(vt[n - 1], vt[largest - 1]);
		maxHeap(a, largest);
	}
}
