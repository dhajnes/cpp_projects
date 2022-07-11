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

#define MIN_INF numeric_limits<ll>::min()
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
    
    return true;
}

int main(){
    int n;  // number of nodes
    int m;  // number of directed paths
    cin >> n >> m;
    vector<bool> visited(n, false);
    vector<bool> local_visited(n, false);
    vector<int> ts;
    ts.reserve(n);

    vector<int> vals(n,0);
    for (int i = 0; i < n; i++){
        int val;
        cin >> val;
        vals[i] = val;
    }
    // print(vals, "vals");
    // cout << "int max: " << INT_MAX;
    vector<vector<int>> adj(n);  // initialized to zeros in the first dim
    for (int i = 0; i < m; i++){
        int first, second;
        cin >> first >> second;
        first--; second--;
        adj[first].push_back(second);
    }

    // show_adj_table(adj);
    for (uint start = 0; start < visited.size(); start++){
        compute_toposort(start, visited, local_visited, adj, ts);
    }
    reverse(ts.begin(), ts.end());

    // cout << "toposort:\n";
    vector<int> toposort_values(n,0);
    int cnt = 0;
    for (auto x : ts){
        // cout << x +1 << " ";
        toposort_values[cnt] = vals[x];
        cnt++;
    }
    // cout << "\n";

    // print(toposort_values, "toposort_values");
    
    // now on values of topologically sorted nodes find LIS
    vector<ll> dp(n, 0);
    ll lis = 0;
    for (int i = 0; i < n; i++){
        dp[i] = 1;
        for (int j = 0; j < i; j++){
            if (toposort_values[j] < toposort_values[i]){
                dp[i] = max(dp[i], dp[j]+1);
            }
        }
        lis = max(lis, dp[i]);
    }
    print(dp, "dp");
    cout << lis << "\n";

    return 0;
}