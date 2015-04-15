#include"queue.h"
#include"ListNode.h"

#include<iostream>

using namespace std;

template <typename Elem>
class LQueue : public Queue<Elem>
{
public:
	LQueue(int sz)
	{
		front = rear = NULL;
		size = 0;
	}
	~LQueue()
	{
		clear();
	}
	void clear()
	{
		while (front != NULL)
		{
			rear = front;
			front = front->next;
			delete rear;
		}
		rear = NULL;
		size = 0;
	}
	bool enqueue(const Elem &);
	bool dequeue(Elem &);
	bool frontValue(Elem &) const;
	int length() const
	{
		return size;
	}
private:
	ListNode<Elem> *front, *rear;
	int size;
};

template <typename Elem>
bool  LQueue<Elem>::enqueue(const Elem &it)
{
	if (rear != NULL)    	//Not Empty
	{
		rear = new ListNode<Elem>(it, NULL);
		rear = rear->next;
	}
	else 
		front = rear = new ListNode<Elem>(it, NULL);
	size++;
	return true;
}

template <typename Elem>
bool LQueue<Elem>::dequeue(Elem &it)
{
	if (front == NULL) 
		return false;     //Empty
	it = front->value;
	ListNode<Elem> *tmp = front;
	front = front->next;
	delete tmp;
	size--;
	if (front == NULL) 
		rear = NULL;
	return true;
}

template <typename Elem>
bool LQueue<Elem>::frontValue(Elem &it)const
{
	if (size == 0)
		return false;
	it = front->value;
	return true;
}
