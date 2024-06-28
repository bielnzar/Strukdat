/*
Nama : Nabiel Nizar Anwari
NRP  : 5027231087
Code : Pohon Sequoia
*/

#include <bits/stdc++.h>

using namespace std;

vector<int> bfs(unordered_map<int, vector<int>> &tree, int start, int finish){
    queue<vector<int>> q;
    unordered_set<int> visited;
    q.push({start});

    while (!q.empty()){
        vector<int> current = q.front();
        q.pop();
        int last = current.back();

        if (last == finish) {
            return current;
        }

        if (visited.find(last) == visited.end()){ 
            visited.insert(last);
            for (int adjNode : tree[last]){
                vector<int> temp = current;
                temp.push_back(adjNode);
                q.push(temp);
            }
        }
    }
    return {};
}

int main()
{
    unordered_map<int, vector<int>> tree;

    int start, finish;
    int max_node = 0;

    while (true){
        string command;
        cin >> command;
        if (command == "stop"){
            break;
        }

        start = stoi(command);
        cin >> finish;
        tree[start].push_back(finish);
        tree[finish];

        max_node = max(max_node, max(start, finish));
    }

    vector<int> path = bfs(tree, 0, max_node);

    unordered_set<int> visited;
    queue<int> q;
    q.push(0);
    visited.insert(0);

    while (!q.empty()){
        int node = q.front();
        q.pop();

        if (tree.find(node) != tree.end()){
            cout << node;
            for (int adjNode : tree[node]) {
                cout << " " << adjNode;
                if (visited.find(adjNode) == visited.end()){
                    q.push(adjNode);
                    visited.insert(adjNode);
                }
            }
            cout << endl;
        }
    }

    if (visited.find(max_node) == visited.end()){
        cout << max_node << endl;
    }

    if (!path.empty()){
        for (size_t i = 0; i < path.size(); ++i){
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
