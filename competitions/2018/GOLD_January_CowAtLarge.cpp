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

// Look at the BIT problem in holder.cpp!!!!

int n, k;
vector<int> paths[100000];
int anc[100000];
vector<int> succ[100000];
vector<int> farmernodes;
int states[100000];

void dfs(int par, int cur) {
    for (auto child : paths[cur]) {
        if (child == par) continue;
        anc[child] = cur;
        succ[cur].push_back(child);
        dfs(cur, child);
    }
    
    if (paths[cur].size() == 1) {
        farmernodes.push_back(cur);
    }
}

int main() {
    set_IO("atlarge");
    
    cin >> n >> k;
    fori(n-1) {
        int a, b;
        cin >> a >> b;
        paths[a-1].push_back(b-1);
        paths[b-1].push_back(a-1);
    }
    
    anc[k-1] = -1;
    dfs(-1, k-1);
    
//    cout << farmernodes.size() << "\n";
    vector<int> bessie;
    
    bessie.push_back(k-1);
    
    int requiredfarmers = (int) farmernodes.size();
    
    while (true) {
//        cout << "bcur: " ;
        for (auto b : bessie) {
//            cout << b+1 << " ";
            states[b] = 1;
        }
//        cout << "\n";
//        
//        cout << "farmers: ";
        bool quit = true;
        for (int i = 0; i < farmernodes.size(); i++) {
            auto f = farmernodes[i];
            auto a = anc[f];
            
            if (f == -1 || a == -1) {
                farmernodes[i] = -1;
                continue;
            }
//            cout << f+1 << " ";
            quit = false;
            
            if (states[a] == 1) { // Bessie was there.
                states[a] = 3;
                farmernodes[i] = -1;
            } else if (states[a] == 2) { // Farmer was there.
                requiredfarmers--;
                farmernodes[i] = -1;
            } else if (states[a] == 3) { 
                farmernodes[i] = -1;
            } else {
                farmernodes[i] = a;
                states[a] = 2;
            }
        }
//        cout << "\n";
        
        if (quit) {
            break;
        }
        
        vector<int> nextbessie;
        for (auto b : bessie) {
            for (auto child : succ[b]) {
                if (states[child] == 0) {
                    nextbessie.push_back(child);
                }
            }
        }
        bessie = nextbessie;
    }
    
    cout << requiredfarmers << endl;
    
    return 0;
}

