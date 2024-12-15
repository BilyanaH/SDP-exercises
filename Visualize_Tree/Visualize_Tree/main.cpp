#include <iostream>
#include <fstream>
#include <string>

struct Node {
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

int main() {
    // Създаване на примерното дърво
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    // Генериране на DOT файл
    generateDot(root, "tree.dot");

    // Освобождаване на памет
    delete root->left->left;
    delete root->left->right;
    delete root->right->left;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
