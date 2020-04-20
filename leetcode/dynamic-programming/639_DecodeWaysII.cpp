class Solution {
public:
    int numDecodings(string s) {
        vector<long> dp(s.size()+1);
        dp[0] = 1;
        
        for (int i = 1; i < s.size()+1; i++) {
            char first = s[i-1];
            
            if (first != '0') {
                if (first == '*') dp[i] += dp[i-1]*9;
                else dp[i] += dp[i-1];
            }
            
            if (i-2 < 0) continue;
            
            string dbl = s.substr(i-2, 2);
            
            if (dbl[0] == '*' && dbl[1] == '*') 
            {
                dp[i] += dp[i-2]*15;
            } 
            else if (dbl[0] == '*') 
            {
                if (dbl[1]-'0' <= 6) dp[i] += dp[i-2]*2;
                else dp[i] += dp[i-2];
            } 
            else if (dbl[1] == '*') 
            {
                if (dbl[0] == '1') dp[i] += dp[i-2]*9;
                else if (dbl[0] == '2') dp[i] += dp[i-2]*6;
            } 
            else 
            {
                int val = stoi(dbl);
                if (val >= 10 && val <= 26) dp[i] += dp[i-2];
            }
            
            dp[i] %= 1000000007;
            
            // cout << i << " " << dp[i] << endl;
        }
        
        return (int) dp[s.size()];
    }
};

