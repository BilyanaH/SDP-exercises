#include <queue>
using namespace std;

template <typename T>
class StackWithQueue {
	queue<T> stack;
public:
	void push(T x);
	T pop();
	T top();
	bool empty() const;
};



template<typename T>
void StackWithQueue<T>::push(T x)
{	
	stack.push(x);
	int n = stack.size();
	while (n>=0)
	{
		int el = stack.front();
		stack.pop();
		stack.push(el);
		n--;
	}
}

template<typename T>
T StackWithQueue<T>::pop()
{
	
	T el = stack.front();
	stack.pop();
	return el;
}

template<typename T>
T StackWithQueue<T>::top()
{
	
	return stack.front();
}

template<typename T>
bool StackWithQueue<T>::empty() const
{
	return stack.empty();
}
