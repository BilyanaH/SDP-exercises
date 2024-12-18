#include <stack>
#include <vector>
#ifndef BSTITERATOR_H
#define BSTITERATOR_H

struct TreeNode {
	int data;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : data(x), left(nullptr), right(nullptr) {}
};

class BSTIterator {
	std::stack<TreeNode*> s;
	std::vector<int> inorder;
	int index=-1;
	void pushLeftChildren(TreeNode* root);
    
public:
    BSTIterator(TreeNode* root);

    int next();

    bool hasNext();

	bool hasPrev();

	int prev();
};

#endif // BSTITERATOR_H
