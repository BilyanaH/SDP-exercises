#include "MinStack.hpp"

void MinStack::push(int val)
{
	myStack.push(val);
	if (minElements.empty()|| val < minElements.top()) {
		minElements.push(val);
	}
	else  {
		minElements.push(minElements.top());
	}
}

void MinStack::pop()
{
	myStack.pop();
	minElements.pop();
}

int MinStack::top()
{
	return myStack.top();
}

int MinStack::getMin()
{
	return minElements.top();
}
