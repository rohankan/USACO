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

int n;
//long lefts[50000];
//long rights[50000];
ipair rects[50000];

int main() {
    set_IO("split");
    
    long maxx = 0;
    long minx = bigval;
    long maxy = 0;
    long miny = bigval;
    
    cin >> n;
    
    long a, b;
    fori(n) {
        cin >> a >> b;
        rects[i] = {a, b};
        maxx = max(maxx, a);
        minx = min(minx, a);
        maxy = max(maxy, b);
        miny = min(miny, b);
    }
    
//    cout << maxx << " " << minx << " " << maxy << " " << miny << endl;
    long onerectarea = (maxx - minx) * (maxy - miny);
    
//    fori(n) {
//        lefts[i] = -1;
//        rights[i] = -1;
//    }
    
    long tworectarea = 1e18;
    
    sort(rects, rects+n);
    
    int curx = 0;
    int leftminy = bigval;
    int leftmaxy = 0;
    
    int i = 0;
    vector<long> vals;
    while (i < n) {
        leftminy = min(rects[i].second, leftminy);
        leftmaxy = max(rects[i].second, leftmaxy);
        curx = rects[i].first;
        
        while (rects[i].first == rects[i+1].first) {
            leftminy = min(rects[i].second, leftminy);
            leftmaxy = max(rects[i].second, leftmaxy);
            i++;
        }
        
        leftminy = min(rects[i].second, leftminy);
        leftmaxy = max(rects[i].second, leftmaxy);
        
        vals.push_back((curx - minx) * (leftmaxy - leftminy));
//        cout << curx << " " << leftmaxy << " " << leftminy << " " << vals[vals.size()-1] << endl;
        i++;
    }
    
    curx = 0;
    leftminy = bigval;
    leftmaxy = 0;
    
    i = n-1;
    vector<long> vals2;
    while (i >= 0) {
        leftminy = min(rects[i].second, leftminy);
        leftmaxy = max(rects[i].second, leftmaxy);
        curx = rects[i].first;
        
        while (rects[i].first == rects[i-1].first) {
            leftminy = min(rects[i].second, leftminy);
            leftmaxy = max(rects[i].second, leftmaxy);
            i--;
        }
        
        leftminy = min(rects[i].second, leftminy);
        leftmaxy = max(rects[i].second, leftmaxy);
//        cout << curx << " " << leftmaxy << " " << leftminy << endl;
        
//        rights[i] = (maxx - curx) * (leftmaxy - leftminy);
        vals2.push_back((maxx - curx) * (leftmaxy - leftminy));
//        indexes2.push_back(i);
//        cout << rights[i] << endl;
        i--;
    }
    
    for (int i = 0; i < vals.size()-1; i++) {
//        cout << vals[i] << " " << vals2[vals2.size()-i-2] << endl;
        tworectarea = min(tworectarea, vals[i] + vals2[vals2.size()-i-2]);
    }
    
//    cout << tworectarea << endl;
    
    sort(rects, rects+n, [](ipair a, ipair b) {return a.second < b.second;});
//    fori(n) {
//        cout << rects[i].first << " " << rects[i].second << endl;
//    }
    
    int cury = 0;
    int bottomminx = bigval;
    int bottommaxx = 0;
    
    i = 0;
    
    vals.clear();
    while (i < n) {
        bottomminx = min(rects[i].first, bottomminx);
        bottommaxx = max(rects[i].first, bottommaxx);
        cury = rects[i].second;
        
        while (rects[i].second == rects[i+1].second) {
            bottomminx = min(rects[i].first, bottomminx);
            bottommaxx = max(rects[i].first, bottommaxx);
            i++;
        }
        
        bottomminx = min(rects[i].first, bottomminx);
        bottommaxx = max(rects[i].first, bottommaxx);
        
        vals.push_back((cury - miny) * (bottommaxx - bottomminx));
        i++;
    }
    
    cury = 0;
    bottomminx = bigval;
    bottommaxx = 0;
    
    i = n-1;
    vals2.clear();
    while (i >= 0) {
        bottomminx = min(rects[i].first, bottomminx);
        bottommaxx = max(rects[i].first, bottommaxx);
        cury = rects[i].second;
        
        while (rects[i].second == rects[i-1].second) {
            bottomminx = min(rects[i].first, bottomminx);
            bottommaxx = max(rects[i].first, bottommaxx);
            i--;
        }
        
        bottomminx = min(rects[i].first, bottomminx);
        bottommaxx = max(rects[i].first, bottommaxx);
        
        vals2.push_back((maxy - cury) * (bottommaxx - bottomminx));
        i--;
    }
    
    for (int i = 0; i < vals.size()-1; i++) {
        tworectarea = min(tworectarea, vals[i] + vals2[vals2.size()-i-2]);
    }
    
//    cout << onerectarea << " " << tworectarea << endl;
    
    cout << (onerectarea - tworectarea) << endl;
    
    return 0;
}

