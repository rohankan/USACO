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
#include <unordered_map>
#include <list>
#include <string>
#include <string.h>
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
#define bigval 100000000
using namespace std;

typedef pair<int, int> ipair;
typedef pair<double, double> dpair;

void set_IO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}

int main() {
    
    return 0;
}

int n, m, c;
int moonies[2000];
vector<ipair> roads;

long long dp[1001][2001];

int main() {
//    set_IO("cows");
    set_IO("time");
    
    cin >> n >> m >> c;
    fori(n) cin >> moonies[i];
    int a, b;
    fori(m) {
        cin >> a >> b;
        roads.push_back({a-1, b-1});
    }
    
    long long max_money = 0;
    
    fori(1001) {
        memset(dp[i], -1, sizeof dp[i]);
    }
    dp[0][0] = 0;
    
    for (int i = 1; i < 1001; i++) {
        int alt = i % 2;
        
        memset(dp[alt], -1, sizeof dp[alt]);
        for (auto road : roads) {
            if (dp[1-alt][road.first] == -1) continue;
            
            dp[alt][road.second] = max(dp[alt][road.second], dp[1-alt][road.first] + moonies[road.second]);
            
//            if (dp[alt][road.second] > 0 && road.second == 0) {
//                cout << road.first << " " << dp[1-alt][road.first] << endl;
//            }
        }
        
//        cout << alt << " " << dp[alt][0] << " " << dp[alt][0] - i * i * c << endl;
        max_money = max(max_money, dp[alt][0] - i * i * c);
    }
    
    cout << max_money << endl;
    
    return 0;
}

