#include <iostream>
#include <iomanip> 
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

/*
CIN INPUT:
<start>

<end>
*/

void solve() {
    string s;
    cin >> s;

//    cout << "yo" << endl;

    fori(s.size()) {
        bool good[3];
        // cout << i << ' ' << s[i] << '\n'; 
        forj(3) {
            good[j] = false;
        } 
        if (i-1 >= 0 && s[i-1] != '?') {
            good[s[i-1]-'a'] = true;
        }
        if (i+1 < s.size() && s[i+1] != '?') {
            good[s[i+1]-'a'] = true;
        } 

        forj(3) {
            if (good[j] && s[i]-'a' == j) {
                cout << -1 << '\n';
                return;
            } else if (s[i] == '?' && !good[j]) {
                s[i] = (char) ((int)('a') + j); 
            }
        }
    }

    cout << s << '\n'; 
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
//        cout << "Case #" << i+1 << ": ";
        solve();
//        int cor;
//        cin >> cor; 
//        
//        if (cor == -1) {
//            break;
//        }
    }
    
    return 0;
}

