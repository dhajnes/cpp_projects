#include <bits/stdc++.h>

typedef long long ll;
#define MIN_INF numeric_limits<ll>::min()
using namespace std;

void show_adj_table(const vector<vector<int>> &adj){
    cout << "--------------\n| ADJ. TABLE |\n--------------\n";
    for (uint i = 0; i < adj.size(); i++){
        cout << i+1 << " | ";
        for (uint j = 0; j < adj[i].size(); j++){
            cout << adj[i][j]+1 << " ";
            
        }
        cout << "\n";
    }
}

void print(const vector<bool> &vec, const string &txt){
    cout << "vec: " << txt << "\n";
    for (uint i = 0; i < vec.size(); i++){
        cout << i+1 << " | " << vec[i] << "\n";
    }
    cout << "\n";
}

void print(const vector<int> &vec, const string &txt){
    cout << "vec: " << txt << "\n";
    for (uint i = 0; i < vec.size(); i++){
        cout << i+1 << " | " << vec[i] << "\n";
    }
    cout << "\n";
}

void print(const vector<ll> &vec, const string &txt){
    cout << "vec: " << txt << "\n";
    for (uint i = 0; i < vec.size(); i++){
        cout << i+1 << " | " << vec[i] << "\n";
    }
    cout << "\n";
}

bool compute_toposort(int start, vector<bool> &visited, vector<bool> &local_visited,
         const vector<vector<int>> &adj, vector<int> &ts){
    
    local_visited[start] = true;
    

    for(int u: adj[start])
    {   
        if(local_visited[u]){
        return false;
        }
        if (!visited[u]){
            if(!compute_toposort(u, visited, local_visited, adj, ts)) return false;
        }
    }

    local_visited[start] = false;
    if(!visited[start]){
        ts.push_back(start);
    }
    visited[start] = true;
    // print_vector(visited, "visited");
    
    return true;
}


int main(){
    int n, m;
    cin >> n >> m;
    vector<bool> visited(n, false);
    vector<bool> local_visited(n, false);
    vector<vector<int>> adj(n);
    vector<ll> gold(n);
    vector<int> ts;
    ts.reserve(n);
    for (int i = 0; i < n; i++){
        ll n_ingots;
        cin >> n_ingots;
        gold[i] = n_ingots;
    }

    for (int i = 0; i < m; i++){
        int first, second;
        cin >> first >> second;
        first--; second--;
        adj[first].push_back(second);        
    }
    for (uint start = 0; start < visited.size(); start++){
        compute_toposort(start, visited, local_visited, adj, ts);
    }
    reverse(ts.begin(), ts.end());

    vector<ll> max_gold_vec = gold;
    for (auto u: ts){
        for (auto node: adj[u]){
            ll maybe_gold = gold[node];
            // print_vector_ll(max_gold_vec, "max_gold_vec");
            max_gold_vec[node] = max(max_gold_vec[node], max_gold_vec[u] + maybe_gold);
        }
    }
    
    print(ts, "toposort");
    cout << "vec: " << "toposort" << "\n";
    for (uint i = 0; i < ts.size(); i++){
        cout << ts[i]+1 << " ";
    }
    cout << "\n";
    
    print(max_gold_vec, "max_gold_vec");
    
    show_adj_table(adj);

    cout << "-----------\n| VISITED |\n-----------\n";
    for (uint i = 0; i < n; i++){
        cout << i+1 << " | " << visited[i] << "\n";
    }
    cout << "-----------\n";
    cout << *max_element(max_gold_vec.begin(), max_gold_vec.end()) << "\n"; 
    return 0;
}