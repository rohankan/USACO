/*
 ID: rohanka3
 PROG: agrinet
 LANG: C++11
 */

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

//const int MAX_N = 249;
//int arr[MAX_N];
int n;

// 0-initial, 1-rundown, 2-merge.
//void dfs(int idx, int par, int command) {
//    if (command == 0) {
//        if (arr[idx-1] == arr[idx]) {
//            
//        }
//    }
//    
//    dfs(idx+1);
//    dfs(idx-1);
//}

int main() {
    set_IO("248");
    
    cin >> n;
    vector<int> v;
    int best = 0;
    
    v.resize(n);
    fori(n) {
        cin >> v[i];
        best = max(best, v[i]);
    }
    
    queue<pair<vector<int>, int>> q;
    q.push({v, 0});
    
    while (!q.empty()) {
        auto v = q.front().first; auto idx = q.front().second; q.pop();
        
        if (v.size() == 1) continue;
        
//        cout << idx << " | ";
//        for (auto p : v) {
//            cout << p << " ";
//        }cout << endl;
        
        int prevadd = -1;
        int start = -1;
        int stop = -1;
        
        for (int i = ((idx == 0) ? 0 : idx-1); i <= v.size(); i++) {
//            if (v[i] == 0) continue;
            
//            if (v[i] == v[i+1] && (v[i] != prevadd || (evencheck && i % 2 == 0) || (oddcheck && (i-1) % 2 == 0))) {
//                vector<int> v2 = v;
//                prevadd = v[i];
//                if (i % 2 == 0) {
//                    evencheck = false;
//                } else {
//                    oddcheck = false;
//                }
//                v2[i+1] = v2[i]+1;
//                v2.erase(v2.begin()+i);
//                best = max(best, v2[i]);
//                q.push({v2, i});
//            }
            
//            cout << start << " " << prevadd << endl;
            
//            cout << start << " " << stop << endl;
            
            if (i != v.size() && v[i] == v[i+1]) {
                if (start == -1) {
                    prevadd = v[i];
                    start = i;
                }
            } else if (start != -1) {
                stop = i;
                
                int size = (stop - start) + 1;
                
                if (size % 2 == 0) {
                    vector<int> nxt = v;
                    
                    nxt.erase(nxt.begin(), nxt.begin()+size/2);
                    
                    fori(size/2) {
                        nxt[i] = prevadd+1;
                    }
                    
                    q.push({nxt, 0});
                } else {
                    vector<int> nxt = v;
                    
                    nxt.erase(nxt.begin(), nxt.begin()+size/2+1);
                    
                    fori(size/2) {
                        nxt[i] = prevadd+1;
                    }
                    
                    q.push({nxt, 0});
                    
                    // Resetting.
                    nxt = v;
                    
                    nxt.erase(nxt.begin()+size/2+1, nxt.begin()+stop);
                    nxt.erase(nxt.begin());
                    
                    fori(size/2) {
                        nxt[i] = prevadd+1;
                    }
                    
                    q.push({nxt, 0});
                }
                
                best = max(best, prevadd+1);
                
                start = stop = prevadd = -1;
            }
        }
        
//        cout << q.size() << endl;
    }
//    cout << biggest << endl;
    cout << best << endl;
    
    return 0;
}

