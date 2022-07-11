#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

void print_vector(vector<int> vec){
    cout << "Printing vector:" <<"\n";
    for (uint i=0; i<vec.size(); i++){
        cout << vec[i] << ", ";
    }
    cout << "\n";
}

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
