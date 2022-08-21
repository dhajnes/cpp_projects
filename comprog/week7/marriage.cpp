#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
map <int, string> id2name;
map <string, int> name2id;

// used for storage
map <int, pair<string,int>> q_answers;

void show_weight_table(const vector<vector<pair<int,int>>> &adj){
    cout << "--------------\n| ADJ. TABLE |\n--------------\n";
    for (uint i = 0; i < adj.size(); i++){
        cout << i+1 << " | ";
        for (uint j = 0; j < adj[i].size(); j++){
            cout << "(" << adj[i][j].first+1 << ", " << adj[i][j].second << " ) ";
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

// class UnionFind{
//     private:
//         vector<int> parent;
//     public:
//         UnionFind(int N) {
//             parent.resize(N);
//             for (int i = 0; i < N; i++) parent[i] = i;
//         }
//         int findSet(int i){
//             // print(parent, "parent:");
//             if (parent[i] == i) return i;
//             else return findSet(parent[i]);  // perhaps add path compression?
//         }
//         bool isSameSet(int i, int j){
//             return findSet(i) == findSet(j);
//         }
//         void unionSet(int i, int j){
//             i = findSet(i), j = findSet(j);
//             if (!isSameSet(i, j)){  // or (i != j)
//                 parent[i] = j;
//             }

//         }
// };  // Lec 7, p17, compro22 SoSe
map <int, string> id2name;
map <string, int> name2id;

class UnionFind{
    private:
        vector<int> parent, rank; 
    public:
        UnionFind(int N) {
            rank.assign(N,0);  // initialize
            parent.resize(N);
            for (int i = 0; i < N; i++) parent[i] = i;
        }
        void unionSet(int i, int j){
            i = findSet(i), j = findSet(j);
            if (!isSameSet(i, j)){  // or (i != j)
                if (rank[i] > rank[j])
                {
                    parent[j] = i;
                }
                else 
                {
                    parent[i] = j;
                    if (rank[i] == rank[j]) rank[j]++;
                }
            }
        }
        int findSet(int i){
            if (parent[i] == i)
            {
                return i;
            }
            else
            {
                return parent[i] = findSet(parent[i]);  // perhaps add path compression?
            }
        }
        bool isSameSet(int i, int j){
            return findSet(i) == findSet(j);
        }

};  // Lec 7, p20, compro22 SoSe

// lowest common ancestor
void lca(int u, const vector<vector<int>> &adj, vector<int> &ancestor, UnionFind &UF, vector<bool> &visited,  vector<vector<pair<int, int>>> &queries, vector<int> &depth_field){  // lowest common ancestor
    for (auto v: adj[u])
    {
        depth_field[v] = depth_field[u] + 1;
        lca(v, adj, ancestor, UF, visited, queries, depth_field);
        UF.unionSet(u,v);
        ancestor[UF.findSet(u)] = u;
    }
    visited[u] = true;

    for (auto quer : queries[u]){
            int v = quer.first;
            int order = quer.second;
            // cout << "v: " << v << "order " << order << "\n";
            if (visited[v]){
                // cout << "LCA of " << u+1 << " and " << v+1 << " is " << ancestor[UF.findSet(v)]+1 << "\n";
                int lca_temp = ancestor[UF.findSet(v)];

                // compute distance of relatives SWWEEEEET HOOOOME AAALAABAAAAMA
                
                int dist = (depth_field[u] - depth_field[lca_temp]) + (depth_field[v] - depth_field[lca_temp]);
                // cout << dist << "\n";
                // print(depth_field, "depth_field");
                q_answers[order] = {id2name[lca_temp], dist};  // adds the query result into a map
            }
    }
}  // adapted from Lecture 7, p. 32, compro22, SoSe

int main(){
    int n, q;
    cin >> n >> q;
    vector<string> names(n);
    vector<int> ids(n);


    vector<vector<int>> adj(n);
    auto UF = UnionFind(n);
    vector<int> ancestor(n);

    // needed to solve wrong answer
    for (int i = 0; i < n; i++) ancestor[i] = i;


    vector<vector<pair<int, int>>> queries(n);
    vector<bool> visited(n, false);
    vector<int> depth_field(n,0);

    // adj load
    for (int i = 0; i < n; i++){
        string name;
        cin >> name;
        names[i] = name;
        ids[i] = i;
        id2name[i] = name;
        name2id[name] = i;
    }

    for (int i = 0; i < n-1; i++){
        string name;
        cin >> name;
        adj[name2id[name]].push_back(i+1);
    }
    
    for(int i = 0; i < q; i++){
        string first, second;
        cin >> first >> second;
        queries[name2id[first]].push_back({name2id[second], i});

        // put in the query from both sides, LCA may not find onesided query only
        if (name2id[second] != name2id[first]){
            queries[name2id[second]].push_back({name2id[first], i});
        }  
    }

    lca(0, adj, ancestor, UF, visited, queries, depth_field);    
      for (int i = 0; i < q; i++){
        cout << q_answers[i].first << " " << q_answers[i].second << "\n";
    }    

    return 0;
}