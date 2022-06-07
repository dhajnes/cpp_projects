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

int main(){
    int n;  // number of possible flights
    int k;  // number of starting slots
    cin >> n >> k;
    vector<ll> p(n, 0);
    for (int i = 0; i < n; i++){
        ll value;
        cin >> value;
        p[i] = value;
    }

    sort(p.begin(), p.end());

    // print(p, "p");
    ll sum = 0;
    for (int i = n-1; i >= 0; i--){
        if (i < n-k) break;
        // cout << "i: " << i <<" p[i]: " << p[i] << "\n";
        sum += p[i];
    }
    cout << sum << "\n";
    
    return 0;
}