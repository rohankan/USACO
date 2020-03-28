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
typedef pair<pair<int, int>, pair<int, int>> quadpair;
typedef pair<double, double> dpair;

void set_IO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}

int maxgroup = 0;
int sizes[100000];
int ufs[100000];  // Initialize by parent to itself.

int ufs_find(int curr) {
    return ufs[curr] == curr ? curr : (ufs[curr] = ufs_find(ufs[curr]));
}

void ufs_merge(int x, int y) {
    bool addon = ufs_find(x) != ufs_find(y);
    ufs[ufs_find(x)] = ufs_find(y);
    
    if (addon) {
        sizes[ufs_find(y)] += sizes[x];
        maxgroup = max(maxgroup, sizes[ufs_find(y)]);
    }
}

int n, b;
int deep[100001];
unordered_map<int, vector<int>> indexes;
//quadpair shoes[100000];
//int depths[100000];
//int steps[100000];

//bool bin_search(int maxdepth, int step) {
////    int lo = 0;
////    int hi = n-1;
////    
////    while (lo <= hi) {
////        int m = (lo + hi) / 2;
////        
//////        cout << lo << " " << m << " " << hi << " " << arr[m] << " " << val << endl;
////        
////        if (deep[m].first == val) {
////            return m;
////        } else if (val < arr[m]) {
////            hi = m-1;
////        } else {
////            lo = m+1;
////        }
////    }
//    auto it = indexes.upper_bound(maxdepth);
//    
//    cout << maxdepth << " " << step << " " << it->second << endl;
//    
//    if (it == indexes.end()) {
//        return true;
//    }
//    
//    for (int i = it->second; i < n; i++) {
//        cout << deep[i].first << " " << deep[i].second << endl;
//        if (deep[i].second % step == 0) {
//            return false;
//        }
//    }
//    
//    return true;
//}

int arr[100000];
map<int, int> maxes;
//set<int> deep;

int main() {
    set_IO("snowboots");
    
    cin >> n >> b;
    fori(n) {
        int a;
        cin >> a;
        arr[i] = a;
        ufs[i] = i;
        sizes[i] = 1;
        deep[i] = a;
        indexes[a].push_back(i);
    }
    
    sort(deep, deep+n);
    
    maxgroup = 1;
    int lastweight = deep[n-1]+1;
    bool flag = false;
    
    for (int i = n-1; i >= 0; i--) {
        auto vec = indexes[lastweight];
        
//        cout << lastweight << " " << vec.size() << endl;
        
//        int deepval = i != -1 ? deep[i] : -1;
        
//        cout << deep[i].first << " : " << lastweight << endl;
        
        int deepval = deep[i];
        
        if (deepval == lastweight) {
            flag = false;
            continue;
        } else if (!flag && deepval+1 != lastweight) {
            i++;
            deepval = lastweight-1;
            flag = true;
        } else {
            flag = false;
        }
        
        int w = deepval;
        
        for (auto j : vec) {
            if (j+1 < n && arr[j+1] > w) {
                ufs_merge(j, j+1);
            } 
            if (j-1 >= 0 && arr[j-1] > w) {
                ufs_merge(j-1, j);
            }
        }
        
//        cout << w << " " << it->second << " " << lastindex << endl;
        
        maxes[deepval] = maxgroup;
//        cout << deepval << " " << maxgroup << " " << lastweight << endl;
        lastweight = deepval;
//        cout << lastweight << " " << maxgroup << endl;
    }
    
    maxes[deep[n-1]] = 0;
    
//    maxes[0] = n-2;
    
    
    
    int d, s;
    fori(b) {
        cin >> d >> s;
        
        if (maxes.lower_bound(d)->second >= s) {
            cout << 0 << endl;
        } else {
            cout << 1 << endl;
        }
    }
    
//    int depth, step;
//    fori(b) {
////        cin >> depths[i] >> steps[i];
//        cin >> depth >> step;
//        
//        shoes[i] = {{depth, step}, {-1, i}};
//        
////        cout << bin_search(depth, step) << endl;
//    }
//    
//    sort(shoes, shoes+b, [](quadpair a, quadpair b) {return a.first.first > b.second.first;});
//    
//    int lastindex = n;
//    fori(b) {
//    }
//    
//    sort(shoes, shoes+b, [](quadpair a, quadpair b) {return a.second.second < b.second.second;});
//    
//    fori(b) {
//        cout << shoes[i].second.first << endl;
//    }
//    
////    fori(n) {
////        cout << deep[i].first << " " << deep[i].second << endl;
////    }
    
    return 0;
}

