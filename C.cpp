#include<bits/stdc++.h>
using namespace std;
 
#define ll long long 
#define pb push_back
#define rloop(n) for(long long i=n-1;i>=0;i--)
#define pb push_back
#define ll long long 
#define vi vector<int>
#define vl vector<ll>
#define vs vector<string>
#define FAST ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
 
signed main(){
    FAST;
    int t;
    cin >> t;
    while (t--) {
        long long n, k;
        cin >> n >> k;
        long long arr[n];
        for(long long i = 0; i < n; i++) {
            cin >> arr[i];
        }
        long long last = n-1;
        long long result = 0;
        for(long long i = 0; i < n; i++) {
            if (arr[i] == arr[0]) {
                result++;
            }
            if (result == k) {
                last = i;
                break;
            }
        }
        if (result < k){
            cout << "NO" << endl;
            continue;
        } else {
            if(arr[0] == arr[n - 1]){
                cout << "YES" << endl;
                continue;
            }
        }
         
        result = 0;
        for (int i = n - 1; i > last; i--){
            if(arr[i] == arr[n - 1]) {
                result++;
            }
        }
         
        if(result >= k) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}