#include "stack.h"
#include<iostream>

using namespace std;

template <typename Elem>
class AStack : public Stack<Elem>
{
private:
	int size;		// max size of stack
	int top;			// index for top object
	Elem *listArray;	// stack storage space
public:
	AStack(int sz)
	{
		size = sz;
		top = 0;
		listArray = new Elem[sz];
	}
	~AStack()
	{
		delete[] listArray;
	}
	void clear()
	{
		top = 0;
	}
	bool push(const Elem &);
	bool pop(Elem &);
	bool top(Elem &) const;
	int length() const
	{
		return top;
	}
};

template <typename Elem>  // push item into stack
bool AStack<Elem>::push(const Elem &it)
{
	if (top == size) return false;   // Full
	else
	{
		listArray[top++] = it;
		return true;
	}
}

template <typename Elem> // pop top element
bool AStack<Elem>::pop(Elem &it)
{
	if (top == 0) return false;   // Empty
	else
	{
		it = listArray[--top];
		return true;
	}
}

template <typename Elem>  // return top element
bool AStack<Elem>::top(Elem &it) const
{
	if (top == 0) return false;
	else
	{
		it = listArray[top - 1];
		return true;
	}
}


