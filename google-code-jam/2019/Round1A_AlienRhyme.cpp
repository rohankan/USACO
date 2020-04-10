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

//unordered_set<int, custom_hash> s;

const int TRIECHARMAX = 26;

int charkey(char c) {
    return c-'A';
}


struct Node {
    string s;
    int total;
    unordered_map<char, Node*> children;
    
    Node(string val) {
        s = val;
        total = 0;
    }
    
    void insert(string val) {
        if (val.size() == 0) {
            total++;
            return;
        }
        
        char c = val.at(0);
        
        if (!contains(c)) {
            children[c] = new Node(val.substr(0, 1));
        } 
        
        children[c]->insert(val.substr(1));
    }
    
    Node* find(string s) { // does not account for when the string is not in the trie.
        Node* cur = this;
        int n = (int) s.size();
        
        for (int i = 0; i < n; i++) {
            cur = cur->children[s[0]];
            if (cur->s == s) {
                return cur;
            }
            s = s.substr(1);
        }
        return nullptr;
    }
    
    bool contains(char c) {
        return children.find(c) != children.end();
    }
};

Node trie("");

int pairs = 0;

ipair dfs(Node* n) { // <number, leftovers>
    if (n->children.size() == 0) {
        int t = n->total;
        
        if (t >= 2) {
            return {1, t-2};
        } else {
            return {0, t};
        }
    }
    
    int leftovers = n->total;
    int total = 0;
    
    for (auto it = n->children.begin(); it != n->children.end(); it++) {
        auto p = dfs(it->second);
        total += p.first;
        leftovers += p.second;
    }
    
    if (n->s == "") {
        return {total, leftovers};
    }
    
    if (leftovers >= 2) {
        return {total + 1, leftovers-2};
    } else {
        return {total, leftovers};
    }
}

void solve() {
    int n;
    cin >> n;
    
    Node trie("");
    
    fori(n) {
        string s;
        cin >> s;
        string a;
        rev(j, s.size()-1) {
            a += s[j];
        }
        trie.insert(a);
    }
    
    cout << dfs(&trie).first*2 << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    
    return 0;
}


