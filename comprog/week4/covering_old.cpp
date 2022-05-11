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
    bool vb = false;
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

    vector<int> marks(max_num+1, -1);
    uint max_arity = 0;
    uint arity_cnt = 0;
    for (uint i = 0; i < s.size(); i++){  // choose examined superset
        arity_cnt = 0;
        for (auto const &k : s[i]){
            marks[k] = i;  // mark itself into the marks
        }
        if(vb){
            cout << "marks: \n";
            for (uint i = 0; i < marks.size(); i++){
                cout << i << " ";
            }
            cout << "\n";
            for (uint i = 0; i < marks.size(); i++){
                cout << "--";
            }
            cout << "\n";
            for (auto const &j: marks){
                cout << j << " ";
            }
            cout << "\n";
        }
        
        for (uint j = 0; j < s.size(); j++){  // cycle through subsets
            
            if (j == i) continue;  // dont examine self

            uint hits_cnt = 0;
            for (auto const &k : s[j]){
                if (marks[k] == (int) i) hits_cnt++;
            }
            if(hits_cnt == s[j].size()) arity_cnt++;
        }
        if (arity_cnt > max_arity) max_arity = arity_cnt;
    }
    cout << max_arity << "\n";

    // cout << "PRINTING ALL SETS:\n";
    // for (uint i = 0; i < s.size(); i++){
    //     for (auto const &j: s[i]){
    //         cout << j << " ";
    //     }
    //     cout << "\n";
    // }

    return 0;
}