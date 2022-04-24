// compile (for debugging): g++ -Wall -Wextra -fsanitize=undefined,address -D_GLIBCXX_DEBUG -g <file>
// compile (as on judge): g++ -x c++ -Wall -O2 -static -pipe <file>
// Output file will be a.out in both cases
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

bool customsort(const pair<ll,ll> &a, const pair<ll,ll> &b){
        if (a.first != b.first){
            return(a.first < b.first);
        }
        else{
            return(a.second > b.second);
        }
}

int main() {
    int n;
    cin >> n;
    vector< pair<ll, ll> > offers;
    offers.reserve(n);
    ll d_i; ll v_i;

    for (int i=0; i < n; i++){
        cin >> d_i;
        cin >> v_i;
        if (d_i >= v_i) continue;
        offers.push_back(make_pair(d_i, v_i));
    }

    if (offers.empty()){
        cout << 0 << " " << 0;
        return 0;
    }

    sort(offers.begin(), offers.end(), customsort);

    // cout << "Sorted pairs: \n";
    // for (uint i=0; i < offers.size(); i++){
    //     cout << offers[i].first << " " << offers[i].second << "\n";
    // }
    ll borrowed = offers[0].first;
    ll brutto = offers[0].second;

    for (uint i=1; i < offers.size(); i++){
        if (brutto < offers[i].first){

            // borrow needed wines
            borrowed += (offers[i].first - brutto);
            brutto = offers[i].first;
        }
        // do the transaction
        brutto += offers[i].second - offers[i].first;
    }
    cout << borrowed << " " << brutto - borrowed;

    return 0;
}