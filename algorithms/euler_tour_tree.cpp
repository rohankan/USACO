
const int MAX_N = 100000;

int eulertour[MAX_N*2];
int eulerindex = 0;
vector<int> paths[MAX_N];

void make_tour(int cur, int par) {
    eulertour[eulerindex++] = cur;
    
    for (auto p : paths[cur]) {
        if (p == par) continue;
        make_tour(p, cur);
    }
    
    eulertour[eulerindex++] = cur;
}

