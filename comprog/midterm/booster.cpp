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
