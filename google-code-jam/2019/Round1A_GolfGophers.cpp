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
#define rev(val, stop) for (int (val) = (stop); val >= 0; val--)
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

//unordered_set<int, custom_hash> s;

int n, m;
int arr[18];

void query(int i) {
//    cerr << i << endl;
    forj(18) {
        cout << i;
        if (j < 17) {
            cout << " ";
        }
    }
    cout << endl;
    
    forj(18) {
        cin >> arr[j];
    }
}

int arrsum() {
    int total = 0;
    fori(18) total += arr[i];
    return total;
}

int primes[7] = {11, 12, 13, 14, 15, 16, 17};

void solve() {
    int sums[7];
    
    fori(7) {
        query(primes[i]);
        
//        fori(18) {
//            cerr << arr[i] << " ";
//        }cerr << endl;
        
//        cerr << "sum: " << primes[i] << " " << arrsum() << endl;
        sums[i] = arrsum() % primes[i];
    }
    
    bool passed = false;
//    fori(7) {
//        cerr << "s " << i << " " << sums[i] << endl;
//    }
    
    for (int val = sums[6]; val <= m; val += primes[6]) {
        bool good = true;
        
        for (int j = 5; j >= 0; j--) {
            if (val % primes[j] != sums[j]) {
                good = false;
                break;
            }
        }
        
//        cerr << val << " " << good << endl;
        
        if (good) {
            cout << val << endl;
//            cerr << "found: " << val << endl;
            passed = true;
            break;
        }
    }
    
    if (!passed) {
        cout << 5 << endl; // just to move on.
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int t;
    cin >> t;
    cin >> n >> m;
    for (int i = 0; i < t; i++) {
//        cout << "Case #" << i+1 << ": ";
        solve();
        
        int cor;
        cin >> cor;
        
        if (cor == -1) {
            break;
        }
    }
    
    return 0;
}

