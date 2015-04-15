#include "List.h"
#include <iostream>
#include <cassert>
#define MAXSIZE 100

//Array Based List
template <typename Elem>
class AList : public List<Elem>
{
private:
	int maxSize;		// max size of list
	int listSize;		// The length of of list
	int fence;			// pos of current element
	Elem *listArray;	// storage space
public:
	AList(int size = 0)       //Constructor  int size=DefaultListSize
	{
		maxSize = size;
		listSize = fence = 0;
		listArray = new Elem[maxSize];
		assert(listArray != 0);
	}
	~AList()
	{
		delete[] listArray;    // Destructor
	}
	void clear()
	{
		delete[] listArray;
		listSize = fence = 0;
		listArray = new Elem[maxSize];
		assert(listArray != 0);
	}
	//set fence's  location
	void setStart()
	{
		fence = 0;
	}
	//set fence's  location
	void setEnd()
	{
		fence = listSize;
	}
	//set fence's  location
	void prev()
	{
		if (fence != 0) fence--;
	}
	//set fence's  location
	bool setPos(int pos)
	{
		if (pos >= 0 && pos <= listSize)  fence = pos;
		return (pos >= 0) && (pos <= listSize);
	}
	void next()
	{
		if (fence <= listSize) fence++;
	}
	int leftLength()const
	{
		return fence;
	}
	int rightLength()const
	{
		return listSize - fence;
	}
	bool getValue(Elem &it)const
	{
		if (rightLength() == 0) return false;
		else
		{
			it = listArray[fence];
			return true;
		}
	}
	bool isEmpty()
	{
		return (listSize == 0);
	}
	bool insert(const Elem &);
	bool append(const Elem &);
	bool remove(Elem &);
	void print() const;
};

//Insert the Elem at current position
template <typename Elem> 
bool AList <Elem>::insert(const Elem &it)
{
	if (listSize == maxSize) return false;
	if ((fence <0) || (fence > listSize - 1)) return false;
	for (int i = listSize; i > fence; i--)
	{
		listArray[i] = listArray[i - 1];
	}
	listArray[fence] = it;
	listSize++;
	return true;
}

//Append the Elem to end of the list
template <typename Elem> 
bool AList<Elem>::append(const Elem &it)
{
	if (listSize == maxSize) return false;
	listArray[listSize++] = it;
	return true;
}

// remove element in fence position & return the Elem of current
template <typename Elem>
bool AList<Elem>::remove(Elem &it)
{
	if (rightLength() == 0) return false;
	if ((fence < 0) || (fence >= listSize)) return false;
	it = listArray[fence];
	for (int i = fence; i < listSize - 1; i++)listArray[i] = listArray[i + 1];
	listSize--;
	return  true;
}

template <typename Elem>
void AList<Elem>::print() const
{
	int temp = 0;
	cout << "<";
	while (temp < fence)
		cout << listArray[temp++] << " ";
	cout << "|";  //fence location
	while (temp < listSize)
		cout << listArray[temp++] << " ";
	cout << ">\n";
}
