#include "bits/stdc++.h"
using namespace std;



int main() {
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(false); cin.tie(NULL);
#endif // ONLINE_JUDGE

    int n, q; cin >> n >> q;

    vector< int > v(n);
    for(auto &it : v) cin >> it;

    while(n & (n - 1))n++; // make n to 2^x

    // n = 2^x , so, we need n+n-1 nodes in segment tree
    vector< int > tree(n + n, 0);

    // assigning leaf nodes (i<n) may cause error if n is not power of two initially
    for(int i = 0; i < (int)v.size(); i++)
        tree[n + i] = v[i];

    // constructing segment tree
    for(int i = n + n - 1; i > 1; i--) tree[i / 2] = max(tree[i / 2], tree[i]);


    const int INF = 2e9;

    // query node, range start, range end, value
    function< int(int, int, int, int) > query = [&]
    (int node, int st, int ed, int value) {

        // required value does not belong to the segment
        if(tree[node] < value) return INF;

        // required value belongs to the segment and check for leaf node
        if(st == ed) {
            return st;
        }

        int mid = (st + ed) >> 1;

        int ret = query(node * 2, st, mid, value);
        // checking if required value belongs to the first half
        // we need the lowest position
        if(ret ^ INF) return ret;
        else {
            return query(node * 2 + 1, mid + 1, ed, value);
        }
    };

    // updating segment tree with new value
    auto update = [&](int pos, int value) {
        pos += n;
        tree[pos] = value;

        for(int i = pos; i > 1; i /= 2) {
            if(i & 1) {
                tree[i / 2] = max(tree[i - 1], tree[i]);
            } else {
                tree[i / 2] = max(tree[i], tree[i + 1]);
            }
        }

        return ;
    };


    for(int j = 0; j < q; j++) {
        int x; cin >> x;

        int pos = query(1, 0, n - 1, x);
        int ans = 0;

        if(pos != INF) ans = pos + 1;

        cout << ans << ' ';
        if(ans) update(pos, tree[n + pos] - x);
    }


    return 0;
}




