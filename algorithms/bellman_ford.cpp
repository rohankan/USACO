#define INF 2147483640

typedef pair<int, pair<int, int>> tripair;

const int MAX_N = 100000;

int n;
vector<tripair> edges; // <weight, <from, to>>
int dist[MAX_N];
int parent[MAX_N];

// Returns whether there is a negative cycle.
bool bellman_ford(int src) {
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    
    dist[src] = 0;
    
    for (int i = 1; i < n; i++) {
        for (auto edge : edges) {
            auto w = edge.first;
            int from = edge.second.first, to = edge.second.second;
            
            if (dist[from] + w < dist[to]) {
                dist[to] = dist[from] + w;
                parent[to] = from;
            }
        }
    }
    
    for (auto edge : edges) {
        auto w = edge.first;
        int from = edge.second.first, to = edge.second.second;
        
        if (dist[from] + w < dist[to]) {
            return true; // Negative cycle.
        }
    }
    
    return false; // No negative cycle.
}

