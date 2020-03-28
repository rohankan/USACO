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

int n;
int values[2500];
int dfsvals[2500];
vector<int> paths[2500];

int runitback = 0;
int goup = 1;
unordered_set<int> groups;
int flag = -1;
bool visited[2500];
int cache[2500];

bool dfscheck(int cur, int par) {
//    cout << cur << " " << par << " " << dfsvals[cur] << endl;
    int v = dfsvals[cur] % 12 == 0;
    for (auto p : paths[cur]) {
        if (p == par) continue;
        bool v2 = dfscheck(p, cur);
//        cout << p << " " << cur << " " << v2 << endl;
        v = v && v2;
    }
    visited[cur] = v;
    if (!v) {
//        cout << cur << " " << v << " " << dfsvals[cur] << " " << paths[cur].size() << endl;
        groups.insert(cur);
    }
    return v;
}

bool docheck(int cur) {
    if (dfsvals[cur] == 0) {
        auto it = groups.find(cur);
        visited[cur] = true;
        if (it != groups.end()) {
            groups.erase(it);
        }
        
        if (groups.size() == 0) {
            flag = 1;
            return true;
        }
    } else {
        groups.insert(cur);
        visited[cur] = false;
    }
    return false;
}

int dfs(int cur, int par) {
    if (visited[cur]) {
        return goup;
    }
    
    if (par != -1) {
        dfsvals[cur] = (dfsvals[cur] + 1);
    }
    
    dfsvals[cur] %= 12;
    
//    cout << cur << " " << dfsvals[cur] << " " << par << endl;
    
    if (docheck(cur)) {
        return goup;
    }
    
    for (auto p : paths[cur]) {
        if (p == par) continue;
//        subtreesum += dfs(p, cur);
//        dfsvals[cur]++;
        int val;
        int cycles = 0;
        do {
            val = dfs(p, cur);
            dfsvals[cur] = (dfsvals[cur] + 1) % 12;
            cout << ": " << dfsvals[cur] << " " << cur << endl;
            if (docheck(cur)) {
                return goup;
            }
            cycles++;
            
            if (cycles == 12) {
                flag = 2;
                return goup;
            }
        } while (val == runitback);
    }
    
    // is leaf.
//    if (par != -1 && paths[cur].size() == 1 && dfsvals) {
//        auto it = groups.find(cur);
//        visited[cur] = true;
//        if (it != groups.end()) groups.erase(it);
    
    int subtreesum = (12 - dfsvals[cur]) % 12;
    
    cout << cur+1 << " " << par+1 << " " << subtreesum << " " << groups.size() << " " << dfsvals[cur] << endl;
    
    if (docheck(cur)) {
        return goup;
    }
    
    if (subtreesum != 0) {
        return runitback;
    } else {
        return goup;
    }
    
//    return subtreesum;
}

int main() {
    set_IO("cows");
    
    cin >> n;
    fori(n) {
        cin >> values[i];
//        cout << values[i] << endl;
    }
    fori(n-1) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        paths[a].push_back(b);
        paths[b].push_back(a);
//        cout << a << " " << b << endl;
    
    }
    
    int total = 0;
    fori(n) {
        i = 1;
        forj(n) {
            dfsvals[j] = values[j] % 12;
            visited[j] = false;
            cache[j] = -1;
        }
//        groups.clear();
        
//        fori(n) 
        
        flag = -1;
        dfscheck(i, -1);
        dfs(i, -1);
//        cout << flag << endl;
        if (flag == 1) {
//            cout << i+1 << endl;
            total++;
        }
//        return 0;
    }
    
    cout << total << endl;
    
    return 0;
}

