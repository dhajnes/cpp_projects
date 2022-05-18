#include <bits/stdc++.h>
#define INF numeric_limits<ll>::max()

using namespace std;
typedef long long ll;


void dijkstra(ll start, vector<ll> & dist, const vector<vector<pair<ll, ll>>> & adj){
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
} // compro lecture_5, slide 38


int main(){
    bool vb = false;
    ll n_nodes, b_lines, m, t;
    cin >> n_nodes >> b_lines >> m >> t;
    vector<vector<pair<ll, ll>>> adj(n_nodes);  // initialized to zeros in the first dim
    vector<ll> dist(n_nodes, INF);
    
    
    // read the edges and save them into Adjacency List
    for (int i = 0; i < b_lines; i++){
        ll first, second, weight;
        cin >> first >> second >> weight;
        first--; second--;
        adj[first].push_back({second, weight});
        adj[second].push_back({first, weight});
    }
    
    dijkstra(1-1, dist, adj);

    if(vb)
    {

    cout << "--------------\n| ADJ. TABLE |\n--------------\n";
    for (uint i = 0; i < adj.size(); i++){
        cout << i+1 << " | ";
        for (uint j = 0; j < adj[i].size(); j++){
            cout << "("<< adj[i][j].first+1 << " [" << adj[i][j].second << "]) ";
            
        }
        cout << "\n";
    }
    cout << "\n- - - - -\n\n";
    cout << "-----------\n| distances |\n-----------\n";
    for (uint i = 0; i < adj.size(); i++){
        cout << i+1 << " | " << dist[i] << "\n";
    }
    cout << "-----------\n";
    }
    // cout << "n_nodes -1: " << n_nodes-1 << "\n"; 
    cout << dist[n_nodes-1] << "\n";

    return 0;
}