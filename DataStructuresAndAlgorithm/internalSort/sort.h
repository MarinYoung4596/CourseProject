#ifndef _SORT_H_
#define  _SORT_H_

#include <vector>

using namespace std;

template<typename TYPE> void bubbleSort(vector<TYPE> &, int, int);
template<typename TYPE> void selectSort(vector<TYPE> &, int, int);
template<typename TYPE> void insertSort(vector<TYPE> &, int, int);

template<typename TYPE> void quickSort(vector<TYPE> &, int, int);
template<typename TYPE> int partition(vector<TYPE> &, int, int, TYPE &);

template<typename TYPE> void mergeSort(TYPE, TYPE, int, int);
template<typename TYPE> void merge(TYPE, TYPE, int, int, int);

template<typename TYPE> void shellSort(vector<TYPE> &);
template<typename TYPE> void ins_sort_2(vector<TYPE> &, int, int);

template<typename TYPE> void heapSort(vector<TYPE> &, int, int);

template<typename TYPE> void printVector(vector<TYPE>);
#endif