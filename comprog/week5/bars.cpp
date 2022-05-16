#include <bits/stdc++.h>

using namespace std;
typedef long long ll;


void dfs(int v, vector<bool> *visited, vector<vector<int>> *adj, int max_depth, int curr_depth){
        (*visited)[v] = true;
        vector<bool> temp_visited = *visited;
        
        for (int u: (*adj)[v])
        {
            if (curr_depth < max_depth)
            {   
                
                dfs(u, visited, adj, max_depth, curr_depth+1);
            }
        }
    }

void bfs(int start, vector<bool> &visited, const vector<vector<int>> &adj, int max_depth){
    queue<pair<int,int>> Q;

    Q.push({start, 0});
    visited[start] = true;
    // int curr_depth = 0;

    while (!Q.empty())
    {   

        auto v = Q.front();
        if (v.second >= max_depth) break;
        Q.pop();

        for (int u: (adj)[v.first]){
            if (!visited[u]){
                Q.push({u, v.second+1});
                visited[u] = true;
            }
        }
    }
}

int main(){
    // bool vb = false;
    int n, m, s, d;
    cin >> n >> m >> s >> d;
    s--;
    vector<vector<int>> adj(n);  // initialized to zeros in the first dim
    vector<bool> visited(n, false);
    
    // read the edges and save them into Adjacency List
    for (int i = 0; i < m; i++){
        int first, second;
        cin >> first >> second;
        first--; second--;
        adj[first].push_back(second);
        adj[second].push_back(first);
    }
    
    bfs(s, visited, adj, d);
    int count = 0;
    for (int i = 0; i < n; i++){
        if(visited[i]) count++;
    }
    
    
    // cerr << "--------------\n| ADJ. TABLE |\n--------------\n";
    // for (uint i = 0; i < adj.size(); i++){
    //     cerr << i+1 << " | ";
    //     for (uint j = 0; j < adj[i].size(); j++){
    //         cerr << adj[i][j]+1 << " ";
            
    //     }
    //     cerr << "\n";
    // }
    // cerr << "\n- - - - -\n\n";
    // cerr << "-----------\n| VISITED |\n-----------\n";
    // for (uint i = 0; i < adj.size(); i++){
    //     cerr << i+1 << " | " << visited[i] << "\n";
    // }
    // cerr << "-----------\n";

    cout << count << "\n";
    return 0;
}