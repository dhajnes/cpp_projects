#include <bits/stdc++.h>

using namespace std;

typedef long long ll;


int get_whole_num(ll *i, const string& inp){
    char num_chars[4];
    int cnt = 0;
    while (true){
        if (inp[*i] == ',' || inp[*i] == ')') break;
        num_chars[cnt] = inp[*i];
        cnt++;
        (*i)++;  // moves pointer by one
    }
    num_chars[cnt] = '\0';
    // cout << "`whole_num`: \n" << stoi(num_chars) << "\n";
    return stoi(num_chars);
}

int main(){
    // bool vb = false;
    vector<string> trees;
    ios::sync_with_stdio(false);
    string line;
    while(getline(cin, line)){
        trees.push_back(line);
    }
    vector<set<int>> s((int) trees.size(), set<int>{});
    
    int max_num = 0;
    int num;

    /* -- PARSE THE INPUT INTO SETS -- */
    
    for (uint i = 0; i < trees.size(); i++){ // for tree in trees
        
        for (ll j = 0; j < (ll) trees[i].size(); j++){ // for char in tree
            
            if (isdigit(trees[i][j])){
                num = get_whole_num(&j, trees[i]);
                s[i].insert(num);
                if (num > max_num){
                    max_num = num;
                }
            }
        }
    }

    vector<int> markers(max_num+1, -1);
    vector<ll> masks(s.size(), 0);
    uint max_arity = 0;
    uint arity_cnt = 0;
    ll mask_len = 8 * sizeof(ll);

    // generate masks
    for (uint i = 0; i < s.size(); i++){
        for (auto const &k : s[i])
        {   
            masks[i] = masks[i] | 1 << (k % mask_len);  
        }
    }

    // choose examined candidate superset
    for (uint i = 0; i < s.size(); i++)
    {  
        arity_cnt = 0;
        for (auto const &k : s[i])
        {   
            markers[k] = i; // mark itself into the marks 
        }
        
        // cycle through candidate subsets
        for (uint j = 0; j < s.size(); j++)
        {  
            if (j == i) continue;  // dont examine self

            if ((~masks[i] & masks[j]) != 0)
            {
                continue;
            }

            else
            {    
                bool is_subset = true;
                for (auto const &k : s[j]){
                    if (markers[k] != (int) i)
                    {   
                        is_subset = false;
                        break;
                    }
                }   
                if(is_subset) arity_cnt++;
            
            }
        }
        if (arity_cnt > max_arity) max_arity = arity_cnt;
    }
    cout << max_arity << "\n";

    return 0;
}