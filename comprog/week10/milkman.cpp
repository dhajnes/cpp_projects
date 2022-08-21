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

int gcd(int a, int b){
    int mod;
    while ((a % b) > 0)
    {
        mod = a % b;
        a = b;
        b = mod;
    }
    return b;
}

class segtree {
private:
    vector<long long> values;
    size_t size;

    int parent(int i) {
        return i / 2;
    }
    int left(int i) {
        return 2 * i;
    }
    int right(int i) {
        return 2 * i + 1;
    }

    void update(int i) {
        // values[i] = values[left(i)] + values[right(i)];
        values[i] = gcd(values[left(i)], values[right(i)]);
        if (i > 1) update(parent(i));
    }

    // Query sum of interval [i, j)
    // current_node represents the interval [l, r)
    long long query(int i, int j, int l, int r, int current_node) {
        if (r <= i || j <= l) return 0; // current interval and query interval don't intersect
        if (r <= j && i <= l) return values[current_node]; // current interval contained in query interval

        int m = (l + r) / 2;
        // return query(i, j, l, m, left(current_node)) + query(i, j, m, r, right(current_node));
        return gcd(query(i, j, l, m, left(current_node)), query(i, j, m, r, right(current_node)));
    }

public:
    segtree(size_t n) {
	size = 1<<(int)ceil(log2(n));
        values.assign(2 * size, 0);
    }

    segtree(vector<long long> v): segtree(v.size()) {
        for (size_t i = 0; i < v.size(); ++i) values[i + size] = v[i];
        // for (size_t i = size - 1; i > 0; --i) values[i] = values[left(i)] + values[right(i)];
        for (size_t i = size - 1; i > 0; --i) values[i] = gcd(values[left(i)], values[right(i)]);
    }

    // Query sum of interval [i, j)
    long long query(int i, int j) {
        return query(i, j, 0, size, 1);
    }

    // Set value at position i to val
    void update(int i, long long val) {
        values[i + size] = val;
        update(parent(i + size));
    }
};



int main(){
    ios::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<ll> v(n);
    for (ll& l: v) cin >> l;

    segtree s(v);
    while (q--) {
        char type;
        cin >> type;

        if (type == '!') {
            // update
            ll k, u;
            cin >> k >> u;
            s.update(k - 1, u);
        } else {
            // query
            int a, b;
            cin >> a >> b;
            cout << s.query(a - 1, b) << endl;
        }
    }


    

    return 0;
}