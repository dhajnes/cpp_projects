# include <bits/stdc++.h>

typedef long long ll;
using namespace std;

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

void show_adj_table(const vector<vector<pair<int,int>>> &adj){
    cout << "--------------\n| ADJ. TABLE |\n--------------\n";
    for (uint i = 0; i < adj.size(); i++){
        cout << i+1 << " | ";
        for (uint j = 0; j < adj[i].size(); j++){
            cout << "("<< adj[i][j].first +1 << " " << adj[i][j].second << ") ";
            
        }
        cout << "\n";
    }
}

void dijkstra(int start, vector<ll> & dist, const vector<vector<pair<ll, ll>>> & adj){
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
    int n, m, k1, k2;
    // n - num of locations
    // m - num of oneway streets
    // k1 - num of friends
    // k2 - num of supermarkets (nodes)

    // weighted directed graph


    cin >> n >> m >> k1 >> k2;
    int friend_loc;
    cin >> friend_loc;
    friend_loc--;
    vector<int> supermarkets(k2, 0);
    for (int i = 0; i < k2; i++){
        int super;
        cin >> super;
        super--; 
        supermarkets[i] = super;
    }

    // read the edges and save them into Adjacency List
    vector<vector<pair<ll, ll>>> adj(n);  // initialized to zeros in the first dim
    for (int i = 0; i < m; i++){
        ll first, second, weight;
        cin >> first >> second >> weight;
        first--; second--;
        adj[first].push_back({second, weight});
        // adj[second].push_back({first, weight});
    }

    // show_adj_table(adj);
    vector<ll> dists(n, LONG_LONG_MAX);
    dijkstra(friend_loc, dists, adj);

    ll min_length = LONG_LONG_MAX;
    bool impossible = true;
    for (int i = 0; i < k2; i++){
        int s = supermarkets[i];
        // cout << "supermarket s+1: " << s+1;
        if (dists[s] != -1){
            if (dists[s] < min_length){
                min_length = dists[s];
                impossible = false;
            }
        }
    }
    // print(dists, "dists");
    if (impossible){
        cout << "impossible\n";
        return 0;
    }
    else{
        cout << min_length << "\n";
    }


    return 0;
}

