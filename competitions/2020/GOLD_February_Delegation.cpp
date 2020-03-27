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
vector<int> paths[100000];
bool visited[100000];
vector<int> leaves;

const int MAX_N = 100000;
const int MAX_D = 17; // = floor(maximum_depth) + 1 (typically maximum_depth = log2(MAX_N))
// 2 ^ MAX_D is roughly MAX_N.

int depth[MAX_N];
int parent[MAX_N][MAX_D];

void dfs(int cur, int par) {
    int total = 0;
    
    for (auto p : paths[cur]) {
        if (p == par) continue;
        depth[p] = depth[cur] + 1;
        parent[p][0] = cur;
        dfs(p, cur);
        total++;
    }
    
    if (total == 0) {
        leaves.push_back(cur);
    }
}

//bool bfs(int size) {
//    queue<int> q;
//    
//    for (auto l : leaves){
//        q.push(l);
//    }
//    
//    while (!q.empty()) {
//        
//    }
//}

bool flag = false;
int dasize;
int sset[100001];

int ldfs(int cur, int par, int depth) {
    //handle starting node later.
//    fori(depth) {
//        cout << "  ";
//    }
//    cout << cur+1 << " " << par+1 << " -> " << endl;;
    int size = paths[cur].size();
    
    int ret = 0;
    
    if (par == -1 || size > 2)  
    {
//        unordered_set<int> s;
        vector<int> vals;
        for (auto p : paths[cur]) {
            if (p == par) continue;
            int v = ldfs(p, cur, depth+1);
            vals.push_back(v);
//            vals.push_back(ldfs(p, cur));
        }
        
        for (auto v : vals) {
            sset[v]++;
        }
        
//        if (cur == 7) {
//            
//        }
        
        int badcount = vals.size();
        int badsize = -1;
        
        for (auto v : vals) {
            if (v == 0) {
                badcount--;
                sset[0]--;
                continue;
            }
            if (sset[v] == 0) {
                continue;
            }
            
            if (dasize % 2 == 0 && v == dasize/2) {
                if (sset[v] == 1) {
                    badsize = v;
//                    flag = true;
//                    cout << "A: " <<  v << endl;
//                    ret = 0;
//                    break;
                } else {
                    sset[v] -= 2;
                    badcount -= 2;
                }
            } else {
                if (sset[dasize-v] >= 1) {
                    badcount -= 2;
                    sset[v]--;
                    sset[dasize-v]--;
                } else {
                    badsize = v;
                }
//                else {
//                }
            }
        }
        
//        if (cur == 3) {
//            
//        }
        
        for (auto v : vals) {
            sset[v] = 0;
        }
        
        if (!flag) {
            if (badcount > 1) {
//                cout<< "bad" << " " << badcount <<endl;
                flag = true;
                ret = 0;
            } else if (badcount == 1) {
                ret = badsize;
//                cout << "badsize: " << ret << endl;
            } else {
//                cout << dasize << endl;
//                cout << "badcount: " << badcount << endl;
                ret = 0;
            }
        }
        
        if (par != -1) {
            ret += 1;
        }
    } 
    else if (size == 2) 
    {
        for (auto p : paths[cur]) {
            if (p != par) {
                int val = 1 + ldfs(p, cur, depth+1);
//                cout << val << endl;
                ret = val % dasize;
                break;
            }
        }
    } 
    else //size == 1
    {
        ret = 1;
    } 
    
//    fori(depth) {
//        cout << "  ";
//    }
//    cout << size << " " << ret % dasize << endl;
//    cout << ret << endl;
    return ret % dasize;
}

bool root_dfs(int i) {
    fori(n+1) {
        sset[i] = 0;
    }
    dasize = i;
    flag = false;
    
    int val = ldfs(0, -1, 0);
    
//    cout << i << " " << val << " " << flag << endl;
    
//    cout << "::" << val << " " << flag<< endl;
    
    return !flag && (val % dasize == 0);
}

int main() {
    set_IO("deleg");
    
    cin >> n;
    int a, b;
    fori(n-1) {
        cin >> a >> b;
        a--; b--;
        paths[a].push_back(b);
        paths[b].push_back(a);
    }
    
//    dfs(0, -1);
//    depth_dp();
    
    
//    for (auto l : leaves) {
//        cout << l << endl;
//    }
    
    int numedges = n-1;
    
    cout << 1; // 1 is always possible.
    for (int i = 2; i < numedges+1; i++) {
        if (numedges % i != 0) {
            cout << 0;
            continue;
        }
        
        if (root_dfs(i)) {
            cout << 1;
        } else {
            cout << 0;
        }
        
//        return 0;
    }
    
    return 0;
}

