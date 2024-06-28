#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

struct BSTNode {
    int key;
    BSTNode *left, *right;
    int anak_kiri;
};

struct BST {
    BSTNode *_root;
    unsigned int _size;
};

BSTNode* __bst__createNode(unsigned long long value) {
    BSTNode *newNode = new BSTNode;
    newNode->key = value;
    newNode->left = newNode->right = nullptr;
    newNode->anak_kiri = 0;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, unsigned long long value) {
    if (root == nullptr) 
        return __bst__createNode(value);

    if (value < root->key) {
        root->anak_kiri++;
        root->left = __bst__insert(root->left, value);    
    }
    else if (value > root->key) {
        root->right = __bst__insert(root->right, value);
    }
    
    return root;
}

int parent;

BSTNode* __bst__search(BSTNode *root, unsigned long long value) {
    parent = 0;
    while (root != nullptr) {
        if (value < root->key) {
            root = root->left;    
        }
        else if (value > root->key) {
            parent += root->anak_kiri + 1;
            root = root->right;
        }
        else
            return root;
    }
    return root;
}

BSTNode* __bst__search2(BSTNode *root, unsigned long long value) {
    parent = 0;
    while (root != nullptr) {
        if (value < root->key) {
            if (value == root->left->key && root->left != nullptr){
                break;
            }
            root = root->left;    
        }
        else if (value > root->key) {
            parent += root->anak_kiri + 1;
            if (value == root->right->key && root->right != nullptr){
                break;
            }
            root = root->right;            
        }
        else
            return root;
    }
    return root;
}

BSTNode* __bst__findMinNode(BSTNode *node) {
    BSTNode *currNode = node;
    while (currNode && currNode->left != nullptr)
        currNode = currNode->left;
    
    return currNode;
}

BSTNode* __bst__remove(BSTNode *root, unsigned long long value) {
    if (root == nullptr) return nullptr;

    if (value > root->key) 
        root->right = __bst__remove(root->right, value);
    else if (value < root->key) 
        root->left = __bst__remove(root->left, value);
    else {
        
        if (root->left == nullptr) {
            BSTNode *rightChild = root->right;
            delete root;
            return rightChild;
        }
        else if (root->right == nullptr) {
            BSTNode *leftChild = root->left;
            delete root;
            return leftChild;
        }

        BSTNode *temp = __bst__findMinNode(root->right);
        root->key     = temp->key;
        root->right   = __bst__remove(root->right, temp->key);
    }
    return root;
}

void bst_init(BST *bst) {
    bst->_root = nullptr;
    bst->_size = 0u;
}

bool bst_isEmpty(BST *bst) {
    return bst->_root == nullptr;
}

int bst_find(BST *bst, unsigned long long value) {
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == nullptr)
        return 0;
    
    if (temp->key == value)
    {
        return temp->anak_kiri + parent + 1;    
    }
    else
        return 0;
}

int bst_find2(BST *bst, unsigned long long value) {
    BSTNode *temp = __bst__search2(bst->_root, value);
    if (temp == nullptr)
        return 0;
    if(temp->key == value){
        return 0;
    }else{
        return temp->key;
    }
}

void bst_insert(BST *bst, unsigned long long value) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}

void bst_remove(BST *bst, unsigned long long value) {
    if (bst_find(bst, value)) {
        bst->_root = __bst__remove(bst->_root, value);
        bst->_size--;
    }
}

int main()
{
    BST set;
    bst_init(&set);

    int i, q, data;
    char command[20];
    cin >> q;
    for(i=0; i<q; i++)
    {    
        cin >> command >> data;
        
        if(strcmp(command, "Insert") == 0)
        {
            bst_insert(&set, data);    
        }
        else if(strcmp(command, "Parent") == 0)
        {
            int hasil = bst_find(&set, data);
            if(hasil != 0 && hasil != bst_find(&set, set._root->key))
            {
                int amin=bst_find2(&set, data);
                cout << "Child of " << amin << endl;
            }
            else
            {
                cout << "Orphanage, here it comes" << endl;
            }
        }
        else if(strcmp(command, "Order") == 0)
        {
            int hasil = bst_find(&set, data);
            if(hasil != 0)
            {
                cout << "Order : " << hasil << endl;
            }
        }
    }
    
    return 0;
}
