#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void show_dp(const vector<vector<ll>> &dp){
    cout << "--------------\n| DP |\n--------------\n";
    for (uint i = 0; i < dp.size(); i++){
        cout << i << " | ";
        for (uint j = 0; j < dp[i].size(); j++){
            // cout << dp[i][j] << " ";
            printf("%*d ", 3, dp[i][j]);
            
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
        // cout << "(" << c << " + " << r-i << ")";
        // if (c + r-i == 0 ) cout << "| (c + r-i)% mod == 0 | is zero here i: " << i << "c: " << c << " r: " << r << "\n";
        // if ((c + r-i)% mod == 0 ) cout << "| (c + r-i)% mod == 0 | is zero with modulo at i: " << i << "c: " << c << " r: " << r << "\n";
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