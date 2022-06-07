# include <bits/stdc++.h>

typedef long long ll;
using namespace std;

void print(const vector<bool> &vec, const string &txt){
    cout << "vec: " << txt << "\n";
    for (uint i = 0; i < vec.size(); i++){
        cout << i+1 << " | " << vec[i] << "\n";
    }
    cout << "\n";
}

void print(const vector<int> &vec, const string &txt){
    cout << "vec: " << txt << "\n";
    for (uint i = 0; i < vec.size(); i++){
        cout << i+1 << " | " << vec[i] << "\n";
    }
    cout << "\n";
}

void print(const vector<ll> &vec, const string &txt){
    cout << "vec: " << txt << "\n";
    for (uint i = 0; i < vec.size(); i++){
        cout << i+1 << " | " << vec[i] << "\n";
    }
    cout << "\n";
}

class Node {
    public:
        ll val{-1};
        bool X{false};
        vector<Node *> children{};
        Node * parent{nullptr};
};


int whole_num(ll *i, const string& inp){
    /*Here, the number is guaranteed to be 3 chars long.*/
    char num_chars[4];
    for (int k = 0; k < 3; k++){
        num_chars[k] = inp[*i];
        (*i)++;  // moves the value of the pointer by one
    }
    
    num_chars[3] = '\0';
    // cout << "num_chars: " << num_chars << "\n";
    int out_num = stoi(num_chars);
    return out_num;
}



int deeper(Node *node, ll *i, const string &inp){
    
    while((*i) < (ll) inp.size()){

        if (inp[*i] == ')'){
            (*i)++;
            break;
        }
        if (inp[*i] == '(' || inp[*i] == ','){
            (*i)++;
        }
        
        if (isdigit(inp[*i])){
            int num = whole_num(i, inp);
            if (num == -1){
                return -1;
            }
            Node* new_node = new Node{num, false, {}, node};
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
            if (deeper(new_node, i, inp) == -1) return -1;

        }
        else if (inp[*i] == '*')
        {
            Node* new_node = new Node{'*', false, {}, node};
            node->children.push_back(new_node);
            (*i)++;
            if (deeper(new_node, i, inp) == -1) return -1;
        }
    }
    return 0;
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

int main(){
    string line;
    ll amax;
    ll y;
    cin >> amax >> y;
    getline(cin, line);
    getline(cin, line);
    
    Node root;
    // cycle through chars of string
    int flag = 0;
    for (ll j = 0; j < (ll) line.size(); j++){

        root.val = line[0];
        if(root.val == 'X')
        {
            root.X = true;
        }
        j++;
    
        flag = deeper(&root, &j, line);
        
    }
    if (flag == -1){
        delete_tree(&root);
        cout << "impossible\n";
        return 0;
    }

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
    cout << "impossible" << "\n";
    delete_tree(&root);
    return 0;
}