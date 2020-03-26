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

int numgroups = 0;
int ufs[200000];  // Initialize by parent to itself.
int u[200000];
int v[200000];

int ufs_find(int curr) {
    return ufs[curr] == curr ? curr : (ufs[curr] = ufs_find(ufs[curr]));
}

void ufs_merge(int x, int y) {
    numgroups--;
    ufs[ufs_find(x)] = ufs_find(y);
}

int removal[200000];
int order[200000];
bool ans[200000];

int main() {
    set_IO("closing");
    
    cin >> n >> m;
    fori(m) {
        cin >> u[i] >> v[i];
        u[i]--; v[i]--;
    }
    
    fori(n) {
        cin >> removal[i];
        removal[i]--;
        order[removal[i]] = i;
        ufs[i] = i;
    }
    
    fori(m) {
        if (order[u[i]] > order[v[i]]) {
            paths[v[i]].push_back(u[i]);
        } else {
            paths[u[i]].push_back(v[i]);
        }
    }
    
    int numcomponents = 0;
    
    for (int i = n-1; i >= 0; i--) {
        auto node = removal[i];
        numcomponents++;
        
        for (auto p : paths[node]) {
//            cout << p << endl;
            if (ufs_find(p) != ufs_find(node)) {
                ufs_merge(node, p);
                numcomponents--;
            }
        }
        
//        cout << node << " " << numcomponents << endl;
        
        ans[i] = (numcomponents == 1);
    }
    
    fori(n) {
        if (ans[i]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}

