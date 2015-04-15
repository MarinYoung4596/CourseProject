#ifndef _LISTNODE_H_
#define _LISTNODE_H_

template <typename Elem>
class ListNode
{
public:
	Elem value;
	ListNode *next;

	ListNode(const Elem &val, ListNode *nextval = NULL) : value(val), next(nextval) {}
	ListNode(ListNode *nextval = NULL) : next(nextval) {}
};
#endif