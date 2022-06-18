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

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

void visit(int v, vector<bool> &visited, const vector<vector<pair<ll,ll>>> &adj,
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> &PQ){
    visited [v] = true;
    for (auto p: adj[v]){
        int u = p.first;
        int w = p.second;
        if (!visited[u])
        {
            PQ.push({w, v, u});
        }
    }
}

int main(){
    int n;  // number of cities
    int m;  // number of streets
    cin >> n >> m;

    vector<vector<pair<ll, ll>>> adj(n);

    // read the edges and save them into Adjacency List
    for (int i = 0; i < m; i++){
        ll first, second, weight;
        cin >> first >> second >> weight;
        first--; second--;
        adj[first].push_back({second, weight});
        adj[second].push_back({first, weight});  // bidirectional streets
    }
    
    vector<bool> visited(n, false);
    // <weight, from, to>
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> PQ;
    visit(0, visited, adj, PQ);
    while (!PQ.empty()) {
        auto front = PQ.top(); PQ.pop();
        int w, from, to;
        tie(w, from, to) = front;
        if (!visited[to]) {
            cout << "Add " << from+1 << "-" << to+1 << " to MST\n";
            visit(to, visited, adj, PQ);
        }
    }

    // output the maximum total quality


    return 0;
}