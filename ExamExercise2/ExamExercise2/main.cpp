#include <iostream>
#include <stack>
#include <queue>
#include <fstream>

template <typename T>
struct Node {
	T data;
	Node<T>* left, * right;
};

template <typename T>
void writeDot(Node<T>* root, std::ofstream& out) {
	if (!root) return;
	if (root->left) {
		out << "\"" << root->data << "\" -> \"" << root->left->data
			<< "\" [label=\"L\", dir=both, arrowhead=normal, arrowtail=none];\n";
		writeDot(root->left, out);
	}
	if (root->right) {
		out << "\"" << root->data << "\" -> \"" << root->right->data
			<< "\" [label=\"R\", dir=both, arrowhead=normal, arrowtail=none];\n";
		writeDot(root->right, out);
	}
}
template <typename T>
void generateDot(Node<T>* root, const std::string& filename) {
	std::ofstream out(filename);
	if (!out) return;
	out << "digraph Tree {\nnode [shape=circle];\n";
	out << "splines=polyline;\n";
	out << "rankdir=TB;\n";
	writeDot(root, out);
	out << "}\n";
}
//dot -Tpng tree.dot -o tree.png


bool iseven(int a) {
	return a % 2 == 0;
}
bool isOddEven(Node<int>* root) {
	std::queue< Node<int>*> q;
	Node<int>* node;
	Node<int>* prev;

	int level = 0;
	if (root) {
		node = root;
		prev = root;
		q.push(node);
	}
	while (!q.empty())
	{
		int stackSize = q.size();
		bool isFirst = true;
		node = q.front();
		prev = q.front();
		for (size_t i = 0; i < stackSize; i++)
		{
			if (iseven(level) && iseven(node->data) || !iseven(level) && !iseven(node->data)) {
				return false;
			}
			if (iseven(level) && !isFirst && prev->data > node->data) {
				return false;
			}
			else if (!iseven(level) && !isFirst && prev->data < node->data) {
				return false;
			}
			if (node->left) {
				q.push(node->left);
			}
			if (node->right) {
				q.push(node->right);
			}
			q.pop();
			prev = node;
			if (!q.empty())
				node = q.front();
			isFirst = false;
		}
		level++;
	}
	return true;
}

bool isBalancedBSTHelper(Node<int>* root, int& height, int minVal, int maxVal) {
	if (!root) {
		height = 0;
		return true;
	}
	if (root->data < minVal || root->data > maxVal) {
		return false;
	}
	int leftHeight = 0, rightHeight = 0;

	bool leftBalanced = isBalancedBSTHelper(root->left, leftHeight, minVal, root->data);
	bool rightBalanced = isBalancedBSTHelper(root->right, rightHeight, root->data, maxVal);

	height = 1 + std::max(leftHeight, rightHeight);

	if (abs(leftHeight - rightHeight) > 1) {
		return false;
	}

	return leftBalanced && rightBalanced;
}

bool isBalancedBST(Node<int>* root) {
	int height = 0;
	return isBalancedBSTHelper(root, height, INT_MIN, INT_MAX);
}
Node<std::string>* findWordRecursive(Node<std::string>* node, const std::string& word, int& index, Node<std::string>*& startNode) {
	if (!node)
		return startNode;
	findWordRecursive(node->left, word, index, startNode);
	if (startNode != nullptr) {
		if (word.compare(index, node->data.size(), node->data) == 0) {
			index += node->data.size();
		}
		else if(index != word.size()){
			startNode = nullptr;
			index = 0;
		}
	}
	if (startNode == nullptr) {
		if (word.compare(index, node->data.size(), node->data) == 0) {
			startNode = node;
			index += node->data.size();
		}
	}
	 findWordRecursive(node->right, word, index, startNode);
}
Node<std::string>* findWord(Node<std::string>* root, std::string word)
{
	int index = 0;
	Node<std::string>* startNode = nullptr;
	return findWordRecursive(root, word, index, startNode);

}
int main() {
	Node<int>* root = new Node<int>{ 1, nullptr, nullptr };
	root->left = new Node<int>{ 10, nullptr, nullptr };
	root->right = new Node<int>{ 4, nullptr, nullptr };
	root->left->left = new Node<int>{ 3, nullptr, nullptr };
	root->right->left = new Node<int>{ 7, nullptr, nullptr };
	root->right->right = new Node<int>{ 9, nullptr, nullptr };
	root->left->left->left = new Node<int>{ 12, nullptr, nullptr };
	root->left->left->right = new Node<int>{ 8, nullptr, nullptr };
	root->right->left->left = new Node<int>{ 6, nullptr, nullptr };
	root->right->right->right = new Node<int>{ 2, nullptr, nullptr };


	Node<int>* root2 = new Node<int>{ 10, nullptr, nullptr };
	root2->left = new Node<int>{ 9, nullptr, nullptr };
	root2->right = new Node<int>{ 13, nullptr, nullptr };
	root2->left->left = new Node<int>{ 5, nullptr, nullptr };
	root2->right->left = new Node<int>{ 12, nullptr, nullptr };
	root2->right->right = new Node<int>{ 15, nullptr, nullptr };
	root2->left->left->left = new Node<int>{ 3, nullptr, nullptr };
	//	root2->left->left->left->left = new Node<int>{ 2, nullptr, nullptr };
	//	root2->left->left->left->left->left = new Node<int>{ 1, nullptr, nullptr };
	root2->left->left->right = new Node<int>{ 6, nullptr, nullptr };
	root2->right->left->left = new Node<int>{ 11, nullptr, nullptr };
	root2->right->right->right = new Node<int>{ 20, nullptr, nullptr };
	root2->right->right->right->right = new Node<int>{ 21, nullptr, nullptr };
	//root2->right->right->right->right->right = new Node<int>{ 22, nullptr, nullptr };
	//root2->right->right->right->right->right->right = new Node<int>{ 23, nullptr, nullptr };

	Node<int>* root3 = new Node<int>{ 10, nullptr, nullptr };
	root3->left = new Node<int>{ 5, nullptr, nullptr };
	root3->right = new Node<int>{ 15, nullptr, nullptr };
	root3->left->left = new Node<int>{ 2, nullptr, nullptr };
	root3->left->right = new Node<int>{ 7, nullptr, nullptr };
	root3->right->left = new Node<int>{ 12, nullptr, nullptr };
	root3->right->right = new Node<int>{ 20, nullptr, nullptr };
	root3->right->right->right = new Node<int>{ 21, nullptr, nullptr };
	root3->right->right->right->right = new Node<int>{ 22, nullptr, nullptr };

	generateDot(root, "tree.dot");
	generateDot(root2, "tree2.dot");
	generateDot(root3, "tree3.dot");
	std::cout << isOddEven(root) << std::endl;
	//std::cout << isBalancedBST(root2) << std::endl;
	std::cout << isBalancedBST(root3) << std::endl;

	Node<std::string>* root4 = new Node<std::string>{ "xel", nullptr, nullptr };
	root4->left = new Node<std::string>{ "go", nullptr, nullptr };
	root4->left->left = new Node<std::string>{ "al", nullptr, nullptr };
	root4->left->left->left = new Node<std::string>{ "a", nullptr, nullptr };
	root4->left->right = new Node<std::string>{ "thms", nullptr, nullptr };
	root4->left->right->left = new Node<std::string>{ "ri", nullptr, nullptr };
	root4->left->right->right = new Node<std::string>{ "u", nullptr, nullptr };
	root4->right = new Node < std::string>{ "yes", nullptr, nullptr };
	root4->right->left = new Node < std::string>{ "ya", nullptr, nullptr };
	root4->right->right = new Node < std::string>{ "za", nullptr, nullptr };
	generateDot(root4, "tree4.dot");
	std::string word = "uxelyayesza";

	Node<std::string>* result = findWord(root4, word);
	if (result)
		std::cout << "Found word starting at node: " << result->data << std::endl;

	delete root->left->left->left;
	delete root->left->left->right;
	delete root->right->left->left;
	delete root->right->right->right;
	delete root->left->left;
	delete root->right->left;
	delete root->right->right;
	delete root->left;
	delete root->right;
	delete root;

	delete root2->left->left->left;
	delete root2->left->left->right;
	delete root2->right->left->left;
	delete root2->right->right->right;
	delete root2->left->left;
	delete root2->right->left;
	delete root2->right->right;
	delete root2->left;
	delete root2->right;
	delete root2;
	return 0;
}