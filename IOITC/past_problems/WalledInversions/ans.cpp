#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "
#define ll long long

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
	ll int n, q; cin >> n >> q;

	vector<ll int> arr(n); for (ll int i = 0; i < n; i++) cin >> arr[i];

	vector<pair<ll int, ll int>> queries(q);

	for (ll int i = 0; i < q; i++) {
		cin >> queries[i].first;
		queries[i].second = i;
	}

	sort(all(queries));
	vector<Tree<ll int>> segs;
	ll int seg_cnt = 0;
	ll int end = -1;
	vector<ll int> who(n, -1);
	vector<pair<ll int, ll int>> interval;
	ll int cur = 0;

	vector<ll int> ans;

	for (ll int i = 0; i < q; i++) {
		segs.push_back(Tree<ll int>());
		ll int start = end + 1;
		end = queries[i].first - 1;
		who[start] = seg_cnt;
		who[end] = seg_cnt;

		for (ll int j = start; j <= end; j++) {
			cur += (ll int)(segs[seg_cnt].size()) - segs[seg_cnt].order_of_key(arr[j]);
			segs[seg_cnt].insert(arr[j]);
		}
		interval.emplace_back(start, end);
		
		seg_cnt++;
	}
	
	{
		segs.push_back(Tree<ll int>());
		ll int start = end + 1;
		end = n - 1;
		who[start] = seg_cnt;
		who[end] = seg_cnt;

		for (ll int j = start; j <= end; j++) {
			cur += (ll int)(segs[seg_cnt].size()) - segs[seg_cnt].order_of_key(arr[j]);
			segs[seg_cnt].insert(arr[j]);
		}
		interval.emplace_back(start, end);
		
		seg_cnt++;
	}

	ans.push_back(cur);

	for (ll int i = 0; i < q; i++) {
		swap(queries[i].first, queries[i].second);
	}


	sort(all(queries));
	reverse(all(queries));

	for (ll int i = 0; i < q; i++) {
		ll int partition = queries[i].second;

		ll int seg1 = who[partition - 1];
		ll int seg2 = who[partition];
		
		ll int start = interval[seg1].first;
		ll int end = interval[seg2].second;

		interval.emplace_back(start, end);
		who[start] = seg_cnt;
		who[end] = seg_cnt;

		bool flipped = 0;
		if (segs[seg1].size() < segs[seg2].size()) {
			swap(seg1, seg2);
			flipped = 1;
		}

		segs.push_back(Tree<ll int>());
		segs[seg_cnt].swap(segs[seg1]);
		
		for (ll int elt : segs[seg2]) {
			if (flipped) cur += segs[seg_cnt].order_of_key(elt);
			else cur += (ll int)(segs[seg_cnt].size()) - segs[seg_cnt].order_of_key(elt);
		}

		for (ll int elt : segs[seg2]) {
			segs[seg_cnt].insert(elt);
		}

		ans.push_back(cur);

		seg_cnt++;
	}

	reverse(all(ans));
	for (ll int i = 1; i <= q; i++) {
		cout << ans[i] << endl;
	}
}

int main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll int T = 1;
	// cin >> T;
	while (T--)
		solve();
}