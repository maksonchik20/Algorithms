from collections import deque
import math
mod = 535039202387281331
def abc():
    def main():
        tt = int(input())
        pows = [1] * (2 * 10 ** 5 + 10)
        for i in range(1, 2 * 10 ** 5 + 10):
            pows[i] = (pows[i - 1] * 2) % mod
        for _ in range(tt):
            n, m = list(map(int, input().split()))
            s = [int(i) for i in input()]
            d = {}
            pref, suf, cnt = [], [0] * n, []
            pref.append((s[0] * pows[n-1])%mod)
            suf[-1] = s[-1]
            for i in range(1, n):
                pref.append((pref[-1] + s[i] * pows[n - i - 1])%mod)
            for i in range(n-2, -1, -1):
                suf[i] = (suf[i+1] + s[i] * pows[n-1-i]) % mod
            cnt.append(s[0])
            print(pref)
            print(suf)
            for i in range(1, n):
                cnt.append(cnt[-1] + s[i])
            print(cnt)
            for i in range(m):
                l, r = list(map(int, input().split()))
                l-=1
                r-=1
                new_num = 0
                if l != 0:
                    new_num = (new_num + pref[l-1]) % mod
                if r != n-1:
                    new_num = (new_num + suf[r+1]) % mod
                count = cnt[r] - cnt[l] + s[l]
                new_num = (new_num + ((pows[count]-1) * pows[n - r - 1])) % mod
                d[new_num]=1
            print(len(list(d.keys())))
    main()
     
     
     
if __name__ == "__main__":
    abc()