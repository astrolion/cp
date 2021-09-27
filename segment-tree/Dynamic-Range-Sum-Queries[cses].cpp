#include "bits/stdc++.h"
using namespace std;
/**
Given an array of n integers, your task is to process q queries of the following types:
1. update the value at position k to u
2. what is the sum of values in range [a,b]?

**/


int main() {
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(false); cin.tie(NULL);
#endif // ONLINE_JUDGE

    int n, q; cin >> n >> q;
    vector< int > v(n);

    for(auto &it : v) cin >> it;

    while(n & (n - 1))n++; // making n to power of 2

    // need 2n-1 nodes in segment tree where n is power of 2
    vector< long long > tree(n + n, 0);

    // assigning leaf nodes
    for(int i = 0; i < (int)v.size(); i++) tree[n + i] = v[i];

    // building segment tree
    for(int i = n + n - 1; i > 1; i--) tree[i >> 1] += tree[i];

    // query [ node, segment start, segment end, a, b ]
    function< long long(int, int, int, int, int) > query = [&]
    (int node, int st, int ed, int a, int b) {

        // segment outside the range
        if(b < st or ed < a) return 0LL;

        // segment inside the range
        if(st >= a and ed <= b) return tree[node];

        int mid = (st + ed) / 2;
        return query(node * 2, st, mid, a, b) + query(node * 2 + 1, mid + 1, ed, a, b);

    };

    // update at position pos, with value {value}
    auto update = [&](int pos, int value) {
        pos += n;
        while(pos) {
            tree[pos] += value;
            pos >>= 1;
        }
        return ;
    };


    while(q--) {
        int type;  cin >> type;
        if(type == 1) {
            int pos, value; cin >> pos >> value;
            pos--;
            update(pos, value - tree[n + pos]);
        } else {
            int a, b;  cin >> a >> b;
            cout << query(1, 0, n - 1, a - 1, b - 1) << '\n';
        }
    }




    return 0;
}




