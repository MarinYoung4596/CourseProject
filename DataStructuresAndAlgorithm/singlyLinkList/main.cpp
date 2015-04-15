#include "arrayList_impl.h"
#include "linkList_impl.h"

using namespace std;

template<typename Elem>
void testCase_ArrayList()
{
	int sz = 0;

	int array[MAXSIZE];
	cout << "enter list size:" << endl;
	cin >> sz;
	AList <int> arr(MAXSIZE);
	cout << "enter array:" << endl;
	for (int i = 0; i < sz; i++)
	{
		cin >> array[i];
		arr.append(array[i]);
	}
	/****************************/
	arr.setStart();
	cout << "print arr:" << endl;
	arr.print();
	/****************************/
	int a;
	cout << "enter append number:" << endl;
	cin >> a;
	arr.append(a);
	cout << "arr:" << endl;
	arr.print();
	/****************************/
	int b;
	cout << "set fence position:" << endl;
	cin >> b;
	if (b<0 || b>sz)cout << "wrong, enter again!\n";
	arr.setPos(b);
	arr.print();
	/****************************/
	int c;
	cout << "enter insert number:" << endl;
	cin >> c;
	arr.insert(c);
	arr.print();
	/****************************/
	int d;
	cout << "remove:" << endl;
	arr.remove(d);
	arr.print();
	cout << "removed number:\t" << d << endl;
	/****************************/
	int e, f;
	cout << "set pos:\n";
	cin >> f;
	arr.setPos(f);
	arr.getValue(e);
	cout << "Value at position " << f << ":\t" << e <<endl;
	/****************************/
	cout << "arr LeftLength:\n" << arr.leftLength() << endl;
	arr.setEnd();
	cout << arr.rightLength() << endl;
	/****************************/
	arr.clear();
	cout << "clear arr:\n";
	arr.print();
}

//template<typename Elem>
//void testCase_LinkList()
//{
//	int sz;
//	LList<int> arr();
//	int array[MAXSIZE];
//	cout << "enter list size:" << endl;
//	cin >> sz;
//	cout << "enter array:" << endl;
//	for (int i = 0; i < sz; i++)
//	{
//		cin >> array[i];
//		arr.append(array[i]);
//	}
//	/****************************/
//	arr.setStart();
//	cout << "print arr:" << endl;
//	arr.print();
	///****************************/
	//int a;
	//cout << "enter append number:" << endl;
	//cin >> a;
	//arr.append(a);
	//cout << "arr:" << endl;
	//arr.print();
	///****************************/
	//int b;
	//cout << "set fence position:" << endl;
	//cin >> b;
	//if (b<0 || b>sz)cout << "wrong,enter again!\n";
	//arr.setPos(b);
	//arr.print();
	///****************************/
	//int c;
	//cout << "enter insert number:" << endl;
	//cin >> c;
	//arr.insert(c);
	//arr.print();
	///****************************/
	//int d;
	//cout << "remove:" << endl;
	//arr.remove(d);
	//arr.print();
	//cout << "removed number:\n" << d << endl;
	///****************************/
	//int e, f;
	//cout << "set pos:\n";
	//cin >> f;
	//arr.setPos(f);
	//arr.getValue(e);
	//cout << "Value:\n" << e;
	///****************************/
	//cout << "arr LeftLength:\n" << arr.leftLength() << endl;
	//arr.setEnd();
	//cout << arr.rightLength() << endl;
	///****************************/
	//arr.clear();
	//cout << "clear arr:\n";
	//arr.print();
//}

int main(int argc, char **argv)
{
	//testCase_ArrayList<int>();
	//testCase_LinkList<int>();

	int sz;
	LList<int> arr();
	int array[MAXSIZE];
	cout << "enter list size:" << endl;
	cin >> sz;
	cout << "enter array:" << endl;
	for (int i = 0; i < sz; i++)
	{
		cin >> array[i];
		arr.append(array[i]);
	}
	/****************************/
	arr.setStart();
	cout << "print arr:" << endl;
	arr.print();
	
	int x;
	cin >> x;
	return 0;
}