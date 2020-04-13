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

vector<string> endings;
vector<string> starts;

vector<string> split(string s, char delim) {
    string ret = "";
    vector<string> v;
    
    for (char c : s) {
        if (c == '*') {
            v.push_back(ret);
            ret = "";
        } else {
            ret += c;
        }
    }
    
    v.push_back(ret);
    
    return v;
}

bool solve() {
    int n;
    cin >> n; 
    
    endings.clear();
    starts.clear();
    
    vector<string> v(n);
    vector<vector<string>> regions;
    string maxstart = "";
    string maxend = "";
    int maxregion = 0;
    
    fori(n) {
        cin >> v[i];
        
        vector<string> splits = split(v[i], '*');
        
        bool hasstart = splits[0] != "";
        
        if (hasstart) {
            starts.push_back(splits[0]);
            if (splits[0].size() > maxstart.size()) {
                maxstart = splits[0];
            }
        }
        
        bool hasend = splits[splits.size()-1] != "";
        
//        cout << v[i] << " " << hasstart << " " << hasend << " " << splits.size() << endl;
        
        if (hasend) {
            endings.push_back(splits[splits.size()-1]);
            if (splits[splits.size()-1].size() > maxend.size()) {
                maxend = splits[splits.size()-1];
            }
        }
        
        vector<string> addons;
        for (int j = hasstart; j < (splits.size()-hasend); j++) {
            auto str = splits[j];
            if (str != "") {
                addons.push_back(str);
            }
        }
        maxregion = max(maxregion, (int) addons.size());
        
        regions.push_back(addons);
    }
    
    for (int i = 0; i < maxstart.size(); i++) {
        char comp = '\n';
        
        for (auto s : starts) {
            if (s.size() <= i) {
                continue;
            }
            if (comp == '\n') {
                comp = s[i];
            } else if (s[i] != comp) {
                return false;
                break;
            }
        }
    }
    
    for (int i = 0; i < maxend.size(); i++) {
        char comp = '\n';
        
        for (auto s : endings) {
            if (s.size() <= i) {
                continue;
            }
            char val = s[s.size()-i-1];
            if (comp == '\n') {
                comp = val;
            } else if (val != comp) {
                return false;
                break;
            }
        }
    }
    
    cout << maxstart;
    bool good = false;
    for (int i = 0; i < maxregion; i++) {
        for (auto v : regions) {
            if (v.size() <= i) {
                continue;
            }
            
            cout << v[i];
        }
    }
    cout << maxend << '\n';
    
//    int n;
//    cin >> n;
//    
////    ans = "";
//    vector<string> ans;
//    vector<vector<string>> regions;
//    
//    fori(n) {
//        string s; 
//        cin >> s;
//        
//        vector<string> v;
//        
//        for (int j = 0; j < s.size();) {
//            int e = j;
//            for (int k = j; k < s.size(); k++) {
//                if (s[k] == '*') {
//                    break;
//                }
//                e = k;
//            }
//            
//            string asdf = s.substr(j, (e-j+1));
//            
//            if (asdf == "*") {
//                v.push_back("*");
//            } else {
//                v.push_back(asdf);
//            }
//            
//            j = e+1;
//        }
//        
//        regions.push_back(v);
//    }
//    
//    ans = regions[0];
//    
//    string a = "";
//    for (string v : regions[0]) {
//        a += v;
//    }
//    
//    bool jump = false;
//    for (int i = 1; i < regions.size(); i++) {
//        int idx = 0;
//        
//        for (string r : regions[i]) {
//            if (r == "*") {
//                jump = true;
//                continue;
//            }
//            
//            int l = max(0, idx-(int)r.size());
//            int s = r.size() + min(idx-(int)r.size(), 0);
//            
//            if (r.substr(l, s) == queryon(a, idx, s)) {
//                
//            }
//            
//            jump = false;
//        }
//    }
//    
//    if (flag) {
//        cout << "*\n";
//    } else {
//        for (auto st : ans) {
//            cout << st;
//        }
//        cout << "\n";
//    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cout << "Case #" << i+1 << ": ";
        if (!solve()) {
            cout << "*\n";
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

//1
//5
//*CONUTS*
//*COCONUTS
//*OCONUTS
//*CONUTS
//*S

