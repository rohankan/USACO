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
typedef pair<double, double> dpair;

void set_IO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}

int n, q;

const int MAX_N = 100000;
const int MAX_D = 17; 

int depth[MAX_N];
int parent[MAX_N][MAX_D];
vector<int> paths[MAX_N];
int ents[MAX_N];

void dfs(int cur, int par) {
    for (auto p : paths[cur]) {
        if (p == par) continue;
        depth[p] = depth[cur] + 1;
        parent[p][0] = cur;
        dfs(p, cur);
    }
}

void depth_dp() {
    for (int d = 1; d < MAX_D; d++) {
        for (int i = 0; i < MAX_N; i++) {
            parent[i][d] = parent[parent[i][d-1]][d-1];
        }
    }
}

int get_LCA(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    
    for (int d = MAX_D-1; d >= 0; d--) {
        if (depth[a] - (1<<d) >= depth[b]) {
            a = parent[a][d];
        }
    }
    
    for (int d = MAX_D-1; d >= 0; d--) {
        if (parent[a][d] != parent[b][d]) {
            a = parent[a][d];
            b = parent[b][d];
        }
    }
    
    if (a != b) {
        a = parent[a][0];
        b = parent[b][0];
    }
    
    return a;
}

int segtree[MAX_N * 4];

void st_update(int idx, int l, int r, int i, int v) {
    if (l == r) {
        segtree[idx] = v;
        return;
    }
    
    int m = (l+r)/2;
    if (i <= m) {
        st_update(2*idx, l, m, i, v);
    } else {
        st_update(2*idx+1, m+1, r, i, v);
    }
    
    segtree[idx] = segtree[2*idx] ^ segtree[2*idx+1];
}

void st_update(int i, int v) {
    st_update(1, 0, MAX_N-1, i, v);
}

int st_query(int idx, int l, int r, int lhs, int rhs) {
    if (l >= lhs && r <= rhs) return segtree[idx];
    
    int ret = 0;
    int m = (l+r)/2;
    
    if (m >= lhs) {
        ret ^= st_query(2*idx, l, m, lhs, rhs);
    }
    
    if (m+1 <= rhs) {
        ret ^= st_query(2*idx+1, m+1, r, lhs, rhs);
    }
    
    return ret;
}

int st_query(int l, int r) {
    if (l > r) swap(l, r);
    return st_query(1, 0, MAX_N-1, l, r);
}

int subtreesizes[MAX_N];

void subtreedfs(int cur, int par) {
    int numnodes = 1;
    
    for (auto p : paths[cur]) {
        if (p == par) continue;
        subtreedfs(p, cur);
        numnodes += subtreesizes[p];
    }
    
    subtreesizes[cur] = numnodes;
}

int topchain[MAX_N];
int stindices[MAX_N];
int stindex = 0;

void hld(int cur, int par, int top) {
    topchain[cur] = top;
    stindices[cur] = stindex;
    st_update(stindex, ents[cur]);
    stindex++;
    
    int best = -1;
    
    for (auto p : paths[cur]) {
        if (p == par) continue;
        if (best == -1 || subtreesizes[p] > subtreesizes[best]) {
            best = p;
        }
    }
    
    if (best == -1) return;
    
    hld(best, cur, top);
    
    for (auto p : paths[cur]) {
        if (p == par || p == best) continue;
        hld(p, cur, p);
    }
}

int hld_query_util(int child, int par) {
    int ret = 0;
    while(child != par) {
        if(topchain[child] == child) { 
            ret ^= ents[child];
            child = parent[child][0];
        }
        else if(depth[topchain[child]] > depth[par]) {
            ret ^= st_query(stindices[topchain[child]], stindices[child]);
            child = parent[topchain[child]][0];
        }
        else {
            ret ^= st_query(stindices[par]+1, stindices[child]);
            break;
        }
    }
    return ret;
}

int hld_query(int l, int r) {
    int lca = get_LCA(l, r);
    return hld_query_util(l, lca) ^ hld_query_util(r, lca) ^ ents[lca];
}

int main() {
    set_IO("cows");
    
    cin >> n >> q;
    fori(n) cin >> ents[i];
    
    fori(n-1) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        paths[a].push_back(b);
        paths[b].push_back(a);
    }

    dfs(0, -1);
    depth_dp();
    subtreedfs(0, -1);
    hld(0, -1, 0);
    
    fori(q) {
        int a, b, c;
        cin >> a >> b >> c;
        
        if (a == 1) {
            b--;
            st_update(stindices[b], c);
            ents[b] = c;
        } else {
            b--; c--;
            int lca = get_LCA(b, c);
            cout << (hld_query(b, lca) ^ hld_query(c, lca) ^ ents[lca]) << endl;
        }
    }
    
    return 0;
}

