class Solution {
public:
    int numDecodings(string s) {
        vector<int> dp(s.size()+1);
        dp[0] = 1;
        
        for (int i = 1; i < s.size()+1; i++) {
            if (s[i-1] - '0' != 0) {
                dp[i] += dp[i-1];
            }
            
            if (i-2 >= 0) {
                int val = stoi(s.substr(i-2, 2));
                
                if (val >= 10 && val <= 26) {
                    dp[i] += dp[i-2];
                }
            }
            
//             for (int l = 1; l <= 26; l++) {
//                 string num = to_string(l);
                
//                 int idx = i - (int) num.size();
                
//                 // cout << num.size() << endl;
//                 // cout << i << " " << l << " " << num << " " << (i-(int) num.size()) << endl;
                
//                 if (idx < 0) {
//                     break;
//                 } else if (s.substr(idx, num.size()) != num) {
//                     continue;
//                 }
                
//                 dp[i] += dp[idx];
//             }
            
            // cout << i << " " << dp[i] << endl;
        }
        
        return dp[s.size()];
    }
};

