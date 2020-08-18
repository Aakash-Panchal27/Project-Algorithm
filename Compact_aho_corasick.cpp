struct AhoCorasick {
    vector<node> v{node()};
    void insert(string& s){
        int id = 0;
        for(auto c:s){
            if(v[id].trie.find(c)==v[id].trie.end()) {
                v.push_back(node());
                v[id].trie[c] = (int)v.size() - 1;
                create_links(id, v[id].trie[c], c);
            }
            id = v[id].trie[c];
        }
        v[id].is_end = true;
    }
    
    void create_links(int start_id, int node_id, char c){
        start_id = v[start_id].suffix_link;
        while(start_id != -1 && v[start_id].trie.find(c) == v[start_id].trie.end()) {
            start_id = v[start_id].suffix_link;
        }
        
        // End of suffix_link creation
        if(start_id == -1) 
            v[node_id].suffix_link = 0;
        else
            v[node_id].suffix_link = v[start_id].trie[c];
        
        // Create Output Link
        if(v[v[node_id].suffix_link].is_end)
            v[node_id].output_link = v[node_id].suffix_link;
        else
            v[node_id].output_link = v[v[node_id].suffix_link].output_link;
    }
};
