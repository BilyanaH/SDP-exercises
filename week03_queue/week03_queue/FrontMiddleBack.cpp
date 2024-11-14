#include "Deque.cpp"
#include <stack>
using namespace std;

template <typename T>
class FrontMiddleBack {
private:
	int size;
	Deque<T> left;
	Deque<T> right;
	void adjust();
public:
	FrontMiddleBack() ;
	void pushFront(T val);
	void pushMiddle(T val);
	void pushBack(T val);
	T popFront();
	T popMiddle();
	T popBack();
};

template<typename T>
void FrontMiddleBack<T>::adjust()
{
	int diff = size % 2;
	while (left.getSize() > (diff + right.getSize()))
	{
		int val = left.getBack();
		left.popBack();
		right.pushFront(val);
	}	
	while (left.getSize() < (diff + right.getSize()))
	{
		int val = right.getFront();
		right.popFront();
		left.pushBack(val);
	}
}

template<typename T>
FrontMiddleBack<T>::FrontMiddleBack() : size(0)
{
}

template<typename T>
void FrontMiddleBack<T>::pushFront(T val)
{
	adjust();
	left.pushFront(val);
	size++;
	adjust();
}

template<typename T>
void FrontMiddleBack<T>::pushMiddle(T val)
{
	adjust();
	if (size % 2) {
		int val = left.getBack();
		left.popBack();
		right.pushFront(val);
	}
	left.pushBack(val);
	size++;
	adjust();
}

template<typename T>
void FrontMiddleBack<T>::pushBack(T val)
{
	adjust();
	right.pushBack(val);
	size++;
	adjust();
}

template<typename T>
T FrontMiddleBack<T>::popFront()
{
	if (size == 0) {
		return -1;
	}
	adjust();
	int val = left.getFront();
	left.popFront();
	size--;
	adjust();
	return val;
}

template<typename T>
T FrontMiddleBack<T>::popMiddle()
{
	if (size == 0) {
		return -1;
	}
	adjust();
	int val = left.getBack();
	left.popBack();
	size--;
	adjust();
	return val;
}

template<typename T>
T FrontMiddleBack<T>::popBack()
{
	if (size == 0) {
		return -1;
	}
	if (size == 1) {
		adjust();
		int val = left.getBack();
		left.popBack();
		size--;
		adjust();
		return val;
	}
	adjust();
	int val = right.getBack();
	right.popBack();
	size--;
	adjust();
	return val;
}
