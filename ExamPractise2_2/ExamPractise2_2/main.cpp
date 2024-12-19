#include <iostream>
#include <vector>
#include <cassert>

template <typename T>
struct Node {
	T data;
	Node* left;
	Node* right;
};
bool tryReadWord(const Node<char>* tree, const char* word, int length) {
	if (length == 0)
		return true;
	if (tree == nullptr) {
		return false;
	}
	if (tree->data == *word) {
		word++;
		length--;
		if (tryReadWord(tree->left, word, length) || tryReadWord(tree->right, word, length)) {
			return true;
		}
	}
	return false;
}
bool readWord(const Node<char>* tree, const char* word) {
	int size = strlen(word);
	if (size < 4) {
		return false;
	}

	for (size_t i = 2; i < size - 1; i++)
	{
		if (word[i] == tree->right->data)
			return tryReadWord(tree->left, word, i) && tryReadWord(tree->right, word + i, size - i);
	}
	return false;
}
int maxLevel(const Node<char>* tree) {
	if (tree == nullptr) {
		return 0;
	}
	std::vector<const Node<char>*> nodes;
	nodes.push_back(tree);
	int level = 0, iter = 0;
	const Node<char>* prev = nullptr;
	while (!nodes.empty())
	{
		int size = nodes.size();
		bool flag = true;
		for (size_t i = 0; i < size; i++)
		{
			tree = nodes[0];
			if (prev &&  prev->data > tree->data)
				flag = false;
			if (tree->left != nullptr)
				nodes.push_back(tree->left);
			if (tree->right != nullptr)
				nodes.push_back(tree->right);
			prev = tree;
			nodes.erase(nodes.begin());

		}
		iter++;
		prev = nullptr;
		if (flag)
			level = iter;
	}
	return level;
}

void deleteTree(Node<char>* tree) {
	if (tree == nullptr) {
		return;
	}
	deleteTree(tree->left);
	deleteTree(tree->right);
	delete tree;
}

void printTree(Node<char>* root, int space = 0, int height = 5) {
	if (root == nullptr) return;

	space += height;
	printTree(root->right, space);

	std::cout << std::endl;
	for (int i = height; i < space; i++) std::cout << ' ';
	std::cout << root->data << "\n";

	printTree(root->left, space);
}

    template <typename T>
    struct DLListElem {
        T data;
        DLListElem* next;
        DLListElem* prev;
    };

    template <typename T>
    void sortAscending(DLListElem<T>* start, DLListElem<T>* end) {
        if (start == nullptr || start == end) return;
        bool swapped;
        do {
            swapped = false;
            DLListElem<T>* current = start;
            while (current->next != end) {
                if (current->data > current->next->data) {
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
            end = current;
        } while (swapped);
    }

    /*
    Time complexity: O(n^2)
    The function uses a bubble sort algorithm, which has a time complexity of O(n^2) in the worst case.
    */

int main() {
	Node<char>* c = new Node<char>{ 'c', nullptr, nullptr };
	Node<char>* e = new Node<char>{ 'e', nullptr, nullptr };
	Node<char>* h = new Node<char>{ 'h', nullptr, nullptr };
	Node<char>* a = new Node<char>{ 'a', nullptr, nullptr };
	Node<char>* d = new Node<char>{ 'd', c, e };
	Node<char>* i = new Node<char>{ 'i', h, nullptr };
	Node<char>* b = new Node<char>{ 'b', a, d };
	Node<char>* g = new Node<char>{ 'g', i, nullptr };
	Node<char>* f = new Node<char>{ 'f', b, g };
	printTree(f);
	Node<char>* root = f;

	assert(readWord(root, "bdcgi") == true);
	assert(readWord(root, "bdgi") == true);
	assert(readWord(root, "bcdgi") == false);
	assert(readWord(root, "bdgh") == false);

	Node<char>* singleNode = new Node<char>{ 'a', nullptr, nullptr };
	
	Node<char>* leftChild = new Node<char>{ 'a', nullptr, nullptr };
	Node<char>* rightChild = new Node<char>{ 'b', nullptr, nullptr };
	Node<char>* root2 = new Node<char>{ 'c', leftChild, rightChild };
	
	Node<char>* leftChild2 = new Node<char>{ 'b', nullptr, nullptr };
	Node<char>* rightChild2 = new Node<char>{ 'a', nullptr, nullptr };
	Node<char>* root3 = new Node<char>{ 'c', leftChild2, rightChild2 };
	
;
    Node<char>* d1 = new Node<char>{ 'd', nullptr, nullptr };
    Node<char>* c1 = new Node<char>{ 'c', nullptr, nullptr };
    Node<char>* b1 = new Node<char>{ 'b', nullptr, nullptr };
    Node<char>* a1 = new Node<char>{ 'a', nullptr, nullptr };
    Node<char>* e1 = new Node<char>{ 'e', b1, a1 };
    Node<char>* f1 = new Node<char>{ 'f', d1, c1 };
    Node<char>* h1 = new Node<char>{ 'h', f1, e1 };

	std::cout << "Tree: ";
	printTree(h1);
	std::cout << std::endl;

	assert(maxLevel(root) == 4);
	assert(maxLevel(singleNode) == 1);
	assert(maxLevel(root2) == 2);
	assert(maxLevel(root3) == 1);
	assert(maxLevel(h1) == 1);

	std::cout << "All tests passed!" << std::endl;

	deleteTree(root);
	deleteTree(singleNode);
	deleteTree(root2);
	deleteTree(root3);
	deleteTree(h);

	return 0;

}