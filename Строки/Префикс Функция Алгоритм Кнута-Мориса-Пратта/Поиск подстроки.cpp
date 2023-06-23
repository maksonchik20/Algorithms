#include <bits/stdc++.h>

using namespace std;

vector<int> prefix_function(string s) {
	int n = (int) s.length();
	vector<int> pi (n);
	for (int i=1; i<n; ++i) {
		int j = pi[i-1];
		while (j > 0 && s[i] != s[j])
			j = pi[j-1];
		if (s[i] == s[j])  ++j;
		pi[i] = j;
	}
	return pi;
}

int main() {
    string s, t;
    cin >> s >> t;
    string s_pref_func = t + "$" + s;
    vector<int> pf = prefix_function(s_pref_func);
    for (int i = t.size() + 1; i < s_pref_func.size(); i++) {
        if (pf[i] == t.size()) {
            cout << i - 2 * t.size() << " ";
        }
    }
    return 0;
}