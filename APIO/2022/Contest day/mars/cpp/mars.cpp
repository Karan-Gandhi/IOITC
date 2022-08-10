#include "mars.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()
#define endl '\n'
#define pl(var) " [" << #var << ": " << (var) << "] "

template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "[" << p.first << ", " << p.second << "]"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) { cout << "["; for(int i = 0; i < (int)v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) { cin >> p.first; return cin >> p.second; }

string to_bit(int n) {
	string res(100, '0');

	int ind = 0;

	while (n > 0) {
		int rem = n % 2;
		n /= 2;
		res[ind++] = rem + '0';
	}
	return res;
}

std::string process(std::vector <std::vector<std::string>> a, int i, int j, int k, int n)
{
	if (n == 1) {
		int dx[4] = {1, -1, 0, 0};
		int dy[4] = {0, 0, 1, -1};
		vector<vector<bool>> grid(2 * n + 1, vector<bool>(2 * n + 1, 0));

		for (int i = 0; i <= 2 * n; i++) {
			for (int j = 0; j < 3; j++) {
				grid[i][j] = a[i][j][0] - '0';
			}
		}

		vector<vector<bool>> vis(2 * n + 1, vector<bool>(2 * n + 1, 0));
		auto dfs = [&](int x, int y) {
			if (vis[x][y]) return;

			queue<pair<int, int>> q;
			q.emplace(x, y);

			while (q.size() != 0) {
				pair<int, int> node = q.front();
				q.pop();

				if (vis[node.first][node.second]) continue;
				vis[node.first][node.second] = 1;

				for (int i = 0; i < 4; i++) {
					int nx = node.first + dx[i];
					int ny = node.second + dy[i];

					if (nx >= 0 && nx <= 2 * n && ny >= 0 && ny <= 2 * n && grid[nx][ny]) {
						q.emplace(nx, ny);
					}
				}
			}
		};

		int res = 0;

		for (int i = 0; i <= 2 * n; i++) {
			for (int j = 0; j <= 2 * n; j++) {
				if (!vis[i][j] && grid[i][j]) {
					dfs(i, j);
					res++;
				}
			}
		}

		return to_bit(res);		
	} else if (k == 0) {
		string flattned = string(100, '0');

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				flattned[3 * i + j] = a[i][j][0];
			}
		}

		return flattned;
	} else if (n == 2 && k == 1) {
		// now i have the flattened strings

		vector<vector<bool>> grid(2 * n + 1, vector<bool>(2 * n + 1, 0));

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				grid[i][j] = a[0][0][3 * i + j] - '0';
			}
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				grid[i][j + 2] = a[0][2][3 * i + j] - '0';
			}
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				grid[i + 2][j + 2] = a[2][2][3 * i + j] - '0';
			}
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				grid[i + 2][j] = a[2][0][3 * i + j] - '0';
			}
		}

		// now just count the islands
		// for (auto i : grid) {
		// 	cout << i << endl;
		// }

		int dx[4] = {1, -1, 0, 0};
		int dy[4] = {0, 0, 1, -1};

		vector<vector<bool>> vis(2 * n + 1, vector<bool>(2 * n + 1, 0));
		auto dfs = [&](int x, int y) {
			if (vis[x][y]) return;

			queue<pair<int, int>> q;
			q.emplace(x, y);

			while (q.size() != 0) {
				pair<int, int> node = q.front();
				q.pop();

				if (vis[node.first][node.second]) continue;
				vis[node.first][node.second] = 1;

				// cout << pl(node) << endl;

				for (int i = 0; i < 4; i++) {
					int nx = node.first + dx[i];
					int ny = node.second + dy[i];

					if (nx >= 0 && nx <= 2 * n && ny >= 0 && ny <= 2 * n && grid[nx][ny]) {
						q.emplace(nx, ny);
					}
				}
			}
		};

		int res = 0;

		for (int i = 0; i <= 2 * n; i++) {
			for (int j = 0; j <= 2 * n; j++) {
				if (!vis[i][j] && grid[i][j]) {
					dfs(i, j);
					res++;
				}
			}
		}

		return to_bit(res);
		// cout << pl(res) << endl;
	} else if (k == 1) {
		vector<vector<bool>> grid(2 * n + 1, vector<bool>(2 * n + 1, 0));

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				grid[i][j] = a[0][0][3 * i + j] - '0';
			}
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				grid[i][j + 2] = a[0][2][3 * i + j] - '0';
			}
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				grid[i + 2][j + 2] = a[2][2][3 * i + j] - '0';
			}
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				grid[i + 2][j] = a[2][0][3 * i + j] - '0';
			}
		}

		string flattned(100, '0');

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				flattned[5 * i + j] = grid[i][j] + '0';
			}
		}

		return flattned;
	} else if (k == 2 && n == 3) {
		vector<vector<bool>> grid(2 * n + 1, vector<bool>(2 * n + 1, 0));

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				grid[i][j] = a[0][0][5 * i + j];
			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				grid[i][j + 4] = a[0][4][5 * i + j];
			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				grid[i + 4][j + 4] = a[4][4][5 * i + j];
			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				grid[i + 4][j] = a[4][0][5 * i + j];
			}
		}

		int dx[4] = {1, -1, 0, 0};
		int dy[4] = {0, 0, 1, -1};

		vector<vector<bool>> vis(2 * n + 1, vector<bool>(2 * n + 1, 0));
		auto dfs = [&](int x, int y) {
			if (vis[x][y]) return;

			queue<pair<int, int>> q;
			q.emplace(x, y);

			while (q.size() != 0) {
				pair<int, int> node = q.front();
				q.pop();

				if (vis[node.first][node.second]) continue;
				vis[node.first][node.second] = 1;

				// cout << pl(node) << endl;

				for (int i = 0; i < 4; i++) {
					int nx = node.first + dx[i];
					int ny = node.second + dy[i];

					if (nx >= 0 && nx <= 2 * n && ny >= 0 && ny <= 2 * n && grid[nx][ny]) {
						q.emplace(nx, ny);
					}
				}
			}
		};

		int res = 0;

		for (int i = 0; i <= 2 * n; i++) {
			for (int j = 0; j <= 2 * n; j++) {
				if (!vis[i][j] && grid[i][j]) {
					dfs(i, j);
					res++;
				}
			}
		}

		return to_bit(res);
	} else if (k == 2) {
		vector<vector<bool>> grid(2 * n + 1, vector<bool>(2 * n + 1, 0));

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				grid[i][j] = a[0][0][5 * i + j];
			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				grid[i][j + 4] = a[0][4][5 * i + j];
			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				grid[i + 4][j + 4] = a[4][4][5 * i + j];
			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				grid[i + 4][j] = a[4][0][5 * i + j];
			}
		}

		string flattned(100, '0');
	}
	return std::string(100 ,'0');
}
