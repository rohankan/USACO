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

int indices[MAX_N][2];
int eulerindex = 0;

void make_tour(int cur, int par) {
    indices[cur][0] = eulerindex+1;
    eulerindex++;
    
    for (auto p : paths[cur]) {
        if (p == par) continue;
        make_tour(p, cur);
    }
    
    indices[cur][1] = eulerindex+1;
    eulerindex++;
}

int bitree[2*MAX_N+1];  

void update_tree(int j, int prevval, int val) { 
    int tmp = j; 
    
    for (j = indices[tmp][0]; j <= n*2; j += (j&-j)) {
        bitree[j] ^= prevval;
        bitree[j] ^= val;
    }
    for (j = indices[tmp][1]; j <= n*2; j += (j&-j)) {
        bitree[j] ^= prevval;
        bitree[j] ^= val;
    }
}

int prefix_sum(int j) { 
    int tot = 0; 
    for (j = indices[j][0]; j > 0; j -= (j&-j)) {
        tot ^= bitree[j]; 
    }
    return tot; 
}

int main() {
    set_IO("cowland");
    
    cin >> n >> q;
    fori(n) cin >> ents[i];
    
    fori(n-1) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        paths[a].push_back(b);
        paths[b].push_back(a);
    }
    
    make_tour(0, -1);
    dfs(0, -1);
    depth_dp();
    
    fori(n) {
        update_tree(i, 0, ents[i]);
    }
    
    fori(q) {
        int a, b, c;
        cin >> a >> b >> c;
        
        if (a == 1) {
            b--;
            update_tree(b, ents[b], c);
            ents[b] = c;
        } else {
            b--; c--;
            cout << (prefix_sum(b) ^ prefix_sum(c) ^ ents[get_LCA(b, c)]) << endl;
        }
    }
    
    return 0;
}

