#include <bits/stdc++.h>
typedef long long ll;
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

void print(const vector<vector<int>> &vec, const string &txt){
    cout << "vec: " << txt << "\n";
    for (uint r = 0; r < vec.size(); r++){
        cout << r+1 << " | ";
        for (uint c = 0; c < vec[r].size(); c++){
            cout << vec[r][c] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

#define INF numeric_limits<int>::max()

vector<vector<int>> capacity;
vector<vector<int>> adj;
vector<int> parent;

void bfs(int s) {
    parent.assign(adj.size(), -1);
    parent[s] = -2; // s is visited

    queue<int> Q;
    Q.push(s);
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int v : adj[u]) // go u -> v
            if (parent[v] == -1 and capacity[u][v] > 0) {
                Q.push(v);
                parent[v] = u;
            }
    }
}

int maxflow(int s, int t) {
    int totalflow = 0;
    int u;
    while (true) {
        // build bfs tree
        bfs(s);
        if (parent[t] == -1) // t unreachable
            break;
        // find bottleneck capacity
        int bottleneck = INF;
        u = t;
        while (u != s) {
            int v = parent[u];
            bottleneck = min(bottleneck, capacity[v][u]);
            u = v;
        }
        // update capacities along path
        u = t;
        while (u != s) {
            int v = parent[u];
            capacity[v][u] -= bottleneck;
            capacity[u][v] += bottleneck;
            u = v;
        }
        totalflow += bottleneck;
    }
    return totalflow;
}

int main(){
    int t;  // number of test cases
    int l;  // amount of available policemen
    int n;  // amount of intersections
    int m;  // number of lines with edges

    // for each test case
    cin >> t;
    for (int test_cases = 0; test_cases < t; test_cases++){
        cin >> l >> n >> m;
        // adj.assign(n, vector<int>(0, 0));  // <------------ HMMMMMM
        adj.clear();
        adj.resize(n);
        capacity.assign(n, vector<int>(n, 0));

        // for each edge in this test case
        int u, v, c;
        for (int n_edges = 0; n_edges < m; n_edges++) {
            cin >> u >> v >> c;
            u--; v--;
            adj[u].push_back(v);
            // if (count(adj[v].begin(), adj[v].end(), u) == 0){
            adj[v].push_back(u);
            // }
            // show_adj_table(adj);
            capacity[u][v] += c;
            capacity[v][u] += c;
        }
        // cout << "For test case: " << test_cases << "\n";

        int out = maxflow(0,n-1);
        
        // show_adj_table(adj);
        // print(capacity, "capacity");
        // cout << "out: " << out << "\n";
        cout << "Case #" << test_cases+1 << ": ";
        if (out <= l){
            cout << "yes\n";
        }
        else cout << "no\n";
    }
    
    
    return 0;
}