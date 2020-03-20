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
#define bigval 1000000000
using namespace std;

typedef pair<int, int> ipair;
typedef pair<double, double> dpair;

void set_IO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}

int n, m;
int in_degrees[100000];
int ordering[100000];
vector<ipair> observations[50000];
vector<int> paths[100000];

bool topological_sort(int num_obs) { // Returns whether topological sort is possible.
    fori(n) {
        paths[i].clear();
    }
    
    fori(num_obs) {
        for (auto p : observations[i]) {
            paths[p.first].push_back(p.second);
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (auto p : paths[i]) {
            in_degrees[p]++;
        }
    }
    
    // Replace with priority queue for O(nlog(n)) lexicographical sort instead of O(n). 
    priority_queue<int> q; 
    
    for (int i = 0; i < n; i++) {
        if (in_degrees[i] == 0) {
            q.push(-i);
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (q.empty()) {
            return false; // The graph contains a cycle.
        }
        
        int cur = -q.top();
        q.pop();
        
        ordering[i] = cur;
        
        for (auto p : paths[cur]) {
            in_degrees[p]--;
            
            if (in_degrees[p] == 0) {
                q.push(-p);
            }
        }
    }
    
    return true;
}

int main() {
    set_IO("milkorder");
    
    cin >> n >> m;
    
    fori(m) {
        int o, p, k;
        cin >> o >> p;
        forj(o-1) {
            cin >> k;
            observations[i].push_back({p-1, k-1});
            p = k;
        }
    }
    
    int lo = 0, hi = m+1;
    while (lo+1 < hi) {
        int mid = (lo + hi) / 2;
        
        if (topological_sort(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    
    topological_sort(lo);  // The tipping point is lo.
    
//    cout<< topological_sort(m-1) << endl;
    
    fori(n-1) {
        cout << ordering[i]+1 << " ";
    }
    cout << ordering[n-1]+1 << endl;
        
    return 0;
}

