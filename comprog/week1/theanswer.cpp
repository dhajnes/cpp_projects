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
    // print_ll_vector(numbers);

    for (int i=0; i < n-2; i++){
        // cout << "outer for: \n";
        
        ll first = numbers[i];
        ll diff = first - 42;
        // cout << "first: " << first << " and diff: " << diff << "\n";

        for (int j = i+1; j < n-1; j++){
            // cout << "middle for: \n";
            ll second = numbers[j];
            // cout << "second: " << second << "\n";

            if(binary_search(numbers.begin(), numbers.end(), (-diff - second))){
                cout << first << " " << second << " " << (-diff - second) << "\n";
                return 0;
            }
            
       
        }
    }
    cout << "impossible";

}
