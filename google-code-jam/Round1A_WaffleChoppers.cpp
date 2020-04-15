#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>
#include <numeric>
#include <math.h>
#include <map>
#include <string.h>
#include <unordered_map>
#include <list>
#include <string>
#include <chrono>
#include <utility>
#include <array>
#include <bitset>
#define fori(n) for(int i = 0; i < n; i++) 
#define forj(n) for(int j = 0; j < n; j++) 
#define fork(n) for(int k = 0; k < n; k++) 
#define rev(val, stop) for (int (val) = (int) (stop); val >= 0; val--)
#define f0r(val, start, stop) for(int (val) = (start); (val) < (stop); val++)

using namespace std;

typedef pair<int, int> ipair;
typedef pair<double, double> dpair;
typedef pair<int, pair<int, int>> tripair;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (std::pair<T1, T2> const &pair) const {
        std::size_t h1 = std::hash<T1>()(pair.first);
        std::size_t h2 = std::hash<T2>()(pair.second);
        
        return h1 ^ h2;
    }
};

//unordered_set<int, custom_hash> s;

int operations[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int r, c;
//long modr, modc;

//long tokey(long i, long j) {
//    if (r > c) {
//        return i*modr + j;
//    } else {
//        return j*modc + i;
//    }
//}
//
//ipair topair(long key) {
//    if (r > c) {
//        return {key/modr, key%modr};
//    } 
//    return {key%modc, key/modc};
//}

/*
1
3 6 1 1
.@@..@
.....@
@.@.@@
*/
int rowsums[100];
int colsums[100];

bool solve() {
    int r, c;
    cin >> r >> c;
    int h, v;
    cin >> h >> v;
    bool arr[100][100];
    fori(r) forj(c) {char c; cin >> c; arr[i][j] = (c == '@');}
    
    int total = 0;
    
    memset(rowsums, 0, sizeof(rowsums));
    memset(colsums, 0, sizeof(colsums));
    
    fori(r) {
        forj(c) {
            colsums[j] += arr[i][j];
            rowsums[i] += arr[i][j];
            total += arr[i][j];
        }
    }
    
    
    int prod = (h+1) * (v+1);
//    cout << total << " " << prod << endl;
    if (total % prod != 0) {
        return false;
    }
    
    int req = total / prod;
//    
//    fori(r) {
//        cout << rowsums[i] << endl;
//    }
    
    vector<int> rowsplits;
    rowsplits.push_back(0);
    
    
    int cumsum = 0;
    int rowreq = total / (h+1);
//    cout << "asdf: " << rowreq << endl;
    fori(r) {
        cumsum += rowsums[i];
        if (cumsum == rowreq) {
            cumsum = 0;
            rowsplits.push_back(i+1);
        } else if (cumsum > rowreq) {
            return false;
        }
    }
    
    if (cumsum != 0) {
        return false;
    }
    
//    cout << "asdf" << endl;
    
    vector<int> colsplits;
    colsplits.push_back(0);
    
    cumsum = 0;
    int colreq = total / (v+1);
    fori(c) {
        cumsum += colsums[i];
        if (cumsum == colreq) {
            cumsum = 0;
            colsplits.push_back(i+1);
        } else if (cumsum > colreq) {
            return false;
        }
    }
    
    if (cumsum != 0) {
        return false;
    }
    
    for (int i = 0; i < rowsplits.size()-1; i++) {
        for (int j = 0; j < colsplits.size()-1; j++) {
            int c = 0;
            
            for (int a = rowsplits[i]; a < rowsplits[i+1]; a++) {
                for (int b = colsplits[j]; b < colsplits[j+1]; b++) {
                    c += arr[a][b];
                }
            }
            
            if (c != req) {
                return false;
            }
        }
    }
    
    cout << "POSSIBLE\n";
    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cout << "Case #" << i+1 << ": ";
        if (!solve()) {
            cout << "IMPOSSIBLE\n";
        }
//        int cor;
//        cin >> cor; 
//        
//        if (cor == -1) {
//            break;
//        }
    }
    
    return 0;
}

