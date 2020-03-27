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

const long MOD = 1000000007;

int n;
ipair segments[100001];
int rightpoints[200002];
int overlaps = 0;

// 2hrs. 10 mins.

//int num_overlaps(int i) {
//    auto seg = segments[i];
//    auto it = rightpoints.lower_bound(seg.first);
//    
//    cout << rightpoints.end()
//    
////    cout << i << " : " << *it << endl;
////    cout << seg.second << endl;
//    
//    int num = 0;
//    while (it != rightpoints.end()) {
//        num++;
//        it++;
//    }
//    
////    cout << num << endl;
//    
//    return num;
//}

long pows[100002];

int main() {
    set_IO("help");
    
    cin >> n;
    fori(n) {
        int a, b;
        cin >> a >> b;
        segments[i] = {a, b};
    }
    
    pows[0] = 1;
    fori(n+1) {
        pows[i+1] = (pows[i] * 2) % MOD;
    }
    
    sort(segments, segments+n);
    
    long ans = 1;
    rightpoints[segments[0].second]++;
    overlaps++;
    
    int prevleft = segments[0].first;
    
    for (int i = 2; i < n+1; i++) {
        int curleft = segments[i-1].first;
        
        for (int j = prevleft; j < curleft; j++) {
            overlaps -= rightpoints[j];
        }
//        cout << "i: " << i << " " << num_overlaps(i) << endl;
//        int prevval = dp[i-1];
//        dp[i] = prevval + 1 + (i - num_overlaps(i-1)) * (dp[i-1] + i);
//        dp[i] = prevval + 1 + (dp[i-1] + pows[i-1-(num_overlaps(i-1))] - 1);
        ans = (((2 * ans) % MOD) + pows[i-1-overlaps]) % MOD;
        
//        if (dp[i] < 0) {
//            dp[i] += MOD;
//        }
//        dp[i] %= MOD;
        
        rightpoints[segments[i-1].second]++;
        overlaps++;
//        cout << num_overlaps(i) << endl;
//        cout << pows[i-1] << " " << pows[num_overlaps(i)] << " " << dp[i] << endl;
//        cout << dp[i] << endl;
//        rightpoints.insert(segments[i-1].second);
        prevleft = curleft;
    }
    
    cout << ans << endl;
    
    return 0;
}

