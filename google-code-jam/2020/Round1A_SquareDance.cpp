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
#include <chrono>
#include <utility>
#include <array>
#include <bitset>
#define fori(n) for(int i = 0; i < n; i++) 
#define forj(n) for(int j = 0; j < n; j++) 
#define fork(n) for(int k = 0; k < n; k++) 
#define rev(val, stop) for (int (val) = (int) (stop); val >= 0; val--)
#define f0r(val, start, stop) for(int (val) = (start); (val) < (stop); val++)

using namespace std;

typedef pair<int, int> ipair;
typedef pair<double, double> dpair;
typedef pair<int, pair<int, int>> tripair;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (std::pair<T1, T2> const &pair) const {
        std::size_t h1 = std::hash<T1>()(pair.first);
        std::size_t h2 = std::hash<T2>()(pair.second);
        
        return h1 ^ h2;
    }
};

//unordered_set<int, custom_hash> s;

int operations[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int r, c;
//long modr, modc;

//long tokey(long i, long j) {
//    if (r > c) {
//        return i*modr + j;
//    } else {
//        return j*modc + i;
//    }
//}
//
//ipair topair(long key) {
//    if (r > c) {
//        return {key/modr, key%modr};
//    } 
//    return {key%modc, key/modc};
//}

void solve() {
    cin >> r >> c;
    vector<vector<int>> arr(r);
    vector<set<int>> rows(r);
    vector<set<int>> cols(c);
//    vector<vector<unordered_set<ipair>>> mappings;
    long long total = 0;
    long long ans = 0;
    
    set<int> s;
    fori(c) s.insert(i);
    fori(r) rows[i] = s;
    
    s.clear();
    fori(r) s.insert(i);
    fori(c) cols[i] = s;
    
    unordered_set<ipair, pair_hash> changes;
    
    fori(r) {
        vector<int> v(c);
        forj(c) {
            int k;
            cin >> k;
            v[j] = k;
            total += k;
            changes.insert({i, j});
        }
        arr[i] = v;
    }
    
//    if (r*c == 100000) {
//        cout << 45 << "\n";
//        return;
//    }
    
//    fori(r) {
//        forj(c) {
//            double avg = 0;
//            int size = 0;
//            fork(4) {
//                int a = i + operations[k][0], b = j + operations[k][1];
//                if (a < 0 || b < 0 || a >= r || b >= c) {
//                    continue;
//                }
//                avg += arr[a][b];
//                size++;
//            }
//            
//            if (arr[i][j]*size < avg) {
//                rows[i].erase(j);
//                cols[j].erase(i);
//                fork(4) {
//                    int a = i + operations[k][0], b = j + operations[k][1];
//                    if (a < 0 || b < 0 || a >= r || b >= c) {
//                        continue;
//                    }
//                    cout << a << " " << b << endl;
//                    changes.insert(tokey(a, b));
//                }
//            }
//        }
//    }
    
    ans += total;
    
//    cout << "answer: " << ans << " " << changes.size() << endl; 
    do {
        unordered_set<ipair, pair_hash> nextchanges;
        
        vector<ipair> erasures;
        
        for (auto it = changes.begin(); it != changes.end(); it++) {
//            ipair p = topair(*it);
            int i = (*it).first, j = (*it).second;
            
            auto rit = rows[i].find(j);
            auto cit = cols[j].find(i);
            
//            if (rit == rows[i].end() || cit == cols[j].end()) {
//                continue;
//            }
            
//            cout << "it: " << i << " " << j << " " << (*rit) << " " << (*cit) << endl;
            
            vector<ipair> vals;
            if (rit != rows[i].begin()) {
                vals.emplace_back(i, *prev(rit));
            }
            auto n = next(rit);
            if (n != rows[i].end()) {
                vals.emplace_back(i, *n);
            }
            if (cit != cols[j].begin()) {
                vals.emplace_back(*prev(cit), j);
            }
            auto n2 = next(cit);
            if (n2 != cols[j].end()) {
                vals.emplace_back(*n2, j);
            }
            
            int tot = 0;
            for (ipair p : vals) {
//                cout << p.first << " " << p.second << endl;
                tot += arr[p.first][p.second];
            }
            
//            cout << vals.size() << " " << tot << endl;
            
            if (arr[i][j] * vals.size() < tot) {
                for (auto p : vals) {
                    nextchanges.insert(p);
                }
                erasures.emplace_back(i, j);
                total -= arr[i][j];
            }
        }
        
        for (ipair p : erasures) {
            int i = p.first, j = p.second;
//            cout << arr[i][j] << endl;
            rows[i].erase(j);
            cols[j].erase(i);
            auto it = nextchanges.find(p);
            if (it != nextchanges.end()) {
                nextchanges.erase(it);
            }
        }
        
        if (nextchanges.empty()) {
            break;
        }
        
        ans += total;
        
        changes = nextchanges;
    } while (!changes.empty());
    
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cout << "Case #" << i+1 << ": ";
        solve();
//        int cor;
//        cin >> cor; 
//        
//        if (cor == -1) {
//            break;
//        }
    }
    
    return 0;
}

