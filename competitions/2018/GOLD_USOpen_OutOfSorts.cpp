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

int n;
ipair arr[1000001];

int bitree[1000001];  // Indexes start from 1. Index 0 is a dummy node.

void update_tree(int j, int val) { 
    for (; j <= n; j += (j&-j)) {
        bitree[j] += val;
    }
}

int prefix_sum(int j) { 
    int sum = 0; 
    for (; j > 0; j -= (j&-j)) {
        sum += bitree[j]; 
    }
    return sum; 
}

int main() {
    set_IO("sort");
    
    cin >> n;
    fori(n) {
        int a;
        cin >> a;
        arr[i+1] = {a+1, i+1};
    }
    
    sort(arr+1, arr+n+1);
    
    int most = 0;
    for (int i = 1; i < n+1; i++) {
        update_tree(arr[i].second, 1);
        most = max(most, i - prefix_sum(i));
    }
    
    cout << max(most, 1) << endl;
    
    return 0;
}

