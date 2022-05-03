#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

// create all combinations with repetition
vector<tuple<int,int,int>> all;
for (int a = 0; a<3; a++){
    for (int b = 0; b<3; b++)

}

int main(){
    int n, A, B, C;
    cin >> n >> A >> B >> C;
    int chunks[] = {A,B,C};
    // maximize the number of cuttings 
    int max_cnt = 0;
    for (int i=0; i<3; i++){
        int n_temp = n;
        int cnt = 0;
        if (n_temp-chunks[i] > 0){
            n_temp -= chunks[i];

            cnt++;
        }
        

        
    }
}