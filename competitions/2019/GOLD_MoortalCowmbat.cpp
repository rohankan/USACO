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
#define F0R(val, n) for(int val = 0; val < n; val++)
#define F1R(val, n) for(int val = n-1; val > -1; val--)
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
int dp[100001][26];
int mindp[100001];
int graph[26][26];
int dists[26][26];
int conversions[100001][26];

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
    
    fori(m) {
        conversions[0][i] = 0;
    }
    
    fori(m) {
        for (int j = 0; j < n; j++) {
            conversions[j+1][i] = conversions[j][i] + dists[arr[j]][i];
//            cout << j+1 << " " << i << " " << conversions[j+1][i] << " " << arr[j] << " " << dists[arr[j]][i] << endl;
        }
    }
    
    fori(n+1) {
        forj(m) {
            dp[i][j] = 1e9;
        }
    }
    
//    fori(m) {
//        dp[0][i] = 0;
//    }
    
    fori(n+1) {
        mindp[i] = 1e9;
    }
    mindp[0] = 0;
    
    for (int i = 1; i < n+1; i++) {
        forj(m) {
            dp[i][j] = min(dp[i][j], dp[i-1][j] + dists[arr[i-1]][j]);
            if (i-k >= 0) {
                dp[i][j] = min(dp[i][j], conversions[i][j] - conversions[i-k][j] + mindp[i-k]);
            }
            mindp[i] = min(mindp[i], dp[i][j]);
        }
    }
    
    cout << mindp[n] << endl;
    
    return 0;
}

