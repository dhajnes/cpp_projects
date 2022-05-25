#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

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

bool first_necessary_condition(int n, const vector<vector<int>> &adj, const vector<int> &indegree){
    /*  
    i) at most one vertex has out_degree == 1 + indegree
    and
    ii) at most one vertex has in_degree == 1 + outdegree
    iii) all other vertices: in_degree == out_degree 
    */
    bool first = false;
    bool second = false;
    
    for (int i = 0; i < n; i++){
        // i)
        if ((int) adj[i].size() == indegree[i] + 1)
        {
            if (first) return false;
            else first = true;
        }
        // ii)
        else if (indegree[i] == 1 + (int) adj[i].size())
        {
            if (second) return false;
            else second = true;
        }
        else{
        // iii)
            if (indegree[i] != (int) adj[i].size())
            {
                return false;
            }
        }
    }
    return true;
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);

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

    show_adj_table(adj);
    print_vector(indegree, "Indegree");
    if (first_necessary_condition(n, adj, indegree)) cout << "True\n";
    else cout << "False\n";
    
    return 0;
}