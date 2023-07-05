#include <bits/stdc++.h>
using namespace std;

struct segtree {
    int lb, rb;
    int sum = 0;
    int push = 0;
    segtree *l = 0, *r = 0;
    segtree (int _lb, int _rb, int push) {
        lb = _lb, rb = _rb;
    }
    void extend () {
        if (!l && lb + 1 < rb) {
            int mid = (lb + rb) / 2;
            l = new segtree(lb, mid, push);
            l->push += push;
            r = new segtree(mid, rb, push);
            r->push += push;
        }
    }
    void add (int k, int x) {
        extend();
        sum += x;
        push += x;
        if (l) {
            if (k < l->rb)
                l->add(k, x);
            else
                r->add(k, x);
        }
    }
    int get_sum (int lq, int rq) {
        if (lb >= lq && rb <= rq)
            return sum;
        if (max(lb, lq) >= min(rb, rq))
            return 0;
        extend();
        return l->get_sum(lq, rq) + r->get_sum(lq, rq);
    }
};

int main() {
    segtree tree(1, 1000000001, 0);
    tree.add(5, 1);
    tree.add(5, 1);
    tree.add(100000000, 100);
    cout << tree.get_sum(1, 1000000001);
    return 0;
}



// массовые операции недописано
// #include <bits/stdc++.h>
// using namespace std;

// struct segtree {
//     int lb, rb;
//     int sum = 0;
//     int push = 0;
//     segtree *l = 0, *r = 0;
//     segtree (int _lb, int _rb, int push) {
//         lb = _lb, rb = _rb;
//     }
//     void extend () {
//         if (!l && lb + 1 < rb) {
//             int mid = (lb + rb) / 2;
//             l = new segtree(lb, mid, push);
//             l->push += push;
//             r = new segtree(mid, rb, push);
//             r->push += push;
//         }
//     }
//     void add (int k, int k2, int x) {
//         extend();
//         sum += x;
//         push += x;
//         if (l) {
//             if (k < l->rb)
//                 l->add(k, k2, x);
//             else
//                 r->add(k, k2, x);
//         }
//     }
//     int get_sum (int lq, int rq) {
//         if (lb >= lq && rb <= rq)
//             return sum;
//         if (max(lb, lq) >= min(rb, rq))
//             return 0;
//         extend();
//         return l->get_sum(lq, rq) + r->get_sum(lq, rq);
//     }
// };

// int main() {
//     segtree tree(1, 1000000001, 0);
//     tree.add(5, 1);
//     tree.add(5, 1);
//     tree.add(100000000, 100);
//     cout << tree.get_sum(1, 1000000001);
//     return 0;
// }