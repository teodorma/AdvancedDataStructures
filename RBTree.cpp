#include <iostream>
#include <vector>
#include <fstream>

std::ofstream gout("RBTree.out");
using namespace std;
enum Color { RED, BLACK };

struct Node {
    int data;
    bool color;
    Node *left, *right, *parent;

    Node(int data): data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {

public:
    Node *root;

    void rotateLeft(Node *&ptr) {
        Node *rightChild = ptr->right;
        ptr->right = rightChild->left;
        if (ptr->right != nullptr) ptr->right->parent = ptr;
        rightChild->parent = ptr->parent;
        if (ptr->parent == nullptr) root = rightChild;
        else if (ptr == ptr->parent->left) ptr->parent->left = rightChild;
        else ptr->parent->right = rightChild;
        rightChild->left = ptr;
        ptr->parent = rightChild;
    }

    void rotateRight(Node *&ptr) {
        Node *leftChild = ptr->left;
        ptr->left = leftChild->right;
        if (ptr->left != nullptr) ptr->left->parent = ptr;
        leftChild->parent = ptr->parent;
        if (ptr->parent == nullptr) root = leftChild;
        else if (ptr == ptr->parent->right) ptr->parent->right = leftChild;
        else ptr->parent->left = leftChild;
        leftChild->right = ptr;
        ptr->parent = leftChild;
    }

    void fixInsert(Node *&ptr) {
        Node *parentPtr = nullptr;
        Node *grandParentPtr = nullptr;

        while (ptr != root && ptr->color != BLACK && ptr->parent && ptr->parent->color == RED) {

            parentPtr = ptr->parent;
            grandParentPtr = ptr->parent->parent;

            if (parentPtr == grandParentPtr->left) {
                Node *unclePtr = grandParentPtr->right;
                if (unclePtr != nullptr && unclePtr->color == RED) {
                    grandParentPtr->color = RED;
                    parentPtr->color = BLACK;
                    unclePtr->color = BLACK;
                    ptr = grandParentPtr;
                } else {
                    if (ptr == parentPtr->right) {
                        rotateLeft(parentPtr);
                        ptr = parentPtr;
                        parentPtr = ptr->parent;
                    }
                    rotateRight(grandParentPtr);
                    swap(parentPtr->color, grandParentPtr->color);
                    ptr = parentPtr;
                }
            } else {
                Node *unclePtr = grandParentPtr->left;
                if ((unclePtr != nullptr) && (unclePtr->color == RED)) {
                    grandParentPtr->color = RED;
                    parentPtr->color = BLACK;
                    unclePtr->color = BLACK;
                    ptr = grandParentPtr;
                } else {
                    if (ptr == parentPtr->left) {
                        rotateRight(parentPtr);
                        ptr = parentPtr;
                        parentPtr = ptr->parent;
                    }
                    rotateLeft(grandParentPtr);
                    ptr = parentPtr;
                }
            }
        }

        root->color = BLACK;
    }

    Node* insertBST(Node *&root, Node *&ptr) {
        if (root == nullptr) return ptr;

        if (ptr->data < root->data) {
            root->left = insertBST(root->left, ptr);
            root->left->parent = root;
        } else if (ptr->data > root->data) {
            root->right = insertBST(root->right, ptr);
            root->right->parent = root;
        }

        return root;
    }

    Node* minValueNode(Node *&node) {
        if (node == nullptr) return nullptr;

        Node *ptr = node;
        while (ptr->left != nullptr)
            ptr = ptr->left;
        return ptr;
    }

    Node* deleteBST(Node *&root, int data) {
        if (root == nullptr) return root;

        if (data < root->data)
            root->left = deleteBST(root->left, data);
        else if (data > root->data)
            root->right = deleteBST(root->right, data);
        else {
            if (root->left == nullptr || root->right == nullptr)
                return root->left ? root->left : root->right;

            Node *temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteBST(root->right, temp->data);
        }
        return root;
    }

    void fixDelete(Node *&node) {
        if (node == nullptr)
            return;

        if (node == root) {
            root = nullptr;
            return;
        }

        if (node->color == RED || node->left != nullptr || node->right != nullptr) {
            Node *newNode = node->left ? node->left : node->right;

            if (node == node->parent->left) {
                node->parent->left = newNode;
                if (newNode != nullptr)
                    newNode->parent = node->parent;
                delete node;
                if (newNode != nullptr)
                    newNode->color = BLACK;
                return;
            } else {
                node->parent->right = newNode;
                if (newNode != nullptr)
                    newNode->parent = node->parent;
                delete node;
                if (newNode != nullptr)
                    newNode->color = BLACK;
                return;
            }
        }

        Node *sibling = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;
        ptr->color = RED;
        while (ptr != root && ptr->color == BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    parent->color = RED;
                    rotateLeft(parent);
                    sibling = parent->right;
                }

                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    if (parent->color == RED) {
                        parent->color = BLACK;
                        break;
                    } else {
                        parent->color = RED;
                    }
                    ptr = parent;
                } else {
                    if (sibling->right == nullptr || sibling->right->color == BLACK) {
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        rotateRight(sibling);
                        sibling = parent->right;
                    }

                    sibling->color = parent->color;
                    parent->color = BLACK;
                    if (sibling->right != nullptr)
                        sibling->right->color = BLACK;
                    rotateLeft(parent);
                    break;
                }
            } else {
                sibling = parent->left;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    parent->color = RED;
                    rotateRight(parent);
                    sibling = parent->left;
                }

                if ((sibling->right == nullptr || sibling->right->color == BLACK) &&
                    (sibling->left == nullptr || sibling->left->color == BLACK)) {
                    sibling->color = RED;
                    if (parent->color == RED) {
                        parent->color = BLACK;
                        break;
                    } else {
                        parent->color = RED;
                    }
                    ptr = parent;
                } else {
                    if (sibling->left == nullptr || sibling->left->color == BLACK) {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotateLeft(sibling);
                        sibling = parent->left;
                    }

                    sibling->color = parent->color;
                    parent->color = BLACK;
                    if (sibling->left != nullptr)
                        sibling->left->color = BLACK;
                    rotateRight(parent);
                    break;
                }
            }
        }


        if (node == node->parent->left)
        node->parent->left = nullptr;
        else
        node->parent->right = nullptr;
        delete node;
        root->color = BLACK;
    }

    RedBlackTree() { root = nullptr; }

    void insert(const int &data) {
        Node *node = new Node(data);
        root = insertBST(root, node);
        fixInsert(node);
    }

    void deleteNode(const int &data) {
        Node *node = deleteBST(root, data);
        fixDelete(node);
    }

    bool find(int data) {
        Node *current = root;
        while (current != nullptr) {
            if (data == current->data) {
                return true;
            } else if (data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }

    int findLargestLessThanOrEqual(int data) {
        Node *current = root;
        int result = -1; // Assuming all values are positive for simplicity
        while (current != nullptr) {
            if (current->data <= data) {
                result = current->data;
                current = current->right;
            } else {
                current = current->left;
            }
        }
        return result;
    }

    int findSmallestGreaterThanOrEqual(int data) {
        Node *current = root;
        int result = -1; // Assuming all values are positive for simplicity
        while (current != nullptr) {
            if (current->data >= data) {
                result = current->data;
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return result;
    }

    void printRange(int X, int Y) {
        vector<int> range;
        getRange(root, X, Y, range);
        for (int num : range) {
            gout << num << " ";
        }
        gout << endl;
    }

    void getRange(Node *node, int X, int Y, vector<int> &range) {
        if (node == nullptr) return;
        if (X < node->data) {
            getRange(node->left, X, Y, range);
        }
        if (X <= node->data && Y >= node->data) {
            range.push_back(node->data);
        }
        if (Y > node->data) {
            getRange(node->right, X, Y, range);
        }
    }
};
