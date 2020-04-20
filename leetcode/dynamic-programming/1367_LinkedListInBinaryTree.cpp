/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

bool check(ListNode* ll, TreeNode* node) {
    if (ll == NULL) {
        return true;
    } else if (node == NULL) {
        return false;
    }
    
    if (node->val == ll->val) {
        return check(ll->next, node->left) || check(ll->next, node->right);
    } 
    
    return false;
}

bool dfs(ListNode* ll, TreeNode* node) {
    if (node == NULL) {
        return false;
    } else if (check(ll, node)) {
        return true;
    }
    
    return dfs(ll, node->left) || dfs(ll, node->right);
}

class Solution {
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        return dfs(head, root);
    }
};

