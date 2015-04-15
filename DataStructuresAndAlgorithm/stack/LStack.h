#include"stack.h"
#include"ListNode.h"
#include<iostream>

using namespace std;

template <typename Elem> // link list based stack implementation
class LStack : public Stack<Elem>
{
private:
	ListNode<Elem> *top;	// pointer to first element
	int size;			// count number of elements
public:
	LStack(int sz)
	{
		top = NULL;
		size = sz;
	}
	~LStack()
	{
		clear();
	}
	void clear()
	{
		ListNode<Elem> *tmp;
		while (top != NULL)
		{
			tmp = top;
			top = top->next;
			delete tmp;
		}
		size = 0;
	}
	bool push(const Elem &);
	bool pop(Elem &);
	bool top(Elem &) const;
	int length() const
	{
		return size;
	}
};

template <typename Elem>  // push item onto stack
bool LStack<Elem>::push(const Elem &it)
{
	top = new ListNode<Elem>(it, top);
	size++;
	return true;
}

template <typename Elem> // pop top element
bool LStack<Elem>::pop(Elem &it)
{
	if (size == 0) return false;
	it = top->value;
	ListNode<Elem> *tmp = top->next;
	delete top;
	top = tmp;
	size--;
	return true;
}

template <typename Elem>  // return top element
bool LStack<Elem>::top(Elem &it) const
{
	if (size == 0) return false;
	it = top->value;
	return true;
}

