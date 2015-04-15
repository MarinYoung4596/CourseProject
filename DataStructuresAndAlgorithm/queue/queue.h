#ifndef _QUEUE_H_
#define _QUEUE_H_

template <typename Elem>
class Queue
{
public:
	virtual void clear() = 0; 				// Remove all object
	virtual bool enqueue(const Elem &) = 0;	// insert object at rear
	virtual bool dequeue(Elem &) = 0; 		// remove/return front element
	virtual bool frontValue(Elem &) const = 0; //return value of front element
	virtual int length() const = 0;			//return true if queue is empty
};
#endif

