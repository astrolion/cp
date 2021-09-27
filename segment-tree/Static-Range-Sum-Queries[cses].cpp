#include "bits/stdc++.h"
using namespace std;

/**
Given an array of n integers,
your task is to process q queries of the form:
what is the sum of values in range [a,b]?
**/



int main() {
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(false); cin.tie(NULL);
#endif // ONLINE_JUDGE

    int n, q; cin >> n >> q;

    vector< int > v(n);
    for(auto &it : v) cin >> it;

    // make n = power of 2.
    while(n & (n - 1)) {
        n++;
        v.push_back(0); // not so important, just for avoiding silly bugs
    }

    // n is power of two, so we need just n+n-1 nodes in segment tree
    vector< long long >tree(n + n);

    // assigning leaf node
    for(int i = 0; i < n; i++) {
        tree[n + i] = v[i];
    }

    // building segment tree
    for(int i = n + n - 1; i > 1; i--) tree[i / 2] += tree[i];

    // query - node, segment_start, segment_end, a, b
    // where [a,b] is the query range a<=b

    function< long long(int, int, int, int, int) > query = [&]
    (int node, int st, int ed, int a, int b) {

        // segment is outside the range [a, b]
        if(b < st or ed < a) return 0LL;

        // segment is inside the range [a, b]
        if(st >= a and ed <= b) return tree[node];

        int mid = (st + ed) >> 1;

        return query(node * 2, st, mid, a, b) + query(node * 2 + 1, mid + 1, ed, a, b);

    };

    while(q--) {
        int a, b; cin >> a >> b;
        cout << query(1, 0, n - 1, a - 1, b - 1) << '\n';
    }







    return 0;
}




