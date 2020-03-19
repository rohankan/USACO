#include <math.h>
#include <vector>

using namespace std;

typedef pair<int, int> ipair;

const int n = 1000;
vector<ipair> paths[n];
int dists[n][n];

// All-pairs shortest path algorithm.
void floyd_warshall() {
    for (int i = 0; i < n; i++) {
        for (auto p : paths[i]) {
            dists[i][p.first] = p.second;
        }
    }
    
    for (int k = 0; k < n; k++) {  
        for (int i = 0; i < n; i++) {  
            for (int j = 0; j < n; j++) {  
                if (dists[i][k] + dists[k][j] < dists[i][j]) {
                    dists[i][j] = dists[i][k] + dists[k][j];  
                } 
            }  
        }  
    }
}  

