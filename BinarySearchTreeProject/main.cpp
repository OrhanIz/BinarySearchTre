#include <iostream>


template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
public:
    TreeNode(T value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

template <typename T, typename Compare>
class BinarySearchTree {
    TreeNode<T>* root;
    Compare comp;

public:
    BinarySearchTree() {
        root = nullptr;
    }

  
    void add(T value) {
        TreeNode<T>* newNode = new TreeNode<T>(value);
        if (root == nullptr) {
            root = newNode;
            return;
        }
        TreeNode<T>* current = root;
        TreeNode<T>* parent = nullptr;
        while (current != nullptr) {
            parent = current;
            if (comp(value, current->data)) {
                current = current->left;
            }
            else if (comp(current->data, value)) {
                current = current->right;
            }
            else {
                delete newNode;
                return;
            }
        }
        if (comp(value, parent->data)) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }
    }

  
    void printInorder(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        printInorder(node->left);
        std::cout << node->data << " ";
        printInorder(node->right);
    }
    void printInorder() {
        printInorder(root);
    }

    TreeNode<T>* findAddressMin(TreeNode<T>* node) {
        if (node == nullptr) {
            return nullptr;
        }
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

 
    TreeNode<T>* deleteNode(TreeNode<T>* node, T value) {
        if (node == nullptr) {
            return node;
        }

        if (comp(value, node->data)) {
            node->left = deleteNode(node->left, value);
        }
        else if (comp(node->data, value)) {
            node->right = deleteNode(node->right, value);
        }
        else {
            if (node->left == nullptr) {
                TreeNode<T>* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode<T>* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode<T>* temp = findAddressMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    void deleteNode(T value) {
        root = deleteNode(root, value);
    }
};


struct Compare {
    bool operator()(int a, int b) {
        return a < b; 
    }
};

int main() {
    BinarySearchTree<int, Compare> bst;

  
    bst.add(50);
    bst.add(30);
    bst.add(20);
    bst.add(40);
    bst.add(70);
    bst.add(60);
    bst.add(80);

    std::cout << "Inorder traversal: ";
    bst.printInorder();
    std::cout << std::endl;

    std::cout << "Deleting 20...\n";
    bst.deleteNode(20);
    std::cout << "Inorder traversal after deleting 20: ";
    bst.printInorder();
    std::cout << std::endl;

    std::cout << "Deleting 30...\n";
    bst.deleteNode(30);
    std::cout << "Inorder traversal after deleting 30: ";
    bst.printInorder();
    std::cout << std::endl;

    std::cout << "Deleting 50...\n";
    bst.deleteNode(50);
    std::cout << "Inorder traversal after deleting 50: ";
    bst.printInorder();
    std::cout << std::endl;

    return 0;
}
