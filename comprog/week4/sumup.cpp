#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

int whole_num(ll *i, const string& inp){
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

class Node {
    public:
        int val{-1};
        vector<Node *> children{};
        Node * parent{nullptr};
};

int deeper(Node *node, ll *i, const string &inp){
    
    while((*i) < (ll) inp.size()){
        // cout << "Going deeper with i: " << *i << "\n";
        if (inp[*i] == ')'){
            // cout << "\nBREAKING\n";
            (*i)++;
            break;
        }
        if (inp[*i] == '(' || inp[*i] == ','){
            (*i)++;
            // continue;
        }
        
        if (isdigit(inp[*i])){
            Node* new_node = new Node{whole_num(i, inp), {}, node};
            node->children.push_back(new_node);          
        }
        else if (inp[*i] == '+')
        {
            // Node new_node;
            Node* new_node = new Node{'+', {}, node};
            node->children.push_back(new_node);
            (*i)++;
            deeper(new_node, i, inp);

        }
        else if (inp[*i] == '*')
        {
            Node* new_node = new Node{'*', {}, node};
            node->children.push_back(new_node);
            (*i)++;
            deeper(new_node, i, inp);
        }
    }
    return 1;
}


void node_info(Node * root){
    cout << "_____________\n| NODE INFO |\n-------------\n";

    if (root->children.empty()){
        cout  << "name: " << root->val << "\n";
        cout << "no children";
    }
    else{
        cout  <<  "name: " << (char) root->val << "\n";
        cout << "children: [";
        for (uint i = 0; i < root->children.size(); i++){
            // print_tree(root->children[i]);         
            if (root->children[i]->children.empty()){
                cout  << root->children[i]->val << " ";
            } 
            else{
                cout << (char) root->children[i]->val << " ";
            }
        }
        cout << "]\n";

    }
    cout << "\n";
}

void print_tree(Node * root, int indent){
    // node_info(root);

    if (root->children.empty()){
            // cout << "is empty? : " << root->children.empty() << "\n";
            for (int i = 0; i < indent; i++) cout << " ";
            cout  << root->val << "\n";
        }
    else{
        for (int i = 0; i < indent; i++) cout << " ";
        cout << (char)(root->val) << "\n";
        // cout << "children:\n";
        for (uint i = 0; i < root->children.size(); i++){
            print_tree(root->children[i], indent + 2);           
        }
    }
    
    return;
}

void delete_tree(Node * root){

    if (root->children.empty()){
            return;
        }
    else{
        
        for (uint i = 0; i < root->children.size(); i++){
            delete_tree(root->children[i]);           
            delete root->children[i];
        }
    }
}

ll eval_tree(Node * root){
    ll total;

    if (root->children.empty()){
        return root->val;
    }
    else
    {
        if(root->val == '*'){
            total = 1;
            for (uint i = 0; i < root->children.size(); i++){
                total *= eval_tree(root->children[i]);
            }
        }
        else{
            total = 0;
            for (uint i = 0; i < root->children.size(); i++){
                total += eval_tree(root->children[i]);
            }
        }  
    }
    return total;
}




int main() {
    bool vb = false;
    vector<string> trees;
    string line;
    while(getline(cin, line)){
        trees.push_back(line);
    }

    ll total = 0;
    // cycle through trees
    for (uint i = 0; i < trees.size(); i++){
        // cout << "current tree: " << trees[i] << "\n";
        Node root;
        // cycle through chars of string
        for (ll j = 0; j < (ll) trees[i].size(); j++){

            root.val = trees[i][0];
            j++;
            deeper(&root, &j, trees[i]);
        }   
        // cout << "tree:\n";
        // print_tree(&root, 0);
        total += eval_tree(&root);
        delete_tree(&root);
    }
    

    if(vb){
        cout << "trees:\n";
        for (uint i = 0; i < trees.size(); i++){  
            cout << trees[i] << "\n";
        }
    }
    
    cout << total << "\n";
    
    return 0;
}
