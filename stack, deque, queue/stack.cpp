#include <bits/stdc++.h>
using namespace std;

int main() {
    stack<int> st;
    string type;
    cin >> type;
    if (type == "exit") {
        cout << "bye";
        return 0;
    }
    int n;
    while (type != "exit") {
        if (type == "push") {
            cin >> n;
            st.push(n);
            cout << "ok" << "\n";
        } else if (type == "pop") {
            if (st.size() == 0) {
                cout << "error" << "\n";
            } else {
                cout << st.top() << "\n";
                st.pop();
            }
        } else if (type == "back") {
            if (st.size() == 0) {
                cout << "error" << "\n";
            } else {
                cout << st.top() << "\n";
            }
        } else if (type == "size") {
            cout << st.size() << "\n";
        } else if (type == "clear") {
            cout << "ok" << "\n";
            st = stack<int>();
        }
        cin >> type;
    }
    cout << "bye";
    return 0;
}