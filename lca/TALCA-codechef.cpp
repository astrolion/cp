#include "bits/stdc++.h"
using namespace std;

const int LOG = 20;
const int N = 2e5 + 5;
vector< int > g[N];
int parent[N][LOG + 5];
int t_in[N], t_out[N];
int depth[N];
int Time = 0;

void dfs(int node, int par, int level = 1) {
    t_in[node] = ++Time;
    depth[node] = level;
    parent[node][0] = par;
    for(int i = 1; i < LOG; i++) {
        parent[node][i] = parent[ parent[node][i - 1] ][i - 1];
    }

    for(int v : g[node]) {
        if(v != par)
            dfs(v, node, level + 1);
    }
    t_out[node] = ++Time;
}

bool is_ancestor(int u,  int v) {
    return t_in[u] <= t_in[v] && t_out[u] >= t_out[v];
}

int lca(int u, int v) {
    if(is_ancestor(u, v))
        return u;
    if(is_ancestor(v, u))
        return v;
    for(int i = LOG; i >= 0; i--) {
        if( parent[u][i] && !is_ancestor(parent[u][i], v)  )
            u = parent[u][i];
    }
    return parent[u][0];
}



int main() {
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(false); cin.tie(NULL);
#endif // ONLINE_JUDGE

    int n, q; cin >> n;

    for(int i = 0; i < n - 1; i++) {
        int from, to; cin >> from >> to;
        g[from].push_back(to), g[to].push_back(from);
    }

    dfs(1, 0);


    cin >> q;
    while(q--) {
        int root, node1, node2; cin >> root >> node1 >> node2;

        vector< int > v = { lca(root, node1), lca(root, node2), lca(node1, node2) };

        vector< pair<int, int> > ans;
        for(auto it : v) {
            ans.push_back( {(abs(depth[it] - depth[root]) + abs(depth[it] - depth[node1]) + abs(depth[it] - depth[node2])), it });
        }

        sort(ans.begin(), ans.end());

        cout << ans[0].second << '\n';


    }




    return 0;
}
