
typedef pair<int, pair<int, int>> tripair;

const int MAX_N = 100;

int n;
vector<pair<int, int>> paths[MAX_N];
int parent[MAX_N]; // Gives parent of node in MST.
bool visited[MAX_N];

int prim_mst() {
    priority_queue<tripair, vector<tripair>, greater<tripair>> pq; // <dist to tree, index, par>
    pq.push({0, {0, -1}});
    int mst_size = 0;
    
    while (!pq.empty()) {
        auto p = pq.top();
        int dist = p.first;
        int u = p.second.first, par = p.second.second;
        pq.pop();
        
        if (visited[u]) continue;
        
        visited[u] = true;
        parent[u] = par;
        mst_size += dist;
        
        for (auto p : paths[u]) {
            pq.push({p.second, {p.first, u}});
        }
    }
    
    return mst_size;
}

