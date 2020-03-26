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

int n, m;
vector<int> paths[200000];
unordered_set<int> treepaths[200000];
bool isconnected[200000];
bool visited[200000];
int connected = 0;
int unconnected = 0;

//int numgroups = 0;
//int ufs[200000];  // Initialize by parent to itself.
//
//int ufs_find(int curr) {
//    return ufs[curr] == curr ? curr : (ufs[curr] = ufs_find(ufs[curr]));
//}
//
//void ufs_merge(int x, int y) {
//    numgroups--;
//    ufs[ufs_find(x)] = ufs_find(y);
//}

void dfs(int cur, int par) {
    if (isconnected[cur]) return;
//    ufs_merge(cur, par);
    if (par != -1) {
        treepaths[cur].insert(par);
        treepaths[par].insert(cur);
    }
//    parent[cur] = par;
    isconnected[cur] = true;
    connected++;
    
    for (auto p : paths[cur]) {
        dfs(p, cur);
    }
}

//vector<int> que;
//bool good = false;
//int found = -1;
//
//void dfs_closed(int closed, int cur, int par) {
//    cout << closed+1 << " " << cur+1 << " " << par+1 << endl;
//    for (auto p : paths[cur]) {
//        if (p == par) {
//            continue;
//        } else if (ufs_find(p) != ufs_find(closed)) {
//            if (closed == cur) {
//                continue;
//            } 
//            
//            good = true;
//            found = p;
//            continue;
//        }
//        
//        if (closed == cur && !good) {
//            found = p;
//        }
//        
//        que.push_back(p);
//        
//        dfs_closed(closed, p, cur);
//    }
//}

int main() {
    set_IO("cows");
    
    cin >> n >> m;
    
    int a, b;
    fori(m) {
        cin >> a >> b;
        a--; b--;
        paths[a].push_back(b);
        paths[b].push_back(a);
    }
    
    fori(n) visited[i] = true;
    
//    fori(n) {
//        ufs[i] = i;
//        numgroups++;
//    }
    
    dfs(0, -1);
    
    unconnected = n - connected;
//    cout << unconnected << endl;
    
    if (unconnected == 0) {
        cout << "YES\n";
    }
    
    int q;
    fori(n-1) {
        cin >> q; q--;
        visited[q] = false;
        
        if (!isconnected[q]) {
            unconnected--;
        }
        
        
//        int curpar = ufs_find(q);
//        
//        for (auto p : paths[q]) {
//            int par = -1;
//            for (auto p2 : paths[p]) {
//                if (p2 != q) {
//                    
//                }
//            }
//        }
        
        for (auto c : treepaths[q]) {
            treepaths[c].erase(treepaths[c].find(q));
            
            bool good = false;
            
            for (auto p : paths[c]) {
                if (!visited[p]) continue;
                treepaths[c].insert(p);
                good = true;
            }
            
            if (!good) {
                isconnected[c] = false;
                unconnected++;
            }
        }
        
        cout<< unconnected << endl;
//        cout << unconnected << endl;
        
//        ufs[q] = -1;
//        
//        good = false;
//        que.clear();
//        found = -1;
//        
//        dfs_closed(q, q, -1);
//        
//        cout << good << " " << found << ": ";
//        
//        for (auto i : que) {
//            cout << i+1 << " ";
//            ufs[i] = found;
//        }
//        cout << endl;
//        
//        if (!good) {
//            numgroups++;
//        }
        
        if (i == n-2) {
            cout << "YES\n";
        } else if (unconnected == 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
        
//        for (auto c : paths[q]) {
//            if (closed[c]) continue;
//            
//            bool good = true;
//            if (parent[c] == q) {
//                bool check = false;
//                for (auto c2 : paths[c]) {
//                    if (!closed[c2]) {
//                        parent[c] = c2; // check this!!!
//                        check = true;
//                        break;
//                    }
//                }
//                good = good && check;
//            }
//            
//            
//        }
    }
    
    return 0;
}

