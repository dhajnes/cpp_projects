#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

void print_array(int *pre, int length){
    cout << "Printing array:\n";
    for (int i=0; i<length; i++){
        cout << pre[i] << ", ";
    }
    cout << "\n";
}

void print_vector(vector<int> vec){
    cout << "Printing vector:" <<"\n";
    for (uint i=0; i<vec.size(); i++){
        cout << vec[i] << ", ";
    }
    cout << "\n";
}



class dpClass {
  public:
    int val{0};
    int prev;
};

int main() {
    bool vb = false;
    int n; int m; vector<int> A; 
    cin >> n >> m;
    vector<dpClass> dp(n, dpClass{});
    A.reserve(n);
    

    for (int i=0; i < n; i++){
        int a;
        cin >> a;
        // A is a vector filled with wine offers
        A.push_back(a);
    }
    int best_id = 0;
    for (int i=0; i < n; i++){
        if (i < m){
            dp[i].val = A[i];
            dp[i].prev = -1;
        }
        else{
            int _max_id = -1;
            int _max_val = -1;
            for (int j = i-m; j > i-2*m; j--){
                if (j<0) break;
                if(_max_val == -1){
                    _max_val = dp[j].val;
                    _max_id = j;
                }
                else{
                    if (dp[j].val > _max_val){
                        _max_id = j;
                        _max_val = dp[j].val;
                    }
                }
            }

            dp[i].val = A[i] + dp[_max_id].val;
            dp[i].prev = _max_id;
            
        }
        if (dp[i].val > dp[best_id].val) best_id = i; 
    }
    
    vector<int> indices;
    int curr_idx = best_id;
    while(1){
        if (curr_idx == -1) {
            break;
        }
        indices.push_back(curr_idx);
        curr_idx = dp[curr_idx].prev;
    }

    reverse(indices.begin(), indices.end());
    cout << dp[best_id].val << " " << indices.size() << "\n";
    for (uint i=0; i < indices.size(); i++){
        cout << indices[i]+1;
        if (i < indices.size()-1) cout << " ";
    }
    cout << "\n";

    return 0;
}
