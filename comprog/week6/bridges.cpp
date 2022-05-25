#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

int dfs(int u, int depth, int dfsRoot, int rootChildren, const vector<vector<int>> &adj, vector<int> &dfs_min, vector<int> &dfs_num, vector<int> &dfs_parent){
    dfs_min[u] = dfs_num[u] = depth;
    depth++;
    int n_bridges = 0;
    for (auto v: adj[u]){
        if (dfs_num[v] == -1)  // tree edge
        {
            dfs_parent[v] = u;
        
            if (u==dfsRoot) {
                rootChildren++;
            }

            n_bridges += dfs(v, depth, dfsRoot, rootChildren, adj, dfs_min, dfs_num, dfs_parent);

            if (dfs_num[u] <= dfs_min[v] && u != dfsRoot){
                // is AP
            }
            if (dfs_num[u] < dfs_min[v]){
                // is a bridge
                // cout << "ISABRDIGE\n";
                n_bridges++;
            }
            dfs_min[u] = min(dfs_min[u], dfs_min[v]);
        }
        else if (v != dfs_parent[u]){  // Back Edge
            dfs_min[u] = min(dfs_min[u], dfs_num[v]);
        }
    }
    return n_bridges;
} // comprog22 lecture 6, slide 18 and 19a

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> dfs_num(n, -1);
    vector<int> dfs_min(n, -1);
    vector<int> dfs_parent(n, -1);
    int dfsRoot, rootChildren;
    int dfs_depth = 0;
    int n_bridges = 0;

    // read the edges and save them into Adjacency List
    for (int i = 0; i < m; i++){
        int first, second;
        cin >> first >> second;
        first--; second--;
        adj[first].push_back(second);
        adj[second].push_back(first);
    }

    // cout << "--------------\n| ADJ. TABLE |\n--------------\n";
    // for (uint i = 0; i < adj.size(); i++){
    //     cout << i+1 << " | ";
    //     for (uint j = 0; j < adj[i].size(); j++){
    //         cout << adj[i][j]+1 << " ";
            
    //     }
    //     cout << "\n";
    // }

    for (int i = 0; i < n; i++)
    {
        if(dfs_num[i] == -1)
        {
            dfsRoot = i;
            rootChildren = 0;
            n_bridges += dfs(i, dfs_depth, dfsRoot, rootChildren, adj, dfs_min, dfs_num, dfs_parent);
            // if (rootChildren > 1){
            //     cout << i << 
            // }
        }

    }
    cout << n_bridges << "\n";

    return 0;
}
