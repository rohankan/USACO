#include <math.h>
#include <vector>

using namespace std;

int dijkstras(int source, int dest, int **graph, int n) {
    vector<int> distances(n);
    vector<int> visited(n);
    
    for (int i = 0; i < n; i++) {
        distances[i] = INFINITY;
    }
    distances[source] = 0;
    
    // Setting the next node to follow.
    for (int i = 0; i < n; i++) {
        int current = -1;
        
        for (int j = 0; j < n; j++) {
            if (visited[j]) {
                continue;
            }
            
            if (current == -1 || distances[j] < distances[current]) {
                current = j;
            }
        }
        
        visited[current] = true;
        for (int j = 0; j < n; j++) {
            int path = distances[current] + graph[current][j];
            if (path < distances[j]) {
                distances[j] = path;
            }
        }
    }
    
    return distances[dest];
}

#include <queue>

typedef pair<int, int> ipair;
vector<ipair> paths[100]; 

int dijkstras(int src, int dest, int n) {
    priority_queue<ipair, vector<ipair>, greater<ipair>> pq;
    vector<int> dist(n, 100000);
    pq.push({0, src});
    dist[src] = 0;
    
    while (!pq.empty()) {
        int u = pq.top().second; pq.pop();
        
        for (auto item : paths[u]) {
            int i = item.first, distance = item.second;
            
            if (dist[u] + distance < dist[i]) {
                dist[i] = dist[u] + distance;
                pq.push({dist[i], i});
            }
        }
    }
    
    return dist[dest];
}


