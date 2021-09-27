#include "bits/stdc++.h"
using namespace std;

/**
Given an array of n integers,
your task is to process q queries of the following types:
1. increase each value in range [a,b] by u
2. what is the value at position k
**/


int main() {
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(false); cin.tie(NULL);
#endif // ONLINE_JUDGE

    int n, q; cin >> n >> q;

    vector< int > v(n);
    for(auto &it : v) cin >> it;

    // make n to power of 2
    while(n & (n - 1)) n++;

    // n is power of 2, so need 2n-1 nodes in segment tree
    vector< long long > tree(n + n, 0);

    // update , (node, range start, range end, a, b, value) where a <= b
    function< void(int, int, int, int, int, int) > upd = [&]
    (int node, int st, int ed, int a, int b, int value) {

        // out of the segment
        if(b < st or ed < a) return ;

        // inside the segment
        if(st >= a and ed <= b) {
            tree[node] += value;
            return ;
        }

        int mid = (st + ed) >> 1;
        upd(node * 2, st, mid, a, b, value);
        upd(node * 2 + 1, mid + 1, ed, a, b, value);

    };

    // query for position {pos}
    auto query = [&](int pos) {
        long long sum = v[pos];
        pos += n;
        while(pos) {
            sum += tree[pos];
            pos >>= 1;
        }
        return sum;
    };

    while(q--) {
        int type; cin >> type;
        if(type == 1) {
            int a, b, value; cin >> a >> b >> value;
            // increase value in range [a,b] by {value}
            upd(1, 0, n - 1, a - 1, b - 1, value);
        } else {
            int pos; cin >> pos;
            cout << query(pos - 1) << '\n';
        }

    }
    return 0;

}




