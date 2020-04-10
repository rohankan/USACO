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

//unordered_set<int, custom_hash> s;

void solve() {
    int p, q;
    cin >> p >> q;
    
    unordered_map<int, int> east;
    unordered_map<int, int> west;
    unordered_map<int, int> north;
    unordered_map<int, int> south;
    int wsum = 0, esum = 0, nsum = 0, ssum = 0;
    
    fori(p) {
        int x, y; char d;
        cin >> x >> y >> d;
        if (d == 'N') {
            north[y]++;
            nsum++;
        } else if (d == 'S') {
            south[y]++;
            ssum++;
        } else if (d == 'W') {
            west[x]++;
            wsum++;
        } else {
            east[x]++;
            esum++;
        }
    }
    
    int left = 0, counter = 0;
    int lsum = wsum, rsum = 0;
    
    counter = (int) wsum;
    
    for (int s = 0; s <= q; s++) {
        if (west.find(s) != west.end()) {
            lsum -= west[s];
        } 
        
        int c = lsum + rsum;
        
//        cout << s << " " << c << " " << lsum << " " << rsum << endl;
        
        if (c > counter) {
            counter = c;
            left = s;
        }
        
        if (east.find(s) != east.end()) {
            rsum += east[s];
        }
    }
    
    int bottom = 0;
    counter = (int) ssum;
    lsum = ssum; rsum = 0;
    
    for (int s = 0; s <= q; s++) {
        if (south.find(s) != south.end()) {
            lsum -= south[s];
        } 
        
        int c = lsum + rsum;
        
        if (c > counter) {
            counter = c;
            bottom = s;
        }
        
        if (north.find(s) != north.end()) {
            rsum += north[s];
        }
    }
    
    cout << left << " " << bottom << endl;
    
//    cout << east.size() << endl;
//    while (i < east.size()-1 || j < west.size()-1) {
//        cout << i << " " << j << " " << counter << " " << east[i] << " " << west[j] << endl;
//        if (east[i] < west[j]-1 && i < east.size()-1) {
//            i++;
//        } else {
//            int c = i + west.size()-j-1;
//            if (east[i]+1 == west[j]) {
//                c--;
//            }
//            cout << c << endl;
//            if (c > counter) {
//                counter = i + (int) west.size()-j-1;
//                left = east[i]+1;
//            }
//            j++;
//        }
//    }
    
//    cout << i << " " << j << endl;
//    cout << i + west.size()-j-1 << " " << counter << endl;
//    
//    if (i + west.size()-j-1 > counter) {
//        counter = i + (int) west.size()-j-1;
//        left = east[i]+1;
//        cout << east[i] << endl;
//    }
//    
//    int bottom = 0;
//    counter = i = j = 0;
//    while (i < north.size()-1 || j < south.size()-1) {
//        if (north[i] < south[j]-1 && i < north.size()-1) {
//            i++;
//        } else {
//            if (north[i] > south[j]-1 && i + south.size()-j-1 > counter) {
//                counter = i + (int) south.size()-j-1;
//                bottom = north[i]+1;
//            }
//            j++;
//        }
//    }
//    
////    cout << i << " " << j << endl;
//    
//    if (i + south.size()-j-1 > counter) {
//        counter = i + (int) south.size()-j-1;
//        bottom = north[i]+1;
//    }
//    
//    cout << left << " " << bottom << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    
    return 0;
}

