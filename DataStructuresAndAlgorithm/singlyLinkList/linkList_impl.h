#include "ListNode.h"
#include "List.h"

#include<iostream>

using namespace std;

//singly-Linked Lists node
template <typename Elem>
class LList : public List<Elem>
{
private:
	ListNode<Elem>* head;
	ListNode<Elem>* tail;
	ListNode<Elem>* fence;
	int leftcnt;		//Size of left partition
	int rightcnt;		//Size of right partition

	void init()
	{
		fence = tail = head = new ListNode<Elem>;
		leftcnt = rightcnt = 0;
	}
	void removeall()
	{
		while (head != NULL)
		{
			fence = head;
			head = head->next;
			delete fence;
		}
	}

public:
	LList()//DefaltListSize
	{
		init();
	}
	~LList()
	{
		removeall();
	}
	void clear()
	{
		removeall();
		init();
	}
	bool insert(const Elem &);
	bool append(const Elem &);
	bool remove(Elem &);
	void prev();
	void setStart()
	{
		fence = head;
		rightcnt += leftcnt;
		leftcnt = 0;
	}
	void setEnd()
	{
		fence = tail;
		leftcnt += rightcnt;
		rightcnt = 0;
	}
	void next()
	{
		if (fence != tail)
		{
			fence = fence->next;
			rightcnt--;
			leftcnt++;
		}
	}
	int leftLength()const
	{
		return leftcnt;
	}
	int rightLength() const
	{
		return rightcnt;
	}
	bool setPos(int pos);
	bool getValue(Elem &it) const
	{
		if (rightcnt == 0)return false;
		it = fence->next->value;
		return true;
	}
	bool isEmpty()
	{
		return ((leftcnt + rightcnt) == 0);
	}
	void print() const;
};

//Insertion: insert at front of right partition
template <typename Elem>
bool LList<Elem>::insert(const Elem &it)
{
	fence->next = new ListNode<Elem>(it, fence->next);
	if (tail == fence) 
		tail = fence->next;  //New tail
	rightcnt++;
	return true;
}

//Remove:remove & return right Elem of fence
template <typename Elem>
bool LList<Elem>::remove(Elem &it)
{
	if (fence->next == NULL) 
		return false;
	it = fence->next->value;
	ListNode<Elem> *ltemp = fence->next;
	fence->next = ltemp->next;
	if (tail == ltemp) tail = fence;
	delete ltemp;
	rightcnt--;
	return true;
}

//SetPos: Set the size of left partition to pos
template <typename Elem>
bool  LList<Elem>::setPos(int pos)
{
	if ((pos < 0) || (pos >= leftcnt + rightcnt)) return false;
	fence = head;
	for (int i = 0; i < pos; i++)
		fence = fence->next;
	return true;
}

//SetPos: move fence one step left, no change if left is empty
template <typename Elem>
void LList<Elem>::prev()
{
	ListNode<Elem>* temp = head;
	if (fence == head) return;
	while (temp->next != fence) temp = temp->next;
	fence = temp;
	leftcnt--;
	rightcnt++;
	delete temp;  //young add
}

template<typename Elem>
void LList<Elem>::print() const
{
	ListNode<Elem>* temp = head;
	cout << "<";
	while (temp != fence)
	{
		cout << temp->next->element << " ";
		temp = temp->next;
	}
	cout << "|";
	while (temp->next != NULL)
	{
		cout << temp->next->element << " ";
		temp = temp->next;
	}
	cout << ">\n";
}
