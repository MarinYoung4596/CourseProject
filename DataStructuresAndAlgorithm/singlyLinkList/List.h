#ifndef _LIST_H_
#define _LIST_H_

using namespace std;

template <typename Elem> class List
{
public:
	virtual void clear() = 0; 				// Remove all object
	virtual bool insert(const Elem &) = 0;	// insert item after fence pos
	virtual bool append(const Elem &) = 0;	// insert item at tail
	virtual bool remove(Elem &) = 0;		// remove/return item after fence
	virtual void setStart() = 0;			//set fence at list start (head)
	virtual void setEnd() = 0;				//set fence at list end (tail)
	virtual void next() = 0;				//move fence to next pos
	virtual void prev() = 0;				//move fence to prev pos
	virtual int leftLength() const = 0;		//return length of the list before fence
	virtual int rightLength() const = 0;	//return length of the list after fence
	virtual bool setPos(int pos) = 0;		//set fence to specified pos
	virtual bool getValue(Elem&) const = 0; //return item s value of fence
	virtual bool isEmpty() = 0;				//return true if list is empty
	virtual void print() const = 0;			//print the contents of the list
};
#endif
