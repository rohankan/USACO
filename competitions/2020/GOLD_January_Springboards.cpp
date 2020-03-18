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

int n, p;
map<int, int> m;
vector<pair<pair<int, int>, pair<int, int>>> points;
int ans[100001];

void ins(int y, int val) {
    auto it = prev(m.upper_bound(y));
    if (it->second < val) {
        return;
    }
    
    it++;
    while (it != m.end() && it->second > val) m.erase(it++);
    m[y] = val;
}

int main() {
    set_IO("boards");
    
    m[0] = 0;
    
    cin >> n >> p;
    fori(p) {
        ipair a, b;
        cin >> a.first >> a.second >> b.first >> b.second;
        points.push_back({a, {i, 1}}); // start point
        points.push_back({b, {i, -1}}); // end point
    }
    
    sort(points.begin(), points.end()); // Lexicographical sort by x.
    
//    ans[points[0].second.first]
//    m[points[0].first.second] = points[0].first.first + points[0].first.second;
    
    for(auto point : points) {
        if (point.second.second == 1) { // start point
            auto it = prev(m.upper_bound(point.first.second));
            ans[point.second.first] = it->second + point.first.first + point.first.second;
        } else { // end point
//            cout << point.first.second << endl;
            ins(point.first.second, ans[point.second.first] - point.first.first - point.first.second);
        }
    }
    
//    cout << m.rbegin()->first << " " << m.rbegin()-> second << endl;
    cout << m.rbegin()->second + 2*n << endl;
    
    return 0;
}

