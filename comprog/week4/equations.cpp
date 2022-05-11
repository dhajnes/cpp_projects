#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

int whole_num(ll *i, const string& inp){
    /*Here, the number is guaranteed to be 3 chars long.*/
    char num_chars[4];
    for (int k = 0; k < 3; k++){
        num_chars[k] = inp[*i];
        (*i)++;  // moves the value of the pointer by one
    }
    
    num_chars[3] = '\0';
    // cout << "`whole_num`: \n" << stoi(num_chars) << "\n";
    return stoi(num_chars);
}

class Node {
    public:
        ll val{-1};
        bool X{false};
        vector<Node *> children{};
        Node * parent{nullptr};
};

int deeper(Node *node, ll *i, const string &inp){
    
    while((*i) < (ll) inp.size()){
        // cout << "Going deeper with i: " << *i << "\n";
        // if(inp[*i] == '\n'){
        //     cout << "FOUND A NEWLINE AT INDEX: " << *i << '\n';
        // }
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
            Node* new_node = new Node{whole_num(i, inp), false, {}, node};
            node->children.push_back(new_node);          
        }
        else if (inp[*i] == 'X')
        {
            Node* new_node = new Node{'X', true, {}, node};
            node->children.push_back(new_node);  
            (*i)++;
        }
        else if (inp[*i] == '+')
        {
            // Node new_node;
            Node* new_node = new Node{'+', false, {}, node};
            node->children.push_back(new_node);
            (*i)++;
            deeper(new_node, i, inp);

        }
        else if (inp[*i] == '*')
        {
            Node* new_node = new Node{'*', false, {}, node};
            node->children.push_back(new_node);
            (*i)++;
            deeper(new_node, i, inp);
        }
    }
    return 0;
}


void node_info(Node * root){
    cout << "_____________\n| NODE INFO |\n-------------\n";

    if (root->children.empty()){
        if (root->X)
        {
            cout  << "name: " << (char) root->val << "\n";
        }
        else
        {
            cout  << "name: " << root->val << "\n";
        }
        
        cout << "no children";
    }
    else{
        cout  <<  "name: " << (char) root->val << "\n";
        cout << "children: [";
        for (uint i = 0; i < root->children.size(); i++){
            // print_tree(root->children[i]);         
            if (root->children[i]->children.empty()){
                if (root->children[i]->X){
                    cout  << (char) root->children[i]->val << " ";
                }
                else
                {
                    cout  << root->children[i]->val << " ";
                }
                
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
            if (root->X)
            {
                cout << (char) root->val << "\n";
            }
            else
            {
                cout  << root->val << "\n";
            }
            
        }
    else{
        for (int i = 0; i < indent; i++) cout << " ";
        cout << (char)(root->val) << "\n";
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

ll eval_tree(Node * root, ll x){
    ll total;

    if (root->children.empty()){
        if (root->X){
            return x;
        }
        else{
            return root->val;
        }
        
    }
    else
    {
        if(root->val == '*'){
            total = 1;
            for (uint i = 0; i < root->children.size(); i++){
                total *= eval_tree(root->children[i], x);
            }
        }
        else{
            total = 0;
            for (uint i = 0; i < root->children.size(); i++){
                total += eval_tree(root->children[i], x);
            }
        }  
    }
    return total;
}


int main() {
    // vector<string> trees;
    string line;
    ll amax;
    ll y;
    cin >> amax >> y;
    getline(cin, line);
    getline(cin, line);
    
    Node root;
    // cycle through chars of string
    for (ll j = 0; j < (ll) line.size(); j++){

        root.val = line[0];
        if(root.val == 'X')
        {
            root.X = true;
        }
        j++;
        deeper(&root, &j, line);
    }   

    // for (ll i = 1; i <= amax; i++){
    //     // cout << "i: " << i << "\n";
    //     // cout << "Tree evaluated with X = " << i << "\nOutput: " << eval_tree(&root, i) << "\n";
    //     if (eval_tree(&root, i) == y){
    //         cout << i << "\n";
    //         delete_tree(&root);
    //         return 0;
    //     }
    // }
    ll lb = 1;
    ll ub = amax;

    ll mid;
    ll candidate_output = -1;
    ll possible_answer = -1;
    while(lb <= ub){
        mid = (ub - lb)/2 + lb;
        candidate_output = eval_tree(&root, mid);
        if (candidate_output == y){
            cout << mid << "\n";
            delete_tree(&root);
            return 0;
        }
        else if (candidate_output < y)
        {
            lb = mid + 1;
            possible_answer = mid;
            possible_answer++;
        }
        else
        {
            ub = mid - 1;
        }
        
    }
    // if (possible_answer != -1){
    //     cout << mid << "\n";
    //     delete_tree(&root);
    // }
    // else{
        cout << "impossible" << "\n";
        delete_tree(&root);
    // }
    
    

    
    
    // cout << total << "\n";
    
    return 0;
}
