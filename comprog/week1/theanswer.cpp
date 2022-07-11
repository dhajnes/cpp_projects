#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

void print_int_vector(vector<int> array){
    for (int x : array){
        cout << x << " ";
    }
    cout << "\n";
}

void print_ll_vector(vector<ll> array){
    for (ll x : array){
        cout << x << " ";
    }
    cout << "\n";
}

void print_ll_set(set<ll> array){
    for (ll x : array){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    int n;
    cin >> n;
    vector<ll> numbers;
    for (int i=0; i < n; i++){
        ll num;
        cin >> num;
        numbers.push_back(num);
    }
    sort(numbers.begin(), numbers.end());

    for (int i=0; i < n-2; i++){
        
        ll first = numbers[i];
        ll diff = first - 42;

        for (int j = i+1; j < n-1; j++){
            ll second = numbers[j];
            if(binary_search(numbers.begin(), numbers.end(), (-diff - second))){
                cout << first << " " << second << " " << (-diff - second) << "\n";
                return 0;
            }
        }
    }
    cout << "impossible";

}
