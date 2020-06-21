vector<int> z_function(string s) {
    int n = (int) s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        // Take advantage of previous value
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        
        // Now do it usual brute-force way
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        
        // Set new range [l,r]
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
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
    vector<int> z = z_function(p);

    // p = "ab#abbbabab";
    //         ^
    //        m+1
    cout << "occurences in s at the following indices: ";
    for(int i = m + 1; i < z.size(); i++) {
        if(z[i] == m) {
            cout << i - m - 1 << " ";
        }
    }
    
    return 0;
}
