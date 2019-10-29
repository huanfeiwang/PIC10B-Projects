#include <iostream>
#include <string>
#include <fstream>

using namespace std;
class Action {
    void act(string str) {} ;
};

class Sumlength: public Action {
    public:
        Sumlength() { total = 0; };
        void act(string str) {
            total += str.length();
        };
        int getTotal() {
            return total;
        };
    private:
        int total;
};

class TreeNode {
    public:
        void insert_node(TreeNode* new_node);
        void print_inorder(Sumlength& a);
        void print_preorder();
        void print_postorder();

    private:
    string data;
    TreeNode* left;
    TreeNode* right;
    friend class BinarySearchTree;
};

class BinarySearchTree {
    public:
        BinarySearchTree();
        void insert(string data);
        void erase(string data);
        void inorder(Sumlength& a);
        void preorder();
        void postorder();
        int count(string data) const;
    private:
        TreeNode* root;
};

BinarySearchTree::BinarySearchTree() {
    root = NULL;
}

void BinarySearchTree::inorder(Sumlength& a) {
    if (root != NULL) root->print_inorder(a);
}

void BinarySearchTree::preorder()  {
    if (root != NULL) root->print_preorder();
}

void BinarySearchTree::postorder()  {
    if (root != NULL) root->print_postorder();
}

void BinarySearchTree::insert(string data)
{
     TreeNode* new_node = new TreeNode;
     new_node->data = data;
     new_node->left = NULL;
     new_node->right = NULL;
     if (root == NULL) root = new_node;
     else root->insert_node(new_node);
}

void TreeNode::insert_node(TreeNode* new_node)
{
    if (new_node->data < data) {
        if (left == NULL) left = new_node;
        else left->insert_node(new_node);
    } else if (data < new_node->data) {
        if (right == NULL) right = new_node;
        else right->insert_node(new_node);
    }
}

void TreeNode::print_inorder(Sumlength& a) {
    a.act(data);
    if (left != NULL)
        left->print_inorder(a);
    cout << data << "\n";
    if (right != NULL)
        right->print_inorder(a);
}

void TreeNode::print_preorder() {
    cout << data << "\n";
    if (left != NULL)
        left->print_preorder();
    if (right != NULL)
        right->print_preorder();
}

void TreeNode::print_postorder() {
    if (left != NULL)
        left->print_postorder();
    if (right != NULL)
        right->print_postorder();
    cout << data << "\n";
}


int main() {
    fstream in;
    in.open("data4.txt");
    string line;
    BinarySearchTree Tree;
    while (getline(in, line)) {
        Tree.insert(line);
    }
    Sumlength sum;
    cout << "\nPrinting the elements of the tree inorder:\n";
    Tree.inorder(sum);

    cout << "\nThe sum of all lengths of the strings stored in a tree: " << sum.getTotal() << endl;

    cout << "\nPrinting the elements of the tree preorder:\n";
    Tree.preorder();
    cout << "\nPrinting the elements of the tree postorder:\n";
    Tree.postorder();
    system("pause");
    return(0);
}
