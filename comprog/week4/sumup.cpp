#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

ll whole_num(ll *i, const string& inp){
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

class Node {
    public:
        vector<ll> vals;
        vector<Node *> children;
        vector<Node *> parents;
        bool isFirst = false;
        bool isSum;

        ll output(){
            if (isSum){
                return accumulate(vals.begin(), vals.end(), 0);
            }
            else{
                return accumulate(vals.begin(), vals.end(), 1, multiplies<ll>());
            }
        }
};

ll deeper(Node *node, ll *i, const string &inp){
    // ll out;
    while((*i) < (ll) inp.size()){
        if (inp[*i] == ')') break;
        if (inp[*i] == '(' || inp[*i] == ','){
            (*i)++;
            continue;
        }
        
        if (isdigit(inp[*i])){
            node->vals.push_back(whole_num(i, inp));
        }
        else if (inp[*i] == '+')
        {
            Node new_node;
            new_node.parents.push_back(node);
            new_node.isSum = true;
            node->children.push_back(&new_node);
            node->vals.push_back(deeper( &new_node, i, inp));

        }
        else if (inp[*i] == '*')
        {
            Node new_node;
            new_node.parents.push_back(node);
            new_node.isSum = false;
            node->children.push_back(&new_node);
            node->vals.push_back(deeper( &new_node, i, inp));
        }
    }
    return node->output();
}

int main() {
    bool vb = true;
    vector<string> trees;
    string line;
    while(getline(cin, line)){
        trees.push_back(line);
    }

    char c;
    
    ll total = 0;

    // cycle through trees
    for (uint i = 0; i < trees.size(); i++){
        cout << "current tree: " << trees[i] << "\n";
        Node root;
        root.isFirst = true;
        auto curr_node = root;
        // cycle through chars of string
        for (ll j = 0; j < (ll) trees[i].size(); j++){
            
            c = trees[i][j];
            if (c == '+')
            {
                cout<< "WAS ++\n";
                curr_node.isSum = true;
                
            }
            else if (c == '*')
            {
                cout<< "WAS **\n";
                curr_node.isSum = false;
            }
            curr_node.vals.push_back(deeper(&curr_node, &j, trees[i]));

        }
        total += curr_node.output();
    }
    cout << total << "\n";

    if(vb){
        cout << "trees:\n";
        for (uint i = 0; i < trees.size(); i++){  
            cout << trees[i] << "\n";
        }
    }
    
    return 0;
}
