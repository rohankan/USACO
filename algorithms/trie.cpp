// Trie implementation without path compression. Replace unordered_map with char->int array if needed.

const int TRIECHARMAX = 26;

int charkey(char c) {
    return c-'A';
}


struct Node {
    string s;
    int total;
    unordered_map<char, Node*> children;
    
    Node(string val) {
        s = val;
        total = 0;
    }
    
    void insert(string val) {
        if (val.size() == 0) {
            total++;
            return;
        }
        
        char c = val.at(0);
        
        if (!contains(c)) {
            children[c] = new Node(val.substr(0, 1));
        } 
        
        children[c]->insert(val.substr(1));
    }
    
    Node* find(string s) { // does not account for when the string is not in the trie.
        Node* cur = this;
        int n = (int) s.size();
        
        for (int i = 0; i < n; i++) {
            cur = cur->children[s[0]];
            if (cur->s == s) {
                return cur;
            }
            s = s.substr(1);
        }
        return nullptr;
    }
    
    bool contains(char c) {
        return children.find(c) != children.end();
    }
};

Node trie("");

void printtrie(Node* n, int depth) {
    if (depth > 0) {
        for (int i = 0; i < depth-1; i++) {
            cout << " ";
        }
        cout << n->s << " " << n->total << endl;
    }
    
    for (auto it = n->children.begin(); it != n->children.end(); it++) {
        printtrie(it->second, depth+1);
    }
}
