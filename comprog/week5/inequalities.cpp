#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

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