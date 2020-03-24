//0-1 knapsack problem (dp). Given a list of items, each with a weight and value, choose the 
//optimal combination of items (include / exclude are the only options) to maximize value while
//achieving a particular total weight.

int n;
int requiredweight;
int dp[10001][10001];
int weights[10000];
int values[10000];

int knapsack() { 
    for (int i = 0; i < n+1; i++) { 
        for (int j = 0; j < requiredweight+1; j++) { 
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (weights[i-1] <= j) {
                dp[i][j] = max(values[i-1] + dp[i-1][j-weights[i-1]],  dp[i-1][j]); 
            } else {
                dp[i][j] = dp[i-1][j]; 
            }
        } 
    } 
    
    return dp[n][requiredweight]; 
} 

