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

long long query(int i) {
    cout << i << endl;
    long long val;
    cin >> val;
    return val;
}

long long exp(int base, int power){
    if(power == 0) return 1;
    if(power == 1) return (base);
    long long ans = exp(base,power/2);
    ans = (ans * ans);
    if(power%2 == 1) ans = (ans*base);
    return (ans);
}

void solve() {
    long long rings[6];
    
//    for (int i = 200; i < 501; i++) {
//        ipair pwrs[6];
//        forj(6) {
//            pwrs[j] = {(i/(j+1)) % 63, j};
//        }
//        sort(pwrs, pwrs+6);
//        
//        cerr << pwrs[5].second << " " << pwrs[4].second << " " << pwrs[3].second << endl;
//        
//        if (pwrs[5].second == 3 && pwrs[4].second == 4 && pwrs[3].second == 5) {
//            cerr << i << endl;
//        }
//    }
//    return;
    
    // 2 tries.
    int i = 200;
    long long nrings = query(i);
    
    f0r(j, 3, 6) {
        long long pwr = exp(2, (int) i/(j+1));
        rings[j] = nrings / pwr;
        nrings -= (rings[j] * pwr);
    }
    
    i = 40;
    nrings = query(i);
    
    f0r(j, 3, 6) {
        long long pwr = exp(2, (int) i/(j+1));
        nrings -= rings[j] * pwr;
    }
    
    forj(3) {
        long long pwr = exp(2, (int) i/(j+1));
        rings[j] = nrings / pwr;
        nrings -= (rings[j] * pwr);
    }
    
//    for (int i : {200}) {
//        long long nrings = query(i);
//        
//        for (int j = 3; j < 6; j++) {
//            long long pwr = exp(2, (int) i/(j+1));
//            rings[j] = nrings / pwr;
//            nrings -= (rings[j] * pwr);
//        }
//        
//        pwrs[3] = exp(2, i/4)
//        
//        cerr << "nrings: " << nrings << endl;
//        
//        ipair pwrs[6];
//        forj(6) {
//            pwrs[j] = {(i/(j+1)) % 63, j};
//        }
//        
//        sort(pwrs, pwrs+6);
//        
//        rev(j, 5) {
//            long long m = exp(2, pwrs[j].first);
//            rings[pwrs[j].second] = nrings / m;
//            cerr << pwrs[j].first << " " << pwrs[j].second << " " << nrings << " " << nrings/m << endl;
//            nrings -= (rings[pwrs[j].second] * m);
//        }
//    }
    
    fori(6) {
        cout << rings[i];
//        cerr << rings[i] << endl;
        if (i < 5) cout << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int t, w;
    cin >> t >> w;
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

