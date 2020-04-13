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

struct Node {
    vector<int> paths;
    int i, j;
};

//unordered_set<int, custom_hash> s;
ipair ans[500];
int pascal[501][501];
bool visited[501][501];
int goal;
int flag;

int operations[6][2] = {{-1, -1}, {0, -1}, {0, 1}, {-1, 0}, {1, 0}, {1, 1}};

void dfs(int depth, int i, int j, int total) {
    if (depth > 500 || total > goal || flag != -1 || visited[i][j]) {
        return;
    } else if (total == goal) {
        flag = depth;
        return;
    }
    
//    cout << depth << " " << i << " " << j << ' ' << total << endl;
    
    ans[depth] = {i+1, j+1};
    visited[i][j] = true;
    int newtotal = total + pascal[i][j];
    
    pair<int, ipair> values[6];
    int size = 0;
    
    fork(6) {
        int a = i + operations[k][0];
        int b = j + operations[k][1];
        
        if (a < 0 || b < 0 || b > a) {
            continue;
        }
        
//        cout << operations[k][0] << " " << operations[k][1] << " " << a << " " << b << " " << pascal[a][b] << endl;
        values[size++] = {pascal[a][b], {a, b}};
    }
    
    sort(values, values+size);
    
//    fork(size) cout << values[k].first << endl;
    
    rev(k, size-1) {
        int a = values[k].second.first, b = values[k].second.second;
        
//        cout << a << " " << b << " " << values[k].first << endl;
        
        dfs(depth+1, a, b, newtotal);
    }
    
//    if (pascal[i+1][j+1] > pascal[i+1][j]) {
//        dfs(depth+1, i+1, j+1, newtotal);
//        dfs(depth+1, i+1, j, newtotal);
//    } else {
//        dfs(depth+1, i+1, j, newtotal);
//        dfs(depth+1, i+1, j+1, newtotal);
//    }
    
    if (!flag) {
        ans[depth] = {-1, -1};
        visited[i][j] = false;
    }
}

void solve() {
    flag = -1;
    cin >> goal;
    
    fori(501) {
        forj(501) {
            visited[i][j] = false;
        }
    }
    
    dfs(0, 0, 0, 0);
    
    fori(flag) {
        cout << ans[i].first << " " << ans[i].second << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    pascal[0][0] = 1;
    f0r(i, 1, 501) {
        pascal[i][0] = 1;
        pascal[i][i] = 1;
        f0r(j, 1, i) {
            pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j];
        }
    }
    
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cout << "Case #" << i+1 << ":\n";
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

