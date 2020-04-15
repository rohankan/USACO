/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

int best;

int dfs(TreeNode* cur, int depth) {
    if (cur == NULL) {
        return 0;
    }
    
    int left = dfs(cur->left, depth+1);
    int right = dfs(cur->right, depth+1);
    
    // cout << cur->val << " " << left << " " << right << endl;
    
    if (left + right > best) {
        best = left + right;
    }
    
    return max(left, right) + 1;
}

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        best = 0;
        dfs(root, 0);
        return best;
    }
};

