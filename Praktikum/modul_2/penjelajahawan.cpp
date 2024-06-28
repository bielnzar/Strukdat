#include <iostream>

// Function untuk membuat tree
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Function insert node
TreeNode* insert(TreeNode* root, int value) {
    if (root == nullptr) {
        root = new TreeNode(value);
    } else if (value < root->val) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

// Function BST
TreeNode* buildBST(int values[], int size) {
    TreeNode* root = nullptr;
    for (int i = 0; i < size; ++i) {
        root = insert(root, values[i]);
    }
    return root;
}

// Function untuk mencari path
void findPaths(TreeNode* root, int targetSum, int path[], int pathLen, int minPath[], int& minPathLen) {
    if (root == nullptr)
        return;

    path[pathLen] = root->val;
    pathLen++;

    int sum = 0;
    for (int i = pathLen - 1; i >= 0; i--) {
        sum += path[i];
        if (sum == targetSum && pathLen < minPathLen) {
            // Update minimum path
            for (int j = 0; j < pathLen; j++) {
                minPath[j] = path[j];
            }
            minPathLen = pathLen;
            break; // Break untuk update shortest path
        }
    }
    findPaths(root->left, targetSum, path, pathLen, minPath, minPathLen);
    findPaths(root->right, targetSum, path, pathLen, minPath, minPathLen);

    // Backtrack
    pathLen--;
}

int main() {
    using namespace std;

    int size;
    cin >> size;

    int* values = new int[size];
    for (int i = 0; i < size; ++i) {
        cin >> values[i];
    }

    TreeNode* root = buildBST(values, size);
    delete[] values;

    int target;
    cin >> target;

    int* path = new int[size];
    int* minPath = new int[size];
    int minPathLen = size + 1; // Inisialisasi dengan value lebih dari possible max length
    findPaths(root, target, path, 0, minPath, minPathLen);

    if (minPathLen <= size) {
        for (int i = 0; i < minPathLen; i++) {
            cout << minPath[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Womp Womp" << endl;
    }

    return 0;
}
