#include "BSTIterator.h"

void BSTIterator::pushLeftChildren(TreeNode* root) {
    while (root) {
        s.push(root);
        root = root->left;
    }
}

BSTIterator::BSTIterator(TreeNode* root)
{
    pushLeftChildren(root);
}

int BSTIterator::next()
{
	index++;
	if (index == inorder.size())
	{    
		TreeNode* top = s.top();
		inorder.push_back(s.top()->data);
		s.pop();
		pushLeftChildren(top->right);
		return top->data;
	}
	return inorder[index];

}

bool BSTIterator::hasNext()
{
	return index< inorder.size()-1||!s.empty();
}

bool BSTIterator::hasPrev()
{
    return index>0;
}

int BSTIterator::prev()
{
    return inorder[--index];
}
