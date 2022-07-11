#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

void print_array(vector<int> array){
    for (int x : array){
        cout << x << " ";
    }
    cout << "\n";
}


int main(){
    int n;
    cin >> n;

    // special cases
    
    vector<int> stamps;
    stamps.reserve(n);
    int outlier_id = -1;

    // load the input
    for (int i=0; i<n; i++){
        int value;
        cin >> value;
        stamps.push_back(value);
    }

    if (n==1){
        cout << "impossible\n";
        return 1;
    }

    // traverse the input
    bool outlier_found = false;
    int local_min_id = -1;
    for (uint i=0; i<stamps.size()-1; i++){
        if (stamps[i] > stamps[i+1]){
            if (outlier_found == false){
                outlier_id = i;
                for (uint j = outlier_id + 1; j<stamps.size(); j++){
                    if (local_min_id == -1){
                        local_min_id = j;
                    }
                    else if (stamps[j] <= stamps[local_min_id]){
                        local_min_id = j;
                    }
                }
            }
            outlier_found = true;
        }
    }

    // try to swap
    swap(stamps[outlier_id], stamps[local_min_id]);
    for (uint i = 0; i < stamps.size()-1; i++){
        if (stamps[i] > stamps[i+1]){
            cout << "impossible\n";
            return 0;
        }
    }
    cout << outlier_id + 1 << " " << local_min_id + 1 << "\n";
    return 0;

}
