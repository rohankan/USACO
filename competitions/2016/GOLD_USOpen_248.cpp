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
int arr[249];
int dp[249][249];

int main() {
    set_IO("248");
    
    cin >> n;
    fori(n) cin >> arr[i];
    
    int ret = 0;
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            
            if (i == j) {
                dp[i][j] = arr[i];
                continue;
            }
            
            for (int k = i; k < j; k++) {
                if (dp[i][k] == dp[k+1][j] && dp[i][k] > 0) {
                    dp[i][j] = dp[i][k] + 1;
                }
            }
            
//            cout << i << " " << j << " " << dp[i][j] << endl;
            
            ret = max(ret, dp[i][j]);
        }
    }
    
    cout << ret << endl;
    
    return 0;
}

