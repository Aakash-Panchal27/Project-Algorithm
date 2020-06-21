long long hash(string& s) {
    int p = 31;
    int m = 1e9 + 9;
    long long Hash = 0;
    long long p_pow = 1;
    for (char c : s) {
        Hash = (Hash + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return Hash;
}


vector<int> Rabin_Karp(string& s, string& p) {
    int p = 31; 
    int m = 1e9 + 9;
    int s_sz = s.size(), p_sz = p.size();

    int mn = max(s_sz, p_sz);
    vector<long long> p_pow(mn);
    p_pow[0] = 1;

    // Precomputation of all powers
    for (int i = 1; i < mn; i++) 
        p_pow[i] = (p_pow[i-1] * p) % m;

    // Prefix sums
    vector<long long> h(s_sz + 1, 0);
    for (int i = 0; i < s_sz; i++)
        h[i+1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;
    
    // Compute hash of s
    long long hash_p = 0;
    for (int i = 0; i < p_sz; i++) 
        hash_p = (hash_p + (p[i] - 'a' + 1) * p_pow[i]) % m;

    vector<int> occurrences_id;
    for (int i = 0; i + p_sz - 1 < s_sz; i++) { 
        long long cur = (h[i+n] + m - h[i]) % m; 
        if (cur == hash_p * p_pow[i] % m)
            occurrences_id.push_back(i);
    }
    return occurrences_id;
}
