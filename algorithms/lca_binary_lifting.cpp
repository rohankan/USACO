// Calculates the LCA of any two nodes in a tree using DFS, DP for parents of a node,
// and binary lifting to efficiently compute LCA in O(log(n)) time.

const int MAX_N = 100000;
const int MAX_D = 17; // = floor(maximum_depth) + 1 (typically maximum_depth = log2(MAX_N))
// 2 ^ MAX_D is roughly MAX_N.

int depth[MAX_N];
int parent[MAX_N][MAX_D];
vector<int> paths[MAX_N];

void dfs(int cur, int par) {
    for (auto p : paths[cur]) {
        if (p == par) continue;
        depth[p] = depth[cur] + 1;
        parent[p][0] = cur;
        dfs(p, cur);
    }
}

void depth_dp() {
    for (int d = 1; d < MAX_D; d++) {
        for (int i = 0; i < MAX_N; i++) {
            parent[i][d] = parent[parent[i][d-1]][d-1];
        }
    }
}

int get_LCA(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    
    for (int d = MAX_D-1; d >= 0; d--) {
        if (depth[a] - (1<<d) >= depth[b]) {
            a = parent[a][d];
        }
    }
    
    for (int d = MAX_D-1; d >= 0; d--) {
        if (parent[a][d] != parent[b][d]) {
            a = parent[a][d];
            b = parent[b][d];
        }
    }
    
    if (a != b) {
        a = parent[a][0];
        b = parent[b][0];
    }
    
    return a;
}

