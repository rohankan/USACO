
int visited[200000];
vector<int> paths[200000];

//DFS-style floodfill.
int floodfill(int cur) {
    if (visited[cur]) return;
    
    visited[cur] = true;
    
    for (auto p : paths[cur]) {
        floodfill(p);
    }
}

int n;
int visited[10000][10000];
int grid[10000][10000];

//DFS-style floodfill on 2D grid.
int floodfill(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n || visited[x][y]) return;
    
    visited[x][y] = true;
    
    floodfill(x-1, y);
    floodfill(x+1, y);
    floodfill(x, y-1);
    floodfill(x, y+1);
}

