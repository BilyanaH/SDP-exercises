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
int Friends(int n, int k) {
	queue<int> q;
	for (size_t i = 1; i <= n; i++)
	{
		q.push(i);
	}
	while (q.size() != 1) {
		for (size_t i = 1; i < k; i++)
		{
			int person = q.front();
			q.pop();
			q.push(person);
		}
		q.pop();
	}
	return q.front();
}
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	queue<int> q;
	vector<int> output;
	int i = 0;
	int max = nums[i];
	while (q.size() < k) {
		if (nums[i] > max) {
			max = nums[i];
		}
		q.push(nums[i++]);
	}
	output.push_back(max);
	while (i < nums.size()) {
		int exitingElement = q.front();
		q.push(nums[i++]);
		q.pop();
		if (exitingElement == max) {
			max = INT_MIN;
			std::queue<int> tempQueue = q;
			while (!tempQueue.empty()) {
				max = std::max(max, tempQueue.front());
				tempQueue.pop();
			}
		}
		else {
			max = std::max(max, nums[i]);
		}
		output.push_back(max);
	}
	return output;
}

struct Cell {
	int x, y, dist;
};
int row[] = { -1, 0, 0, 1 };
int col[] = { 0, -1, 1, 0 };
bool isValid(std::vector<std::vector<int>> const& mat,
	std::vector<std::vector<bool>>& visited,
	int row, int col)
{
	return (row >= 0 && row < mat.size()) && (col >= 0 && col < mat[0].size()) && mat[row][col] && !visited[row][col];
}
int findShortestPathLength(vector<vector<int>> const& mat, Cell& src, Cell& dest) {
	if (mat.size() == 0 || mat[src.x][src.y] == 0 ||
		mat[dest.x][dest.y] == 0)
	{
		return -1;
	}
	int M = mat.size();
	int N = mat[0].size();
	std::vector<std::vector<bool>> visited; // = std::vector<bool>(M, std::vector<bool>(N))
	visited.resize(M, vector<bool>(N));

	std::queue<Cell> q;

	int i = src.x;
	int j = src.y;
	visited[i][j] = true;
	q.push({ i,j,0 });

	while (!q.empty())
	{
		Cell cell = q.front();
		q.pop();
		int i = cell.x, j = cell.y, dist = cell.dist;
		if (i == dest.x && j == dest.y) {
			return cell.dist;
		}
		for (int k = 0; k < 4; k++)
		{
			if (isValid(mat, visited, i + row[k], j + col[k]))
			{
				// mark next cell as visited and enqueue it
				visited[i + row[k]][j + col[k]] = true;
				q.push({ i + row[k], j + col[k], dist + 1 });
			}
		}
	}
	return -1;
}

struct Warrior {
	int attack;
	int position;
	bool isAlive;
};
vector<int> BridgeBattle(vector<int> input) {
	std::queue<Warrior*> negatives;
	std::stack<Warrior*> positives;
	std::vector<Warrior*> warriors(input.size());
	for (size_t i = 0; i < input.size(); i++)
	{
		Warrior* warrior = new Warrior();
		warrior->attack = input[i];
		warrior->position = i;
		warrior->isAlive = true;
		warriors[i] = warrior;
	}
	bool hasPositive = false;
	bool hasNegative = false;
	for (int i = 0; i < input.size(); i++)
	{
		if (warriors[i]->attack < 0)
		{
			hasNegative = true;
			negatives.push(warriors[i]);
			if (positives.empty()) {
				negatives.pop();
			}
			if (!hasPositive) {
				continue;
			}
			for (size_t j = i + 1; j < warriors.size(); j++)
			{
				if (warriors[j]->attack < 0) {
					negatives.push(warriors[j]);
					i++;
				}
				else {
					break;
				}
			}
			while (!positives.empty() && !negatives.empty()) {
				Warrior* positive = positives.top();
				Warrior* negative = negatives.front();
				if (positive->attack == abs(negative->attack)) {
					positive->isAlive = false;
					negative->isAlive = false;
					positives.pop();
					negatives.pop();
				}
				else if (positive->attack < abs(negative->attack))
				{
					positive->isAlive = false;
					positives.pop();
				}
				else
				{
					negative->isAlive = false;
					negatives.pop();
				}
				hasPositive = false;
			}
			while (!negatives.empty())
			{
				negatives.pop();
			}
		}
		else
		{
			positives.push(warriors[i]);
			hasPositive = true;
		}
	}
	if (!hasNegative)
	{
		std::cout << std::endl;
	}

	// Събиране на резултатите
	vector<int> result;
	for (Warrior* warrior : warriors) {
		if (warrior->isAlive) {
			result.push_back(warrior->attack);
		}
	}

	return result;

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
	//4
	BinaryNumbers(16);
	//5
	assert(Friends(5, 2) == 3);
	assert(Friends(6, 5) == 1);
	//6	
	// Test case 1
	std::vector<int> nums1 = { 1 };
	int k1 = 1;
	std::vector<int> expected1 = { 1 };
	assert(maxSlidingWindow(nums1, k1) == expected1);

	// Test case 2
	std::vector<int> nums2 = { 1, -1 };
	int k2 = 1;
	std::vector<int> expected2 = { 1, -1 };
	assert(maxSlidingWindow(nums2, k2) == expected2);

	// Test case 3
	std::vector<int> nums3 = { 9, 11 };
	int k3 = 2;
	std::vector<int> expected3 = { 11 };
	assert(maxSlidingWindow(nums3, k3) == expected3);

	// Test case 4
	std::vector<int> nums4 = { 4, -2 };
	int k4 = 2;
	std::vector<int> expected4 = { 4 };
	assert(maxSlidingWindow(nums4, k4) == expected4);
	//7
	vector<vector<int>> maze = {
	   { 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
	   { 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
	   { 0, 0, 1, 0, 1, 1, 1, 0, 0, 1 },
	   { 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
	   { 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
	   { 1, 0, 1, 1, 1, 0, 0, 1, 1, 0 },
	   { 0, 0, 0, 0, 1, 0, 0, 1, 0, 1 },
	   { 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
	   { 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
	   { 0, 0, 1, 0, 0, 1, 1, 0, 0, 1 }
	};

	Cell source = { 0, 0 };
	Cell destination = { 7, 5 };
	assert(findShortestPathLength(maze, source, destination) == 12);
	//8
	std::vector<int> expected8 = { -1, -2, -7, -8, 2, 3 };
	assert(BridgeBattle({ -1, -2, 4, 5, 6, -3, -6, -7, -8, 2, 3 }) == expected8);
	return 0;

	/*Input: [-1, -2, 4, 5, 6, -3, -6, -7, -8, 2, 3]
	Output: -1 - 2 - 7 - 8 2 3
	Explanation :
	Бойците със сила - 1 - 2 имат знак минус,
	тоест се движат от дясно наляво и тъй като
	започваме с тях, това означава, че са преминали
	успешно моста, защото не са срещнали никой по пътя
	си.Битка става при засечка на положителна с
	отрицателна стойност само ако отрицателната
	стойност е подадена след конкретната положителна.
	Битката на моста се води от 4 5 6 - 3 - 6 - 7 - 8.
	Тъй като при тях е станала засечка.Първият дуел е
	между б и - 3. 6 > 3 и го изхвърля.След това
	б срещу - б се изхвърлят взаимно 6 = 6.
	След тях - 7 последователно отстранява 5 и 4
	(7 > 5, 7 > 4).В крайна сметка - 7 и - 8
	преминават успешно моста.За бойците 2 и 3,
	които са в края аналогично(те са бойци със
	знак + тоест се движат от ляво надясно и тъй
	като след ТЯХ Няма отрицателни числа те не са
	засекли никой по пътя си).Цялостно всички
	преминали по моста са : -1 - 2 - 7 - 8 2 3.
	(Последователността на числата на изхода е
		същата като тази на входа.)*/
}
