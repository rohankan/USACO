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

int n, m, k;
int arr[100001];
int dp[100001];
int graph[26][26];
int dists[26][26];
int conversions[100001][26];
int minconvs[100001];

void floyd_warshall() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            dists[i][j] = graph[i][j];
        }
    }
    
    for (int k = 0; k < m; k++) {  
        for (int i = 0; i < m; i++) {  
            for (int j = 0; j < m; j++) {  
                if (dists[i][k] + dists[k][j] < dists[i][j]) {
                    dists[i][j] = dists[i][k] + dists[k][j];  
                } 
            }  
        }  
    }
}

int minconv(int i, int j) {
    int minval = 1e8;
    
    if (i-1 < 0) {
        fork(m) {
            minval = min(minval, conversions[j][k]);
        }
    } else {
        fork(m) {
            minval = min(minval, conversions[j][k] - conversions[i-1][k]);
        }
    }
    
    return minval;
}

int main() {
    set_IO("cowmbat");
    
    cin >> n >> m >> k;
    fori(n) {
        char c;
        cin >> c;
        arr[i] = c-'a';
    }
    
    fori(m) {
        forj(m) {
            cin >> graph[i][j];
        }
    }
    
    floyd_warshall();
    
    fill(begin(dp), begin(dp)+n+1, 1e8);
    
    dp[0] = 0;
    
    fori(m) {
        conversions[0][i] = dists[arr[0]][i];
    }
    
    fori(m) {
        for (int j = 1; j < n; j++) {
            conversions[j][i] = conversions[j-1][i] + dists[arr[j]][i];
        }
    }
    
    int conversions[26];
    
    fill(begin(conversions), begin(conversions)+m, 0);
    
    for (int i = 1; i < n+1; i++) {
        
        dp[i] = min(dp[i], dp[0] + minconv(0, i-1));
        for (int j = k; j <= i-k; j++) {
            dp[i] = min(dp[i], dp[j] + minconv(j, i-1));
//            cout << " " << dp[j] << " " << minconv(j, i-1) << " " << dp[i] << endl;
        }
        
//        cout << i << " " << dp[i] << endl;
//        forj(m) {
//            conversions[i][j] = conversions[i-1][j]
//        }
        
//        for (int x = 0; x <= i-k; x++) {
//            dp[i] = min(dp[i], dp[x] + conversions(x+1, i));
//        }
    }
    
    cout << dp[n] << endl;
    
    return 0;
}

