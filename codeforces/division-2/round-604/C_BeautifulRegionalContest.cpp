#include <iostream>
#include <iomanip>
#include <algorithm>
#include <chrono>
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
#include <unordered_map>
#include <list>
#include <string>
#include <string.h>
#include <utility>
#include <array>
#include <bitset>
#define fori(n) for(int i = 0; i < n; i++)
#define forj(n) for(int j = 0; j < n; j++)
#define fork(n) for(int k = 0; k < n; k++)
#define rev(val, stop) for (int (val) = (stop); val >= 0; val--)
#define f0r(val, start, stop) for(int (val) = (start); (val) < (stop); val++)
#define bigval 1000000000
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

void set_IO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}

void solve() {
    int n;
    cin >> n;
    vector<int> partitions;
    int cur = -1;
    
    fori(n/2+1) {
        int a;
        cin >> a;
        
        if (cur == -1) {
            cur = a; 
        } else if (a != cur) {
            partitions.push_back(i-1);
            cur = a;
        }     
    }
    
    f0r(i, n/2+1, n) {
        int a;
        cin >> a;
    }
    
//    cout << "newone: " << partitions.size() << ' ' << n <<  endl;
    
    if (partitions.size() == 0) {
        cout << "0 0 0\n";
        return;
    }
    
    int g = partitions[0] + 1;
    int total = partitions.back() - g + 1;
    f0r(i, 1, partitions.size()) {
        int s = partitions[i] - g + 1;
//        cout << partitions[i-1] << ' ' << partitions[i] << ' ' << total << ' ' << s << endl;
        if (g < s && g < (total-s)) {
            cout << g << ' ' << s << ' ' << (total-s) << '\n';
            return;
        }
    }
    
    cout << "0 0 0\n";
}

int main() {
    int t;
    cin >> t;
    fori(t) {
        solve();
    }
    return 0;
}



