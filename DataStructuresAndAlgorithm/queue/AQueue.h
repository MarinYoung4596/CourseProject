#include "queue.h"

template <typename Elem>
class AQueue : public Queue<Elem>
{
public:
	AQueue(int sz)
	{
		size = sz + 1;
		front = 0;
		rear = 0;
		listArray = new Elem[size];
	}
	~AQueue()
	{
		delete[] listArray;
	}
	void clear()
	{
		front = rear = 0;
	}
	bool enqueue(const Elem &);
	bool dequeue(Elem &);
	bool frontValue(Elem &)const;
	int length() const
	{
		return ((rear - front) + size) % size;
	}

private:
	int size;			// max size of queue
	int front, rear;	// front and rear index
	Elem *listArray;	// storage space
};

template <typename Elem>
bool AQueue<Elem>::enqueue(const Elem &it)
{
	if ( ((rear + 1) % size) == front) 
		return false; //Full
	listArray[rear] = it;
	rear = (rear + 1) % size;
	return true;
}

template <typename Elem>
bool AQueue<Elem>::dequeue(Elem &it)
{
	if (rear == front) 
		return false;  // Empty
	it = listArray[front];
	front = (front + 1) % size;
	return true;
}

template <class Elem>
bool AQueue<Elem>::frontValue(Elem &it) const
{
	if (rear == front) 
		return false;  //Empty
	it = listArray[front];
	return true;
}


