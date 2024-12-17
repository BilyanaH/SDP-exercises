#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <string>

template <typename T>
struct Node
{
	T data;
	Node* left;
	Node* right;
    Node(T value) : data(value), left(nullptr), right(nullptr) {}
};
template <typename T>
void writeDot(Node<T>* root, std::ofstream& out) {
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
template <typename T>
void generateDot(Node<T>* root, const std::string& filename) {
    std::ofstream out(filename);
    if (!out) return;
    out << "digraph Tree {\nnode [shape=circle];\n";
    writeDot(root, out);
    out << "}\n";
}
//dot -Tpng tree.dot -o tree.png
template <typename T>
void inorderRec(Node<T>* node, std::vector<T>& result) {
	if (node->left) {
		inorderRec(node->left, result);
	}	
    result.push_back(node->data);
	if (node->right) {
		inorderRec(node->right, result);
	}
}
template <typename T>
std::vector<T>& inorderIter(Node<T>* root, std::vector<T>& result) {
    std::stack<Node<T>*> st;
    Node<T>* node = root;
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
template <typename T>
std::vector<T> inorder(Node<T>* root) {
	std::vector<T> result;
	//inorderRec(root, result);
    inorderIter(root, result);
	return result;
}
void testInorderTraversal(Node<int>* root1, Node<int>* root2) {
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
void allPathsHelper(Node<int>* node, std::vector<std::string>& result, std::string path) {
    if (node->left == nullptr && node->right == nullptr) {
        path.append(std::to_string(node->data));
        result.push_back(path);
        return;
    }
    path.append(std::to_string(node->data) + "->");
    allPathsHelper(node->left, result, path);
    allPathsHelper(node->right, result, path);
}
std::vector<std::string> allPaths(Node<int>* root) {
    std::vector<std::string> result;
    std::string path;
    allPathsHelper(root, result, path);
    return result;
}
void testAllPaths(Node<int>* root1, Node<int>* root2) {
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
std::vector<std::vector<int>> treeLevels(Node<int>* node) {
    std::queue<Node<int>*> q;
    if (node) {
        q.push(node);
    }
    std::vector<std::vector<int>> result;
    while (!q.empty()) {
        int levelSize = q.size();
        std::vector<int>level;
        for (size_t i = 0; i < levelSize; i++)
        {
            Node<int>* root = q.front();
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
void testTreeLevels(Node<int>* root1, Node<int>* root2, Node<int>* root3) {
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
std::vector<int> rightSideView(Node<int>* root) {
    std::queue<Node<int>*> q;
    if (root) {
        q.push(root);
    }
    std::vector<int> result;
    while (!q.empty()) {
        int size = q.size();
        while (size > 0) {
            Node<int>* current = q.front();
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
void testrightSideView(Node<int>* root1, Node<int>* root2, Node<int>* root3) {
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
void combine(std::stack<char>& ops, std::stack<Node<char>*>& stack) {
    Node<char>* root = new Node<char>(ops.top());
    ops.pop();
    root->right = stack.top();
    stack.pop();
    root->left = stack.top();
    stack.pop();
    stack.push(root);
}
int getPriority(char c)
{
    switch (c)
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
}
Node<char>* BuildBinaryExpressionTreeFromInfixExpression(const std::string& input) {
    std::stack<char>ops;
    std::stack<Node<char>*> stack;

    for (size_t i = 0; i < input.length(); i++)
    {
        char ch = input[i];
        if (ch == '(') {
            ops.push(ch);
        }
        else if (ch == ')') {
            while (ops.top() != '(') {
                combine(ops, stack);
            }
            ops.pop();
        }
        else if (isdigit(ch)) {
            stack.push(new Node<char>(ch));
        }
        else {
            while (ops.empty() == false && getPriority(ops.top()) >= getPriority(ch)) {
                combine(ops, stack);
            }
            ops.push(ch);
        }

    }
    while (stack.size() > 1)
    {
        combine(ops, stack);
    }
    return stack.top();
}
int getOperatorPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0; // For numbers/leaf nodes
}
std::string reconstructExpression(Node<char>* root, int parentPrecedence = 0) {
    if (!root) return "";
    if (!root->left && !root->right) {
        return std::string(1, root->data);
    }
    int currentPrecedence = getOperatorPrecedence(root->data);
    std::string left = reconstructExpression(root->left, currentPrecedence);
    std::string right = reconstructExpression(root->right, currentPrecedence);
    std::string expression = left + root->data + right;
    if (currentPrecedence < parentPrecedence) {
        return "(" + expression + ")";
    }
    return expression;
}
void testBuildBinaryExpressionTreeFromInfixExpression() {
    std::string input1 = "2-3/(5*2)+1";
    Node<char>* root1 = BuildBinaryExpressionTreeFromInfixExpression(input1);
    generateDot(root1, "tree4.dot");
    std::string reconstructed1 = reconstructExpression(root1);
    if (reconstructed1 == input1) {
        std::cout << "Test case 1 passed!\n";
    }
    else {
        std::cout << "Test case 1 failed! Expected: " << input1 << ", Got: " << reconstructed1 << "\n";
    }

    std::string input2 = "3*4-2*5";
    Node<char>* root2 = BuildBinaryExpressionTreeFromInfixExpression(input2);
    generateDot(root2, "tree5.dot");
    std::string reconstructed2 = reconstructExpression(root2);
    if (reconstructed2 == input2) {
        std::cout << "Test case 2 passed!\n";
    }
    else {
        std::cout << "Test case 2 failed! Expected: " << input2 << ", Got: " << reconstructed2 << "\n";
    }

    std::string input3 = "1+2+3+4+5";
    Node<char>* root3 = BuildBinaryExpressionTreeFromInfixExpression(input3);
    generateDot(root3, "tree6.dot");
    std::string reconstructed3 = reconstructExpression(root3);
    if (reconstructed3 == input3) { 
        std::cout << "Test case 3 passed!\n";
    }
    else {
        std::cout << "Test case 3 failed! Expected: " << input3 << ", Got: " << reconstructed3 << "\n";
    }

    delete root1;
    delete root2;
    delete root3;
}

int main(){
    Node<int>* root1 = new Node<int>(4);
    root1->left = new Node<int>(2);
    root1->right = new Node<int>(5);
    root1->left->left = new Node<int>(1);
    root1->left->right = new Node<int>(3);
    generateDot(root1, "tree1.dot");

    Node<int>* root2 = new Node<int>(3);
    root2->left = new Node<int>(9);
    root2->right = new Node<int>(20);
    root2->right->left = new Node<int>(15);
    root2->right->right = new Node < int>(7);
    generateDot(root2, "tree2.dot");

    Node<int>* root3 = new Node<int>(1);
    Node<int>* Node1 = new Node<int>(2);
    Node<int>* Node2 = new Node<int>(3);
    Node<int>* Node3 = new Node<int>(4);
    Node<int>* Node4 = new Node<int>(5);
    Node<int>* Node5 = new Node<int>(6);
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
    testBuildBinaryExpressionTreeFromInfixExpression();

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