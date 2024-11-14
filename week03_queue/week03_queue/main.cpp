#include <iostream>
#include <queue>
#include <cassert>
#include "QueueWithStack.cpp"
#include "StackWithQueue.cpp"
#include "FrontMiddleBack.cpp"
using namespace std;

void BinaryNumbers(int n) {
	queue<std::string> nums;
	nums.push("1");
	for (size_t i = 0; i < n; i++)
	{
		nums.push(nums.front() + "0");
		nums.push(nums.front() + "1");
		std::cout << nums.front() << " ";
		nums.pop();
	}
}

int main() {
	//1
	StackWithQueue<int>* myStack = new StackWithQueue<int>();
	myStack->push(1);
	myStack->push(2);
	assert(myStack->top() == 2); // return 2
	assert(myStack->pop() == 2); // return 2
	assert(myStack->empty() == false); // return False
	//2
	QueueWithStack<int>* myQueue = new QueueWithStack<int>();
	myQueue->push(1); // queue is: [1]
	myQueue->push(2); // queue is: [1, 2] (leftmost is front of the queue)
	assert(myQueue->peek() == 1); // return 1
	assert(myQueue->pop() == 1); // return 1, queue is [2]
	assert(myQueue->empty() == false); // return false
	BinaryNumbers(16);
	//3
	Deque<int> dq(5);
	dq.pushBack(1);
	dq.pushBack(2);
	dq.pushBack(3);
	dq.pushBack(4);
	dq.pushBack(5);

	cout << "Front element: " << dq.getFront() << endl;
	cout << "Rear element: " << dq.getBack() << endl;
	
	dq.pushBack(6);	
	dq.popFront();

	cout << "After resizing, Front element: " << dq.getFront() << endl;
	cout << "After resizing, Rear element: " << dq.getBack() << endl;
	dq.popBack();
	cout << "After resizing, Rear element: " << dq.getBack() << endl;

	FrontMiddleBack<int>* q = new FrontMiddleBack<int>();
	q->pushFront(1);   // [1]
	q->pushBack(2);    // [1, 2]
	q->pushMiddle(3);  // [1, 3, 2]
	q->pushMiddle(4);  // [1, 4, 3, 2]
	assert(q->popFront() == 1);     // return 1 -> [4, 3, 2]
	assert(q->popMiddle() == 3);    // return 3 -> [4, 2]
	assert(q->popMiddle() == 4);    // return 4 -> [2]
	assert(q->popBack() == 2);      // return 2 -> []
	assert(q->popFront() == -1);     // return -1 -> [] (The queue is empty)

	return 0;
}