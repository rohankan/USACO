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

const int MAX_N = 100000;

int n;
int arr[MAX_N];
set<int> colors[MAX_N+2];

bool flag = false;
int maxdepth = 0;
// unordered_set<int> visited[MAX_N+2];

void dfs(int c, int l, int r, int depth) {
    // if (visited[c].find(l) != visited[c].end()) {
    //    return;
    // }
    //
    // visited[c].insert(l);
    
//    cout << c << " " << l << " " << r << " " << depth << endl;
    
    if (l+1 == r) {
        maxdepth = max(depth, maxdepth);
//        cout << "ended " << depth << " " << endl;
        return;
    }
    
    for (int i = l+1; i < r; i++) {
        int col = arr[i];
        
        auto it = colors[col].upper_bound(i);
        
        if (it == colors[col].end()) {
            maxdepth = max(maxdepth, col == 0 ? depth : depth+1);
            continue;
        } else if (*it > r) {
            flag = true;
            return;
        }
        
        dfs(col, i, *it, col == 0 ? depth : depth+1);
        
        i = *it-1;
        
//        int pre = i;
//        while (it != colors[col].end()) {
//            if (*it > r) {
//                flag = true;
//                return;
//            }
//            
//            dfs(col, pre, *it, col == 0 ? depth : depth+1);
//            
//            pre = *it;
//            it++;
//        }
    }
}

int main() {
    set_IO("art2");
    
    cin >> n;
    fori(n) {
        cin >> arr[i];
        colors[arr[i]].insert(i);
    }
    
    dfs(n+1, -1, n, 0);
    
    if (flag) {
        cout << -1 << endl;
    } else {
        cout << maxdepth << endl;
    }
    
    return 0;
}

