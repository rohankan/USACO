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

int n;
long long minflavor;
int flavors[100000];
int spices[100000];
multiset<int> minspices;

int main() {
    set_IO("hayfeast");
    
    cin >> n >> minflavor;
    fori(n) {
        cin >> flavors[i] >> spices[i];
//        cout << flavors[i] << spices[i] << endl;
    }
    
    int lo = -1;
    int hi = -1;
    long long total = 0;
    int minspice = bigval;
    
    while (hi < n || (hi >= n && total >= minflavor)) {
//        cout << lo << " " << hi << " " << total << " " << minspice << endl;
        if (total >= minflavor) {
            lo += 1;
            total -= flavors[lo];
            minspice = min(minspice, *minspices.rbegin());
            minspices.erase(minspices.find(spices[lo]));
        } else {
            hi += 1;
            
            if (hi < n) {
                total += flavors[hi];
                minspices.insert(spices[hi]);
            }
        }
    }
    
    cout << minspice << endl;
    
    return 0;
}

