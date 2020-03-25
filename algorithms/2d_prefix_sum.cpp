// Inclusion/exclusion-based 2D prefix sums.
const int MAX_N = 201;

int n;
int arr[MAX_N][MAX_N];

int rectangle_sum_dimens(int a, int b, int x, int y) { 
    return arr[a+x][b+y] - arr[a][b+y] - arr[a+x][b] + arr[a][b];
}

int rectangle_sum_coords(int a, int b, int a2, int b2) { 
    int x = a2 - a, y = b2 - b;
    return arr[a+x][b+y] - arr[a][b+y] - arr[a+x][b] + arr[a][b];
}

int prefix_sum_2d() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                continue;
            }  
            
            if (i == 0) {
                arr[i][j] = arr[i][j] + arr[i][j-1];
            } else if (j == 0) {
                arr[i][j] = arr[i][j] + arr[i-1][j];
            } else {
                arr[i][j] = arr[i][j] + arr[i-1][j] + arr[i][j-1] - arr[i-1][j-1];
            }
        }
    }
}

