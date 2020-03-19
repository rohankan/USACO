#include <vector>

int n, m;
bool visited[100000];
vector<int> paths[100000];
vector<int> ordering;

int pick_unvisited_node() {
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            return i;
        }
    }
    
    return -1;
}

void topological_sort_util(int cur) {
    if (visited[cur]) {
        return;
    }
    
    visited[cur] = true;
    
    for (auto i : paths[cur]) {
        topological_sort_util(i);
    } 
    
    ordering.push_back(cur);
}

void topological_sort() {
    int node = pick_unvisited_node();
    
    while (node != -1) {
        topological_sort_util(node);
        node = pick_unvisited_node();
    }
}

