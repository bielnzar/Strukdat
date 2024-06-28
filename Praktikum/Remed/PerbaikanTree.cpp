/*
Nama : Nabiel Nizar Anwari
NRP  : 5027231087
Code : Perbaikan Tree
*/

#include <bits/stdc++.h>

using namespace std;

typedef struct AvlNode {
    int data;
    struct AvlNode *left;
    struct AvlNode *right;
    int height;
} AvlNode;

typedef struct AvlTree {
    AvlNode *root;
    unsigned int size;
} AvlTree;  

AvlNode *newNode(int data) {
    AvlNode *newnode = new AvlNode;
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->height = 1;
    return newnode;
}

int getHeight(AvlNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

AvlNode *search(AvlNode *root, int data) {
    while (root != NULL) {
        if (data < root->data) {
            root = root->left;
        } else if (data > root->data) {
            root = root->right;
        } else {
            return root;
        }
    }
    return root;
}

AvlNode *rightRotate(AvlNode *pivotNode){
    AvlNode *newRoot = pivotNode->left;
    AvlNode *temp = newRoot->right;

    newRoot->right = pivotNode;
    pivotNode->left = temp;

    pivotNode->height = max(getHeight(pivotNode->left), getHeight(pivotNode->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

AvlNode *leftRotate(AvlNode *pivotNode){
    AvlNode *newRoot = pivotNode->right;
    AvlNode *temp = newRoot->left;

    newRoot->left = pivotNode;
    pivotNode->right = temp;

    pivotNode->height = max(getHeight(pivotNode->left), getHeight(pivotNode->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

AvlNode *leftcase(AvlNode *root) {
    return rightRotate(root);
}

AvlNode *rightcase(AvlNode *root) {
    return leftRotate(root);
}

AvlNode *leftrightcase(AvlNode *root) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
}

AvlNode *rightleftcase(AvlNode *root) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
}

int getBalance(AvlNode *node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

AvlNode *insert(AvlNode *root, int data) {
    if (root == NULL) {
        return newNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    } else {
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && data < root->left->data) {
        return leftcase(root);
    }
    if (balance < -1 && data > root->right->data) {
        return rightcase(root);
    }
    if (balance > 1 && data > root->left->data) {
        return leftrightcase(root);
    }
    if (balance < -1 && data < root->right->data) {
        return rightleftcase(root);
    }

    return root;
}

AvlNode *minValueNode(AvlNode *node) {
    AvlNode *current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

AvlNode *deleteNode(AvlNode *root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == NULL || root->right == NULL) {
            AvlNode *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            AvlNode *temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return leftcase(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        return leftrightcase(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) {
        return rightcase(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        return rightleftcase(root);
    }

    return root;
}

void avl_init(AvlTree *tree) {
    tree->root = NULL;
    tree->size = 0;
}

bool avl_Empty(AvlTree *tree) {
    return tree->size == 0;
}

bool avl_find(AvlTree *tree, int data) {
    AvlNode *node = search(tree->root, data);
    return (node != NULL);
}

void avl_insert(AvlTree *tree, int data) {
    if (!avl_find(tree, data)) {
        tree->root = insert(tree->root, data);
        tree->size++;
    }
}

void inorder(AvlNode *root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void avl_inorder(AvlTree *tree) {
    inorder(tree->root);
}

void postorder(AvlNode *root){
    if(root){
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

void avl_postorder(AvlTree *tree){
    postorder(tree->root);
}

void preorder(AvlNode *root) {
    if(root){
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void avl_preorder(AvlTree *tree){
    preorder(tree->root);
}

void avl_delete(AvlTree *tree, int data) {
    if (avl_find(tree, data)) {
        tree->root = deleteNode(tree->root, data);
        tree->size--;
    }
}

int main(){
    AvlTree inti;
    avl_init(&inti);

    int input, command;

    while(cin >> input){
        if (input == 1){
            while (cin >> command){
                avl_insert(&inti, command);
                if(cin.peek() == '\n'){
                    break;
                }
            }
        }
        else if(input == 2){
            cin >> command;
            avl_delete(&inti, command);
        }
        else if(input == 3){
            avl_inorder(&inti);
            cout << endl;
        }
        else if(input == 4){
            avl_preorder(&inti);
            cout << endl;
        }
        else if(input == 5){
            avl_postorder(&inti);
            cout << endl;
        }
    }
    return 0;
}
