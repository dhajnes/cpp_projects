#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

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

    uint pow_set_size = pow(2, A1.size());
    // generate all subsets 
    for (uint cnt = 0; cnt < pow_set_size; cnt++){
        if (cnt % 1000 == 0){
            // cout << "1st, cnt: " << cnt << "\n";
        }
        
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
