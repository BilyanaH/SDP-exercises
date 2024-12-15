#include <iostream>

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

};

TreeNode* findMin(TreeNode* node) {
	while (node->left) {
		node = node->left;
	}
	return node;
}
TreeNode* deleteMin(TreeNode* root) {
	if (root->left == nullptr)
	{
		return root->right;
	}
	root->left = deleteMin(root->left);
	return root;
}
TreeNode* deleteNode(TreeNode* root, int key) {
	if (!root)
		return nullptr;
	if (key < root->val) {
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->val) {
		root->right = deleteNode(root->right, key);
	}
	else {
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
	return root;
}

void printInOrder(TreeNode* root) {
	if (!root) return;
	printInOrder(root->left);
	std::cout << root->val << " ";
	printInOrder(root->right);
}
int main() {
	TreeNode* root = new TreeNode(5);
	root->left = new TreeNode(3);
	root->right = new TreeNode(6);
	root->left->left = new TreeNode(2);
	root->left->right = new TreeNode(4);
	root->right->right = new TreeNode(7);

	printInOrder(root);

	root = deleteNode(root, 3); 
	std::cout << std::endl;
	printInOrder(root);
	return 0;
}