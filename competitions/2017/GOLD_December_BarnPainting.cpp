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
#define bigval 2147483647
using namespace std;

typedef pair<int, int> ipair;
typedef pair<double, double> dpair;

void set_IO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}

struct Barn {
    int color = -1;
    vector<int> paths;
};

const int MOD = 1000000007;

Barn barns[100000];
int numbarns, numcolored;
long dp[100000][3];

long solve(int curNode, int curCol, int parNode) {
//    cout << curNode << " " << curCol << " " << parNode << endl;
    auto barn = barns[curNode];
    
    if (barn.color != -1 && barn.color != curCol) {
        return 0;
    }
    
    if (dp[curNode][curCol] != -1) {
        return dp[curNode][curCol];
    }
    
    dp[curNode][curCol] = 1;
    
    for (auto p : barn.paths) {
        if (p == parNode) continue;
        
        int total = 0;
        
        forval(c, 3) {
            if (c == curCol) continue;
            
            total += solve(p, c, curNode);
            total %= MOD;
        }
        
        dp[curNode][curCol] = (dp[curNode][curCol] * total) % MOD;
    }
    
//    cout << dp[curNode][curCol] << endl;
    
    return dp[curNode][curCol];
}

int main() {
    set_IO("barnpainting");
    
    cin >> numbarns >> numcolored;
    
    fori(numbarns-1) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        barns[a].paths.push_back(b);
        barns[b].paths.push_back(a);
    }
    
    fori(numbarns) {
        forj(3) {
            dp[i][j] = -1;
        }
    }
    
    fori(numcolored) {
        int c, a;
        cin >> c >> a;
        barns[c-1].color = a-1;
    }
    
    cout << (solve(0, 0, -1) + solve(0, 1, -1) + solve(0, 2, -1)) % MOD << endl;
    
    return 0;
}

