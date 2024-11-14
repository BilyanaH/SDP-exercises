#include <iostream>
#include <stack>
#include <string>
#include <cassert>
#include <vector>

struct Interval
{
    int begin, end;

    bool operator<(Interval const& i)
    {
        return (begin < i.begin);
    }
    
    bool operator==(const Interval& other) const {
        return begin == other.begin && end == other.end;
    }
};

// Functions from original code
string ReverseWordOrder(string line);
bool Brackets(string line);
int ReversePolishNotation(string line);
int SimpleCalculator(string line);
int Calculator(string line);
string SimplifyPath(string inputPath);
int Plants(std::vector<int> plants);
vector<Interval> Intervals(vector<Interval>);

// Test functions
void testReverseWordOrder() {
    assert(ReverseWordOrder("hello world") == "world hello");
    assert(ReverseWordOrder("This is a test") == "test a is This");
    assert(ReverseWordOrder("SingleWord") == "SingleWord"); // No reversal needed
    assert(ReverseWordOrder("") == ""); // Empty input
}

void testBrackets() {
    // Valid cases
    assert(Brackets("{[]}()[({()(())})]") == true);  // Nested and matching
    assert(Brackets("()[]{}") == true);  // Simple pairs

    // Invalid cases
    assert(Brackets("{[}()]") == false);  // Incorrectly matched
    assert(Brackets("([)]") == false);  // Incorrect nesting
    assert(Brackets("(((") == false);    // Unmatched brackets
}

void testMinStack() {
    MinStack minStack;

    // Test pushing elements
    minStack.push(5);
    assert(minStack.getMin() == 5);  // Minimum is 5
    minStack.push(3);
    assert(minStack.getMin() == 3);  // Minimum is 3
    minStack.push(7);
    assert(minStack.getMin() == 3);  // Minimum is still 3
    minStack.push(2);
    assert(minStack.getMin() == 2);  // Minimum is now 2
    minStack.push(4);
    assert(minStack.getMin() == 2);  // Minimum is still 2

    // Test top element
    assert(minStack.top() == 4);      // Top is 4

    // Test popping elements
    minStack.pop();
    assert(minStack.getMin() == 2);  // Minimum is still 2
    minStack.pop();
    assert(minStack.getMin() == 3);  // Minimum is still 3
    minStack.pop();
    assert(minStack.getMin() == 3);  // Minimum is back to 3
    minStack.pop();
    assert(minStack.getMin() == 5);  // Minimum is back to 5

    // Test popping last element
    minStack.pop();
    // Now the stack is empty, we cannot get min or top, ensure no call after this will cause issues
    // Test if we can still push a new element
    minStack.push(10);
    assert(minStack.getMin() == 10); // Minimum is now 10
}
void testReversePolishNotation() {
    // Basic operations
    assert(ReversePolishNotation("23+") == 5);     // 2 + 3
    assert(ReversePolishNotation("34*") == 12);    // 3 * 4
    assert(ReversePolishNotation("42/") == 2);     // 4 / 2
    assert(ReversePolishNotation("93-") == 6);     // 9 - 3

    // Complex expressions
    assert(ReversePolishNotation("21+3*") == 9);   // (2 + 1) * 3
    assert(ReversePolishNotation("123*+") == 7);   // 1 + (2 * 3)
}

void testSimpleCalculator() {
    // Basic arithmetic
    assert(SimpleCalculator("1+1") == 2);
    assert(SimpleCalculator("2-1") == 1);
    assert(SimpleCalculator("2+(3-1)") == 4);

    // Multiple operations
    assert(SimpleCalculator("(1+(4+5+2)-3)+(6+8)") == 23);
    assert(SimpleCalculator("10+(2-(3+2))") == 7);      // Nested parentheses

    // Edge cases
    assert(SimpleCalculator("0") == 0);                 // Single digit
    assert(SimpleCalculator("10-10") == 0);             // Zero result
    assert(SimpleCalculator("((3))") == 3);             // Extra parentheses
}

void testCalculator() {
    assert(Calculator("3+2*2") == 7);
    assert(Calculator(" 3/2 ") == 1);
    assert(Calculator(" 3+5 / 2 ") == 5);
}

void testSimplifyPath() {
    string input1 = "/home/";
    string input2 = "/../";
    string input3 = "/home//foo/";
    string input4 = "/a/./b/../../c/";
    string input5 = "/a//b////c/d//././/..";

    string output1 = "/home";
    string output2 = "/";
    string output3 = "/home/foo";
    string output4 = "/c";
    string output5 = "/a/b/c";

    assert(output1 == SimplifyPath(input1));
    assert(output2 == SimplifyPath(input2));
    assert(output3 == SimplifyPath(input3));
    assert(output4 == SimplifyPath(input4));
    assert(output5 == SimplifyPath(input5));
}

void testPlants() 
{
    assert(Plants({ 3, 6, 2, 7, 5 }) == 2);
    assert(Plants({ 6, 5, 8, 4, 7, 10, 9 }) == 2);;
    assert(Plants({ 10, 8, 6, 5, 5 }) == 0);
    assert(Plants({ 1, 2, 3, 4, 5 }) == 1);
    assert(Plants({ 4, 4, 4, 4 }) == 0);
    assert(Plants({ 7 }) == 0);
    assert(Plants({ 5, 10, 5, 10, 5 }) == 1);
    assert(Plants({ 8, 4, 7, 3, 2, 6, 5, 7 }) == 2);
    assert(Plants({ 1000, 999, 998, 997, 996, 995 }) == 0);
    assert(Plants({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }) == 1);
    assert(Plants({ 10, 3, 7, 4, 8, 2, 9, 1 }) == 2);
}

void testIntervals() {
    std::vector<Interval> intervals1 = { {1, 5}, {2, 3}, {4, 6}, {7, 8}, {8, 10}, {12, 15} };
    std::vector<Interval> expected1 = { {1, 6}, {7, 10}, {12, 15} };
    assert(Intervals(intervals1) == expected1);

    std::vector<Interval> intervals2 = { {1, 3}, {2, 4}, {5, 7}, {6, 8} };
    std::vector<Interval> expected2 = { {1, 4}, {5, 8} };
    assert(Intervals(intervals2) == expected2);

    std::vector<Interval> intervals3 = { {1, 2}, {3, 4}, {5, 6} };
    std::vector<Interval> expected3 = { {1, 2}, {3, 4}, {5, 6} };
    assert(Intervals(intervals3) == expected3);

    std::vector<Interval> intervals4 = { {1, 10}, {2, 6}, {8, 10} };
    std::vector<Interval> expected4 = { {1, 10} };
    assert(Intervals(intervals4) == expected4);

    std::vector<Interval> intervals5 = { {5, 7} };
    std::vector<Interval> expected5 = { {5, 7} };
    assert(Intervals(intervals5) == expected5);
}
