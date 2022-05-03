#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

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

// inspired by slide 9, lec 3 (Dynamic Programming)
