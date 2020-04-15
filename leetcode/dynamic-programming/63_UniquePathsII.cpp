class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        long dp[100][100];
        
        for (int i = 0; i < obstacleGrid.size(); i++) {
            auto v = obstacleGrid[i];
            
            for (int j = 0; j < v.size(); j++) {
                if (v[j] == 1) {
                    dp[i][j] = 0;
                    continue;
                }
                
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
        
        return dp[obstacleGrid.size()-1][obstacleGrid[0].size()-1];
    }
};

