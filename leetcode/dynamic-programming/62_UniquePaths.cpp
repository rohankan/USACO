// Dynamic programming.
class Solution {
public:
    int uniquePaths(int m, int n) {
        int dp[100][100];
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = 1;
                } else if (i == 0) {
                    dp[i][j] = dp[i][j-1];
                } else if (j == 0) {
                    dp[i][j] = dp[i-1][j];
                } else {
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                }
            }
        }
        
        return dp[m-1][n-1];
    }
};

// Pascal's triangle / binomial theorem.
class Solution {
public:
    int choose(int n, int k) {
        cout << n << " " << k << endl;
        if (k > n || k == 0) return 1; // modified combination.

        if (k*2 > n) {
            k = n-k;
        }

        long long result = n;

        for (int i = 2; i <= k; ++i) {
            result *= (n-i+1);
            result /= i;
        }

        return (int) result;
    }

    int uniquePaths(int m, int n) {
        // Pascal's triangle / binomial theorem.
        if (n > m) {
            swap(n, m);
        }

        return choose(m+n-2, n-1);
    }
};

