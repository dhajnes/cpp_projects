#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    int n_dishes; int n_query;
    cin >> n_dishes >> n_query;
    vector<ll> dishes;
    dishes.reserve(n_dishes);

    int chunk_size = (int)(ceil(sqrt(n_dishes)));
    int n_chunks = (int)(ceil(sqrt(n_dishes)));
    vector<ll> chunks(n_chunks, 0);  // initialize vector to all zeros
    
    // get the petri dishes
    for (int i=0; i<n_dishes; i++){
        int b_i;
        cin >> b_i;
        dishes.push_back(b_i);
    }

    /* end of input loading */

    // divide and conquer; compute sums over chunks
    int chunk_cnt = -1;
    for (uint i=0; i < dishes.size(); i++){
        if (i % chunk_size == 0) chunk_cnt++;
        if (dishes[i] % 2 != 0) chunks[chunk_cnt]++;
    }

    char query_letter; 
    for (int i=0; i<n_query; i++){
        cin >> query_letter;
        if (query_letter == 'Q'){
            int first;
            int second;
            cin >> first >> second;
            first--; second--; // change to indices instead of dish numbers
            ll value = 0;

            for (int id = first; id < second+1; id++){
                // is start of a chunk        // space for a whole chunk
                if ((id % chunk_size == 0) && (id + chunk_size <= second+1)){
                    value += chunks[(int)(floor(id/chunk_size))];
                    id += chunk_size-1;
                    
                }
                else{
                    if (dishes[id] % 2 != 0) value++;
                }
            }
            cout << value << "\n";
        }
        else if (query_letter == 'U'){
            int idx;
            ll value;
            cin >> idx >> value;
            idx--;
            
            if ( (dishes[idx] % 2) == (value % 2)){
                continue;                  
            }
            else{
                int chunk_id = (int)(floor(idx/chunk_size));
                if (dishes[idx] % 2 != 0){
                    chunks[chunk_id]--;
                }
                else{
                    chunks[chunk_id]++;
                }
                dishes[idx] = value;
            }
        }
        else {
            cerr << "Unrecognised query letter: " << query_letter << "\n";
            return 1;
        } 
    }
    return 0;
}
