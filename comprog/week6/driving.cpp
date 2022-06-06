#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
bool vb = false;

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

void print_vector(const vector<int> &vec, const string &txt){
    cout << "vec: " << txt << "\n";
    for (uint i = 0; i < vec.size(); i++){
        cout << i+1 << " | " << vec[i] << "\n";
    }
    cout << "\n";
}

bool first_necessary_condition(int &n, const vector<vector<int>> &adj, const vector<int> &indegree){
    /*  
    i) the first vertex has out_degree == 1 + indegree
    and
    ii) the last vertex has in_degree == 1 + outdegree
    iii) all other vertices: in_degree == out_degree 
    */
    int temp_n = n;
    for (int i = 0; i < n; i++){
        
        
        if(((int) adj[i].size() == 0) && (indegree[i] == 0)){
            // cout << "i: " << i << " | (int) adj[i].size() " << (int) adj[i].size() << " | indegree[i] : " << indegree[i] << "\n";    
            // cout << "temp_n--\n";
            temp_n--;
            continue;
        }
    
        // i)
        if (i == 0){
            if ((int) adj[i].size() != indegree[i] + 1)
            {   
                if(vb){
                    cout << "i: " << i << "\n";
                    cout << "1 false\n";
                }
                return false;
            }
        }
        // ii)
        else if (i == n-1){
            if (indegree[i] != 1 + (int) adj[i].size())
            {   
                if(vb){
                    cout << "i: " << i << "\n";
                    cout << "2 false\n";      
                }
                
                return false;
            }    
        }
        else{
        // iii)
            if (indegree[i] != (int) adj[i].size())
            {   
                if(vb){
                    cout << "i: " << i << "\n";
                    cout << "3 false\n";
                }
                
                return false;
            }
        }
    }
    n = temp_n;
    return true;
}


void flood_dfs(int v, int &visited_cnt, const vector<vector<int>> &adj, vector<bool> &visited){
    visited[v] = true;
    visited_cnt++;
    for (int u : adj[v])
    {
        if (!visited[u]){
            flood_dfs(u, visited_cnt, adj, visited);
        }
    }
}


int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<bool> visited(n, false);
    vector<int> indegree(n, 0);
    int visited_cnt = 0;
    // vector<int> has_path(n, 0);

    // read the edges and save them into Adjacency List
    for (int i = 0; i < m; i++){
        int first, second;
        cin >> first >> second;
        first--; second--;
        adj[first].push_back(second);
        indegree[second]++;
        
        // one directional graph
        // adj[second].push_back(first);
    }
    if (vb){
        show_adj_table(adj);
        print_vector(indegree, "Indegree");
    }
    // int temp_n = n;
    if (first_necessary_condition(n, adj, indegree)){
        flood_dfs(0, visited_cnt, adj, visited);
        // cout << "visited_cnt: " << visited_cnt << " n: " << n << "\n";
        
        
        if (visited_cnt == n){
            cout << "possible\n";
            return 0;
        }
        else{
            if (vb){
                cout << "Because visited_cnt != n:\n";
                cout << "n: " << n << "\n";
            }
            cout << "impossible\n";
            return 0;
        }
        
    } 
    else cout << "impossible\n";
    
    return 0;
}