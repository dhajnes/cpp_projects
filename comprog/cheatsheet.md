# **Week 1**
## `lineup` - wines, find the correct combination
>**bruteforce, all permutations**
- `next_permutation(vec.begin(), vec.end())`
## `outoforder` - sort and bruteforce
>**bruteforce, sorting**
## `theanswer` - find 3 numbers in a list that sum up to 42
>**binary search on a sorted array**
- `sort(vec.begin(), vec.end())`
- `binary_search(vec.begin(), vec.end(), query_value)`



# **Week 2**
## `bordeaux`
## `microbes` - Query-Update problem,
>**divide-and-Conquer**
- the helpful thing here was to compupte sums over chunks
- if update was in some chunk add/subtract the value of the chunk
- if query was over multiple chunks, the whole chunks neednt be checked, only their sums
## `theanswercount` - subset checking, generating power-set
>**subset, lower-bound/upper-bound on a sorted array**
- split set into 2 subsets
- generate its power set using mask (compute sums)
- check for the remaining number in the other sorted set using lb/ub
- this could be done with binary_search, but there may be duplicit numbers that are correct, say 5 times the number you are looking for in a series
```cpp
// generate all subsets 
uint pow_set_size = pow(2, A1.size());
for (uint cnt = 0; cnt < pow_set_size; cnt++){

    ll temp_sum = 0;
    for (uint i=0; i < A1.size(); i++){
        if (cnt & (1 << i)){
            temp_sum += A1[i];
        }
    }
    S1.push_back(temp_sum);
}
```
```cpp
for(uint i=0; i<S1.size(); i++){
        ll candidate = S1[i];
        // S2 is sorted
        auto lb = lower_bound(S2.begin(), S2.end(), (x - candidate));
        auto ub = upper_bound(S2.begin(), S2.end(), (x - candidate));
        total_count += ub-lb;
    }
```



# **Week 3**
## `begging` - check for optimal subproblems
> dynamic programming

```cpp
class dpClass {       // The class
  public:             // Access specifier
    int val{0};        // Attribute (int variable)
    int prev;
};
//...
vector<dpClass> dp(n, dpClass{});
```
- check for sufficient sub-solutions
- optimal choice of waiting time to beg for wine

## `cashier` - Coin-change problem
> dynamic programming

## `cake` - Tiling problem
> 2-D prefix sums, Dynamic Programming
```cpp
vector<vector<int>> p_sums(vector<vector<int>> tray){
    vector<vector<int>> sums(tray.size(), vector<int>(tray[0].size(), 0));
    for (uint r = 0; r < tray.size(); r++){
        for (uint c = 0; c < tray[0].size(); c++){
            if (r == 0 && c == 0){
                sums[r][c] = tray[r][c];
            }
            else if (r == 0){
                sums[0][c] = sums[0][c-1] + tray[0][c];
            }
            else if (c == 0){
                sums[r][0] = sums[r-1][0] + tray[r][0];
            }
            else{
                sums[r][c] = sums[r-1][c] + sums[r][c-1] - sums[r-1][c-1] + tray[r][c];
            }
        }       
    } 
    return sums;
}
//...
for (int r=0; r <= h-h_cake; r++){
        for (int c=0; c <= w-w_cake; c++){
            temp_sum = psv[r+h_cake-1][c+w_cake-1];
            if (r == 0 && c == 0){
                
            }
            else if (r == 0){
                // sums[0][c] = sums[0][c-1] + tray[0][c];
                temp_sum -= psv[r+h_cake-1][c-1];
            }
            else if (c == 0){
                // sums[r][0] = sums[r-1][0] + tray[r][0];
                temp_sum -= psv[r-1][c+w_cake-1];
            }
            else{
                // sums[r][c] = sums[r-1][c] + sums[r][c-1] - sums[r-1][c-1] + tray[r][c];
                temp_sum += -psv[r+h_cake-1][c-1] - psv[r-1][c+w_cake-1] + psv[r-1][c-1];
            }
            if (temp_sum == 0){
                cout << r+1 <<" "<< c+1 <<" "<< r+h_cake <<" "<< c+w_cake << "\n";
                return 0;
            }
        }
    }
```

## `warming` - Longest Increasing Subsequence 
> LIS - Longest Increasing Subsequence, DP - Dynamic Programming
```cpp
int lis = 0;
for (int i=0; i<n; i++){
    dp[i] = 1;
    for (int j=0; j<i; j++){
        if (temperatures[j] < temperatures[i]){
            dp[i] = max(dp[i], dp[j]+1);   
        }
    }
    lis = max(lis, dp[i]);
}
cout << lis << "\n";
```

## `warming2` - LIS with binary search
> LIS, Binary Seacrh

```cpp
int minus_int_inf = numeric_limits<int>::min();
g_vals.push_back(minus_int_inf);

for (int i=0; i < n; i++){
    int g_idx = lower_bound(g_vals.begin(), g_vals.end(), A[i]) - g_vals.begin();
    f_vals.push_back(1 + g_idx-1);  // f_i = 1 + max{l|g_i[l] < A[i]}

    // now the g_vals(i+1) = min{g[f[i]], A[i]}
    if (f_vals[i] > (int)(g_vals.size()-1)){
        // if g_vals too small, append
        g_vals.push_back(A[i]);
    }
    else{
        // else just update the number already there
        g_vals[f_vals[i]] = min(g_vals[f_vals[i]], A[i]);
    }
}
```



# **Week 4**
## `sumup` and `equations`
> Tree parsing, Custom Nodes
```cpp
# include <bits/stdc++.h>

typedef long long ll;
using namespace std;

class Node {
    public:
        ll val{-1};
        bool X{false};
        vector<Node *> children{};
        Node * parent{nullptr};
};


int whole_num(ll *i, const string& inp){
    /*Here, the number is guaranteed to be 3 chars long.*/
    char num_chars[4];
    for (int k = 0; k < 3; k++){
        num_chars[k] = inp[*i];
        (*i)++;  // moves the value of the pointer by one
    }
    
    num_chars[3] = '\0';
    // cout << "num_chars: " << num_chars << "\n";
    int out_num = stoi(num_chars);
    return out_num;
}



int deeper(Node *node, ll *i, const string &inp){
    
    while((*i) < (ll) inp.size()){

        if (inp[*i] == ')'){
            (*i)++;
            break;
        }
        if (inp[*i] == '(' || inp[*i] == ','){
            (*i)++;
        }
        
        if (isdigit(inp[*i])){
            int num = whole_num(i, inp);
            if (num == -1){
                return -1;
            }
            Node* new_node = new Node{num, false, {}, node};
            node->children.push_back(new_node);          
        }
        else if (inp[*i] == 'X')
        {
            Node* new_node = new Node{'X', true, {}, node};
            node->children.push_back(new_node);  
            (*i)++;
        }
        else if (inp[*i] == '+')
        {
            // Node new_node;
            Node* new_node = new Node{'+', false, {}, node};
            node->children.push_back(new_node);
            (*i)++;
            if (deeper(new_node, i, inp) == -1) return -1;

        }
        else if (inp[*i] == '*')
        {
            Node* new_node = new Node{'*', false, {}, node};
            node->children.push_back(new_node);
            (*i)++;
            if (deeper(new_node, i, inp) == -1) return -1;
        }
    }
    return 0;
}


void delete_tree(Node * root){

    if (root->children.empty()){
            return;
        }
    else{
        
        for (uint i = 0; i < root->children.size(); i++){
            delete_tree(root->children[i]);           
            delete root->children[i];
        }
    }
}


ll eval_tree(Node * root, ll x){
    ll total;

    if (root->children.empty()){
        if (root->X){
            return x;
        }
        else{
            return root->val;
        }
        
    }
    else
    {
        if(root->val == '*'){
            total = 1;
            for (uint i = 0; i < root->children.size(); i++){
                total *= eval_tree(root->children[i], x);
            }
        }
        else{
            total = 0;
            for (uint i = 0; i < root->children.size(); i++){
                total += eval_tree(root->children[i], x);
            }
        }  
    }
    return total;
}

void print_tree(Node * root, int indent){
    // node_info(root);

    if (root->children.empty()){
            // cout << "is empty? : " << root->children.empty() << "\n";
            for (int i = 0; i < indent; i++) cout << " ";
            if (root->X)
            {
                cout << (char) root->val << "\n";
            }
            else
            {
                cout  << root->val << "\n";
            }
            
        }
    else{
        for (int i = 0; i < indent; i++) cout << " ";
        cout << (char)(root->val) << "\n";
        for (uint i = 0; i < root->children.size(); i++){
            print_tree(root->children[i], indent + 2);           
        }
    }
    
    return;
}

int main(){
    string line;
    ll amax;
    ll y;
    cin >> amax >> y;
    getline(cin, line);
    getline(cin, line);
    
    Node root;
    // cycle through chars of string
    int flag = 0;
    for (ll j = 0; j < (ll) line.size(); j++){

        root.val = line[0];
        if(root.val == 'X')
        {
            root.X = true;
        }
        j++;
    
        flag = deeper(&root, &j, line);
        
    }
    if (flag == -1){
        delete_tree(&root);
        cout << "impossible\n";
        return 0;
    }

    ll lb = 1;
    ll ub = amax;

    ll mid;
    ll candidate_output = -1;
    ll possible_answer = -1;
    while(lb <= ub){
        mid = (ub - lb)/2 + lb;
        candidate_output = eval_tree(&root, mid);
        if (candidate_output == y){
            cout << mid << "\n";
            delete_tree(&root);
            return 0;
        }
        else if (candidate_output < y)
        {
            lb = mid + 1;
            possible_answer = mid;
            possible_answer++;
        }
        else
        {
            ub = mid - 1;
        }
        
    }
    cout << "impossible" << "\n";
    delete_tree(&root);
    return 0;
}
```

## `covering`
```cpp
int get_whole_num(ll *i, const string& inp){
    char num_chars[4];
    int cnt = 0;
    while (true){
        if (inp[*i] == ',' || inp[*i] == ')') break;
        num_chars[cnt] = inp[*i];
        cnt++;
        (*i)++;  // moves pointer by one
    }
    num_chars[cnt] = '\0';
    // cout << "`whole_num`: \n" << stoi(num_chars) << "\n";
    return stoi(num_chars);
}

int main(){
    // bool vb = false;
    vector<string> trees;
    ios::sync_with_stdio(false);
    string line;
    while(getline(cin, line)){
        trees.push_back(line);
    }
    vector<set<int>> s((int) trees.size(), set<int>{});
    
    int max_num = 0;
    int num;

    /* -- PARSE THE INPUT INTO SETS -- */
    
    for (uint i = 0; i < trees.size(); i++){ // for tree in trees
        
        for (ll j = 0; j < (ll) trees[i].size(); j++){ // for char in tree
            
            if (isdigit(trees[i][j])){
                num = get_whole_num(&j, trees[i]);
                s[i].insert(num);
                if (num > max_num){
                    max_num = num;
                }
            }
        }
    }

    vector<int> markers(max_num+1, -1);
    vector<ll> masks(s.size(), 0);
    uint max_arity = 0;
    uint arity_cnt = 0;
    ll mask_len = 8 * sizeof(ll);

    // generate masks
    for (uint i = 0; i < s.size(); i++){
        for (auto const &k : s[i])
        {   
            masks[i] = masks[i] | 1 << (k % mask_len);  
        }
    }

    // choose examined candidate superset
    for (uint i = 0; i < s.size(); i++)
    {  
        arity_cnt = 0;
        for (auto const &k : s[i])
        {   
            markers[k] = i; // mark itself into the marks 
        }
        
        // cycle through candidate subsets
        for (uint j = 0; j < s.size(); j++)
        {  
            if (j == i) continue;  // dont examine self

            if ((~masks[i] & masks[j]) != 0)
            {
                continue;
            }

            else
            {    
                bool is_subset = true;
                for (auto const &k : s[j]){
                    if (markers[k] != (int) i)
                    {   
                        is_subset = false;
                        break;
                    }
                }   
                if(is_subset) arity_cnt++;
            
            }
        }
        if (arity_cnt > max_arity) max_arity = arity_cnt;
    }
    cout << max_arity << "\n";

    return 0;
}
```



# **Week 5** - Graphs, DFS, BFS
## utility stuff
### loading stuff
```cpp
// read the edges and save them into Adjacency List
vector<vector<pair<ll, ll>>> adj(n_nodes);  // initialized to zeros in the first dim
for (int i = 0; i < b_lines; i++){
    ll first, second, weight;
    cin >> first >> second >> weight;
    first--; second--;
    adj[first].push_back({second, weight});
    adj[second].push_back({first, weight});
}
```
### printing stuff
```cpp
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
```

## `bars`
> DFS - Depth First Search

### recurrent DFS
```cpp
void dfs(int v, vector<bool> *visited, vector<vector<int>> *adj, int max_depth, int curr_depth){
        (*visited)[v] = true;
        vector<bool> temp_visited = *visited;
        
        for (int u: (*adj)[v])
        {
            if (curr_depth < max_depth)
            {     
                dfs(u, visited, adj, max_depth, curr_depth+1);
            }
        }
    }
```
### stacked BFS
```cpp
void bfs(int start, vector<bool> &visited, const vector<vector<int>> &adj, int max_depth){
    queue<pair<int,int>> Q;

    Q.push({start, 0});
    visited[start] = true;
    // int curr_depth = 0;

    while (!Q.empty())
    {   

        auto v = Q.front();
        if (v.second >= max_depth) break;
        Q.pop();

        for (int u: (adj)[v.first]){
            if (!visited[u]){
                Q.push({u, v.second+1});
                visited[u] = true;
            }
        }
    }
}
```

## `fares` - Shortest Path, positive weights
> Dijkstra's algorithm

```cpp
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
```

## `inequalities`
> Toposort, topsort, topological sort
- more advanced topological sort given further below



# **Week 6**

## `bridges`
> DFS for finding bridges

```cpp
int dfs(int u, int depth, int dfsRoot, int rootChildren, const vector<vector<int>> &adj, vector<int> &dfs_min, vector<int> &dfs_num, vector<int> &dfs_parent){
    dfs_min[u] = dfs_num[u] = depth;
    depth++;
    int n_bridges = 0;
    for (auto v: adj[u]){
        if (dfs_num[v] == -1)  // tree edge
        {
            dfs_parent[v] = u;
        
            if (u==dfsRoot) {
                rootChildren++;
            }

            n_bridges += dfs(v, depth, dfsRoot, rootChildren, adj, dfs_min, dfs_num, dfs_parent);

            if (dfs_num[u] <= dfs_min[v] && u != dfsRoot){
                // is AP
            }
            if (dfs_num[u] < dfs_min[v]){
                // is a bridge
                // cout << "ISABRDIGE\n";
                n_bridges++;
            }
            dfs_min[u] = min(dfs_min[u], dfs_min[v]);
        }
        else if (v != dfs_parent[u]){  // Back Edge
            dfs_min[u] = min(dfs_min[u], dfs_num[v]);
        }
    }
    return n_bridges;
} // comprog22 lecture 6, slide 18 and 19a
```

## `caves1` - Longest path - only linear for DAG
> DAG - Directed Acyclic Graph, toposort, topsort, topological sort
- compute toposort
```cpp
bool compute_toposort(int start, vector<bool> &visited, vector<bool> &local_visited,
         const vector<vector<int>> &adj, vector<int> &ts){

    /* toposort might need to be reversed */

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
```
- and then finding the longest path (aka the max of gold):
```cpp
vector<ll> max_gold_vec = gold;
for (auto u: ts){
    for (auto node: adj[u]){
        ll maybe_gold = gold[node];
        // print_vector_ll(max_gold_vec, "max_gold_vec");
        max_gold_vec[node] = max(max_gold_vec[node], max_gold_vec[u] + maybe_gold);
    }
}
```

## 'caves2' - turn DCG to DAG
> SCC - Strongly Connected Component, Turn DCG to DAG, graph condensation
- find SCCs then condense the SCCs to single nodes, ergo creating a DAG
```cpp

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
            // cout << v + 1<< " ";
            ts.push_back(v);
            component.push_front(v);
        } while (v != u);

        SCCs.push_front(component);
        // cout << "\n";
    }
}
```

## `driving` - Euler paths
> Euler paths
```cpp
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

```

- main:
```cpp
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
```

# **Week 7**
`marriage`
> UnionFind (faster), lca (Lowest Common Ancestor)

> **LCA**
> - given a rooted, directed tree and two vertices u and v, vertex q is the LCA of u and v iff q is the lowest vertex s.t. both u and v are contained in the subtree starting at q.

```cpp
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
```

# **Week 8**

> Maximum Flow problem, Modelling as maximum flow
> Edmonds-Karp's algorithm
>   - BFS, picks the shortest augmenting paths. O(VE^2)
>   - adding source: capacity 1 (per frog)
>   - adding sink  : capacity INF

> Flow:
>   - given a network of undirected pipes, source and sink, how much
>     water cand be pumped from s to t?
> More formal def:
>   - given directed G with edge capacities c_e, a source s and sink t
>     Maximum flow  is subject to conditions like:
>       - in every vertex except s and t, in-flow equals out-flow

**Edmonds-Karp Algorithm for Maximum Flow**
```cpp
#include<bits/stdc++.h>

using namespace std;
#define INF numeric_limits<int>::max()

vector<vector<int>> capacity;
vector<vector<int>> adj;
vector<int> parent;

void bfs(int s) {
    parent.assign(adj.size(), -1);
    parent[s] = -2; // s is visited

    queue<int> Q;
    Q.push(s);
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int v : adj[u]) // go u -> v
            if (parent[v] == -1 and capacity[u][v] > 0) {
                Q.push(v);
                parent[v] = u;
            }
    }
}

int maxflow(int s, int t) {
    int totalflow = 0;
    int u;
    while (true) {
        // build bfs tree
        bfs(s);
        if (parent[t] == -1) // t unreachable
            break;
        // find bottleneck capacity
        int bottleneck = INF;
        u = t;
        while (u != s) {
            int v = parent[u];
            bottleneck = min(bottleneck, capacity[v][u]);
            u = v;
        }
        // update capacities along path
        u = t;
        while (u != s) {
            int v = parent[u];
            capacity[v][u] -= bottleneck;
            capacity[u][v] += bottleneck;
            u = v;
        }
        totalflow += bottleneck;
    }
    return totalflow;
}

int main() {
    int s, t, V, E;
    cin >> V >> E >> s >> t;
    int u, v, c;
    adj.resize(V);
    capacity.assign(V, vector<int>(V, 0));
    
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> c;
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += c;
    }
    int out = maxflow(s, t);
    cout << out << endl;
}

```

# **Week 9**
> String Matching, LSP (Longest Suffix-Prefix) - Knuth-Morris-Pratt,
> Also using Trie structure
> DP for LSP in HWs down below

**Knuth-Morris-Pratt**
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

string s, t;
int n, m;

int32_t main() {
    cin >> s >> t;
    n = s.size(); m = t.size();

    vector<int> lsp(m, 0);
    for (int i = 1, prev = 0; i < m; ) {
      if (t[i] == t[prev]) {
        prev++;
        lsp[i] = prev;
        i++; 
      } else if (prev == 0) {
        lsp[i] = 0;
        i++;
      } else { prev = lsp[prev-1]; }
    }

    int start = 0, len = 0;
    while (start + len < n) {
        while (len >= m || s[start+len] != t[len]) {
            if (len == 0) { start++; len = -1; break; }
            int skip = len - lsp[len-1];
            start += skip; len -= skip;
        }
        len++;
        if (len == m)
            cout << "t matches s at " << start << "\n";
    }
}
```

# **Week 10**
> Combinatorics
> modulo mod
> (a + b) % p = ((a % p) + (b % p)) % p
> (a * b) % p = ((a % p) * (b % p)) % p
> (a - b) % p = ((a % p) - (b % p)) % p
> fexp, factorial with modulo
> Fermat's little theorem a^{-1} = a^{p-2} mod p, where p is the modulator

```cpp
ll fexp(ll m, ll n, ll p){
    if (n==0) return 1;
    else if (n%2 == 1){
        return (m * fexp(m, n-1, p)) % p;
    }
    else{
        ll r = fexp(m, n/2, p);
        return (r * r) % p;
    }
}
```

```cpp
ll factorial(ll n)
{
    ll res = 1, i;
     
    for(i = 2; i <= n; i++)
        res = (res * i) % mod;
         
    return res;
}
```

# **Week 11**
> Hamiltonian path
>   - Ham. path is a path that visits every vertex exactly once
>   - NP-hard, n=20

```cpp
#include <bits/stdc++.h>

/*
 * sample input:
4 4
1 4
2 3
3 4
2 4
 * sample output:
0 : 1
1 : 1
2 : 1
3 : 0
 */

using namespace std;

int main(){
	int n, m;
	cin >> n >> m;
	set<pair<int,int>> edges;
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		edges.insert({u,v}), edges.insert({v,u});
	}

	vector<vector<bool>> dp(1<<n, vector<bool>(n, false)); // subset, endnode

	for(int i = 0; i < n; i++){
		dp[1 << i][i] = true;
	}

	for(int X = 1; X < (1<<n); X++){ // all sets
	if(__builtin_popcount(X) < 2) continue;

	for(int v = 0; v < n; v++) {   // all ending vertices
		if(!(X & (1<<v))) continue;  // v not in X

		for(int u = 0; u < n; u++) {
		if(dp[X ^ (1<<v)][u] && edges.count({u, v})){
			dp[X][v] = true;
		}
		}
	}
	}
	for(int i = 0; i < n; i++){
		cout << i << " : " << dp[(1<<n)-1][i] << "\n";
	}
}
```
# Fake Exam
## `buildstair`
> combinatorics, product of factorials, modulo

```cpp
ll fexp(ll m, ll n, ll p){
    if (n==0) return 1;
    else if (n%2 == 1){
        return (m * fexp(m, n-1, p)) % p;
    }
    else{
        ll r = fexp(m, n/2, p);
        return (r * r) % p;
    }
}

ll factorial(ll n)
{
    ll res = 1, i;
     
    for(i = 2; i <= n; i++)
        res = (res * i) % mod;
         
    return res;
}

int main(){
    // cout << mod << "\n";
    int n, h;
    cin >> n;
    map<int, int> blocks;
    for (int i = 0; i < n; i++){
        cin >> h;
        if (blocks.count(h)){
            blocks[h] += 1;
        }
        else{
            blocks[h] = 1;
        }

    }
    ll prod = 1;
    // (a + b) mod p = ((a*mod p) + (b*mod p)) mod p
    // (a * b) mod p = ((a*mod p) * (b*mod p)) mod p
    // (a - b) mod p = ((a*mod p) - (b*mod p)) mod p
    for(const auto& elem : blocks)
    {
        // std::cout << elem.first << " | " << elem.second << "\n";
        prod = ((prod % mod) * (factorial(elem.second) % mod)) % mod;
    }
    cout << prod % mod<< "\n";
    return 0;
}
```

## `chase`
> multiple usage of dijkstra's algo

## `garlands`
> one edit with lsp

# Test Midterm
## `booster`
> DP - Dynamic Programming
```cpp
int main(){
    int n;  // num_positions
    int k;  // num_boosters

    cin >> n >> k;
    vector<vector<int>> adj(n);
    for (int i = 0; i < k; i++){
        int left, right;
        cin >> left >> right;
        left--;
        right--;
        // adj[left].push_back(right);
        adj[right].push_back(left); 
        // needed in other direction for dp
    }
    vector<ll> dp(n, 0); // sets for zeros
    for (int i = 1; i < n; i++){
        ll local_min = dp[i-1]+1;
        for (ll x : adj[i]){
            // dp[i] = min(dp[x]+1, dp[i-1]+1);
            local_min = min(dp[x]+1, local_min);
        }
        dp[i] = local_min;
    }
    cout << dp[n-1] << "\n";

    return 0;
}
```

## `closingtime`
> Shortest Path, Dijkstra, Dijkstra's algorithm
```cpp
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
```

# **General printing stuff**
```cpp
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

```
# TabCharacter:
```
	
```
# Makefile
```make
# the compiler: gcc for C program, define as g++ for C++
CC = g++ -x c++ -std=gnu++17

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
DEBUG_FLAGS  = -g -Wall -Wextra -fsanitize=undefined,address -D_GLIBCXX_DEBUG -O2
JUDGE_FLAGS  = -Wall -O2 -static -pipe

# The build target 
TARGET = caves2

all:
			$(CC) $(JUDGE_FLAGS) -o $(TARGET) $(TARGET).cpp

debug:
			$(CC) $(DEBUG_FLAGS) -o $(TARGET) $(TARGET).cpp

clean:
			$(RM) $(TARGET)
```
# **TEMPLATE**
```cpp
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

int main(){

    return 0;
}
```
# **ALL HWs**
## W1
### `lineup`
```cpp
int main(){
    vector<int> prefs = {0,1,2,3,4,5,6,7,8,9,10};
    int g = 11;  // 11 guests
    int w = 11;  // 11 wines
    int table[g][w];
    for (int i=0; i < g; i++){
        for (int j=0; j < w; j++){
            cin >> table[i][j];
        }
    }

    int max_pleasure = 0;
    do {
        int loc_pleasure = 0;
        for (int i=0; i<g; i++){
            loc_pleasure += table[i][prefs[i]];
        }
        if (loc_pleasure > max_pleasure) max_pleasure = loc_pleasure;
    } while (next_permutation(prefs.begin(), prefs.end()));
    cout << max_pleasure;
}
```

### `outoforder`
```cpp
int main(){
    int n;
    cin >> n;

    // special cases
    
    vector<int> stamps;
    stamps.reserve(n);
    int outlier_id = -1;

    // load the input
    for (int i=0; i<n; i++){
        int value;
        cin >> value;
        stamps.push_back(value);
    }

    if (n==1){
        cout << "impossible\n";
        return 1;
    }

    // traverse the input
    bool outlier_found = false;
    int local_min_id = -1;
    for (uint i=0; i<stamps.size()-1; i++){
        if (stamps[i] > stamps[i+1]){
            if (outlier_found == false){
                outlier_id = i;
                for (uint j = outlier_id + 1; j<stamps.size(); j++){
                    if (local_min_id == -1){
                        local_min_id = j;
                    }
                    else if (stamps[j] <= stamps[local_min_id]){
                        local_min_id = j;
                    }
                }
            }
            outlier_found = true;
        }
    }

    // try to swap
    swap(stamps[outlier_id], stamps[local_min_id]);
    for (uint i = 0; i < stamps.size()-1; i++){
        if (stamps[i] > stamps[i+1]){
            cout << "impossible\n";
            return 0;
        }
    }
    cout << outlier_id + 1 << " " << local_min_id + 1 << "\n";
    return 0;
}
```

### `theanswer` - is not 42 actually
```cpp
int main(){
    int n;
    cin >> n;
    vector<ll> numbers;
    for (int i=0; i < n; i++){
        ll num;
        cin >> num;
        numbers.push_back(num);
    }
    sort(numbers.begin(), numbers.end());

    for (int i=0; i < n-2; i++){
        
        ll first = numbers[i];
        ll diff = first - 42;

        for (int j = i+1; j < n-1; j++){
            ll second = numbers[j];
            if(binary_search(numbers.begin(), numbers.end(), (-diff - second))){
                cout << first << " " << second << " " << (-diff - second) << "\n";
                return 0;
            }
        }
    }
    cout << "impossible";

}
```

## W2
### `bordeaux`
```cpp
bool customsort(const pair<ll,ll> &a, const pair<ll,ll> &b){
        if (a.first != b.first){
            return(a.first < b.first);
        }
        else{
            return(a.second > b.second);
        }
}

int main() {
    int n;
    cin >> n;
    vector< pair<ll, ll> > offers;
    offers.reserve(n);
    ll d_i; ll v_i;

    for (int i=0; i < n; i++){
        cin >> d_i;
        cin >> v_i;
        if (d_i >= v_i) continue;
        offers.push_back(make_pair(d_i, v_i));
    }

    if (offers.empty()){
        cout << 0 << " " << 0;
        return 0;
    }

    sort(offers.begin(), offers.end(), customsort);

    ll borrowed = offers[0].first;
    ll brutto = offers[0].second;

    for (uint i=1; i < offers.size(); i++){
        if (brutto < offers[i].first){

            // borrow needed wines
            borrowed += (offers[i].first - brutto);
            brutto = offers[i].first;
        }
        // do the transaction
        brutto += offers[i].second - offers[i].first;
    }
    cout << borrowed << " " << brutto - borrowed;

    return 0;
}
```

### `microbes`
```cpp
int main() {
    int n_dishes; int n_query;
    cin >> n_dishes >> n_query;
    vector<ll> dishes;
    dishes.reserve(n_dishes);

    int chunk_size = (int)(ceil(sqrt(n_dishes)));
    int n_chunks = (int)(ceil(sqrt(n_dishes)));
    vector<ll> chunks(n_chunks, 0);  // initialize vector to all zeros
    
    // get the petri dishes
    for (int i=0; i<n_dishes; i++){
        int b_i;
        cin >> b_i;
        dishes.push_back(b_i);
    }

    /* end of input loading */

    // divide and conquer; compute sums over chunks
    int chunk_cnt = -1;
    for (uint i=0; i < dishes.size(); i++){
        if (i % chunk_size == 0) chunk_cnt++;
        if (dishes[i] % 2 != 0) chunks[chunk_cnt]++;
    }

    char query_letter; 
    for (int i=0; i<n_query; i++){
        cin >> query_letter;
        if (query_letter == 'Q'){
            int first;
            int second;
            cin >> first >> second;
            first--; second--; // change to indices instead of dish numbers
            ll value = 0;

            for (int id = first; id < second+1; id++){
                // is start of a chunk        // space for a whole chunk
                if ((id % chunk_size == 0) && (id + chunk_size <= second+1)){
                    value += chunks[(int)(floor(id/chunk_size))];
                    id += chunk_size-1;
                    
                }
                else{
                    if (dishes[id] % 2 != 0) value++;
                }
            }
            cout << value << "\n";
        }
        else if (query_letter == 'U'){
            int idx;
            ll value;
            cin >> idx >> value;
            idx--;
            
            if ( (dishes[idx] % 2) == (value % 2)){
                continue;                  
            }
            else{
                int chunk_id = (int)(floor(idx/chunk_size));
                if (dishes[idx] % 2 != 0){
                    chunks[chunk_id]--;
                }
                else{
                    chunks[chunk_id]++;
                }
                dishes[idx] = value;
            }
        }
        else {
            cerr << "Unrecognised query letter: " << query_letter << "\n";
            return 1;
        } 
    }
    return 0;
}
```

### `theanswercount`
```cpp
int main() {
    int n;
    ll x;
    cin >> n >> x;

    vector<ll> A1;
    vector<ll> A2;
    
    vector<ll> S1;
    vector<ll> S2;

    int a1 = (int)(floor(n/2));
    int a2 = n - a1;    

    if (a2 > a1){
        int temp = a2;
        a2 = a1;
        a1 = temp;
    }

    A1.reserve((int)pow(2, a1));
    A2.reserve((int)pow(2, a2));
    

    ll input_n;

    // load the vector
    for (int i=0; i < n; i++){
        cin >> input_n;
        if (i < a1){
            A1.push_back(input_n);
        }
        else{
            A2.push_back(input_n);
        }
    }

    // generate all subsets 
    uint pow_set_size = pow(2, A1.size());
    for (uint cnt = 0; cnt < pow_set_size; cnt++){
        
        ll temp_sum = 0;
        for (uint i=0; i < A1.size(); i++){
            if (cnt & (1 << i)){
                temp_sum += A1[i];
            }
        }
        S1.push_back(temp_sum);
    }

    pow_set_size = pow(2, A2.size());
    for (uint cnt = 0; cnt < pow_set_size; cnt++){
        if (cnt % 1000 == 0){
            // cout << "2nd, cnt: " << cnt << "\n";
        }
        
        ll temp_sum = 0;
        for (uint i=0; i < A2.size(); i++){
            if (cnt & (1 << i)){
                temp_sum += A2[i];
            }
        }
        S2.push_back(temp_sum);
    }
    
    sort(S2.begin(), S2.end());
    ll total_count = 0;
    for(uint i=0; i<S1.size(); i++){
        ll candidate = S1[i];
        // vector<int>::iterator lb,ub;
        auto lb = lower_bound(S2.begin(), S2.end(), (x - candidate));
        auto ub = upper_bound(S2.begin(), S2.end(), (x - candidate));
        total_count += ub-lb;
    }
    cout << total_count;

    return 0;
    // source: subset generation inspired by https://www.geeksforgeeks.org/find-distinct-subsets-given-set/
}
```

## W3
### `begging`
```cpp
class dpClass {
  public:
    int val{0};
    int prev;
};

int main() {
    bool vb = false;
    int n; int m; vector<int> A; 
    cin >> n >> m;
    vector<dpClass> dp(n, dpClass{});
    A.reserve(n);
    

    for (int i=0; i < n; i++){
        int a;
        cin >> a;
        // A is a vector filled with wine offers
        A.push_back(a);
    }
    int best_id = 0;
    for (int i=0; i < n; i++){
        if (i < m){
            dp[i].val = A[i];
            dp[i].prev = -1;
        }
        else{
            int _max_id = -1;
            int _max_val = -1;
            for (int j = i-m; j > i-2*m; j--){
                if (j<0) break;
                if(_max_val == -1){
                    _max_val = dp[j].val;
                    _max_id = j;
                }
                else{
                    if (dp[j].val > _max_val){
                        _max_id = j;
                        _max_val = dp[j].val;
                    }
                }
            }

            dp[i].val = A[i] + dp[_max_id].val;
            dp[i].prev = _max_id;
            
        }
        if (dp[i].val > dp[best_id].val) best_id = i; 
    }
    
    vector<int> indices;
    int curr_idx = best_id;
    while(1){
        if (curr_idx == -1) {
            break;
        }
        indices.push_back(curr_idx);
        curr_idx = dp[curr_idx].prev;
    }

    reverse(indices.begin(), indices.end());
    cout << dp[best_id].val << " " << indices.size() << "\n";
    for (uint i=0; i < indices.size(); i++){
        cout << indices[i]+1;
        if (i < indices.size()-1) cout << " ";
    }
    cout << "\n";

    return 0;
}
```
### `cake`
```cpp
vector<vector<int>> p_sums(vector<vector<int>> tray){
    vector<vector<int>> sums(tray.size(), vector<int>(tray[0].size(), 0));
    for (uint r = 0; r < tray.size(); r++){
        for (uint c = 0; c < tray[0].size(); c++){
            if (r == 0 && c == 0){
                sums[r][c] = tray[r][c];
            }
            else if (r == 0){
                sums[0][c] = sums[0][c-1] + tray[0][c];
            }
            else if (c == 0){
                sums[r][0] = sums[r-1][0] + tray[r][0];
            }
            else{
                sums[r][c] = sums[r-1][c] + sums[r][c-1] - sums[r-1][c-1] + tray[r][c];
            }
        }
        
    } 
    return sums;
}

int main() {

    bool vb = false;

    int h; int w; int h_cake; int w_cake;
    cin >> h >> w;
    vector<vector<int>> bt(h, vector<int> (w, 0));
    int sqr_mm;
    for (int r = 0; r < h ; r++){
        for (int c = 0; c < w; c++){
            cin >> sqr_mm;
            bt[r][c] = sqr_mm;
        }
    }
    cin >> h_cake >> w_cake;

    // create the partial sums
    auto psv = p_sums(bt);

    if(vb){
        cout << "\nbt:\n";
        print_2D_vec(bt);
        cout << "\npartial sums:\n";
        print_2D_vec(psv);
    }
    int temp_sum = 0;
    for (int r=0; r <= h-h_cake; r++){
        for (int c=0; c <= w-w_cake; c++){
            temp_sum = psv[r+h_cake-1][c+w_cake-1];
            if (r == 0 && c == 0){
                
            }
            else if (r == 0){
                // sums[0][c] = sums[0][c-1] + tray[0][c];
                temp_sum -= psv[r+h_cake-1][c-1];
            }
            else if (c == 0){
                // sums[r][0] = sums[r-1][0] + tray[r][0];
                temp_sum -= psv[r-1][c+w_cake-1];
            }
            else{
                // sums[r][c] = sums[r-1][c] + sums[r][c-1] - sums[r-1][c-1] + tray[r][c];
                temp_sum += -psv[r+h_cake-1][c-1] - psv[r-1][c+w_cake-1] + psv[r-1][c-1];
            }
            if (temp_sum == 0){
                cout << r+1 <<" "<< c+1 <<" "<< r+h_cake <<" "<< c+w_cake << "\n";
                return 0;
            }
        }
    }  
    cout << "-1 -1 -1 -1\n";
    return 0;
}
```
### `cashier`
```cpp
int main() {
    bool vb = false;
    int c; int n;
    cin >> c >> n;

    vector<int> coins(n, 0);
    vector<int> dp(c+1, 0);

    if (c == 0){
        cout << 0 << "\n";
        return 0;
    }

    for (int i = 0; i < n; i++){
        int coin;
        cin >> coin;
        coins[i] = coin;
    }
    
    // iterate through dp of size c (change amount)
    for (int i = 0; i < c+1; i++){
        // iterate through types of coins
        if (i == 0){
            dp[i] = 0;
            continue;
        }
        int min_coins = 0;
        for (int j = 0; j < n; j++){
            // if wanted amount is smaller than the coin, continue
            if (i < coins[j]) continue;  
            int id = i - coins[j] ;
            if (dp[id] == 0 && id != 0) continue;
            if (min_coins == 0){
                min_coins = dp[id] + 1;
            }
            else{
                if ((dp[id] + 1) < min_coins){
                    min_coins = dp[id] + 1;
                }
            }            
        }
        dp[i] = min_coins;
    }
    if (dp[c] == 0){
        cout << "impossible" << "\n";
        return 0;
    }
    cout << dp[c] << "\n";
  
    return 0;
}
```
### `warming1`
```cpp
int main() {
    int n;
    int x;
    cin >> n >> x;
    vector<int> temps;
    temps.reserve(n);
    vector<int> f_vals(n,0);
    int t;
    for (int i=0; i<n; i++){
        cin >> t;
        temps.push_back(t);
    }
    
    int lis = 0;
    for (int i=0; i<n; i++){
        f_vals[i] = 1;
        for (int j=0; j<i; j++){
            if (temps[j] < temps[i]){
                f_vals[i] = max(f_vals[i], f_vals[j]+1);   
            }
        }
        lis = max(lis, f_vals[i]);
    }
    cout << lis << "\n";
    
    return 0;
}
```
### `warming2`
```cpp
int main() {
    bool vb = false;
    
    int n;
    int x;
    cin >> n >> x;
    vector<int> A;
    vector<int> f_vals;
    vector<int> g_vals;
    A.reserve(n);
    f_vals.reserve(n);
    int t;
    for (int i=0; i<n; i++){
        cin >> t;
        A.push_back(t);
    }
    int minus_int_inf = numeric_limits<int>::min();
    g_vals.push_back(minus_int_inf);

    for (int i=0; i < n; i++){
        int g_idx = lower_bound(g_vals.begin(), g_vals.end(), A[i]) - g_vals.begin();
        f_vals.push_back(1 + g_idx-1);  // f_i = 1 + max{l|g_i[l] < A[i]}

        // now the g_vals(i+1) = min{g[f[i]], A[i]}
        if (f_vals[i] > (int)(g_vals.size()-1)){
            // if g_vals too small, append
            g_vals.push_back(A[i]);
        }
        else{
            // else just update the number already there
            g_vals[f_vals[i]] = min(g_vals[f_vals[i]], A[i]);
        }
    }


    cout << g_vals.size()-1 << "\n";
    if (vb){
        cout << "g_vals:\n";
        for (uint i=0; i < g_vals.size(); i++){
                    cout << g_vals[i] << ", ";
                }
        cout << "\n";
        
        cout << "f_vals:\n";
        for (uint i=0; i < f_vals.size(); i++){
                    cout << f_vals[i] << ", ";
                }
        cout << "\n";
    }
    
    return 0;
}
```
> PSEUDOCODE:
```
let A       be vector of int
let f_vals  be a vector of functional values for the maximal length
let g_vals  be a vector of smallest element to describe a subset of length given by its index
    

f_i(i) = 1 + max{l|g_i[l] < A[i]}
g_next(i) = min{g[f[i]], A[i]}


for i in A.size
    g_idx = find idx of a g_vals[l] from g_vals s.t. g_vals[l] < A[i]
        --> proably some lowerbound or something
    f_vals[i] = 1 + max(g_vals[g_idx], A[i])
    if (f_vals[i] > g_vals.size-1){
        g_vals.push_back(A[i])
    }
    else{
        g_vals[f_vals[i]] = min(g_vals[f_vals[i]], A[i])
    }
```

## W4
### `covering`
```cpp
int get_whole_num(ll *i, const string& inp){
    char num_chars[4];
    int cnt = 0;
    while (true){
        if (inp[*i] == ',' || inp[*i] == ')') break;
        num_chars[cnt] = inp[*i];
        cnt++;
        (*i)++;  // moves pointer by one
    }
    num_chars[cnt] = '\0';
    // cout << "`whole_num`: \n" << stoi(num_chars) << "\n";
    return stoi(num_chars);
}

int main(){
    // bool vb = false;
    vector<string> trees;
    ios::sync_with_stdio(false);
    string line;
    while(getline(cin, line)){
        trees.push_back(line);
    }
    vector<set<int>> s((int) trees.size(), set<int>{});
    
    int max_num = 0;
    int num;

    /* -- PARSE THE INPUT INTO SETS -- */
    
    for (uint i = 0; i < trees.size(); i++){ // for tree in trees
        
        for (ll j = 0; j < (ll) trees[i].size(); j++){ // for char in tree
            
            if (isdigit(trees[i][j])){
                num = get_whole_num(&j, trees[i]);
                s[i].insert(num);
                if (num > max_num){
                    max_num = num;
                }
            }
        }
    }

    vector<int> markers(max_num+1, -1);
    vector<ll> masks(s.size(), 0);
    uint max_arity = 0;
    uint arity_cnt = 0;
    ll mask_len = 8 * sizeof(ll);

    // generate masks
    for (uint i = 0; i < s.size(); i++){
        for (auto const &k : s[i])
        {   
            masks[i] = masks[i] | 1 << (k % mask_len);  
        }
    }

    // choose examined candidate superset
    for (uint i = 0; i < s.size(); i++)
    {  
        arity_cnt = 0;
        for (auto const &k : s[i])
        {   
            markers[k] = i; // mark itself into the marks 
        }
        
        // cycle through candidate subsets
        for (uint j = 0; j < s.size(); j++)
        {  
            if (j == i) continue;  // dont examine self

            if ((~masks[i] & masks[j]) != 0)
            {
                continue;
            }

            else
            {    
                bool is_subset = true;
                for (auto const &k : s[j]){
                    if (markers[k] != (int) i)
                    {   
                        is_subset = false;
                        break;
                    }
                }   
                if(is_subset) arity_cnt++;
            
            }
        }
        if (arity_cnt > max_arity) max_arity = arity_cnt;
    }
    cout << max_arity << "\n";

    return 0;
}
```

### `equations`
> given whole code above

### `sumup`
```cpp
int whole_num(ll *i, const string& inp){
    char num_chars[4];
    int cnt = 0;
    while (true){
        if (inp[*i] == ',' || inp[*i] == ')') break;
        num_chars[cnt] = inp[*i];
        cnt++;
        (*i)++;  // moves pointer by one
    }
    num_chars[cnt] = '\0';
    // cout << "`whole_num`: \n" << stoi(num_chars) << "\n";
    return stoi(num_chars);
}

class Node {
    public:
        int val{-1};
        vector<Node *> children{};
        Node * parent{nullptr};
};

int deeper(Node *node, ll *i, const string &inp){
    
    while((*i) < (ll) inp.size()){
        // cout << "Going deeper with i: " << *i << "\n";
        if (inp[*i] == ')'){
            // cout << "\nBREAKING\n";
            (*i)++;
            break;
        }
        if (inp[*i] == '(' || inp[*i] == ','){
            (*i)++;
            // continue;
        }
        
        if (isdigit(inp[*i])){
            Node* new_node = new Node{whole_num(i, inp), {}, node};
            node->children.push_back(new_node);          
        }
        else if (inp[*i] == '+')
        {
            // Node new_node;
            Node* new_node = new Node{'+', {}, node};
            node->children.push_back(new_node);
            (*i)++;
            deeper(new_node, i, inp);

        }
        else if (inp[*i] == '*')
        {
            Node* new_node = new Node{'*', {}, node};
            node->children.push_back(new_node);
            (*i)++;
            deeper(new_node, i, inp);
        }
    }
    return 1;
}


void node_info(Node * root){
    cout << "_____________\n| NODE INFO |\n-------------\n";

    if (root->children.empty()){
        cout  << "name: " << root->val << "\n";
        cout << "no children";
    }
    else{
        cout  <<  "name: " << (char) root->val << "\n";
        cout << "children: [";
        for (uint i = 0; i < root->children.size(); i++){
            // print_tree(root->children[i]);         
            if (root->children[i]->children.empty()){
                cout  << root->children[i]->val << " ";
            } 
            else{
                cout << (char) root->children[i]->val << " ";
            }
        }
        cout << "]\n";

    }
    cout << "\n";
}

void print_tree(Node * root, int indent){
    // node_info(root);

    if (root->children.empty()){
            // cout << "is empty? : " << root->children.empty() << "\n";
            for (int i = 0; i < indent; i++) cout << " ";
            cout  << root->val << "\n";
        }
    else{
        for (int i = 0; i < indent; i++) cout << " ";
        cout << (char)(root->val) << "\n";
        // cout << "children:\n";
        for (uint i = 0; i < root->children.size(); i++){
            print_tree(root->children[i], indent + 2);           
        }
    }
    
    return;
}

void delete_tree(Node * root){

    if (root->children.empty()){
            return;
        }
    else{
        
        for (uint i = 0; i < root->children.size(); i++){
            delete_tree(root->children[i]);           
            delete root->children[i];
        }
    }
}

ll eval_tree(Node * root){
    ll total;

    if (root->children.empty()){
        return root->val;
    }
    else
    {
        if(root->val == '*'){
            total = 1;
            for (uint i = 0; i < root->children.size(); i++){
                total *= eval_tree(root->children[i]);
            }
        }
        else{
            total = 0;
            for (uint i = 0; i < root->children.size(); i++){
                total += eval_tree(root->children[i]);
            }
        }  
    }
    return total;
}




int main() {
    bool vb = false;
    vector<string> trees;
    string line;
    while(getline(cin, line)){
        trees.push_back(line);
    }

    ll total = 0;
    // cycle through trees
    for (uint i = 0; i < trees.size(); i++){
        // cout << "current tree: " << trees[i] << "\n";
        Node root;
        // cycle through chars of string
        for (ll j = 0; j < (ll) trees[i].size(); j++){

            root.val = trees[i][0];
            j++;
            deeper(&root, &j, trees[i]);
        }   
        // cout << "tree:\n";
        // print_tree(&root, 0);
        total += eval_tree(&root);
        delete_tree(&root);
    }
    

    if(vb){
        cout << "trees:\n";
        for (uint i = 0; i < trees.size(); i++){  
            cout << trees[i] << "\n";
        }
    }
    
    cout << total << "\n";
    
    return 0;
}
```

## W5
### `bars`
```cpp
void dfs(int v, vector<bool> *visited, vector<vector<int>> *adj, int max_depth, int curr_depth){
        (*visited)[v] = true;
        vector<bool> temp_visited = *visited;
        
        for (int u: (*adj)[v])
        {
            if (curr_depth < max_depth)
            {     
                dfs(u, visited, adj, max_depth, curr_depth+1);
            }
        }
    }

void bfs(int start, vector<bool> &visited, const vector<vector<int>> &adj, int max_depth){
    queue<pair<int,int>> Q;

    Q.push({start, 0});
    visited[start] = true;
    // int curr_depth = 0;

    while (!Q.empty())
    {   

        auto v = Q.front();
        if (v.second >= max_depth) break;
        Q.pop();

        for (int u: (adj)[v.first]){
            if (!visited[u]){
                Q.push({u, v.second+1});
                visited[u] = true;
            }
        }
    }
}

int main(){
    // bool vb = false;
    int n, m, s, d;
    cin >> n >> m >> s >> d;
    s--;
    vector<vector<int>> adj(n);  // initialized to zeros in the first dim
    vector<bool> visited(n, false);
    
    // read the edges and save them into Adjacency List
    for (int i = 0; i < m; i++){
        int first, second;
        cin >> first >> second;
        first--; second--;
        adj[first].push_back(second);
        adj[second].push_back(first);
    }
    
    bfs(s, visited, adj, d);
    int count = 0;
    for (int i = 0; i < n; i++){
        if(visited[i]) count++;
    }

    cout << count << "\n";
    return 0;
}
```

### `fares`
```cpp
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
    
    vector<ll> dist(n_nodes, INF);

    // read the edges and save them into Adjacency List
    vector<vector<pair<ll, ll>>> adj(n_nodes);  // initialized to zeros in the first dim
    for (int i = 0; i < b_lines; i++){
        ll first, second, weight;
        cin >> first >> second >> weight;
        first--; second--;
        adj[first].push_back({second, weight});
        adj[second].push_back({first, weight});
    }
    
    dijkstra(1-1, dist, adj);
    
    // return shortest path to Sylt
    cout << dist[n_nodes-1] << "\n";

    return 0;
}
```

### `inequalities`
```cpp
map<string, int> name_2_ID;
void parse_the_line(map<int, string> & ID_2_name, map<string, int> & name_2_ID,
                    int &ID_cnt, const string &first, const string &second, const string &oper,
                    vector<vector<int>> &adj){
    
    int first_ID = -1;
    int second_ID = -1;
    if(name_2_ID.count(first))
        {
            first_ID = name_2_ID[first];
        }
        else
        {
            ID_cnt++;
            first_ID = ID_cnt;
            name_2_ID[first] = first_ID;
            ID_2_name[first_ID] = first;
        }

        if(name_2_ID.count(second))
        {
            second_ID = name_2_ID[second];
        }
        else
        {
            ID_cnt++;
            second_ID = ID_cnt;
            name_2_ID[second] = second_ID;
            ID_2_name[second_ID] = second;
        }

        if (oper == ">")
        {
            adj[second_ID].push_back(first_ID);
        }
        else if (oper == "<")
        {
            adj[first_ID].push_back(second_ID);
        }
        else
        {
            cout << "Unknown operator: " << oper << ". :(\n";
        }
}

bool dfs(int start, vector<bool> &visited, vector<bool> &local_visited,
         const vector<vector<int>> &adj, deque<int> &ts){
    
    local_visited[start] = true;

    for(int u: adj[start])
    {   
        if(local_visited[u]){
        return false;
        }
        if (!visited[u]){
            if(!dfs(u, visited, local_visited, adj, ts)) return false;
        }
    }

    local_visited[start] = false;
    visited[start] = true;
    ts.push_front(start);
    return true;
}

int main(){
    int n;
    cin >> n;

    vector<vector<int>> adj(n*2);
    
    // vector<string> names(n+1, "");
    map<int, string> ID_2_name;
    map<string, int> name_2_ID;

    string first;
    string second;
    string oper;
    deque<int> ts;
    int ID_cnt = -1;

    // parse the lines
    for (int i = 0; i < n; i++){
        cin >> first >> oper >> second;
        parse_the_line(ID_2_name, name_2_ID, ID_cnt, first, second, oper, adj);       
    }

    vector<bool> visited(ID_2_name.size(), false);
    vector<bool> local_visited(ID_2_name.size(), false);

    bool impossible = false;

    for (uint start = 0; start < visited.size(); start++)
    {
        if (visited[start]){
            continue;
        }
        if (!dfs(start, visited, local_visited, adj, ts)){
            impossible = true;
            break;
        }
    }

    if (impossible){
        cout << "impossible\n";
    }
    else{
        cout << "possible\n";
        for(auto iter = ts.rbegin(); iter != ts.rend(); ++iter) {
            cout << ID_2_name[*iter] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
```

## W6
### `bridges`
```cpp
int dfs(int u, int depth, int dfsRoot, int rootChildren, const vector<vector<int>> &adj, vector<int> &dfs_min, vector<int> &dfs_num, vector<int> &dfs_parent){
    dfs_min[u] = dfs_num[u] = depth;
    depth++;
    int n_bridges = 0;
    for (auto v: adj[u]){
        if (dfs_num[v] == -1)  // tree edge
        {
            dfs_parent[v] = u;
        
            if (u==dfsRoot) {
                rootChildren++;
            }

            n_bridges += dfs(v, depth, dfsRoot, rootChildren, adj, dfs_min, dfs_num, dfs_parent);

            if (dfs_num[u] <= dfs_min[v] && u != dfsRoot){
                // is AP
            }
            if (dfs_num[u] < dfs_min[v]){
                // is a bridge
                // cout << "ISABRDIGE\n";
                n_bridges++;
            }
            dfs_min[u] = min(dfs_min[u], dfs_min[v]);
        }
        else if (v != dfs_parent[u]){  // Back Edge
            dfs_min[u] = min(dfs_min[u], dfs_num[v]);
        }
    }
    return n_bridges;
} // comprog22 lecture 6, slide 18 and 19a

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> dfs_num(n, -1);
    vector<int> dfs_min(n, -1);
    vector<int> dfs_parent(n, -1);
    int dfsRoot, rootChildren;
    int dfs_depth = 0;
    int n_bridges = 0;

    // read the edges and save them into Adjacency List
    for (int i = 0; i < m; i++){
        int first, second;
        cin >> first >> second;
        first--; second--;
        adj[first].push_back(second);
        adj[second].push_back(first);
    }

    for (int i = 0; i < n; i++)
    {
        if(dfs_num[i] == -1)
        {
            dfsRoot = i;
            rootChildren = 0;
            n_bridges += dfs(i, dfs_depth, dfsRoot, rootChildren, adj, dfs_min, dfs_num, dfs_parent);
        }

    }
    cout << n_bridges << "\n";

    return 0;
}
```

### `caves1`
```cpp
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
    int n, m;
    cin >> n >> m;
    vector<bool> visited(n, false);
    vector<bool> local_visited(n, false);
    vector<vector<int>> adj(n);
    vector<ll> gold(n);
    vector<int> ts;
    ts.reserve(n);
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
    for (uint start = 0; start < visited.size(); start++){
        compute_toposort(start, visited, local_visited, adj, ts);
    }
    reverse(ts.begin(), ts.end());

    vector<ll> max_gold_vec = gold;
    for (auto u: ts){
        for (auto node: adj[u]){
            ll maybe_gold = gold[node];
            max_gold_vec[node] = max(max_gold_vec[node], max_gold_vec[u] + maybe_gold);
        }
    }
    
    cout << *max_element(max_gold_vec.begin(), max_gold_vec.end()) << "\n"; 
    return 0;
}
```

### `caves2`
```cpp
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
```

### `driving`
```cpp
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
```

## W7
### `marriage`
```cpp
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
```

### `reelection`
```cpp
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
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, less<tuple<int,int,int>>> PQ;
    visit(0, visited, adj, PQ);
    while (!PQ.empty()) {
        auto front = PQ.top(); PQ.pop();
        int w, from, to;
        tie(w, from, to) = front;
        if (!visited[to]) {
            // cout << "Add " << from+1 << "-" << to+1 << " to MST\n";
            if (w < 0){
                positive_sum += w;
            }

            visit(to, visited, adj, PQ);

        }
    }
    
    // output the maximum total quality
    cout << positive_sum << "\n";

    return 0;
}
```

## W8
### `bankrobbery`
```cpp
#define INF numeric_limits<int>::max()

vector<vector<int>> capacity;
vector<vector<int>> adj;
vector<int> parent;

void bfs(int s) {
    parent.assign(adj.size(), -1);
    parent[s] = -2; // s is visited

    queue<int> Q;
    Q.push(s);
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int v : adj[u]) // go u -> v
            if (parent[v] == -1 and capacity[u][v] > 0) {
                Q.push(v);
                parent[v] = u;
            }
    }
}

int maxflow(int s, int t) {
    int totalflow = 0;
    int u;
    while (true) {
        // build bfs tree
        bfs(s);
        if (parent[t] == -1) // t unreachable
            break;
        // find bottleneck capacity
        int bottleneck = INF;
        u = t;
        while (u != s) {
            int v = parent[u];
            bottleneck = min(bottleneck, capacity[v][u]);
            u = v;
        }
        // update capacities along path
        u = t;
        while (u != s) {
            int v = parent[u];
            capacity[v][u] -= bottleneck;
            capacity[u][v] += bottleneck;
            u = v;
        }
        totalflow += bottleneck;
    }
    return totalflow;
}

int main(){
    int t;  // number of test cases
    int l;  // amount of available policemen
    int n;  // amount of intersections
    int m;  // number of lines with edges

    // for each test case
    cin >> t;
    for (int test_cases = 0; test_cases < t; test_cases++){
        cin >> l >> n >> m;
        // adj.assign(n, vector<int>(0, 0));  // <------------ HMMMMMM
        adj.clear();
        adj.resize(n);
        capacity.assign(n, vector<int>(n, 0));

        // for each edge in this test case
        int u, v, c;
        for (int n_edges = 0; n_edges < m; n_edges++) {
            cin >> u >> v >> c;
            u--; v--;
            adj[u].push_back(v);
            // if (count(adj[v].begin(), adj[v].end(), u) == 0){
            adj[v].push_back(u);
            // }
            // show_adj_table(adj);
            capacity[u][v] += c;
            capacity[v][u] += c;
        }
        // cout << "For test case: " << test_cases << "\n";

        int out = maxflow(0,n-1);
        
        // show_adj_table(adj);
        // print(capacity, "capacity");
        // cout << "out: " << out << "\n";
        cout << "Case #" << test_cases+1 << ": ";
        if (out <= l){
            cout << "yes\n";
        }
        else cout << "no\n";
    }
    
    
    return 0;
}
```

### `biglineup1`
```cpp
#define INF numeric_limits<int>::max()

vector<vector<int>> capacity;
vector<vector<int>> adj;
vector<int> parent;

void bfs(int s) {
    parent.assign(adj.size(), -1);
    parent[s] = -2; // s is visited

    queue<int> Q;
    Q.push(s);
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int v : adj[u]) // go u -> v
            if (parent[v] == -1 and capacity[u][v] > 0) {
                Q.push(v);
                parent[v] = u;
            }
    }
}

int maxflow(int s, int t) {
    int totalflow = 0;
    int u;
    while (true) {
        // build bfs tree
        bfs(s);
        if (parent[t] == -1) // t unreachable
            break;
        // find bottleneck capacity
        int bottleneck = INF;
        u = t;
        while (u != s) {
            int v = parent[u];
            bottleneck = min(bottleneck, capacity[v][u]);
            u = v;
        }
        // update capacities along path
        u = t;
        while (u != s) {
            int v = parent[u];
            capacity[v][u] -= bottleneck;
            capacity[u][v] += bottleneck;
            u = v;
        }
        totalflow += bottleneck;
    }
    return totalflow;
}

int main(){
    int n;
    cin >> n;
    adj.clear();
    adj.resize(2*n+2);
    capacity.assign(2*n+2, vector<int>(2*n+2, 0));

    int e;
    // setup the source
    for (int man = 1; man < n+1; man++){ // source is 0, men are from id 1
        adj[0].push_back(man);
        // adj[man].push_back(0);
        capacity[0][man] += 1;
        // capacity[man][0] += 1;
    }

    // setup the drain
    for (int wine = n+1; wine < 2*n+1; wine++){
        // adj[2*n+1].push_back(wine);
        adj[wine].push_back(2*n+1);
        capacity[wine][2*n+1] += 1;
        // capacity[2*n+1][wine] = INF / 2;
    }

    for (int r = 1; r < n+1; r++){
        for (int c = 0; c < n; c++){
            cin >> e;
            if (e == 1){
                adj[r].push_back(c+n+1);
                adj[c+n+1].push_back(r);
                capacity[r][c+n+1] += 1;
                // capacity[c+n+1][r] += 1;
            }
        }
    }

    // show_adj_table(adj);
    // print(capacity, "capacity");
    int out = maxflow(0,2*n+1);
    cout << out << "\n";

    
    
    return 0;
}
```

## W9
### `addressbook`
```cpp
struct trie {
    bool isEndOfString = false;
    int counter = 0;
    map<char, trie*> edges;
    void insert(string &s, int i = 0) {
        if (i == s.length()) {
            isEndOfString = true;
            return;
        }
        if (edges.count(s[i]) == 0)
            edges[s[i]] = new trie;
        edges[s[i]]->counter++;
        edges[s[i]]->insert(s, i+1);
    }

    int contains(string &s, int i = 0){

        if ( i == s.length()){
            return -1;
        }
        if (edges.count(s[i]) > 0){
            if (edges[s[i]]->contains(s, i+1) == -1){
                return edges[s[i]]->counter;
            }            
            else{
                return edges[s[i]]->contains(s, i+1);
            }
        }
        else return 0;
        

    }
};

trie t;

int main(){

    int n;
    cin >> n;
    string query, word;
    for (int i = 0; i < n; i++){
        cin >> query >> word;
        // cout << query << " " << word << "\n";
        if (query == "add"){
            t.insert(word);
        }
        else if (query == "find"){
            cout << t.contains(word) << "\n";
        }
    }
    


    return 0;
}
```
### `lcs`
```cpp
void show_dp(const vector<vector<int>> &dp, string &s, string &t){
    cout << "    e  ";
    for (int i = 0; i < t.length(); i++){
        cout << t[i] << "  ";
    }
    cout << "\n";

    for (int r = 0; r <= s.length(); r++){
        for (int c = 0; c <= t.length(); c++){
            if (c == 0){
                if (r==0){
                    cout << "e | ";
                }else{
                    cout << s[r-1] << " | ";
                }
            }
            if (dp[r][c] < 10){
                cout << dp[r][c] << "  ";
            }
            else{
                cout << dp[r][c] << " ";
            }
            
        }
        cout << "\n";
    }
}
string s,t;
int main(){

    cin >> s >> t;

    vector<vector<int>> dp(s.length()+1, vector<int>(t.length()+1));
    for(int i = 0; i <= s.length(); ++i) dp[i][0] = i;  // fill the epsilon vector
    for(int j = 0; j <= t.length(); ++j) dp[0][j] = 0;  // fill the epsilon vector
    for(int i = 1; i <= s.length(); ++i) {
        for (int j = 1; j <= t.length(); ++j){
            if (s[i-1] == t[j-1])
            {
                // dp[i][j] = dp[i-1][j-1];
                dp[i][j] = min({dp[i-1][j-1], 1+ dp[i-1][j], dp[i][j-1]});
                // dp[i][j] = min({dp[i-1][j-1], dp[i][j-1]});
            }
            else
            {
                dp[i][j] = min({1+ dp[i-1][j-1], 1+ dp[i-1][j], dp[i][j-1]});
                // dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1]});
            }
        }
    }
    cout << s.size() - dp[s.length()][t.length()] << "\n";
    // show_dp(dp, s, t);
    // show_adj_table(dp);

    return 0;
}
```

## W10
### `milkman` - gcd
```cpp
int gcd(int a, int b){
    int mod;
    while ((a % b) > 0)
    {
        mod = a % b;
        a = b;
        b = mod;
    }
    return b;
}

class segtree {
private:
    vector<long long> values;
    size_t size;

    int parent(int i) {
        return i / 2;
    }
    int left(int i) {
        return 2 * i;
    }
    int right(int i) {
        return 2 * i + 1;
    }

    void update(int i) {
        // values[i] = values[left(i)] + values[right(i)];
        values[i] = gcd(values[left(i)], values[right(i)]);
        if (i > 1) update(parent(i));
    }

    // Query sum of interval [i, j)
    // current_node represents the interval [l, r)
    long long query(int i, int j, int l, int r, int current_node) {
        if (r <= i || j <= l) return 0; // current interval and query interval don't intersect
        if (r <= j && i <= l) return values[current_node]; // current interval contained in query interval

        int m = (l + r) / 2;
        // return query(i, j, l, m, left(current_node)) + query(i, j, m, r, right(current_node));
        return gcd(query(i, j, l, m, left(current_node)), query(i, j, m, r, right(current_node)));
    }

public:
    segtree(size_t n) {
	size = 1<<(int)ceil(log2(n));
        values.assign(2 * size, 0);
    }

    segtree(vector<long long> v): segtree(v.size()) {
        for (size_t i = 0; i < v.size(); ++i) values[i + size] = v[i];
        // for (size_t i = size - 1; i > 0; --i) values[i] = values[left(i)] + values[right(i)];
        for (size_t i = size - 1; i > 0; --i) values[i] = gcd(values[left(i)], values[right(i)]);
    }

    // Query sum of interval [i, j)
    long long query(int i, int j) {
        return query(i, j, 0, size, 1);
    }

    // Set value at position i to val
    void update(int i, long long val) {
        values[i + size] = val;
        update(parent(i + size));
    }
};



int main(){
    ios::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<ll> v(n);
    for (ll& l: v) cin >> l;

    segtree s(v);
    while (q--) {
        char type;
        cin >> type;

        if (type == '!') {
            // update
            ll k, u;
            cin >> k >> u;
            s.update(k - 1, u);
        } else {
            // query
            int a, b;
            cin >> a >> b;
            cout << s.query(a - 1, b) << endl;
        }
    }

    return 0;
}
```

### `pathcounter`
```cpp

const int mod = 998244353;

ll factorial(ll n)
{
    ll res = 1, i;
     
    for(i = 2; i <= n; i++)
        res = (res * i) % mod;
         
    return res;
}

ll fact_custom(ll c, ll r)
{
    ll res = (c%mod + r%mod)%mod;
    // cout << "init: " << res << "\n";
    for (ll i = 1; i < r; i++)
    {
        res = (res * (c + (r-i))) % mod;
    }
    return res;
}

ll fexp(ll m, ll n, ll p){
    if (n==0) return 1;
    else if (n%2 == 1){
        return (m * fexp(m, n-1, p)) % p;
    }
    else{
        ll r = fexp(m, n/2, p);
        return (r * r) % p;
    }
}

int main(){
    int C, R;
    cin >> C >> R;
    // ll nom = factorial(R%mod + C%mod)%mod;
    // ll den = factorial(R%mod)%mod * factorial(C%mod)%mod;

    // cout << factorial(R+C) / (factorial(R) * factorial(C)) << "\n";

    // cout << (nom * fexp(den, mod-2, mod)) % mod << "\n";
    ll nom = fact_custom(C%mod, R%mod)%mod;
    ll den = factorial(R%mod)%mod;
    // cout << "nom: " << nom << " den: " << den << "\n";
    cout << (nom * fexp(den, mod-2, mod)) % mod << "\n";
    // cout << mod << " " << R << "\n";
    // vector<vector<int>> dp(R+1, vector<int> (C+1, 0));  // the size can be perhaps also modulo?
    // vector<int> dp(C+1, 1);

    // cout << "Here?\n";

    // dp[0][0] = 1;  // starting position, needs to be one for algo to work
    // for (int r = 0; r < R+1; r++){
    //     for (int c = 0; c < C+1; c++){
    //         cout << "r: " << r << " c: " << c << "\n";
    //         if (c == 0 && r == 0) continue;  // top left corner
    //         else if (r == 0)  // top row 
    //         {
    //             dp[r][c] = dp[r][c-1] % mod;
    //         }
    //         else if (c == 0)
    //         {
    //             dp[r][c] = dp[r-1][c] % mod;
    //         }
    //         else
    //         {
    //             dp[r][c] = (dp[r-1][c] % mod) + (dp[r][c-1] % mod);
    //         }
    //     }
    // }

    // show_dp(dp);
    // cout << dp[R][C] << "\n";
    // R = R % mod;
    // C = C % mod;
    
    // for (int r = 1; r < R+1; r++){  // skip the first step, done at initialization
    //     for (int c = 0; c < C+1; c++){
    //         if ( c == 0 ) continue;
    //         else{
                // dp[c] = (dp[c-1] % mod) + (dp[c] % mod);
                // dp[c] = ((dp[c-1] % mod) + (dp[c] % mod)) % mod;  // or perhaps like this?
    //         }
    //     }
    // }
    // cout << dp[C] << "\n";
    // ll nom = factorial(R%mod + C%mod);

    // cout << "through factorial:\n" << factorial(R+C) / (factorial(R) * factorial(C)) << "\n";
    return 0;
}
```