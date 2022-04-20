// compile (for debugging): g++ -Wall -Wextra -fsanitize=undefined,address -D_GLIBCXX_DEBUG -g <file>
// compile (as on judge): g++ -x c++ -Wall -O2 -static -pipe <file>
// Output file will be a.out in both cases
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

int main() {
    
    string word_n_names;
    int n_names;
    getline(cin, word_n_names);
    n_names = stoi(word_n_names);
    // cout << n_names + "\n";
    vector<string> names = {};
    for (int i = 0; i < n_names; i++){
        string name;
        getline(cin, name);
        names.push_back(name);
    }

    for (int i = 0; i < n_names; i++){
        cout << "Hello " + names[i] + "!\n";
    }

    return 0;
}
