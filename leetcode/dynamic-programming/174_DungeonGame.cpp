class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        vector<vector<int>> dp = dungeon;
        int n = dungeon.size(), m = dungeon[0].size();
        
        // cout << n << " " << m << endl;
        
        for (int i = n-1; i >= 0; i--) {
            for (int j = m-1; j >= 0; j--) {
                if (i == n-1 && j == m-1) {
                    dp[i][j] = max(1, 1 - dungeon[i][j]);
                } else if (i == n-1) {
                    dp[i][j] = max(1, dp[i][j+1] - dungeon[i][j]);
                } else if (j == m-1) {
                    dp[i][j] = max(1, dp[i+1][j] - dungeon[i][j]);
                } else {
                    dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j]);
                }
                // cout << i << ' ' << j << ' ' << dp[i][j] << endl;
            }
        }
        
        return dp[0][0];
    }
};

