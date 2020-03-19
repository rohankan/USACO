#include <queue>

int in_degrees[100000];
int ordering[100000];
vector<int> paths[100000];

bool topological_sort(int n) { // Returns whether topological sort is possible.
    memset(ordering, -1, n);
    memset(in_degrees, 0, n);
    
    for (int i = 0; i < n; i++) {
        for (auto p : paths[i]) {
            in_degrees[p]++;
        }
    }
    
    // Replace with priority queue for O(nlog(n)) lexicographical sort instead of O(n). 
    priority_queue<int> q; 
    
    for (int i = 0; i < n; i++) {
        if (in_degrees[i] == 0) {
            q.push(-i);
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (q.empty()) {
            return false; // The graph contains a cycle.
        }
        
        int cur = -q.top();
        q.pop();
        
        ordering[i] = cur;
        
        for (auto p : paths[cur]) {
            in_degrees[p]--;
            
            if (in_degrees[p] == 0) {
                q.push(-p);
            }
        }
    }
    
    return true;
}

