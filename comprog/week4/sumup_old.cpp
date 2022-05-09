#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

class Node {
    public:
        vector<int> vals;
        vector<Node> children;
        vector<Node> parents;
        bool isFirst = false;
        bool isSum;

        int output(){
            if (isSum){
                return accumulate(vals.begin(), vals.end(), 0);
            }
            else{
                return accumulate(vals.begin(), vals.end(), 0, multiplies<int>());
            }
        }
};

int main() {
    bool vb = true;
    vector<string> trees;
    string line = "abc";
    while(getline(cin, line)){
        trees.push_back(line);
    }

    char c;
    Node root;
    root.isFirst = true;
    auto current_node = root;

    // cycle through trees
    for (uint i = 0; i < trees.size(); i++){

        // cycle through chars of string
        for (uint j = 0; j < trees[i].size(); j++){
            
            c = trees[i][j];
           if (c == '+' || c == '*'){
               Node temp;
               if (c == '+'){
                   temp.isSum
               }
           }
            

        }
        cout << "\n";
    }

    if(vb){
        cout << "trees:\n";
        for (uint i = 0; i < trees.size(); i++){  
            cout << trees[i] << "\n";
        }
    }
    
    return 0;
}
