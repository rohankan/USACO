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
typedef pair<double, double> dpair;

void set_IO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}

int numwords, numlines, numsylls;
unordered_map<int, vector<int>> classes;
ipair words[5000];
long possibs[5001];
long dp[100001];
int lines[26];

const int MOD = 1000000007;

void genpossibs() {
    dp[0] = 1;
    
    for (int i = 1; i < numsylls+1; i++) {
        for (int j = 0; j < numwords; j++) {
            auto word = words[j];
            auto cls = word.first, syl = word.second;
            
            if (i - syl < 0) continue;
            
            if (i == numsylls) {
                possibs[cls] = (possibs[cls] + dp[i-syl]) % MOD;
            } else {
                dp[i] = (dp[i] + dp[i-syl]) % MOD;
            }
        }
        
        dp[i] %= MOD;
//        cout << i << " " << dp[i] << endl;
    }
//    cout << endl;
}

long long expon(long base, int power){
    if(power == 0) return 1;
    if(power == 1) return (base + MOD) % MOD;
    long long ans = expon(base,power/2);
    ans = (ans * ans + MOD) % MOD;
    if(power%2 == 1) ans = (ans*base + MOD) % MOD;
    return (ans + MOD) % MOD;
}

long sumofpowers() {
    long product = 1;
    
    for (int i = 0; i < 26; i++) {
        auto val = lines[i];
        
        if (val == 0) continue;
        
        long total = 0;
        
        for (auto it2 = classes.begin(); it2 != classes.end(); it2++) {
            total = (total + expon(possibs[it2->first], val)) % MOD;
        }
        
        product = (product * total) % MOD;
    }
    
    return product;
}

int main() {
    set_IO("poetry");
    
    cin >> numwords >> numlines >> numsylls;
    fori(numwords) {
        int a, b;
        cin >> a >> b;
        classes[b].push_back(a);
        words[i] = {b, a};
    }
    
    genpossibs();
    
    fori(numlines) {
        char c;
        cin >> c;
        lines[c-'A']++;
    }
    
    cout << sumofpowers() << endl;
    
    return 0;
}

