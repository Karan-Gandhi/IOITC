int get(vector<vector<int>>& adj, const vector<pair<int, int>>& intervals){
    int edges = 0;
    int n = sz(adj);
    vector<int> L;
    pii top = intervals[0];
    for(int i = 1; i < sz(intervals); i++){
        auto it = intervals[i];
        if(top.second != it.first - 1){
            L.push_back(top.first);
            L.push_back(top.second + 1);
            top = it;
        }
        else top.second = it.second;
    }
    L.push_back(top.first); L.push_back(top.second + 1);
    const int LOG = __lg(n) + 1;
    vector<int> st(n), par(n, -1);
    vector<vector<int>> jump(LOG, vector<int>(n + 1, n));
    jump[0][n] = n;

    int timer = 0;
    // after calling dfs, indexing is start time based
    function<void(int, int)> dfs = [&](int s, int p){
        sort(all(adj[s]));
        st[s] = timer++;
        for(int v: adj[s]) if(v != p){
            par[timer] = st[s]; 
            dfs(v, s);
        }
        jump[0][st[s]] = timer;
    };

    dfs(0, 0);

    for(int i = 1; i < LOG; i++){
        for(int j = 0; j < n; j++){
            jump[i][j] = jump[i - 1][jump[i - 1][j]];
        }
    }

    int ans = 0;
    for(int i = 0; i < sz(L); i += 2){
        int l = L[i], r = L[i + 1] - 1;
        int x = l;
        while(x <= r){
            edges++;
            int pos = (upper_bound(all(L), par[x]) - L.begin()) - 1;
            int take = (pos + 2) % 2;
            int y = pos == -1 ? -2 : L[pos];
            ans += take;
            // go till par[x] <= y, and x <= r
            for(int u = LOG - 1; u >= 0; u--){
                int z = jump[u][x];
                if(par[z] >= y && z <= r){
                    ans += take << u;
                    x = z;
                }
            }

            x = jump[0][x];
        }
    }
    return ans;
}