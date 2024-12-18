#include <iostream>
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
TreeNode* invertBinaryTree(TreeNode* root) {
	if (root == nullptr) 
        return nullptr;
	TreeNode* left = invertBinaryTree(root->left);
	TreeNode* right = invertBinaryTree(root->right);
    root->left = right;
    root->right = left;
    return root;
}
void printTree(TreeNode* root, int space = 0, int height = 5) {
    if (root == nullptr) return;

    space += height;
    printTree(root->right, space);

    std::cout << std::endl;
    for (int i = height; i < space; i++) std::cout << ' ';
    std::cout << root->val << "\n";

    printTree(root->left, space);
}
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

struct Node {
    int key;          // ????
    Node* left;      // ???? ????????
    Node* right;     // ????? ???????o
    Node* parent;    // ????
    int bFactor;     // ?????? ??????
};

int main() {
    TreeNode* root1 = new TreeNode(4);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(7);
    root1->left->left = new TreeNode(1);
    root1->left->right = new TreeNode(3);
    root1->right->left = new TreeNode(6);
    root1->right->right = new TreeNode(9);

    std::cout << "Original tree 1:\n";
    printTree(root1);
    std::cout << std::endl;

    root1 = invertBinaryTree(root1);

    std::cout << "Inverted tree 1:\n";
    printTree(root1);
    std::cout << std::endl;

    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->left->left = new TreeNode(4);
    root2->left->right = new TreeNode(5);

    std::cout << "Original tree 2:\n";
    printTree(root2);
    std::cout << std::endl;

    root2 = invertBinaryTree(root2);

    std::cout << "Inverted tree 2:\n";
    printTree(root2);
    std::cout << std::endl;

    TreeNode* root3 = new TreeNode(1);
    root3->right = new TreeNode(2);
    root3->right->right = new TreeNode(3);

    std::cout << "Original tree 3:\n";
    printTree(root3);
    std::cout << std::endl;

    root3 = invertBinaryTree(root3);

    std::cout << "Inverted tree 3:\n";
    printTree(root3);
    std::cout << std::endl;

    deleteTree(root1);
    deleteTree(root2);
    deleteTree(root3);


	return 0;
}