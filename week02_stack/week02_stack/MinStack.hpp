#ifndef MINSTACK_HPP
#define MINSTACK_HPP

#include <stack>
using namespace std;

class MinStack {
protected:
	stack<int> myStack;
	stack<int> minElements;

public:
	void push(int val);
	void pop();
	int top();
	int getMin();
};

#endif