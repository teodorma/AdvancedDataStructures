#include <iostream>
#include <vector>
#include <fstream>
#include <random>

std::ofstream fout("SkipList.out");

struct TreeNode {
    int val;
    TreeNode* right;
    TreeNode* down;

    explicit TreeNode(int x) : val(x), right(nullptr), down(nullptr) {}
};

class SkipList {
public:
    TreeNode* base;
    double chance;
    std::mt19937 gen;
    std::bernoulli_distribution dist;

    explicit SkipList(int lev, double chance) : base(nullptr), chance(chance), gen(std::random_device()()), dist(chance) {
        if (lev > 0) {
            base = new TreeNode(0);
            TreeNode* current = base;

            for (int i = 1; i < lev; ++i) {
                current->down = new TreeNode(0);
                current = current->down;
            }
        }
    }

    bool coinFlip() {
        return dist(gen);
    }


    TreeNode* addNum(int val, TreeNode* node, bool& coinflip) {
        if (node == nullptr) return nullptr;

        TreeNode* current = node;
        TreeNode* insertedNode = nullptr;
        std::vector<TreeNode*> path;
        while (current != nullptr) {
            while (current->right != nullptr && current->right->val < val) {
                current = current->right;
            }
            path.push_back(current);
            current = current->down;
        }

        bool insertHere = true;
        for (auto it = path.rbegin(); it != path.rend() && insertHere; ++it) {
            TreeNode* temp = *it;
            TreeNode* newNode = new TreeNode(val);
            newNode->right = temp->right;
            temp->right = newNode;
            newNode->down = insertedNode;
            insertedNode = newNode;


            insertHere = coinFlip() && coinflip;
        }

        coinflip = insertHere;
        return insertedNode;
    }

    void deleteNum(int val, TreeNode* node) {
        while (node != nullptr) {
            while (node->right != nullptr && node->right->val < val) {
                node = node->right;
            }

            if (node->right != nullptr && node->right->val == val) {
                TreeNode* toDelete = node->right;
                node->right = node->right->right;
                delete toDelete;
            }

            node = node->down;
        }
    }

    bool search(int val, TreeNode* node) {
        while (node != nullptr) {
            while (node->right != nullptr && node->right->val < val) {
                node = node->right;
            }
            if (node->right != nullptr && node->right->val == val) return true;
            node = node->down;
        }
        return false;
    }

    void printRange(int low, int high, TreeNode* node) {
        TreeNode* current = lowerBound(low, node);
        while (current != nullptr && current->val <= high) {
            fout << current->val << " ";
            current = current->right;
        }
        fout << std::endl;
    }

    void printNumbers(TreeNode* node){
        while (node != nullptr) {
            fout << node->val << " -> ";
            node = node->right;
        }
        fout << "nullptr" << std::endl << std::flush;
    }

    TreeNode* lowerBound(int val, TreeNode* node) {
        TreeNode* best = nullptr;
        while (node != nullptr) {
            TreeNode* current = node;
            while (current != nullptr && current->val < val) {
                current = current->right;
            }
            if (current != nullptr) {
                best = current;
            }
            node = node->down;
        }
        return best;
    }

    TreeNode* upperBound(int val, TreeNode* node) {
        TreeNode* best = nullptr;
        while (node != nullptr) {
            TreeNode* current = node;
            while (current != nullptr && current->val <= val) {
                best = current;
                current = current->right;
            }
            node = node->down;
        }
        return best;
    }

    ~SkipList() {
        while (base != nullptr) {
            TreeNode* nextLevel = base->down;

            TreeNode* current = base;
            while (current != nullptr) {
                TreeNode* nextNode = current->right;
                delete current;
                current = nextNode;
            }

            base = nextLevel;
        }
    }

    [[nodiscard]] TreeNode* get_base() const {
        return base;
    }
    [[nodiscard]] double get_chance() const {
        return chance;
    }
};

