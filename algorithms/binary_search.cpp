int arr[100000];

int bin_search(int n, int val) {
    int lo = 0;
    int hi = n-1;
    
    while (lo <= hi) {
        int m = (lo + hi) / 2;
        
        cout << lo << " " << m << " " << hi << " " << arr[m] << " " << val << endl;

        if (arr[m] == val) {
            return m;
        } else if (val < arr[m]) {
            hi = m-1;
        } else {
            lo = m+1;
        }
   }
    
   return -1;
}

bool condition[100000];

int boundary_binary_search(int n) {
    int lo = 0;
    int hi = n+1;
    
    while (lo+1 < hi) {
        int mid = (lo + hi) / 2;
        
        if (condition[mid]) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    
    return lo;
}
