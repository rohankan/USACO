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

int n, m, c;
int noearlier[100000];
int earliest[100000];
//int purported[100000];
vector<ipair> memories[100000];
vector<int> memories2[100000];
int dependson[100000];

//41 mins.

unordered_set<int> good;

int main() {
    set_IO("timeline");
    
    cin >> n >> m >> c;
//    int minearlier = 0;
    fori(n) {
        cin >> noearlier[i];
//        if (noearlier[i] < noearlier[minearlier]) {
//            minearlier = i;
//        }
    }
    
//    cout << minearlier << endl;
//    earliest[minearlier] = noearlier[minearlier];
    
    fori(c) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        memories[b].push_back({a, c});
        memories2[a].push_back(b);
        dependson[b]++;
    }
    
    fori(n) {
//        st_update(i, dependson[i]);
//        mmap[dependson[i]].insert(i);
        if (dependson[i] == 0) {
            good.insert(i);
        } 
//        else {
////            notgood.insert(i);
//        }
    }
    
    for (int r = 0; r < n; r++) {
//        int cur = mmap[0].
        int cur = *good.begin();
        
        good.erase(good.begin());
//        int cur = mmap[0];// st_query(0, n-1);
//        fori(n) {
//            if (dependson[i] == 0) {
//                cur = i;
//                dependson[i] = -1;
//                break;
//            }
//        }
        
        int res = noearlier[cur];
        for (auto m : memories[cur]) {
            res = max(res, earliest[m.first] + m.second);
        }
        
        for (auto m : memories2[cur]) {
            dependson[m]--;
            
            if (dependson[m] == 0) {
                good.insert(m);
            }
//            mmap[dependson]
//            st_update(m, dependson[m]);)
//            mmap.find(
        }
        
        earliest[cur] = res;
    }
    
    fori(n) {
        cout << earliest[i] << endl;
    }
    
    return 0;
}

