/*
Nama : Nabiel Nizar Anwari
NRP  : 5027231087
Code : 500 Days of Strukdat
*/

#include <bits/stdc++.h>

using namespace std;

typedef struct bstNode{
    int data;
    struct bstNode *left;
    struct bstNode *right;
} BSTNode;

typedef struct bstTree{
    BSTNode *root;
    unsigned int size;
} BST;

BSTNode *bst_createNode(int data){
    BSTNode *newNode = new BSTNode;
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode *bst_insert(BSTNode *root, int data){
    if (root == NULL) {
        return bst_createNode(data);
    }

    if (data < root->data) {
        root->left = bst_insert(root->left, data);
    } 
    else if (data > root->data) {
        root->right = bst_insert(root->right, data);
    }

    return root;
}

BSTNode *bst_search(BSTNode *root, int data){
    while (root != NULL) {
        if (data < root->data){
            root = root->left;
        } 
        else if (data > root->data){
            root = root->right;
        } 
        else{
            return root;
        }
    }
    return root;
}

void bst_init(BST *tree) {
    tree->root = NULL;
    tree->size = 0;
}

bool bst_find(BST *tree, int data){
    BSTNode *temp = bst_search(tree->root, data);
    return temp != NULL && temp->data == data;
}

void bst_insert(BST *tree, int data) {
    if (!bst_find(tree, data)) {
        tree->root = bst_insert(tree->root, data);
        tree->size++;
    }
}

void inorder(BSTNode *root){
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void bst_inorder(BST *tree){
    inorder(tree->root);
}

void postorder(BSTNode *root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

void bst_postorder(BST *tree){
    postorder(tree->root);
}

bool deadend(BSTNode *root, int min, int max){
    if (root == NULL){
        return false;
    }
    if (root->left == NULL && root->right == NULL) return (min == max);
    return
        deadend(root->left, min, root->data - 1) ||
        deadend(root->right, root->data + 1, max);
}

bool bst_deadend(BST *tree){
    return deadend(tree->root, INT_MIN, INT_MAX);
}

bool pythagoras(int *input, int n){
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++){
                int x = input[i] * input[i];
                int y = input[j] * input[j];
                int z = input[k] * input[k];

                if (x + y == z || x + z == y || y + z == x) {
                    cout << "(" << input[i] << ")(" << input[i] << ")+(" << input[j] << ")(" << input[j] << ")=(" << input[k] << ")(" << input[k] << ")" << endl;
                    return true;
                }
            } 
        } 
    }
    return false;
}

int main(){
    BST tree;
    bst_init(&tree);

    int n;
    cin >> n;

    if (n == 0){
        return 0;
    }

    int input[n];
    for (int i = 0; i < n; i++){
        cin >> input[i];
        bst_insert(&tree, input[i]);
    }

    if (bst_deadend(&tree)) {
        cout << "takdir kita sampai di sini." << endl;
        bst_inorder(&tree);
    } 
    else{
        cout << "masih ada ruang untuk cinta kita bertumbuh." << endl;
        bst_postorder(&tree);
    }

    cout << endl;

    if (!pythagoras(input, n)){
        for (int i = 0; i < n; i++){
            cout << input[i] % 2 << " ";
        }
    }

    return 0;
}
