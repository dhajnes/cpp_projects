#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void show_weight_table(const vector<vector<pair<ll,ll>>> &adj){
    cout << "--------------\n| ADJ. TABLE |\n--------------\n";
    for (uint i = 0; i < adj.size(); i++){
        cout << i+1 << " | ";
        for (uint j = 0; j < adj[i].size(); j++){
            cout << "(" << adj[i][j].first+1 << ", " << adj[i][j].second << " ) ";
        }
        cout << "\n";
    }
}

void show_adj_table(const vector<vector<bool>> &adj){
    cout << "--------------\n| ADJ. TABLE |\n--------------\n";
    for (uint i = 0; i < adj.size(); i++){
        cout << i+1 << " | ";
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

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

void visit(int v, vector<bool> &visited, const vector<vector<pair<ll,ll>>> &adj,
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, less<tuple<int,int,int>>> &PQ){
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
    ll positive_sum = 0;

    vector<vector<pair<ll, ll>>> adj(n);
    vector<vector<bool>> edge_visited(n);
    // read the edges and save them into Adjacency List
    for (int i = 0; i < m; i++){
        ll first, second, weight;
        cin >> first >> second >> weight;
        first--; second--;
        if (weight > 0){
            positive_sum += weight;
        }
        adj[first].push_back({second, weight});
        edge_visited[first].push_back(false);
        if (first != second){
            adj[second].push_back({first, weight});  // bidirectional streets
            edge_visited[second].push_back(false);
        }
    }
    // cout << "positive sum after loading: " << positive_sum << "\n";
    
    vector<bool> visited(n, false);
    // <weight, from, to>
    // priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> PQ;
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, less<tuple<int,int,int>>> PQ;
    visit(0, visited, adj, PQ);
    while (!PQ.empty()) {
        auto front = PQ.top(); PQ.pop();
        int w, from, to;
        tie(w, from, to) = front;
        if (!visited[to]) {
            // cout << "Add " << from+1 << "-" << to+1 << " to MST\n";
            // edge_visited[from][to] = true;
            if (w < 0){
                // cout << "minusing w: " << w << "\n";
                positive_sum += w;
            }
            // if (from != to){
            //     edge_visited[to][from] = true;
            // }

            visit(to, visited, adj, PQ);

        }
    }
    

    // output the maximum total quality
    // show_weight_table(adj);
    // show_adj_table(edge_visited);
    cout << positive_sum << "\n";

    return 0;
}