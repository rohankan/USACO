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

int n, m, k;
int arr[100000];
int temp[100000];
int farr[100000];
int diffs[100000];
bool visited[100000];
vector<vector<int>> cycles;

int calc_idx(int cycle_idx, int cur, int repeats) {
    return cycles[cycle_idx][(cur+repeats) % cycles[cycle_idx].size()];
}

int main() {
    set_IO("swap");
    
    cin >> n >> m >> k;
    fori(n) {
        arr[i] = i+1;
        temp[i] = i+1;
    }
    fori(m) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        
        for (int j = l; j < (l+r)/2+1; j++) {
            int k = r - (j - l);
            swap(temp[j], temp[k]);
        }
    }
    
    fori(n) {
        diffs[temp[i]-1] = i - (temp[i]-1);
    }
    
//    fori(n) {
//        cout << diffs[i] << " ";
//    }cout << endl;
//    
//    forj(n) {
//        cout << temp[j] << " ";
//    }cout << endl;
    
    fori(n) {
//        cout << "I: " << i << " " << visited[i] << endl;
        if (visited[i]) continue;
        
        visited[i] = true;
//        cout << i << " ";
        
        vector<int> v;
        v.push_back(i);
        int j = i + diffs[i];
        while (!visited[j]) {
            visited[j] = true;
            v.push_back(j);
            j += diffs[j];
//            cout <<j << " ";
        }
//        cout << endl;
        
        cycles.push_back(v);
    }
    
//    for (auto v: cycles) {
//        for (auto i : v) {
//            cout << i << " ";
//        }cout << endl;
//    }
    
    fori(n) {
        farr[i] = arr[i];
    }
    
    for (int c = 0; c < cycles.size(); c++) {
        auto cycle = cycles[c];
        int repeats = k % cycle.size();
        
//        cout << k << " " << cycle.size() << endl;
        
        if (repeats == 0) continue;
        
        for (int i = cycle.size()-1; i >= 0; i--) {
            int nextidx = calc_idx(c, i, repeats);
            farr[nextidx] = arr[cycle[i]];
        }
        
//        int t = arr[calc_idx(c, cycle.size()-1, repeats)];
//        for (int i = cycle.size()-2; i >= 0; i--) {
//            arr[calc_idx(c, i+1, repeats)] = arr[calc_idx(c, i, repeats)];
//        }
//        arr[calc_idx(c, 0, repeats)] = t;
//        for (int r = 0; r < repeats; r++) {
////            cout << "r: " << repeats << endl;
////            fori(n) {
////                cout << arr[i] << " ";
////            }cout << endl;
//        }
//        else {
//            repeats = (int) cycle.size() - repeats;
//            for (int r = 0; r < repeats; r++) {
//                int t = arr[cycle[0]];
//                for (int i = 1; i < cycle.size(); i++) {
//                    arr[cycle[i-1]] = arr[cycle[i]];
//                }
//                arr[cycle[cycle.size()-1]] = t;
//            }
//        }
    }
    
    fori(n) {
        cout << farr[i] << endl;
    }
    
    return 0;
}


