int n;
string S, s;
vector<int> m;
void manacher() {
    s.clear();
    s.resize(2 * n + 1, '.');
    for (int i = 0, j = 1; i < n; i++, j += 2) s[j] = S[i];
    m.clear();
    m.resize(2 * n + 1, 0);
    // m[i] := max k such that s[i-k, i+k] is palindrome
    int mx = 0, mxk = 0;
    for (int i = 1; i < 2 * n + 1; i++) {
        if (mx - (i - mx) >= 0) m[i] = min(m[mx - (i - mx)], mx + mxk - i);
        while (0 <= i - m[i] - 1 && i + m[i] + 1 < 2 * n + 1 &&
               s[i - m[i] - 1] == s[i + m[i] + 1]) m[i]++;
        if (i + m[i] > mx + mxk) mx = i, mxk = m[i];
    }
}
void init() {
    cin >> S;
    n = (int)S.size();
}
void solve() {
    manacher();
    int mx = 0, ptr = 0;
    for (int i = 0; i < 2 * n + 1; i++)
        if (mx < m[i]) {
            mx = m[i];
            ptr = i;
        }
    for (int i = ptr - mx; i <= ptr + mx; i++)
        if (s[i] != '.') cout << s[i];
    cout << endl;
}
