int ufs[100];  // Initialize by parent to itself.

int ufs_find(int curr) {
    return ufs[curr] == curr ? curr : (ufs[curr] = ufs_find(ufs[curr]));
}

void ufs_merge(int x, int y) {
    ufs[ufs_find(x)] = ufs_find(y);
}
