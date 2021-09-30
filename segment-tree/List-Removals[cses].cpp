/**
You are given a list consisting of n integers.
Your task is to remove elements from the list at given positions,
and report the removed elements.

Input:
The first input line has an integer n: the initial size of the list.
During the process, the elements are numbered 1,2,…,k where k is the current size of the list.

The second line has n integers x1,x2,…,xn: the contents of the list.
The last line has n integers p1,p2,…,pn: the positions of the elements to be removed.

Output:
Print the elements in the order they are removed.

:: solution idea ::
Set all segment tree leaf node to 1
binary search on the segment tree tree with with range [0,Pi-1] lower bound
update the result position in segment tree ( point update result position with value 0 )
**/


#include "bits/stdc++.h"
using namespace std;

int main() {
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(false); cin.tie(NULL);
#endif // ONLINE_JUDGE

    int n; cin >> n;
    vector< int > v(n);

    for(auto &it : v) cin >> it;

    while(n & (n - 1))n++; // make n to 2^x

    // n is power of two so we need 2n-1 nodes in segment tree
    vector< int > tree(n + n, 0);

    // setting leaf node of the tree to 1
    for(int i = 0; i < n; i++) tree[n + i] = 1;

    // build tree
    for(int i = n + n - 1; i > 1; i--) tree[i / 2] += tree[i];

    // point update set set postion {pos} to 0
    auto update = [&](int pos) {
        pos += n;
        while(pos) {
            tree[pos]--;
            pos /= 2;
        }
        return ;

    };


    // query : node , start range, end range, a, b
    // range query with range [a,b] , actually prefix query
    // where a is always 0
    function< int(int, int, int, int, int) > query = [&]
    (int node, int st, int ed, int a, int b) {

        if(b < st or ed < a) return 0;
        if(st >= a and ed <= b) return tree[node];

        int mid = (st + ed) >> 1;
        return query(node * 2, st, mid, a, b) +
               query(node * 2 + 1, mid + 1, ed, a, b);

    };

    for(int i = 0; i < (int)v.size(); i++) {
        int x; cin >> x;

        int st = 0, ed = n - 1;
        int ans = -1;

        // binary search the lower bound
        while(st <= ed) {
            int mid = (st + ed) >> 1;
            int ret = query(1, 0, n - 1, 0, mid);
            if(ret >= x) {
                ans = mid;
                ed = mid - 1;
            } else {
                st = mid + 1;
            }
        }

        if(i) cout << ' ';
        cout << v[ans];

        // updating position value to 0
        update(ans);

    }

    cout << '\n';

    return 0;
}




