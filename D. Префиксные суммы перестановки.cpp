#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define ll long long 
#define vi vector<long long >
#define vl vector<ll>
#define vs vector<string>
#define FAST ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

int main(){
    FAST;
    long long  t;
    cin >> t;
    while(t--){
        long long  n;
        cin >> n;
        vector<long long > arr(n - 1);
        set<long long > st;
        st.insert(n);
        for(long long  i=0; i<n-1; i++){
            cin >> arr[i];
            st.insert(i + 1);
        }
        long long  find_left = 1;
        long long  left = -1;
        if(st.find(arr[0]) != st.end()){
            st.erase(st.find(arr[0]));
        } else {
            if (left == -1) {
                left = arr[0];
            } else {
                find_left = 0;
            }
        }
        for(long long  i = 1; i < n - 1; i++){
            long long  razn = arr[i] - arr[i - 1];
            if(st.find(razn) != st.end()){
                st.erase(st.find(razn));
            } else {
                if(left == -1)
                    left = razn;
                else {
                    find_left = 0;
                    break;
                }
            }
        }
        if(find_left == 0){
            cout << "NO" << "\n";
        } else {
            long long  sum = 0;
            for(long long val : st)
                sum += val;
            if(left == -1){
                long long siquence = n * (n + 1) / 2;
                if (siquence - arr[n - 2] == sum) {
                    cout << "YES" << "\n";
                } else {
                    cout << "NO" << "\n";
                }
            } else {
                if (sum == left) {
                    cout << "YES" << "\n";
                }
                else {
                    cout << "NO" << "\n";
                }
            }
        }
    }
}