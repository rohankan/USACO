/*
 ID: rohanka3
 PROG: agrinet
 LANG: C++11
 */

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
#include <utility>
#include <array>
#include <bitset>
#define sortvec(vec) sort(vec.begin(), vec.end())
#define fori(n) for(int i = 0; i < n; i++) 
#define forj(n) for(int j = 0; j < n; j++) 
#define fork(n) for(int k = 0; k < n; k++) 
#define forval(val, n) for(int val = 0; val < n; val++)
#define forirev(n) for(int i = n-1; i > -1; i--)
#define forvalrev(val, n) for(int val = n-1; val > -1; val--)
#define bigval 2147483640
#define LONG_MAX 0x7FFFFFFFL
using namespace std;

typedef pair<int, int> ipair;
typedef pair<int, pair<int, int>> tripair;
typedef pair<double, double> dpair;

void set_IO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}

#define INF 2147483640

typedef pair<int, pair<int, int>> tripair;

const int MAX_N = 500;
const int MAX_M = 500;

int n, m;
string spotty[500];
string normal[500];

bool check(int size) {
    
    forj(m-size+1) {
        set<string> s;
        
        fori(n) {
            s.insert(spotty[i].substr(j, size));
//            cout << spotty[i].substr(j, size) << " " << size << endl;
        }
        
        bool good = true;
        fori(n) {
            if (s.find(normal[i].substr(j, size)) != s.end()) {
                good = false;
                break;
            }
        }
        
        if (good) {
            return true;
        }
    }
    return false;
}

int boundary_binary_search() {
    int lo = 1;
    int hi = m+1;
    
    while (lo+1 < hi) {
        int mid = (lo + hi) / 2;
        
        if (!check(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    
    return lo+1;
}

int main() {
    set_IO("cownomics");
    
    cin >> n >> m;
    fori(n) {
        cin >> spotty[i];
    }
    fori(n) {
        cin >> normal[i];
    }
    
    cout << boundary_binary_search() << endl;
    
    return 0;
}

