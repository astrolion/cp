#include "bits/stdc++.h"
using namespace std;
/**
Given an array of n integers,
your task is to process q queries of the form:
what is the xor sum of values in range [a,b]?
**/


int main() {
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(false); cin.tie(NULL);
#endif // ONLINE_JUDGE

    int n, q; cin >> n >> q;

    vector< int > v(n);
    for(auto &it : v) cin >> it;


    while(n & (n - 1))n++; // n -> 2^x

    // n is power of 2 , so we need 2n-1 nodes in segment tree
    vector< int > tree(n + n, 0);

    // don't use (i < n) because, n could not be same as v.size()
    for(int i = 0; i < (int)v.size(); i++) {
        tree[n + i] = v[i];
    }

    // building segment tree..
    for(int i = n + n - 1; i > 1; i--) tree[i >> 1] ^= tree[i];

    // not working ..
    /**
    int query = [&](int node, int st, int ed, int a, int b) {
        if(b < st or ed < a) return 0;
        if(st >= a and ed <= b) return tree[node];
        int mid = (st + ed) >> 1;
        return query(node * 1, st, mid, a, b) ^ query(node * 2 + 1, mid + 1, ed, a, b);
    };
    **/

    // query function
    // parameters : node, range_start, range_end, a, b ; where a<=b

    function< int(int, int, int, int, int) > query = [&]
    (int node, int st, int ed, int a, int b) {

        // outside the range
        if(b < st or ed < a) return 0;

        // inside the range
        if(st >= a and ed <= b) return tree[node];

        int mid = (st + ed) >> 1;

        return query(node * 2, st, mid, a, b) ^ query(node * 2 + 1, mid + 1, ed, a, b);

    };


    while(q--) {
        int a, b; cin >> a >> b;
        cout << query(1, 0, n - 1, a - 1, b - 1) << '\n';
    }





    return 0;
}




