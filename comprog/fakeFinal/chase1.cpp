#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<vector<pair<ll, ll>>> adj;
vector<ll> dist;


void show_adj_table(const vector<vector<pair<ll,ll>>> &adj){
    cout << "--------------\n| ADJ. TABLE |\n--------------\n";
    for (uint i = 0; i < adj.size(); i++){
        cout << i+1 << " | ";
        for (uint j = 0; j < adj[i].size(); j++){
            cout << "(" <<adj[i][j].first+1 << "," << adj[i][j].second << "), ";
            
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

// void dijkstra(ll start, vector<ll> & dist, const vector<vector<pair<ll, ll>>> & adj){
void dijkstra(ll start){
    dist[start] = 0;
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    pq.push({0, start});  // <distance, vertex>  
    while(!pq.empty())
    {
        auto front = pq.top();
        pq.pop();
        ll d = front.first;  // distance of the vertex
        ll v = front.second;  // ID of the vertex
        if (d > dist[v]) continue;
        for (auto p : adj[v])  // for child with <target, weight>
        {
            ll u = p.first;
            ll w = p.second;
            if (dist[v] + w < dist[u])
            {
                dist[u] = dist[v] + w;
                pq.push({dist[u], u});
            }
        }
    }
}


int main(){
    int V, E, k ;
    cin >> V >> E >> k;
    adj.clear();
    adj.resize(V);
    dist.clear();
    dist.resize(V, LONG_LONG_MAX);
    // capacity.assign(n, vector<int>(n, 0));

    for (int i = 0; i < E; i++){
        int first, second, weight;
        cin >> first >> second >> weight;
        first--; second--;
        adj[first].push_back({second, weight});
        // adj[second].push_back({first, weight});
    }

    dijkstra(0);

    show_adj_table(adj);
    print(dist, "dist");

    if (dist[V-1] != LONG_LONG_MAX){
        cout << dist[V-1] << "\n";
    }
    else{
        cout << "-1\n";
    }
}