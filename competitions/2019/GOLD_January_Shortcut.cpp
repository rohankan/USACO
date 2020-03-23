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
typedef pair<double, double> dpair;

void set_IO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}

int n, m, t;
int numcows[10000];
int parents[10000];
long long cowsvisited[10000];
vector<ipair> paths[10000];

typedef pair<long long, int> item;

long long dijkstras() {
    int src = 0; // barn is #1.
    priority_queue<item, vector<item>, greater<item>> pq;
    vector<long long> dist(n, LONG_MAX);
    pq.push({0, src});
    dist[src] = 0;
    
    fill(begin(parents), end(parents), -1);
    
    while (!pq.empty()) {
        int u = pq.top().second; pq.pop();
        
        for (auto item : paths[u]) {
            int i = item.first, distance = item.second;
            
            long long newdist = dist[u] + distance;
            
            if (newdist < dist[i] || (newdist == dist[i] && parents[i] > u)) {
                parents[i] = u;
                dist[i] = newdist;
                pq.push({dist[i], i});
            } 
        }
    }
    
//    fori(n) {
//        childs[i] = dchilds[i].size() > 0 ? *dchilds[i].begin() : -1;
//        hasparent[childs[i]] = true;
//    }
    
//    fori(n) {
//        cout << i +1<< ": ";
//        cout << parents[i]+1 << " ";
//        cout << dist[i] << " ";
//        cout << endl;
//    }
    
    fori(n) {
        int k = i;
        while (k != -1) {
            cowsvisited[k] += numcows[i];
            k = parents[k];
        }
    }
    
//    int totaltime = 0;
//    fori(n) {
//        totaltime += numcows[i] * dist[i];
//    }
//    
//    queue<ipair> q;
//    fori(n) {
////        cout << i+1 << " " << hasparent[i] << endl;
//        if (!hasparent[i]) {
//            q.push({i, numcows[i]});
//        }
//    }
//    
//    int firstones = (int) q.size();
//    // BFS.
//    while (!q.empty()) {
//        auto p = q.front(); q.pop();
//        auto i = p.first; auto ncows = p.second;
//        
//        bool wasnotvisited = cowsvisited[i] == 0;
//        
//        if (cowsvisited[i] == 0 && firstones <= 0) {
//            cowsvisited[i] = numcows[i] + ncows;
//        } else {
//            cowsvisited[i] += ncows;
//            firstones--;
//        }
//        
//        auto c = childs[i];
//        
//        if (c == -1) continue;
//        
//        if (wasnotvisited) { // avoid double-counting.
//            q.push({c, cowsvisited[i]});
//        } else {
//            q.push({c, ncows});
//        }
//    }
    
//    cout << "visits: " << endl;
//    
//    fori(n) {
//        cout << i+1 << " " << cowsvisited[i] << endl;
////        if (cowsvisited[i])
//    }
    
    long long bestimprovement = 0;
    fori(n) {
//        cout << i+1 << " " << dist[i] << " " << t << " " << (dist[i] - t) * cowsvisited[i] << endl;
        bestimprovement = max(bestimprovement, (dist[i] - t) * cowsvisited[i]);
    }
    
    return bestimprovement;
}

int main() {
    set_IO("shortcut");
    
    cin >> n >> m >> t;
    fori(n) cin >> numcows[i];
    fori(m) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;b--;
        paths[a].push_back({b, c});
        paths[b].push_back({a, c});
    }
    
    cout << dijkstras() << endl;
    
    return 0;
}

