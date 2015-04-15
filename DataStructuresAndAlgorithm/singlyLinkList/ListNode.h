#ifndef _LISTNODE_H_
#define _LISTNODE_H_

template <typename Elem>
class ListNode
{
public:
	Elem value;
	ListNode *next;

	ListNode() {}
	ListNode(const Elem &val) : value(val), next(NULL) {}
	ListNode(ListNode *nextval = NULL) : next(nextval) {}
	ListNode(const Elem &val, ListNode *nextval = NULL) : value(val), next(nextval) {}
};
#endif