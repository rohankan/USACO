const int MAX_N = 100;

tripair edges[10000]; // <weight, <from, to>>
int nedges;
int nnodes;
int parent[MAX_N];
int ufs[MAX_N];  // Initialize by parent to itself.

int ufs_find(int curr) {
    return ufs[curr] == curr ? curr : (ufs[curr] = ufs_find(ufs[curr]));
}

void ufs_merge(int x, int y) {
    ufs[ufs_find(x)] = ufs_find(y);
}

int kruskal_mst() {
    sort(edges, edges+nedges);
    
    for (int i = 0; i < nnodes; i++) {
        ufs[i] = i;
    }
    
    int mst_size = 0;
    
    for (int i = 0; i < nedges; i++) {
        auto edge = edges[i];
        int weight = edge.first;
        int from = edge.second.first, to = edge.second.second;
        
        if (ufs_find(from) != ufs_find(to)) {
            ufs_merge(from, to);
            parent[to] = from;
            mst_size += weight;
        }
    }
    
    return mst_size;
}

