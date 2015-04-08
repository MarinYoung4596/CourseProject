// sortAlgorithm.cpp : �������̨Ӧ�ó������ڵ㡣
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
�ظ����߷ù�Ҫ��������У�һ�αȽ�����Ԫ�أ�������ǵ�˳�����Ͱ����ǽ���������
ʱ�临�Ӷȣ�O(n^2); �ռ临�Ӷȣ�O(1); �ȶ�
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
ÿһ�δӴ����������Ԫ����ѡ����С������󣩵�һ��Ԫ�أ���������е���ʼλ�ã�ֱ��ȫ�������������Ԫ�����ꡣ
ʱ�临�Ӷȣ�O(n^2); �ռ临�Ӷȣ�O(1); ���ȶ�
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
ÿ����һ��������ļ�¼������ؼ���ֵ�Ĵ�С����ǰ���Ѿ�������ļ����ʵ�λ���ϣ�ֱ��ȫ��������Ϊֹ��
ʱ�临�Ӷȣ�O(n^2); �ռ临�Ӷȣ�O(1); ���ȶ�
*/
template<typename TYPE>
void insertSort(vector<TYPE> &a, int left, int right)
{
	for (int i = left + 1; i < right; i++)
	{
		//���a[j]ǰһ������a[j-1] > a[j]���ͽ���a[j]��a[j-1]����j--ֱ��a[j-1] <= a[j]
		for (int j = i - 1; j >= 0 && a[j] > a[j + 1]; j--)
			swap(a[j], a[j + 1]);
	}
}


/*
ͨ��һ������Ҫ��������ݷָ�ɶ����������֣�����һ���ֵ��������ݶ�������һ���ֵ��������ݶ�ҪС��
Ȼ���ٰ��˷����������������ݷֱ���п�����������������̿��Եݹ���У��Դ˴ﵽ�������ݱ���������С�
ʱ�临�Ӷȣ�O(Nlog2N); �ռ临�Ӷȣ�O(log2N); ���ȶ�
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
���÷��η�.��������������кϲ����õ���ȫ��������У�����ʹÿ��������������ʹ�����жμ�����
ʱ�临�Ӷȣ�O(Nlog2N); �ռ临�Ӷȣ�O(N); �ȶ�
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
�Ѽ�¼���±��һ���������飬��ÿ��ʹ��ֱ�Ӳ��������㷨�������������𽥼��٣�ÿ������Ĺؼ���Խ��Խ�࣬
����������1ʱ�������ļ�ǡ���ֳ�һ�飬�㷨��ֹ.
ʱ�临�Ӷȣ�O(n^1.5); �ռ临�Ӷȣ�O(1); ���ȶ�
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
���öѵ����ʣ��ӽڵ�ļ�ֵ����С�ڣ�����ڣ����ĸ��ڵ�
ʱ�临�Ӷȣ�O(Nlog2N); �ռ临�Ӷȣ�O(1); ���ȶ�
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
