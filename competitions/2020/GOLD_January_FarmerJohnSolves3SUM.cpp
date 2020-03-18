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
#define bigval 100000000
using namespace std;

typedef pair<int, int> ipair;
typedef pair<double, double> dpair;

void set_IO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}

int n, q;
int arr[5000];
long long answers[5001][5001];
int hmap[2000001];

int main() {
    set_IO("threesum");
    
    cin >> n >> q;
    fori(n) cin >> arr[i];
    
    fori(n) {
        for (int j = i+1; j < n; j++) {
            int idx = 1000000 - arr[i] - arr[j];
            
            if (idx >= 0 && idx < 2000001) {
                answers[i][j] = hmap[idx];
            }
            
            hmap[1000000+arr[j]]++;
        }
        
        for (int j = i+1; j < n; j++) {
            hmap[1000000+arr[j]]--;
        }
        
//        for (int k = 1000000-10; k < 1000000+20; k++) {
//            cout << hmap[k];
//        }cout << endl;
    }
    
//    fori(n) {
//        forj(n) {
//            cout << answers[i][j] << " ";
//        }
//        cout << endl;
//    }
    
    for (int i = n-1; i >= 0; --i) {
        for (int j = i+1; j < n; ++j) {
            answers[i][j] += answers[i+1][j] + answers[i][j-1] - answers[i+1][j-1];
        }
    }
    
    int a, b;
    fori(q) {
        cin >> a >> b;
        cout << answers[a-1][b-1] << endl;
    }
    
    return 0;
}

