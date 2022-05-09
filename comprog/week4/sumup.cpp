#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

int whole_num(int *i, string inp){
    char num_chars[4];
    int cnt = 0;
    while (true){
        if (inp[*i] == ',' || inp[*i] == ')') break;
        num_chars[cnt] = inp[*i];
        cnt++;
        (*i)++;  // moves pointer by one
    }
    num_chars[cnt] = '\0';

    return stoi(num_chars);
}

ll deeper(bool isSum, int *i, string inp){
    vector<ll> vals;
    ll out;

    while(true){
        if (inp[*i] == ')' || *i >= (int) inp.size()){
            break;
        }
        if ( isdigit(inp[*i]) )
        {   
            vals.push_back(whole_num(i, inp));
            if (inp[*i] == ')') break;
        }
        else if (inp[*i] == '*')
        {
            (*i)++;
            vals.push_back(deeper(false, i, inp));
        }
        else if (inp[*i] == '+')
        {   
            (*i)++;
            vals.push_back(deeper(true, i, inp));
        }
        (*i)++;
    }

    if (isSum){
        out = accumulate(vals.begin(), vals.end(), 0);
    }
    else{

        out = accumulate(vals.begin(), vals.end(), 1, multiplies<ll>());
    }

    return out;
      
}

int main() {

    vector<string> trees;
    string line;
    while(getline(cin, line)){
        trees.push_back(line);
    }

    char c;
    ll total_sum = 0;
    for (uint i = 0; i < trees.size(); i++){

        for (int j = 0; j < (int) trees[i].size(); j++){
            
            c = trees[i][j];

            if (c == '+') 
            {
                total_sum += deeper(true, &(++j), trees[i]);;
            }
            else if (c == '*')
            {
                total_sum += deeper(false, &(++j), trees[i]);;
            }
        }   
    }
    cout << total_sum << "\n";

    

    // if(vb){
    //     cout << "trees:\n";
    //     for (uint i = 0; i < trees.size(); i++){  
    //         cout << trees[i] << "\n";
    //     }
    // }
    // ll miniarr[2] = {3, 4};
    // ll arr[4] = {10, 20, 30, deeper_baby(false, 2, miniarr)};
    // cout << deeper_baby(true, 4, arr) << "\n";
    
    return 0;
}
