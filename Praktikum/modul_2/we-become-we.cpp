/*

We Become We
- Medium
- Objective: Find the distance of the farthest nodes from the root node

Solution:
1. Insert root to tree (insert_node function)
2. Insert node by looking for parent (insert_node and find_parent function)
3. Calculate heights of left and right subtree (find_height function)
4. Store values of the farthest nodes (find_height function)
4. Add heights together and print farthest nodes (main function)

*/

#include <iostream>

using namespace std;

struct Node
{
    string data;
    Node *left, *right;
};

Node *new_node(string data)
{
    Node *temp = new Node;           // allocate memory for one node
    temp->data = data;               // set the data of the new node to the data passed in the function
    temp->left = temp->right = NULL; // make sure new node has no children
    return temp;                     // return the newly created node
}

void find_parent(Node *root, Node *new_node, bool &found, string parent);
void insert_node(Node *root, string a, string b);
void find_height(Node *root, int curr_level, int &max_height, string &max_data);

int main()
{
    int n;
    string r;

    cin >> n;
    cin >> r;

    Node *root = new_node(r); // create the root node
    string parent, child;

    for (int i = 0; i < n - 1; i++)
    {
        cin >> parent >> child;
        insert_node(root, parent, child);
    }

    int left_height = 0;
    int right_height = 0;

    string a, b;

    find_height(root->left, 1, left_height, a);
    find_height(root->right, 1, right_height, b);

    int c = left_height + right_height;
    cout << "Jarak antara " << a << " dan " << b << " == " << c;
}

void insert_node(Node *root, string parent, string child)
{
    Node *curr_data = root;
    Node *new_node_data = new_node(child);

    bool found = false;

    // if the parent is the root then insert the new node as a child of the root
    if (parent == curr_data->data)
    {
        if (curr_data->left == NULL)
        {
            curr_data->left = new_node_data;
        }
        else
        {
            curr_data->right = new_node_data;
        }
        found = true;
        return;
    }

    // if the parent is not the root then search for the parent in the left and right subtree
    find_parent(curr_data->left, new_node_data, found, parent);
    if (!found)
        find_parent(curr_data->right, new_node_data, found, parent);
}

void find_parent(Node *root, Node *new_node, bool &found, string parent)
{
    // create a temporary root to traverse the tree
    // this is necessary so that the original root node is not lost
    Node *curr_data = root;

    if (curr_data == NULL)
    {
        return;
    }

    // if the parent is found then insert the new node as a child of the parent
    if (curr_data->data == parent)
    {
        if (curr_data->left == NULL)
        {
            curr_data->left = new_node;
        }
        else
        {
            curr_data->right = new_node;
        }

        found = true;
        return;
    }

    // if the parent is not found then search for the parent in the left and right subtree
    find_parent(curr_data->left, new_node, found, parent);
    if (!found)
        find_parent(curr_data->right, new_node, found, parent);

    // as the find_parent recursively got called,
    // the curr_data variable is updated to the left and right child of the curr_data
}

void find_height(Node *root, int curr_level, int &max_height, string &max_data)
{
    Node *curr_data = root;

    // root is NULL means we are at the end of the tree
    // thus return 
    if (root == NULL)
    {
        return;
    }

    // if the current level is greater than the max height then update the max height and max data
    if (curr_level > max_height && root != NULL)
    {
        max_data = curr_data->data;
        max_height = curr_level;
    }

    // recursively call the find_height function for the left and right subtree
    // increment the current level by 1 because it is now recursively going down another level
    find_height(curr_data->left, curr_level + 1, max_height, max_data);
    find_height(curr_data->right, curr_level + 1, max_height, max_data);
}