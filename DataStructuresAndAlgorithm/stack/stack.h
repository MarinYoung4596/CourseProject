#ifndef _STACK_H_
#define _STACK_H_

template <typename Elem>
class Stack
{
public:
	virtual void clear() = 0; 		    // Remove all object
	virtual bool push(const Elem &) = 0;// push object onto stack
	virtual bool pop(Elem &) = 0; 	    // pop/return top element
	virtual bool top(Elem &) const = 0; //return value of top element
	virtual int length() const = 0;	    //return length of stack
};
#endif
