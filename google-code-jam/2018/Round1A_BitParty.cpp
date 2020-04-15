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
//3
//
//2 2 2
//1 2 3
//1 1 2
//
//2 2 2
//1 2 3
//2 1 2
//
//5 100 5
//95 3 3
//2 1 5
//2 4 2
//2 2 4
//1 5 1
/*
 1
 3 4 5
 2 3 3
 2 1 5
 2 4 2
 2 2 4
 2 5 1
*/
int rowsums[100];
int colsums[100];

int r, b, c;
int lines[1000][3];

bool works(long long y) {
    long long total = 0;
    multiset<long long> best;
//    long long minval;
    
    fori(c) {
        long long m = lines[i][1], b = lines[i][2];
        long long val = max((long long) 0, min((long long) lines[i][0], (y-b)/m));
        
        if (best.size() == r) {
            if (*best.begin() < val) {
                best.erase(best.begin());
                best.insert(val);
            }
        } else {
            best.insert(val);
        }
        
//        cout << " " <<  lines[i][0] << " " << m << " " << b << " " << max((long long) 0, min((long long) lines[i][0], (y-b)/m)) << endl;
    }
    
    for (auto val : best) {
        total += val;
    }
    
//    cout << r << " " << y << " " << total << " " << b << " " << (total >= b) <<  endl;
    
    return total >= b;
}

long long boundary_binary_search() {
    long long lo = 0;
    long long hi = 9223372036854775805;
    
    while (lo+1 < hi) {
//        cout << lo << " " << hi << endl;
        long long mid = (lo+hi)/2;
        
        if (works(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    
    return lo+1;
}

void solve() {
    cin >> r >> b >> c;
    
    fori(c) {
        cin >> lines[i][0] >> lines[i][1] >> lines[i][2];
    }
    
//    works(4);
//    works(5);
    cout << boundary_binary_search() << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cout << "Case #" << i+1 << ": ";
        solve();
//        if (!solve()) {
//            cout << "IMPOSSIBLE\n";
//        }
//        int cor;
//        cin >> cor; 
//        
//        if (cor == -1) {
//            break;
//        }
    }
    
    return 0;
}


