#include <bits/stdc++.h>

typedef long long ll;
using namespace std;


// map<int, string> ID_2_name;
//     map<string, int> name_2_ID;

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
bool dfs(int start, vector<bool> &visited, vector<bool> &local_visited, const vector<vector<int>> &adj){
    visited[start] = true;
    local_visited[start] = true;
    for(int u: adj[start])
    {   
        // cout << "local u: " << u << "\n";
        if(local_visited[u]){
        // cout << "LOCAL IMPOSSIBLE\n";
        return false;
        }
        if (!visited[u]){
            if(dfs(u, visited, local_visited, adj)) return false;
        }
    }
    return true;
}


// bool dfs(int start, vector<bool> &visited, const vector<vector<int>> &adj){
//     // vector<bool> visited(n, false);
//     stack<int> S; //LIFO

//     S.push(start);
//     visited[start] = true;
//     map<int, bool> local_visited = {};
//     while(!S.empty()){
//         int v = S.top();
//         S.pop();
//         local_visited.clear();
//         for (int u: adj[v])
//         {
//             if (!visited[u])
//             {
//                 S.push(u);
//                 if(local_visited.count(u)){
//                     // cout << "impossible\n";
//                     return false;
//                 }else{
//                     local_visited[u] = true;
//                 }
//                 visited[u] = true;
//             }
//         }
//     }
//     return true;
// }

int main(){
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    vector<bool> visited(n, false);
    vector<bool> local_visited(n, false);
    // vector<string> names(n+1, "");
    map<int, string> ID_2_name;
    map<string, int> name_2_ID;

    string first;
    string second;
    string oper;
    int ID_cnt = -1;

    // parse the lines
    for (int i = 0; i < n; i++){
        cin >> first >> oper >> second;
        parse_the_line(ID_2_name, name_2_ID, ID_cnt, first, second, oper, adj);       
    }

    if (!dfs(0, visited, local_visited, adj)){
        cout << "impossible\n";
    }else{
        cout << "possible\n";
    }

    cerr << "--------------\n| ADJ. TABLE |\n--------------\n";
    for (uint i = 0; i < adj.size(); i++){
        cerr << ID_2_name[i] << " | ";
        for (uint j = 0; j < adj[i].size(); j++){
            cerr << ID_2_name[adj[i][j]] << " ";
            
        }
        cerr << "\n";
    }
    cerr << "\n- - - - -\n\n";
    cerr << "-----------\n| VISITED |\n-----------\n";
    for (uint i = 0; i < adj.size(); i++){
        cerr << ID_2_name[i] << " | " << visited[i] << "\n";
    }
    cerr << "-----------\n";
    return 0;
}