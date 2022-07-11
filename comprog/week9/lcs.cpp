#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void show_adj_table(const vector<vector<int>> &adj){
    cout << "--------------\n| ADJ. TABLE |\n--------------\n";
    for (uint i = 0; i < adj.size(); i++){
        cout << i << " | ";
        for (uint j = 0; j < adj[i].size(); j++){
            cout << adj[i][j] << " ";
            
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