#include "bits/stdc++.h"
using namespace std;



int main() {
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(false); cin.tie(NULL);
#endif // ONLINE_JUDGE

    int t; cin >> t;

    for(int tc = 1; tc <= t; tc++) {
        string s; cin >> s;

        int n = (int)s.size();

        while(n & (n - 1))n++;

        vector< int > tree(n + n, 0);

        auto query = [&](int pos) {
            pos += n;
            int ret = 0;
            while(pos) {
                ret += tree[pos];
                pos /= 2;
            }
            return ret;
        };

        // update : node, st, ed, a, b

        function< void(int, int, int, int, int) > update = [&]
        (int node, int st, int ed, int a, int b) {

            if(b < st or ed < a) return ;

            if(st >= a and ed <= b) {
                tree[node]++;
                return ;
            }

            int mid = (st + ed) >> 1;
            update(node * 2, st, mid, a, b);
            update(node * 2 + 1, mid + 1, ed, a, b);
        };


        int q; cin >> q;

        cout << "Case " << tc << ":\n";
        while(q--) {
            string type;
            cin >> type;
            if(type == "I") {
                int a, b; cin >> a >> b;
                update(1, 0, n - 1, a - 1, b - 1);
            } else {
                int pos; cin >> pos; pos--;

                int ret = query(pos);

                if(ret & 1) {
                    if(s[pos] == '1') cout << "0\n";
                    else cout << "1\n";
                } else {
                    cout << s[pos] << '\n';
                }
            }

        }

    }

    return 0;
}



