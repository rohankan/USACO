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
#define FOR(val, n, n2) for(int (val) = (signed)(n); (val) <=(signed)(n2); val++)
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

int n, k;
int arr[10000];
int dp[10000];

int main() {
    set_IO("teamwork");
    
    cin >> n >> k;
    fori(n) cin >> arr[i];
    
    dp[0] = arr[0];
    for (int i = 1; i < n; i++) {
        int maxval = arr[i];
        for (int j = i-1; j >= max(i-k, 0); j--) {
//            cout << "  " << dp[j] + (maxval * (i-j)) << endl;
            dp[i] = max(dp[i], dp[j] + (maxval * (i-j)));
            maxval = max(maxval, arr[j]);
        }
        dp[i] = max(dp[i], (maxval * min(i+1, k)));
//        cout << i << " " << dp[i] << endl;
    }
    
    cout << dp[n-1] << "\n";
    
    return 0;
}

