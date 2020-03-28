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
typedef pair<pair<int, int>, pair<int, int>> quadpair;
typedef pair<double, double> dpair;

void set_IO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}

const int MAX_N = 100000;
const int MAX_D = 17;

int n;
vector<int> paths[MAX_N];
long numleaves[MAX_N];
int initiallength = 0;
bool isfolder[MAX_N];
long names[MAX_N];
//int depth[MAX_N];

void dfs(int cur, int par) {
    int leaves = 0;
    
    for (auto p : paths[cur]) {
        if (p == par) continue;
//        depth[p] = depth[cur] + 1;
        dfs(p, cur);
        leaves += numleaves[p];
    }
    
    if (paths[cur].size() == 1 && par != -1) {
        numleaves[cur] = 1;
        initiallength += names[cur];
    } else {
        numleaves[cur] = leaves;
        
        if (par != -1) {
            initiallength += (names[cur] + 1) * numleaves[cur]; //for the slash.
        }
    }
}

long long minval = 1e18;
void dfs2(int cur, int par, long long score, long headerleaves) {
    if (!isfolder[cur]) return;
    
    minval = min(minval, score);
//    cout << cur+1 << " " << score << endl;
    
    for (auto p : paths[cur]) {
        if (p == par || !isfolder[p]) continue;
        
        long leavessum = headerleaves;
        for (auto o : paths[cur]) {
            if (o == par || o == p) continue;
            leavessum += numleaves[o];
        }
        
//        cout << " " << p+1 << " " << leavessum << " " << numleaves[p] << " " << names[cur] << endl;
        dfs2(p, cur, score + (leavessum * 3) - (numleaves[p] * (names[p] + 1)), leavessum);
    }
}

int main() {
    set_IO("dirtraverse");
    
    cin >> n;
    string s;
    int m;
    fori(n) {
        cin >> s;
        names[i] = (int) s.size();
        cin >> m;
        
        isfolder[i] = (m != 0);
        
        forj(m) {
            int a;
            cin >> a;
            a--;
            paths[i].push_back(a);
            paths[a].push_back(i);
        }
    }
    
    dfs(0, -1);
    
//    cout << initiallength << endl;
    
//    fori(n) {
//        cout << numleaves[i] << endl;
//    }
    
    dfs2(0, -1, initiallength, 0);
    
    cout << minval << endl;
    
    return 0;
}

