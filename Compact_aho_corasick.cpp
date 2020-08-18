struct AhoCorasick {
    vector<node> v{node()};
    void insert(string& s, int word_index){
        int id = 0;
        for(auto c:s){
            if(v[id].trie.find(c)==v[id].trie.end()) {
                v.push_back(node(c));
                v[id].trie[c] = (int)v.size() - 1;
            }
            id = v[id].trie[c];
        }
        v[id].is_end = true;
        v[id].word_id = word_index;
    }
    
    void linker() 
    {
        int id=0;
        queue<int> que;
        que.push(id);
        while(!que.empty()) {
            int start_id = que.front();
            que.pop();
            for(auto it:v[start_id].trie) {
                create_links(start_id, it.S, it.F);
                que.push(it.S);
            }
        }
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
    
    bool process(string& s) {
        int id = 0;
        for(auto c:s) {
            // Find proper transition-----------------
            int cur_id = id;
            while(cur_id != -1 && v[cur_id].trie.find(c)==v[cur_id].trie.end()) {
                cur_id = v[cur_id].suffix_link;
            }
            if(cur_id == -1)
            {
                id = 0;
                continue;
            }
            
            // Go through all output links------------
            id = cur_id;
            if(v[v[id].trie[c]].is_end)
                ans[v[v[id].trie[c]].word_id]++;
            id = v[id].trie[c];
            int prev_id = id;
            if(v[id].output_link != -1)
            {
                while(v[id].output_link != -1){
                    ans[v[v[id].output_link].word_id]++;
                    id = v[id].output_link;
                }
            }
            id = prev_id;
        }
    }
};
