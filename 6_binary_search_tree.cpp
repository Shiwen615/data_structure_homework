#include <iostream>
#include <iomanip>
#include <functional>

// node of binary search tree
enum class LRChild
{
    LEFT,
    RIGHT,
    ROOT
};

class Node
{
public:
    int data;
    Node *parent;
    Node *left;
    Node *right;
    Node(int data) : data(data), parent(NULL), left(NULL), right(NULL) {}
};

class BST
{
public:
    Node *root = nullptr;
    BST() : root(NULL) {}
    BST(int data) : root(new Node(data)) {}

    void clear(){
        clear(root);
        root = nullptr;
    }
    void insert(int data)
    {
        if (root == NULL)
        {
            root = new Node(data);
            return;
        }


        Node *current = root;
        LRChild current_is = LRChild::ROOT;
        while (true) {
            if (data == current->data) {
                Node *del_node;
                Node *del_node_child;

                if (current->left && current->right) {
                    del_node = successor(current);
                    current->data = del_node->data;
                }
                else {
                    del_node = current;
                }

                if (del_node->left) {
                    del_node_child = del_node->left;
                }
                else {
                    del_node_child = del_node->right;
                }

                if (del_node_child){
                    del_node_child->parent = del_node->parent;
                }

                if (!del_node->parent) { // del_node == root
                    this->root = del_node_child;
                } else if (del_node == del_node->parent->left) {
                    del_node->parent->left = del_node_child;
                // } else if (del_node == del_node->parent->right) {
                } else {
                    del_node->parent->right = del_node_child;
                }

                delete del_node;
                return;
            }
            if (data < current->data) {
                if (current->left == NULL) {
                    current->left = new Node(data);
                    current->left->parent = current;
                    return;
                }
                current = current->left;
                current_is = LRChild::LEFT;
            }
            else { // data > current->data
                if (current->right == NULL)
                {
                    current->right = new Node(data);
                    current->right->parent = current;
                    return;
                }
                current = current->right;
                current_is = LRChild::RIGHT;
            }
        }
    }

    void printTree() {
        printTree(root, 0);
    }

private:
    void clear(Node *p){
        if (p->left) {
            clear(p->left);
        }
        if (p->right) {
            clear(p->right);
        }
        delete p;
    }
    Node *successor(Node *p) {
        if (p->right) {
            p = p->right;
            while (p->left) {
                p = p->left;
            }
            return p;
        }
        while (p->parent && p == p->parent->right) {
            p = p->parent;
        }
        return p->parent;
    }
    void printTree(Node* p, int indent = 0)
    {
        if (p != nullptr) {
            if (p->right) {
                printTree(p->right, indent + 4);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (p->right) std::cout << " /\n" << std::setw(indent) << ' ';
            std::cout << p->data << "\n ";
            if (p->left) {
                std::cout << std::setw(indent) << ' ' << " \\\n";
                printTree(p->left, indent + 4);
            }
        }
    }
};

int main()
{
    BST bst;

    for (auto &&i : {10,7,12,8,11,4})
    {
        bst.insert(i);
    }
    bst.printTree();

    std::cout << "===============" << std::endl;

    bst.clear();
    for (auto &&i : {3,3,5,9,5,3,4,8,5,3,10,10,8})
    {
        bst.insert(i);
    }
    bst.printTree();
    return 0;
}