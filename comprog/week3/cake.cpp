#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define debug(x) \
    (cerr << #x << ": " << (x) << endl)

void print_2D_vec(vector<vector<int>> vec){
    for (uint r = 0; r < vec.size(); r++){
        for (uint c = 0; c < vec[0].size(); c++){
            cout << vec[r][c] << " ";
        }
        cout << "\n";
    }
}

vector<vector<int>> p_sums(vector<vector<int>> tray){
    vector<vector<int>> sums(tray.size(), vector<int>(tray[0].size(), 0));
    for (uint r = 0; r < tray.size(); r++){
        for (uint c = 0; c < tray[0].size(); c++){
            if (r == 0 && c == 0){
                sums[r][c] = tray[r][c];
            }
            else if (r == 0){
                sums[0][c] = sums[0][c-1] + tray[0][c];
            }
            else if (c == 0){
                sums[r][0] = sums[r-1][0] + tray[r][0];
            }
            else{
                sums[r][c] = sums[r-1][c] + sums[r][c-1] - sums[r-1][c-1] + tray[r][c];
            }
        }
        
    } 
    return sums;
}

int main() {

    bool vb = false;

    int h; int w; int h_cake; int w_cake;
    cin >> h >> w;
    vector<vector<int>> bt(h, vector<int> (w, 0));
    int sqr_mm;
    for (int r = 0; r < h ; r++){
        for (int c = 0; c < w; c++){
            cin >> sqr_mm;
            bt[r][c] = sqr_mm;
        }
    }
    cin >> h_cake >> w_cake;

    // create the partial sums
    auto psv = p_sums(bt);

    if(vb){
        cout << "\nbt:\n";
        print_2D_vec(bt);
        cout << "\npartial sums:\n";
        print_2D_vec(psv);
    }
    int temp_sum = 0;
    for (int r=0; r <= h-h_cake; r++){
        for (int c=0; c <= w-w_cake; c++){
            temp_sum = psv[r+h_cake-1][c+w_cake-1];
            if (r == 0 && c == 0){
                
            }
            else if (r == 0){
                // sums[0][c] = sums[0][c-1] + tray[0][c];
                temp_sum -= psv[r+h_cake-1][c-1];
            }
            else if (c == 0){
                // sums[r][0] = sums[r-1][0] + tray[r][0];
                temp_sum -= psv[r-1][c+w_cake-1];
            }
            else{
                // sums[r][c] = sums[r-1][c] + sums[r][c-1] - sums[r-1][c-1] + tray[r][c];
                temp_sum += -psv[r+h_cake-1][c-1] - psv[r-1][c+w_cake-1] + psv[r-1][c-1];
            }
            if (temp_sum == 0){
                cout << r+1 <<" "<< c+1 <<" "<< r+h_cake <<" "<< c+w_cake << "\n";
                return 0;
            }
        }
    }
    
    cout << "-1 -1 -1 -1\n";

    


    return 0;
}