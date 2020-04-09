
const int TRIECHARMAX = 26;

int charkey(char c) {
    return c-'A';
}

struct Node {
    string s;
    int total;
    Node* children[TRIECHARMAX];
    
    Node(string val) {
        s = val;
        for (int i = 0; i < TRIECHARMAX; i++) {
            children[i] = nullptr;
        }
        total = val.empty() ? 0 : 1;
    }
    
    void insert(string& val, int i) {
        if (i == val.size()) {
            return; // already inserted.
        }
        
        total++;
        
        int idx = charkey(val.at(i));
        
        if (!contains(idx)) {
            children[idx] = new Node(val);
            
            if (s.size() > 1) {
                string split = s.substr(1, s.size()-1);
                children[split[0]-'A'] = new Node(split);
            }
        } else {
            children[idx]->insert(val, i+1);
        }
    }
    
    bool contains(int c) {
        return children[c] != nullptr;
    }
};

Node trie("");

