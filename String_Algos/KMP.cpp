vector<int> prefix_function(string& s) {
    int m = (int)s.size();
    
    vector<int> pf(m);
    
    for (int i = 1; i < m; i++) {
        int k = pf[i-1];
        while (k > 0 && s[i] != s[k])
            k = pf[k-1];
        if (s[i] == s[k])
            k++;
        pf[i] = k;
    }
    return pf;
}

int main()
{
    string s,p;
    s = "abbbabab";
    p = "ab";
    int n = s.size(), m = p.size();

    // To save memory concatenate
    // s in p
    p += "#";
    p += s;
    // p = "ab#abbbabab";
    vector<int> pi = prefix_function(p);

    // p = "ab#abbbabab";
    //         ^
    //        m+1
    cout << "occurences in `s` at the following indices: ";
    for(int i = m + 1; i < pi.size(); i++) {
        if(pi[i] == m) {
            cout << i - 2 * m << " ";
        }
    }
    
    return 0;
}
