// Binary-indexed tree, or fenwick tree.

int n; // Size of binary-indexed tree.
int bitree[100000];  // Indexes start from 1. Index 0 is a dummy node.


void update_tree(int j, int val) { 
    for (; j <= n; j += (j&-j)) {
        bitree[j] += val;
    }
}

int prefix_sum(int j) { 
    int sum = 0; 
    for (; j > 0; j -= (j&-j)) {
        sum += bitree[j]; 
    }
    return sum; 
}

