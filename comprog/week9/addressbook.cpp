#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void show_adj_table(const vector<vector<int>> &adj){
    cout << "--------------\n| ADJ. TABLE |\n--------------\n";
    for (uint i = 0; i < adj.size(); i++){
        cout << i+1 << " | ";
        for (uint j = 0; j < adj[i].size(); j++){
            cout << adj[i][j]+1 << " ";
            
        }
        cout << "\n";
    }
}

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

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

struct trie {
    bool isEndOfString = false;
    int counter = 0;
    map<char, trie*> edges;
    void insert(string &s, int i = 0) {
        if (i == s.length()) {
            isEndOfString = true;
            return;
        }
        if (edges.count(s[i]) == 0)
            edges[s[i]] = new trie;
        edges[s[i]]->counter++;
        edges[s[i]]->insert(s, i+1);
    }

    int contains(string &s, int i = 0){

        if ( i == s.length()){
            return -1;
        }
        if (edges.count(s[i]) > 0){
            if (edges[s[i]]->contains(s, i+1) == -1){
                return edges[s[i]]->counter;
            }            
            else{
                return edges[s[i]]->contains(s, i+1);
            }
        }
        else return 0;
        

    }
};

trie t;

int main(){

    int n;
    cin >> n;
    string query, word;
    for (int i = 0; i < n; i++){
        cin >> query >> word;
        // cout << query << " " << word << "\n";
        if (query == "add"){
            t.insert(word);
        }
        else if (query == "find"){
            cout << t.contains(word) << "\n";
        }
    }
    


    return 0;
}



// precalculation of lsp for Knuth-Morris-Pratt
    // // lsp ~ Longest Suffix-Prefix

    // int start = 0, len = 0;
    // while (start + len < n){
    //     while (len >= m || s[start+len] != t[len]){
    //         if (len == 0){
    //             start++;
    //             len = -1;
    //             break
    //         }
    //         int skip = len - lsp[len-1];
    //         start += skip;
    //         len -= skip;
    //     }
    //     len++;
    //     if (len == m){
    //         cout << "t matches s at " << start << "\n";
    //     }
    // }

