#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void show_adj_table(const vector<vector<int>> &adj){
    cout << "--------------\n| ADJ. TABLE |\n--------------\n";
    for (uint i = 0; i < adj.size(); i++){
        cout << i << " | ";
        for (uint j = 0; j < adj[i].size(); j++){
            cout << adj[i][j] << " ";
            
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
    int n;
    cin >> n;
    adj.clear();
    adj.resize(2*n+2);
    capacity.assign(2*n+2, vector<int>(2*n+2, 0));

    int e;
    // setup the source
    for (int man = 1; man < n+1; man++){ // source is 0, men are from id 1
        adj[0].push_back(man);
        // adj[man].push_back(0);
        capacity[0][man] += 1;
        // capacity[man][0] += 1;
    }

    // setup the drain
    for (int wine = n+1; wine < 2*n+1; wine++){
        // adj[2*n+1].push_back(wine);
        adj[wine].push_back(2*n+1);
        capacity[wine][2*n+1] += 1;
        // capacity[2*n+1][wine] = INF / 2;
    }

    for (int r = 1; r < n+1; r++){
        for (int c = 0; c < n; c++){
            cin >> e;
            if (e == 1){
                adj[r].push_back(c+n+1);
                adj[c+n+1].push_back(r);
                capacity[r][c+n+1] += 1;
                // capacity[c+n+1][r] += 1;
            }
        }
    }

    // show_adj_table(adj);
    // print(capacity, "capacity");
    int out = maxflow(0,2*n+1);
    cout << out << "\n";

    
    
    return 0;
}