#include "MinStack.hpp"
#include "tests.cpp"
#include <iostream>
#include <stack>
#include <string.h>
#include <assert.h>
#include <sstream>
#include <algorithm>

using namespace std;

string ReverseWordOrder(string line) {
	stack<string> s;
	string word;
	std::istringstream stream(line);
	while (stream >> word) {

		s.push(word);
	}
	string text;
	while (!s.empty()) {
		text.append(s.top());
		s.pop();
		if (!s.empty()) {
			text.append(" ");
		}
	}
	return text;
}

bool Brackets(string line) {
	stack<char> stack;
	size_t lengthLine = line.length();
	for (size_t i = 0; i < lengthLine; i++)
	{
		char symbolNow = line[i];
		if (symbolNow == '(' || symbolNow == '[' || symbolNow == '{') {
			stack.push(symbolNow);
		}
		else if (symbolNow == ')') {
			if (stack.top() == '(') {
				stack.pop();
			}
			else {
				return false;
			}
		}
		else if (symbolNow == '}') {
			if (stack.top() == '{') {
				stack.pop();
			}
			else {
				return false;
			}
		}
		else if (symbolNow == ']') {
			if (stack.top() == '[') {
				stack.pop();
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	if (!stack.empty()) {
		return false;
	}
	return true;
}

int ReversePolishNotation(string line) {
	size_t lengthLine = line.length();
	stack<int> myStack;
	for (size_t i = 0; i < lengthLine; i++)
	{
		char symbolNow = line[i];
		if (symbolNow == '*') {
			int b = myStack.top();
			myStack.pop();
			int a = myStack.top();
			myStack.pop();
			myStack.push(a * b);
		}
		else if (symbolNow == '/') {
			int b = myStack.top();
			myStack.pop();
			int a = myStack.top();
			myStack.pop();
			myStack.push(a / b);
		}
		else if (symbolNow == '+') {
			int b = myStack.top();
			myStack.pop();
			int a = myStack.top();
			myStack.pop();
			myStack.push(a + b);
		}
		else if (symbolNow == '-') {
			int b = myStack.top();
			myStack.pop();
			int a = myStack.top();
			myStack.pop();
			myStack.push(a - b);
		}
		else {
			myStack.push(line[i] - '0');
		}
	}
	return myStack.top();
}

int SimpleCalculator(string line) {
	stack<int> numbers, operators;
	int sign = 1, curr = 0;
	size_t lengthLine = line.length();
	for (size_t i = 0; i < lengthLine; i++)
	{
		char symbolNow = line[i];
		if (symbolNow >= '0' && symbolNow <= '9') {
			int num = 0;
			while (i < lengthLine && isdigit(line[i])) {
				num = num * 10 + (line[i] - '0');
				i++;
			}
			i--;
			curr += num * sign;
			sign = 1;
		}
		else if (symbolNow == '(') {
			numbers.push(curr);
			operators.push(sign);
			curr = 0;
			sign = 1;
		}
		else if (symbolNow == ')') {
			curr = curr * operators.top() + numbers.top();
			operators.pop();
			numbers.pop();
		}
		else if (symbolNow == '-') {
			sign *= -1;
		}

	}
	return curr;
}

int Calculator(string line) {
	stack<int> stack;
	int curr = 0;
	char operation = '+';
	int lengthLine = line.length();
	for (int i = 0; i < lengthLine; i++)
	{
		char currentChar = line[i];
		if (currentChar >= '0' && currentChar <= '9') {
			int num = 0;
			while (i < lengthLine && isdigit(line[i])) {
				num = num * 10 + (line[i] - '0');
				i++;
			}
			i--;
		}
		else if (!isdigit(currentChar) && !iswspace(currentChar)) {
			if (operation == '-')
			{
				stack.push(-curr);
			}
			else if (operation == '+')
			{
				stack.push(curr);
			}
			else if (operation == '*') {
				int stackTop = stack.top();
				stack.pop();
				stack.push(stackTop * curr);
			}
			else if (operation == '/') {
				int stackTop = stack.top();
				stack.pop();
				stack.push(stackTop / curr);
			}
			operation = currentChar;
			curr = 0;
		}
		int result = 0;
		while (stack.empty()) {
			result += stack.top();
			stack.pop();
		}
		return result;
	}
}

string SimplifyPath(string inputPath)
{
	stack<string> myStack;
	string result;
	int lengthPath = inputPath.length();
	for (size_t i = 0; i < lengthPath; i++)
	{
		string stringNow;
		while (isalpha(inputPath[i]) || inputPath[i] == '.')
		{
			stringNow += inputPath[i++];
		}
		if (stringNow == "..") {
			if (!myStack.empty())
				myStack.pop();
		}
		else if (!stringNow.empty() && stringNow.compare(".")) {
			myStack.push(stringNow);
		}
	}
	while (!myStack.empty())
	{
		result = '/' + myStack.top() + result;
		myStack.pop();
	}

	if (result.size() == 0)
	{
		return "/";
	}

	return result;
}

//int Plants(std::vector<int> plants)
//{
//	vector<stack<int>> stacks;
//	stack<int> temp;
//	int days = 0;
//
//	for (int i = plants.size() - 1; i >= 0; i--)
//	{
//		temp.push(plants[i]);
//		if (i == 0 || plants[i] > plants[i - 1])
//		{
//			stacks.push_back(temp);
//			temp = stack<int>();
//		}
//	}
//	while (stacks.size() > 1)
//	{
//		days++;
//		for (int i = 0; i < stacks.size() - 1; i++)
//		{
//			stacks[i].pop();
//			if (stacks[i].empty()) {
//				stacks.erase(stacks.begin() + i);
//				i--;
//			}
//		}
//		for (int i = stacks.size() - 1; i > 0; i--)
//		{
//			int first = stacks[i - 1].top();
//			int last;
//			stack<int> temp = stacks[i];
//			while (!temp.empty()) {
//				last = temp.top();
//				temp.pop();
//			}
//			if (last >= first) {
//				stack<int> reverse;
//				while (!stacks[i].empty()) {
//					reverse.push(stacks[i].top());
//					stacks[i].pop();
//				}
//				while (!reverse.empty()) {
//					stacks[i - 1].push(reverse.top());
//					reverse.pop();
//				}
//				stacks.erase(stacks.begin() + i);
//				i--;
//
//			}
//		}
//	}
//	return days;
//}

int Plants(std::vector<int> plants) {
	int n = plants.size();
	std::vector<int> days(n, 0);
	std::stack<int> s;

	for (int i = 0; i < n; i++) {
		int maxDays = 0;
		while (!s.empty() && plants[s.top()] >= plants[i]) {
			maxDays = std::max(maxDays, days[s.top()]);
			s.pop();
		}
		if (!s.empty()) {
			days[i] = maxDays + 1;
		}

		s.push(i);
	}
	return *std::max_element(days.begin(), days.end());
}


vector<Interval> Intervals(vector<Interval> intervals) {
	sort(intervals.begin(), intervals.end());

	std::stack<Interval> stack;
	int n = intervals.size();
	for (size_t i = 0; i < n; i++)
	{
		Interval curr = intervals[i];
		if (stack.empty() || curr.begin > stack.top().end)
		{
			stack.push(curr);
		}
		else if (stack.top().end < curr.end) {
			stack.top().end = curr.end;
		}
	}
	vector<Interval> output;
	while (!stack.empty())
	{
		output.push_back(stack.top());
		stack.pop();
	}

	sort(output.begin(), output.end());
	return output;
}
int main() {
	testReverseWordOrder();
	testBrackets();
	testMinStack();
	testReversePolishNotation();
	testSimpleCalculator();
	testSimplifyPath();
	testPlants();
	testIntervals();
	std::cout << "All tests passed!" << std::endl;

	return 0;
}