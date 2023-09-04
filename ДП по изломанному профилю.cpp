#include <bits/stdc++.h>
using namespace std;

// bool check (string mask, int position) {
//   if (position + 2 < mask.size()) {
//     if ((mask[position] == '/') && (mask[position + 2] == '/')) {
//       return false;
//     }
//   }
//   if (position + 2 < mask.size()) {
//     if ((mask[position] == '/') && (mask[position + 2] == '/')) {
//       return false;
//     }
//   }
// }

int three_to_ten(int number) {
    int result = 0;
    for (int i = 0; number != 0; i++) {
        result += (number % 10) * pow(3, i);
        number /= 10;
    }
    return result;
}
string ten_to_three(int n) {
    int result = 0;
    string s = "";
    while (n > 0) {
        s = (to_string(n%3)) + s;
        n /= 3;
    }
    return s;
}

string give_next(string mask) {
  int cnt = 1;
  string num = "";
  for (int i = 0; i < mask.size(); ++i) {
      if (mask[i] == '/') {
          num += "0";
      } else if (mask[i] == '\\') {
          num += "1";
      } else if (mask[i] == '.') {
          num += "2";
      }
  }
  int ten = three_to_ten((int)stoi(num));
  string res = ten_to_three(ten+1);
  while (res.size() != mask.size()) {
      res = "0" + res;
  }
  for (int i = 0; i < res.size(); ++i) {
      if (res[i] == '0') {
          res[i] = '/';
      } else if (res[i] == '1') {
          res[i] = '\\';
      } else if (res[i] == '2') {
          res[i] = '.';
      }
  }
  return res;
}

int main() {
    string mask = "/////";
    cout << give_next(mask);
//   int n, m;
//   std::cin >> n >> m;
  
//   std::vector<std::vector<map<string, int>>> dp(n, std::vector<map<string, int>>(m));
//   string mask = '';
//   for (int i = 0; i <= n; ++i) {
//     mask += '.';
//   }
//   while (true) {
//     if (check(mask), n - 1 - 0) {
//       dp[0][0][mask] = get_number(mask);
//       mask = give_next(mask);
//       if (mask == '') {
//         break;
//       }
//     }
//   }
//   //perehod
//   for (int i = 0; i < n; ++i) {
//     for (int j = 0; j < m; ++j) {
//       string new_mask = mask;
//       new_mask[n - 1 - i] = '/';
//       if (check(new_mask, n - 1 - i)) {
//         dp[i + 1][j + 1][new_mask] = max(dp[i + 1][j + 1][new_mask], dp[i][j][mask] + 1);
//       }
      
//       //mnogo mnogo 
//     }
//   }
}