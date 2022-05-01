#include <bits/stdc++.h>
using namespace std;
#define int long long

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

const int N = 1e5 + 5, BLOCK = 400;
vector<int> g[N];
vector<int> val(N), tin(N), tout(N), depth(N), dp(N), val_d(N), val_a(N);
int tim = 1;

void dfs(int node, int par)
{
	dp[node] = dp[par] + val[node];
	tin[node] = tim++;
	for(int to: g[node])
	{
		if(to != par)
		{
			depth[to] = depth[node] + 1;
			dfs(to, node);
		}
	}
	tout[node] = tim++;
}

void UpdateDP(int node, int cur_sum, int only_d_sum, int par) 
{
	cur_sum += val_a[node] + only_d_sum;
	val[node] += cur_sum;
	dp[node] = dp[par] + val[node];
	only_d_sum += val_d[node];
 	val_a[node] = val_d[node] = 0;
 	for(int to: g[node])
 	{
 		if(to != par)
 		{
 			UpdateDP(to, cur_sum, only_d_sum, node);
 		}
 	}
}

void Solve() 
{
	int n, q;
	cin >> n >> q;

	for(int i = 1; i <= n - 1; i++)
	{
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	depth[1] = 0;
	for(int i = 1; i <= n; i++)
	{
		cin >> val[i];
	}
	dfs(1, 0);
	vector<array<int, 3> > updates;
	int cnt = 0;
	for(int i = 1; i <= q; i++)
	{
		int command;
		cin >> command;
		if(command == 1)
		{
			cnt++;
			int node, a, d;
			cin >> node >> a >> d;
			val_a[node] += a;
			val_d[node] += d;
			updates.push_back({node, a, d});
			cout << "Update: " << i << endl;
		}
		else
		{
			int node;
			cin >> node;
			int buffer_value = 0;
			for(int j = 0; j < updates.size(); j++)
			{
				int a = updates[j][1], d = updates[j][2], dist = depth[node] - depth[updates[j][0]] + 1;
				if(tin[updates[j][0]] <= tin[node] && tout[node] <= tout[updates[j][0]])
				{
					int lmao_ok = 2 * a + (dist - 1) * d;
					lmao_ok *= dist;
					assert(lmao_ok % 2 == 0);
					lmao_ok /= 2;
					buffer_value += lmao_ok;
				}
			}
			cout << "Query: " << i << endl;
			cout << dp[node] + buffer_value << "\n";
		}
		if(cnt == BLOCK)
		{
			UpdateDP(1, 0, 0, 0);
			cnt = 0;
			updates.clear();
		}
	}
}

int32_t main() 
{
	auto begin = std::chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
	// cin >> t;
	for(int i = 1; i <= t; i++) 
	{
		//cout << "Case #" << i << ": ";
		Solve();
	}
	auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n"; 
	return 0;
}