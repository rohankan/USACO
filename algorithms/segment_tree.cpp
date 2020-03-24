// Segment tree that performs range minimum queries.

int segtree[MAX_N * 4];

void st_update(int idx, int l, int r, int i, int v) {
    if (l == r) {
        segtree[idx] = v;
        return;
    }
    
    int m = (l+r)/2;
    if (i <= m) {
        st_update(2*idx, l, m, i, v);
    } else {
        st_update(2*idx+1, m+1, r, i, v);
    }
    
    segtree[idx] = min(segtree[2*idx], segtree[2*idx+1]);
}

void st_update(int i, int v) {
    st_update(1, 0, MAX_N-1, i, v);
}

int st_query(int idx, int l, int r, int lhs, int rhs) {
    if (l >= lhs && r <= rhs) return segtree[idx];
    
    int ret = INT_MAX;
    int m = (l+r)/2;
    
    if (m >= lhs) {
        ret = min(ret, st_query(2*idx, l, m, lhs, rhs));
    }
    
    if (m+1 <= rhs) {
        ret = min(ret, st_query(2*idx+1, m+1, r, lhs, rhs));
    }
    
    return ret;
}

int st_query(int l, int r) {
    return st_query(1, 0, MAX_N-1, l, r);
}

