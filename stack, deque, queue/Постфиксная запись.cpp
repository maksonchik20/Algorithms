#include <bits/stdc++.h>
using namespace std;

int main() {
    stack<int> st;
    string s;
    while (cin >> s) {
        if (s == "+") {
            int one = st.top();
            st.pop();
            int two = st.top();
            st.pop();
            st.push(one + two);
        } else if (s == "-") {
            int one = st.top();
            st.pop();
            int two = st.top();
            st.pop();
            st.push(two - one);
        } else if (s == "*") {
            int one = st.top();
            st.pop();
            int two = st.top();
            st.pop();
            st.push(one * two);
        } else {
            int n = stoi(s);
            st.push(n);
        }
    }
    cout << st.top() << endl;
    return 0;
}