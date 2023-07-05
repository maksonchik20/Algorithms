n = int(input())
lst = list(map(int, input().split()))
log = [0] * (n+1)
log[1] = 0
for i in range(2, n + 1):
    log[i] = log[i//2] + 1

sparse = [[0] * n for i in range(n)]
for i in range(n):
    sparse[i][0] = lst[i]

for i in range(n-1, -1, -1):
    for j in range(log[n-i] + 1):
        sparse[i][j] = min(sparse[i][j-1], sparse[i+2**(j-1)][j-1])

r = 1
l = 4
pow = log[r-l + 1]
print(min(sparse[l])[pow], sparse[r - 2**pow + 1])


# int main() {
#   int n;
#   std::cin >> n;
#   std::vector<std::vector<int>>table(n, std::vector<int>(log2(n)));
#   for (int i = 0; i < n; ++i) {
#     std::cin >> table[i][0];
#   }
#   //(1 << h)
#   //2 ^ k = (1 << k);
#   //(n << m)// 101000 -> 10100000
#   //n >> m//1010
#   for (int j = 1; j < log2(n); ++j) {
#     for (int i = 0; i < n - (1 << j); ++i) {
#       table[i][j] = max(table[i][j -1], table[i + (1 << (j - 1)) + 1][j-1]);
#     }
#   }
# }