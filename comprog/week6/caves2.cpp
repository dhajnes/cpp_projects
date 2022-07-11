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

void print_vector_bool(const vector<bool> &vec, const string &txt){
    cout << "vec: " << txt << "\n";
    for (uint i = 0; i < vec.size(); i++){
        cout << i+1 << " | " << vec[i] << "\n";
    }
    cout << "\n";
}

void print_vector_int(const vector<int> &vec, const string &txt){
    cout << "vec: " << txt << "\n";
    for (uint i = 0; i < vec.size(); i++){
        cout << i+1 << " | " << vec[i] << "\n";
    }
    cout << "\n";
}

void print_vector_ll(const vector<ll> &vec, const string &txt){
    cout << "vec: " << txt << "\n";
    for (uint i = 0; i < vec.size(); i++){
        cout << i+1 << " | " << vec[i] << "\n";
    }
    cout << "\n";
}

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

const int UNVISITED = -1;
int dfs_counter = 0;
stack<int> S;
vector<int> ts;
deque<deque<int>> SCCs;

void scc(int u, vector<int> &dfs_num, vector<int> &dfs_min, vector<bool> &on_stack, vector<vector<int>> &adj){
    dfs_min[u] = dfs_num[u] = dfs_counter;
    dfs_counter++;
    S.push(u);
    on_stack[u] = true;

    for (auto v: adj[u])
    {   
        if (dfs_num[v] == UNVISITED)
        {
            scc(v, dfs_num, dfs_min, on_stack, adj);
            dfs_min[u] = min(dfs_min[u], dfs_min[v]);
        }
        else if (on_stack[v])  // only on_stack can use back edge
        {   
            dfs_min[u] = min(dfs_min[u], dfs_num[v]);
        }
    }

    if (dfs_min[u] == dfs_num[u])  // output result
    {
        // cout << "    SCC: ";
        int v = -1;
        deque<int> component;
        do  // output SCC starting in u
        {
            v = S.top();
            S.pop();
            on_stack[v] = false;
            ts.push_back(v);
            component.push_front(v);
        } while (v != u);

        SCCs.push_front(component);
    }
}

int main(){
    int n, m;
    cin >> n >> m;

    // for traversing the graph and finding money
    vector<bool> visited(n, false);
    vector<bool> local_visited(n, false);
    vector<vector<int>> adj(n);
    vector<ll> gold(n);

    // for reducing the graph
    vector<int> dfs_num(n, UNVISITED);
    vector<int> dfs_min(n, UNVISITED);
    vector<bool> on_stack(n, false);

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

    for (int i = 0; i < n; i++)
    {   
        if (dfs_num[i] == UNVISITED)
        {   
            scc(i, dfs_num, dfs_min, on_stack, adj);
        }
    }

    reverse(ts.begin(), ts.end());

    map<int,int> compressor;
    for (uint r = 0; r < SCCs.size(); r++){
        for(auto c : SCCs[r]){
            compressor[c] = r;
        }
    }

    vector<set<int>> adj_new((int)SCCs.size());
    vector<ll> new_gold((int)SCCs.size());
    for (auto node : compressor){
        for (uint i = 0; i < adj[node.first].size(); i++)
        {
            if (compressor[adj[node.first][i]] != node.second)
            {
                adj_new[node.second].insert(compressor[adj[node.first][i]]);
            }
        }
    }

    for (auto node : compressor){
        // cout << node.first +1 << " : "  << node.second +1<< "\n";
        new_gold[node.second] += gold[node.first];
    }

    vector<ll> max_gold_vec = new_gold;
    for (uint u = 0; u < SCCs.size(); u++){
        for (auto it = adj_new[u].begin(); it != adj_new[u].end(); ++it){
                ll maybe_gold = new_gold[*it];
                max_gold_vec[*it] = max(max_gold_vec[*it], max_gold_vec[u] + maybe_gold);     
        }
    }

    cout << *max_element(max_gold_vec.begin(), max_gold_vec.end()) << "\n"; 
    return 0;
}