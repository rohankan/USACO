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

int r, c, k;
int arr[750][750];
int prefix[750][750];
int appears[750*750+1];
int counts[750][750];

int main() {
    set_IO("hopscotch");
    
    cin >> r >> c >> k;
    fori(r) {
        forj(c) {
            cin >> arr[i][j];
        }
    }
    
//    fori(r) {
//        forj(c) {
//            prefix[i][j] = -appears[arr[i][j]];
//            appears[arr[i][j]]++;
//        }
//    }
//    
//    fori(r) {
//        forj(c) {
//            cout << (prefix[i][j] >= 0 ? " " : "") << prefix[i][j] << " ";
//        }
//        cout << endl;
//    }
    
    counts[0][0] = 1;
    
    for (int i = 1; i < r; i++) {
        for (int j = 1; j < c; j++) {
            int val = arr[i][j];
            
            if (val != arr[0][0]) {
                counts[i][j]++;
            }
            
            int addon = counts[i][j];
            
            for (int k = i+1; k < r; k++) {
                for (int p = j+1; p < c; p++) {
                    if (arr[k][p] != val) {
                        counts[k][p] = (counts[k][p] + addon) % 1000000007;
                    }
                }
            }
//            cout << i << " " << j << " " << arr[i][j] << " " << counts[i][j] << endl;
        }
    }
    
    cout << counts[r-1][c-1] << endl;
    
    return 0;
}

