int parent[100000];  // Initialize by parent to itself.

int find(int curr) {
    return parent[curr] == curr ? curr : (parent[curr] = find(parent[curr]));
}

void merge(int x, int y) {
    parent[find(x)] = find(y);
}

