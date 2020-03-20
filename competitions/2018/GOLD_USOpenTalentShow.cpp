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

struct Cow {
    int weight;
    int talent;
};

int n, w;
Cow cows[250];
ipair dp[251][1001];

double divide(int a, int b) {
    if (b == 0) {
        return 0;
    }
    return a*1.0 / b;
};

ipair maxpair(ipair a, ipair b) {
    if (divide(a.first, a.second) > divide(b.first, b.second)) {
        return a;
    } 
    return b;
}

int main() {
    set_IO("talent");
    
    cin >> n >> w;
    int a, b, largest = -1;
    fori(n) {
        cin >> a >> b;
        cows[i] = {a, b};
        largest = max(largest, cows[i].weight);
    }
    
    sort(cows, cows+n, [](Cow a, Cow b) {
        return divide(a.talent, a.weight) > divide(b.talent, b.weight); 
    });
    
    int wlim = w + largest;
    
    ipair best_pair = {0, 0};
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= wlim; j++) {
            auto cow = cows[i-1];
            
            if (j - cow.weight > w) {
                continue;
            } 
            
            ipair asdf;
            
            if (0 <= j - cow.weight && j - cow.weight <= w) {
                ipair p = dp[i-1][j-cow.weight];
                asdf = {p.first + cow.talent, p.second + cow.weight};
                
                if (asdf.second != j) {
                    asdf = {0, 0};
                }
            }
            
            if (j <= w) {
                ipair one = dp[i-1][j];
                asdf = maxpair(one, asdf);
                
                if (asdf.second != j) {
                    asdf = {0, 0};
                }
                
                dp[i][j] = asdf;
            } 
            
            if (j >= w && (j - w) < cow.weight) {
                best_pair = maxpair(best_pair, asdf);
            }
        }
//        cout << endl;
    }
    
//    cout << best_pair.first << " " << best_pair.second << endl;
    
    cout << (int) (divide(best_pair.first, best_pair.second) * 1000) << endl;
        
    return 0;
}

