#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <string>

struct Node
{
	int data;
	Node* left;
	Node* right;
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

void writeDot(Node* root, std::ofstream& out) {
    if (!root) return;
    if (root->left) {
        out << "\"" << root->data << "\" -> \"" << root->left->data << "\";\n";
        writeDot(root->left, out);
    }
    if (root->right) {
        out << "\"" << root->data << "\" -> \"" << root->right->data << "\";\n";
        writeDot(root->right, out);
    }
}

void generateDot(Node* root, const std::string& filename) {
    std::ofstream out(filename);
    if (!out) return;
    out << "digraph Tree {\nnode [shape=circle];\n";
    writeDot(root, out);
    out << "}\n";
}
//dot -Tpng tree.dot -o tree.png

void inorderRec(Node* node, std::vector<int>& result) {
	if (node->left) {
		inorderRec(node->left, result);
	}	
    result.push_back(node->data);
	if (node->right) {
		inorderRec(node->right, result);
	}
}
std::vector<int>& inorderIter(Node* root, std::vector<int>& result) {
    std::stack<Node*> st;
    Node* node = root;
    while (node!=nullptr || !st.empty()) {
        while (node != nullptr) {
            st.push(node);
            node = node->left;
        }
        node = st.top();
        st.pop();
        result.push_back(node->data);
        node = node->right;
    }
    return result;
}
std::vector<int> inorder(Node* root) {
	std::vector<int> result;
	//inorderRec(root, result);
    inorderIter(root, result);
	return result;
}
void testInorderTraversal(Node* root1, Node* root2) {
    std::vector<int> expected1 = { 1, 2, 3, 4, 5 };
    std::vector<int> result1 = inorder(root1);

    std::vector<int> expected2 = {9, 3, 15, 20, 7 };
    std::vector<int> result2 = inorder(root2);
    if (result1 == expected1 && result2 == expected2) {
        std::cout << "Test passed!\n";
    }
    else {
        std::cout << "Test failed!\n";
    }
}
void allPathsHelper(Node* node, std::vector<std::string>& result, std::string path) {
    if (node->left == nullptr && node->right == nullptr) {
        path.append(std::to_string(node->data));
        result.push_back(path);
        return;
    }
    path.append(std::to_string(node->data) + "->");
    allPathsHelper(node->left, result, path);
    allPathsHelper(node->right, result, path);
}
std::vector<std::string> allPaths(Node* root) {
    std::vector<std::string> result;
    std::string path;
    allPathsHelper(root, result, path);
    return result;
}

void testAllPaths(Node* root1, Node* root2) {
    std::vector<std::string> result1 = allPaths(root1);
    std::vector<std::string> result2 = allPaths(root2);
    std::vector<std::string> expected1 = {
     "4->2->1",
     "4->2->3",
     "4->5"
    };
    std::vector<std::string> expected2 = {
        "3->9",
        "3->20->15",
        "3->20->7"
    };
    if (result1 == expected1 && result2 == expected2) {
        std::cout << "Test passed!\n";
    }
    else {
        std::cout << "Test failed!\n";
    }
}

std::vector<std::vector<int>> treeLevels(Node* node) {
    std::queue<Node*> q;
    if (node) {
        q.push(node);
    }
    std::vector<std::vector<int>> result;
    while (!q.empty()) {
        int levelSize = q.size();
        std::vector<int>level;
        for (size_t i = 0; i < levelSize; i++)
        {
            Node* root = q.front();
            q.pop();
            level.push_back(root->data);
            if (root->left)
            {
                q.push(root->left);
            }
            if (root->right)
            {
                q.push(root->right);
            }
        }
        result.push_back(level);
    }
    return result;
}

void testTreeLevels(Node* root1, Node* root2, Node* root3) {
    std::vector<std::vector<int>> result1 = treeLevels(root1);
    std::vector<std::vector<int>> result2 = treeLevels(root2);
    std::vector<std::vector<int>> result3 = treeLevels(root3);
    std::vector<std::vector<int>> expected1 = {
        {4},
        {2, 5},
        {1, 3}
    };

    std::vector<std::vector<int>> expected2 = {
        {3},
        {9, 20},
        {15, 7}
    };

    std::vector<std::vector<int>> expected3 = {
        {1},
        {2, 3},
        {4, 5, 6}
    };
    if (result1 == expected1 && result2 == expected2 && result3 == expected3) {
        std::cout << "Test passed!\n";
    }
    else {
        std::cout << "Test failed!\n";        
    }
}

std::vector<int> rightSideView(Node* root) {
    std::queue<Node*> q;
    if (root) {
        q.push(root);
    }
    std::vector<int> result;
    while (!q.empty()) {
        int size = q.size();
        while (size > 0) {
            Node* current = q.front();
            q.pop();
            if (current->left) {
                q.push(current->left);
            }
            if (current->right) {
                q.push(current->right);
            }
            if (size == 1)
            {
                result.push_back(current->data);
            }
            size--;
        }
    }
    return result;
}

void testrightSideView(Node* root1, Node* root2, Node* root3) {
    std::vector<int> result1 = rightSideView(root1);
    std::vector<int> result2 = rightSideView(root2);
    std::vector<int> result3 = rightSideView(root3);
    std::vector<int> expected1 = { 4,5,3 };
    std::vector<int> expected2 = { 3,20,7 };
    std::vector<int> expected3 = { 1,3,6 };
    if (result1 == expected1 && result2 == expected2 && result3 == expected3) {
        std::cout << "Test passed!\n";
    }
    else {
        std::cout << "Test failed!\n";
    }
}


int main(){
    Node* root1 = new Node(4);
    root1->left = new Node(2);
    root1->right = new Node(5);
    root1->left->left = new Node(1);
    root1->left->right = new Node(3);
    generateDot(root1, "tree1.dot");

    Node* root2 = new Node(3);             
    root2->left = new Node(9);             
    root2->right = new Node(20);          
    root2->right->left = new Node(15);     
    root2->right->right = new Node(7);    
    generateDot(root2, "tree2.dot");

    Node* root3 = new Node(1);
    Node* Node1 = new Node(2);
    Node* Node2 = new Node(3);
    Node* Node3 = new Node(4);
    Node* Node4 = new Node(5);
    Node* Node5 = new Node(6);
    root3->left = Node1;
    root3->right = Node2;
    Node1->left = Node3;
    Node1->right = Node4;
    Node2->left = Node5;
    generateDot(root3, "tree3.dot");

	testInorderTraversal(root1, root2);
    testAllPaths(root1, root2);
    testTreeLevels(root1, root2, root3);
    testrightSideView(root1, root2, root3);

    delete root1->left->left;
    delete root1->left->right;
    delete root1->left;
    delete root1->right;
    delete root1;

    delete root2->right->left;
    delete root2->right->right;   
    delete root2->right;
    delete root2->left;
    delete root2;    

    delete root3;
    delete Node1;
    delete Node2;
    delete Node3;
    delete Node4;
    delete Node5;

	return 0;
}