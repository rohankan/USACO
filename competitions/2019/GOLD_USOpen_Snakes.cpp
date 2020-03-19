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

int n, k;
int m[401];
int dp[401][401];

int main() {
    set_IO("snakes");
    
    cin >> n >> k;
    
    
    fori(n) cin >> m[i+1];
    
    dp[0][0] = 0;
    int max_group = 0;
    for (int i = 1; i < n+1; i++) {
        max_group = max(max_group, m[i]);
        dp[i][0] = max_group * i;
//        cout << i << " " << dp[i][0] << endl;
    }
    
    for (int i = 1; i < n+1; i++) {
        for (int j = 1; j < k+1; j++) {
            int max_group = m[i];
            int min_val = bigval;
            for (int a = i-1; a >= 0; a--) {
                min_val = min(min_val, dp[a][j-1] + (i-a)*max_group);
                max_group = max(max_group, m[a]);
            }
            
//            cout << i << " " << j << " " << min_val << " -" << endl;
            
            dp[i][j] = min_val;
        }
    }
    
    long long total = 0;
    for (int i = 1; i < n+1; i++) {
        total += m[i];
    }
    
//    cout << dp[n][k] << endl;
//    cout << total << endl;
    
    cout << dp[n][k] - total << endl;
        
    return 0;
}

