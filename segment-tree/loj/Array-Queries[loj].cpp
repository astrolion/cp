#include "bits/stdc++.h"
using namespace std;



int main() {
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(false); cin.tie(NULL);
#endif // ONLINE_JUDGE

    int t; cin >> t;

    for(int tc = 1; tc <= t; tc++) {
        int n, q; cin >> n >> q;

        vector< int > v(n);
        for(auto &it : v) cin >> it;

        while(n & (n - 1))n++;

        const int INF = 1e9;
        vector< int > tree(n + n, INF);
        // assigning leaf nodes of the segment tree
        for(int i = 0; i < (int)v.size(); i++) {
            tree[n + i] = v[i];
        }

        // building segment tree
        for(int i = n + n - 1; i > 1; i--) {
            tree[i / 2] = min(tree[i / 2], tree[i]);
        }

        // query minimum element in range [a,b]
        // parameters node , st, ed, a, b

        function< int(int, int, int, int, int) > query = [&]
        (int node, int st, int ed, int a, int b) {

            // out of the segment
            if(b < st or ed < a) return INF;

            // in the segment
            if(st >= a and ed <= b) return tree[node];

            int mid = (st + ed) >> 1;
            return min(
                       query(node * 2, st, mid, a, b),
                       query(node * 2 + 1, mid + 1, ed, a, b)
                   );

        };

        cout << "Case " << tc << ":\n";
        while(q--) {
            int a, b; cin >> a >> b;
            cout << query(1, 0, n - 1, a - 1, b - 1) << '\n';
        }



    }



    return 0;
}



