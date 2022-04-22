// compile (for debugging): g++ -Wall -Wextra -fsanitize=undefined,address -D_GLIBCXX_DEBUG -g <file>
// compile (as on judge): g++ -x c++ -Wall -O2 -static -pipe <file>
// Output file will be a.out in both cases
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

bool customsort(const pair<int,int> &a, const pair<int,int> &b){
        if (a.first != b.first){
            return(a.first < b.first);
        }
        else{
            return(b.second < a.second);
        }
        
}

int main() {
    int n;
    cin >> n;
    vector< pair<int, int> > offers;
    offers.reserve(n);
    int d_i; int v_i;

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

    cout << "Sorted pairs: \n";
    for (uint i=0; i < offers.size(); i++){
        cout << offers[i].first << " " << offers[i].second << "\n";
    }
    int borrowed = offers[0].first;
    int brutto = offers[0].second;

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

    // cout << "Set: \n";
    // for (auto it = offers_set.begin(); it !=offers_set.end(); ++it){
    //     cout << it->first << " " << it->second << "\n";
    // }
    

    // set <pair<int, int>> offers_set(offers.begin(), offers.end());  // loaded vector sort into a set of pairs


    // auto end = offers_set.end()--;
    // // cout << "end of offers set: " << it->first << " " << it->second;
    // int n_borrowed = 1;

    // while (n_borrowed <= end->first)
    // {
    //     cout << "Number of borrowed wines: " << n_borrowed << "\n";
    //     auto temp_offers_set = offers_set;
    //     int current_d_i = n_borrowed;
    //     int netto_bottles = current_d_i - n_borrowed;

    //     for (auto it = temp_offers_set.begin(); it !=temp_offers_set.end(); ++it){
    //         if(it->first > current_d_i){
    //             break;
    //         }
            

    //     }

    //     n_borrowed++;
    // }
    return 0;
}