#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

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

// inspired by slide 9, lec 3 (Dynamic Programming)
