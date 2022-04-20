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
    vector<int> prefs = {0,1,2,3,4,5,6,7,8,9,10};
    int g = 11;  // 11 guests
    int w = 11;  // 11 wines
    int table[g][w];
    for (int i=0; i < g; i++){
        for (int j=0; j < w; j++){
            cin >> table[i][j];
        }
    }

    int max_pleasure = 0;
    do {
        int loc_pleasure = 0;
        for (int i=0; i<g; i++){
            loc_pleasure += table[i][prefs[i]];
        }
        if (loc_pleasure > max_pleasure) max_pleasure = loc_pleasure;
    } while (next_permutation(prefs.begin(), prefs.end()));
    cout << max_pleasure;
}
