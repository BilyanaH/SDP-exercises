#include <stack>
using namespace std;

template <typename T>
class QueueWithStack {
private:
	stack<T> inputStack;
	stack<T> outputStack;
	void transfer();
public:
	void push(T x);
	T pop();
	T peek();
	bool empty() const;
};

template<typename T>
void QueueWithStack<T>::transfer()
{
	while (!inputStack.empty()) {
		outputStack.push(inputStack.top());
		inputStack.pop();
	}
}

template <typename T>
void QueueWithStack<T>::push(T x) {
	inputStack.push(x);
}

template<typename T>
T QueueWithStack<T>::pop()
{
	if (outputStack.empty()) {
		transfer();
	}
	T topElement = outputStack.top();
	outputStack.pop();
	return topElement;
}

template<typename T>
T QueueWithStack<T>::peek()
{
	if (outputStack.empty()) {
		transfer();
	}
	return outputStack.top();
}

template<typename T>
bool QueueWithStack<T>::empty() const
{
	return inputStack.empty() && outputStack.empty();
}
