#include <iostream>
#include <climits>
using namespace std;

class AVLTree {
private:
    class Node {
    public:
        int key;
        Node* left;
        Node* right;
        int height;
        Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int height(Node* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    int getBalance(Node* N) {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node* insertNode(Node* node, int key) {
        if (node == nullptr)
            return new Node(key);

        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    Node* searchNode(Node* root, int key) {
        if (root == nullptr || root->key == key)
            return root;

        if (root->key < key)
            return searchNode(root->right, key);

        return searchNode(root->left, key);
    }

    Node* predecessorNode(Node* root, int key) {
        Node* pred = nullptr;
        while (root) {
            if (root->key < key) {
                pred = root;
                root = root->right;
            } else
                root = root->left;
        }
        return pred;
    }

    Node* successorNode(Node* root, int key) {
        Node* succ = nullptr;
        while (root) {
            if (root->key > key) {
                succ = root;
                root = root->left;
            } else
                root = root->right;
        }
        return succ;
    }

    void printInRangeNodes(Node* root, int x, int y) {
        if (root == nullptr)
            return;

        if (root->key > x)
            printInRangeNodes(root->left, x, y);

        if (root->key >= x && root->key <= y)
            cout << root->key << " ";

        if (root->key < y)
            printInRangeNodes(root->right, x, y);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insertNode(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    int search(int key) {
        return (searchNode(root, key) != nullptr) ? 1 : 0;
    }

    int predecessor(int key) {
        Node* predNode = predecessorNode(root, key);
        return (predNode != nullptr) ? predNode->key : INT_MAX;
    }

    int successor(int key) {
        Node* succNode = successorNode(root, key);
        return (succNode != nullptr) ? succNode->key : INT_MIN;
    }

    void printInRange(int x, int y) {
        printInRangeNodes(root, x, y);
        cout << endl;
    }
};
