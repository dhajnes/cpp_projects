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

const ll mod = 1000000007;


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