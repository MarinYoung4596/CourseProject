// sortAlgorithm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "sort.h"

#include <iostream>
#include <vector>

using namespace std;

template<typename TYPE>
void printVector(vector<TYPE> v)
{
	vector<int>::iterator iter = v.begin();
	while (iter != v.end())
		cout << *iter++ << '\t';
	cout << endl;
}


/*
重复地走访过要排序的数列，一次比较两个元素，如果他们的顺序错误就把他们交换过来。
时间复杂度：O(n^2); 空间复杂度：O(1); 稳定
*/
template<typename TYPE>
void bubbleSort(vector<TYPE> &a, int left, int right)
{
	for (int i = left; i < right; i++)
	{
		for (int j = i + 1; j < right; j++)
		{
			if (a[i] > a[j])
				swap(a[i], a[j]);
		}
	}
}


/*
每一次从待排序的数据元素中选出最小（或最大）的一个元素，存放在序列的起始位置，直到全部待排序的数据元素排完。
时间复杂度：O(n^2); 空间复杂度：O(1); 不稳定
*/
template<typename TYPE>
void selectSort(vector<TYPE> &a, int left, int right)
{
	for (int i = left; i < right; i++)
	{
		int minPos = i;
		for (int j = i + 1; j < right; j++)
		{
			if (a[minPos] > a[j])
				minPos = j;
		}
		if (i != minPos)
			swap(a[i], a[minPos]);
	}
}

/*
每步将一个待排序的纪录，按其关键码值的大小插入前面已经排序的文件中适当位置上，直到全部插入完为止。
时间复杂度：O(n^2); 空间复杂度：O(1); 不稳定
*/
template<typename TYPE>
void insertSort(vector<TYPE> &a, int left, int right)
{
	for (int i = left + 1; i < right; i++)
	{
		//如果a[j]前一个数据a[j-1] > a[j]，就交换a[j]和a[j-1]，再j--直到a[j-1] <= a[j]
		for (int j = i - 1; j >= 0 && a[j] > a[j + 1]; j--)
			swap(a[j], a[j + 1]);
	}
}


/*
通过一趟排序将要排序的数据分割成独立的两部分，其中一部分的所有数据都比另外一部分的所有数据都要小，
然后再按此方法对这两部分数据分别进行快速排序，整个排序过程可以递归进行，以此达到整个数据变成有序序列。
时间复杂度：O(Nlog2N); 空间复杂度：O(log2N); 不稳定
*/
template<typename TYPE>
void quickSort(vector<TYPE> &a, int left, int right)
{
	if (left >= right) return;		// do not sort 0 or 1 element
	
	int pivotIndex = (left + right) / 2;
	swap(a[pivotIndex], a[right]);	// put pivot at the end
	int k = partition<TYPE>(a, left, right, a[right]);
	swap(a[k], a[right]);			// a[k], restore the pivot

	quickSort<TYPE>(a, left, k - 1);
	quickSort<TYPE>(a, k + 1, right);
}

template<typename TYPE>
int partition(vector<TYPE> &a, int left, int right, TYPE& pivot)
{
	while (left < right)
	{
		while (left < right && pivot < a[right]) right--;
		while (left < right && a[left] < pivot) left++;
		swap(a[left], a[right]);
	}
	return left;
}


/*
采用分治法.将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，再使子序列段间有序。
时间复杂度：O(Nlog2N); 空间复杂度：O(N); 稳定
*/
template<typename TYPE>
void mergeSort(TYPE a[], TYPE tmp[], int left, int right)
{
	if (left >= right) return;
	int mid = (left + right) / 2;

	mergeSort<TYPE>(a, tmp, left, mid);
	mergeSort<TYPE>(a, tmp, mid + 1, right);

	merge(a, tmp, left, mid, right);
}

template<typename TYPE>
void merge(TYPE a[], TYPE tmp[], int left, int mid, int right)
{
	int i = left,
		j = mid + 1,
		k = 0;
	while (i <= mid && j <= right)
	{
		if (a[i] < a[j])
			tmp[k++] = a[i++];
		else
			tmp[k++] = a[j++];
	}
	while (i <= mid)
		tmp[k++] = a[i++];
	while (j <= right)
		tmp[k++] = a[j++];

	for (i = 0; i < k; i++)
		a[left + i] = tmp[i];
}


/*
把记录按下标的一定增量分组，对每组使用直接插入排序算法排序；随着增量逐渐减少，每组包含的关键词越来越多，
当增量减至1时，整个文件恰被分成一组，算法终止.
时间复杂度：O(n^1.5); 空间复杂度：O(1); 不稳定
*/
template<typename TYPE>
void shellSort(vector<TYPE> &a)
{
	int n = a.size();
	for (int i = n / 2; i > 2; i /= 2)
	{
		for (int j = 0; j < i; j++)
			ins_sort_2<TYPE>(a, j, i);
	}
	ins_sort_2<TYPE>(a, 0, 1);
}

template<typename TYPE>
void ins_sort_2(vector<TYPE> &a, int start, int incr)
{
	int n = a.size();
	for (int i = start + incr; i < n; i += incr)
	{
		for (int j = i; j >= incr; j -= incr)
		{
			if (a[j] < a[j - incr])
				swap(a[j], a[j - incr]);
		}
	}
}


/*
利用堆的性质：子节点的键值总是小于（或大于）它的父节点
时间复杂度：O(Nlog2N); 空间复杂度：O(1); 不稳定
*/
template<typename TYPE>
void heapSort(vector<TYPE> &a)
{

}

template<typename TYPE>
void heapAdjust(vector<TYPE> &a, int pos)
{

}


int main(int argc, char **argv)
{
	int a[] = { 1, 15, 5, 4, 18, 7, 8, 6, 17, 19, 3, 20, 11, 9, 13, 10, 12, 14, 2, 16 };
	vector<int> v1(&a[0], &a[0] + sizeof(a) / sizeof(int));
	printVector(v1);

	bubbleSort(v1, 0, v1.size());
	cout << "bubble sort: " << endl;
	printVector(v1);

	vector<int> v2(&a[0], &a[0] + sizeof(a) / sizeof(int));
	selectSort(v2, 0, v2.size());
	cout << "select sort: " << endl;
	printVector(v2);

	vector<int> v3(&a[0], &a[0] + sizeof(a) / sizeof(int));
	insertSort(v3, 0, v3.size());
	cout << "insert sort: " << endl;
	printVector(v3);

	vector<int> v4(&a[0], &a[0] + sizeof(a) / sizeof(int));
	quickSort(v4, 0, v4.size() - 1);
	cout << "quick sort: "<<endl;
	printVector(v4);

	int b[20];
	mergeSort(a, b, 0, 19);
	cout << "merge sort: " << endl;
	for (int i = 0; i < 20; i++)
		cout << b[i] << '\t';
	cout << endl;

	vector<int> v5(&a[0], &a[0] + sizeof(a) / sizeof(int));
	shellSort(v5);
	cout << "shell sort: " << endl;
	printVector(v5);


	int x;
	cin >> x;
	return 0;
}
