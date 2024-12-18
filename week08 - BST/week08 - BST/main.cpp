#include "BSTIterator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


void writeDot(TreeNode* root, std::ofstream& out) {
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

void generateDot(TreeNode* root, const std::string& filename) {
	std::ofstream out(filename);
	if (!out) return;
	out << "digraph Tree {\nnode [shape=circle];\n";
	writeDot(root, out);
	out << "}\n";
}
//dot -Tpng tree.dot -o tree.png

//0
bool isValidBST(TreeNode* root, TreeNode* minNode = nullptr, TreeNode* maxNode = nullptr) {
	if (!root)
		return true;
	if ((maxNode && root->data > maxNode->data) || (minNode && root->data < minNode->data))
		return false;
	return isValidBST(root->left, minNode, root) && isValidBST(root->right, root, maxNode);
}
//1
TreeNode* findKMin(TreeNode* node, int& k) {
	if (!node) {
		return nullptr;
	}
	TreeNode* kSmallest = findKMin(node->left, k);
	if (kSmallest)
		return kSmallest;
	k--;
	if (k == 0) {
		return node;
	}
	findKMin(node->right, k);

}
//2
std::string serialize(TreeNode* node) {
	if (!node)
		return "";
	return std::to_string(node->data) + " " + serialize(node->left) + serialize(node->right);
}
TreeNode* buildTree(std::vector<int>::iterator start, std::vector<int>::iterator end)
{
	if (start == end)
	{
		return nullptr;
	}
	auto rightSubtreeStart = std::upper_bound(start + 1, end, *start);
	TreeNode* node = new TreeNode(*start);
	node->left = buildTree(start + 1, rightSubtreeStart);
	node->right = buildTree(rightSubtreeStart, end);
	return node;
}
TreeNode* deserialize(std::string input) {
	std::vector<int> preorder;
	std::stringstream ss(input);
	for (std::string s; ss >> s;)
	{
		preorder.push_back(std::stoi(s));
	}
	return buildTree(preorder.begin(), preorder.end());
}
//3
struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};
TreeNode* ConvertSortedListToBinarySearchTree(ListNode* node) {
	if (!node) {
		return nullptr;
	}
	ListNode* slow = node;
	ListNode* fast = node;
	ListNode* prev = nullptr;
	while (fast && fast->next) {

		fast = fast->next->next;
		prev = slow;
		slow = slow->next;
	}

	TreeNode* root = new TreeNode(slow->val);

	if (prev) {
		prev->next = nullptr;
	}
	else {
		node = nullptr;
	}

	root->left = ConvertSortedListToBinarySearchTree(node);
	root->right = ConvertSortedListToBinarySearchTree(slow->next);

	return root;
}
//4
TreeNode* SearchInBinarySearchTree(TreeNode* root, int result) {
	if (!root)
		return nullptr;
	if (root->data == result)
		return root;

	if (result < root->data)
		SearchInBinarySearchTree(root->left, result);
	else
		SearchInBinarySearchTree(root->right, result);
}
//5
void InsertIntoBinarySearchTree(TreeNode* root, int toAdd) {
	if (toAdd < root->data) {
		if (!root->left) {
			root->left = new TreeNode(toAdd);
			return;
		}
		InsertIntoBinarySearchTree(root->left, toAdd);
	}
	else {
		if (!root->right) {
			root->right = new TreeNode(toAdd);
			return;
		}
		InsertIntoBinarySearchTree(root->right, toAdd);
	}
}
//6
TreeNode* findMin(TreeNode* node) {
	while (node && node->left) {
		node = node->left;
	}
	return node;
}
TreeNode* deleteMin(TreeNode* root) {
	if (!root)
		return nullptr;
	if (!root->left)
	{
		return root->right;
	}
	root->left = deleteMin(root->left);
	return root;
}
TreeNode* deleteNode(TreeNode* root, int key) {
	if (!root)
		return nullptr;
	if (key == root->data) {
		TreeNode* toDel = root;
		if (!root->left) {
			TreeNode* toReturn = root->right;
			delete toDel;
			return toReturn;
		}
		if (!root->right) {
			TreeNode* toReturn = root->left;
			delete toDel;
			return toReturn;
		}
		TreeNode* node = findMin(root->right);
		node->right = deleteMin(root->right);
		node->left = root->left;
		delete toDel;
		return node;
	}
	else if (key < root->data) {
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->data) {
		root->right = deleteNode(root->right, key);
	}
	return root;
}

void printInOrder(TreeNode* root) {
	if (!root) return;
	printInOrder(root->left);
	std::cout << root->data << " ";
	printInOrder(root->right);
}
int main() {
	TreeNode* root = new TreeNode(5);
	root->left = new TreeNode(3);
	root->right = new TreeNode(6);
	root->left->left = new TreeNode(2);
	root->left->right = new TreeNode(4);
	root->right->right = new TreeNode(7);
	generateDot(root, "tree.dot");

	std::cout << isValidBST(root) << std::endl;

	TreeNode* root1 = new TreeNode(3);
	root1->left = new TreeNode(1);
	root1->right = new TreeNode(4);
	root1->left->right = new TreeNode(2);
	generateDot(root1, "tree1.dot");

	TreeNode* root2 = new TreeNode(5);
	root2->left = new TreeNode(3);
	root2->right = new TreeNode(6);
	root2->left->left = new TreeNode(2);
	root2->left->right = new TreeNode(4);
	root2->left->left->left = new TreeNode(1);
	generateDot(root2, "tree2.dot");

	int k = 2;//number from 1 to n
	std::cout << "K smallest element int tree: " << findKMin(root, k)->data << std::endl;
	k = 1;
	std::cout << "K smallest element int tree1: " << findKMin(root1, k)->data << std::endl;
	k = 3;
	std::cout << "K smallest element int tree2: " << findKMin(root2, k)->data << std::endl;

	std::string serialized = serialize(root);
	std::cout << "Serialized Tree (Preorder): " << serialized << std::endl;
	TreeNode* deserializedRoot = deserialize(serialized);
	std::cout << "Deserialized Tree (In-order): ";
	printInOrder(deserializedRoot);
	std::cout << std::endl;

	ListNode* list = new ListNode(-10);
	list->next = new ListNode(-3);
	list->next->next = new ListNode(0);
	list->next->next->next = new ListNode(5);
	list->next->next->next->next = new ListNode(9);
	TreeNode* root3 = ConvertSortedListToBinarySearchTree(list);
	printInOrder(root3);
	generateDot(root3, "tree3.dot");

	std::cout << std::endl << SearchInBinarySearchTree(root3, -3)->data << std::endl;
	InsertIntoBinarySearchTree(root1, -1);
	InsertIntoBinarySearchTree(root1, 10);
	InsertIntoBinarySearchTree(root1, 6);
	InsertIntoBinarySearchTree(root1, 5);
	InsertIntoBinarySearchTree(root1, 9);
	InsertIntoBinarySearchTree(root1, 7);
	InsertIntoBinarySearchTree(root1, 0);
	InsertIntoBinarySearchTree(root1, -2);
	InsertIntoBinarySearchTree(root1, -3);
	generateDot(root1, "tree1_1.dot");


	root1 = deleteNode(root1, 4);
	root1 = deleteNode(root1, -3);
	root1 = deleteNode(root1, 9);
	root1 = deleteNode(root1, 3);
	generateDot(root1, "tree1_2.dot");

	TreeNode* root4 = new TreeNode(5);
	root4->left = new TreeNode(3);
	root4->right = new TreeNode(6);
	root4->left->left = new TreeNode(2);
	root4->left->right = new TreeNode(4);
	root4->left->left->left = new TreeNode(1);

	BSTIterator iterator(root4);

	std::cout << "In-order traversal of the BST: ";
	while (iterator.hasNext()) {
		std::cout << iterator.next() << " ";
	}
	std::cout << std::endl;

	delete root->left->left;
	delete root->left->right;
	delete root->left;
	delete root->right->right;
	delete root->right;
	delete root;

	delete root1->left->right;
	delete root1->left;
	delete root1->right;
	delete root1;

	delete root2->left->left->left;
	delete root2->left->left;
	delete root2->left->right;
	delete root2->left;
	delete root2->right;
	delete root2;

	delete deserializedRoot->left->left;
	delete deserializedRoot->left->right;
	delete deserializedRoot->left;
	delete deserializedRoot->right->right;
	delete deserializedRoot->right;
	delete deserializedRoot;

	delete root3->left->left;
	delete root3->left;
	delete root3->right;
	delete root3;

	delete root4->left->left->left;
	delete root4->left->left;
	delete root4->left->right;
	delete root4->left;
	delete root4->right;
	delete root4;

	while (list) {
		ListNode* temp = list;
		list = list->next;
		delete temp;
	}



	return 0;
}