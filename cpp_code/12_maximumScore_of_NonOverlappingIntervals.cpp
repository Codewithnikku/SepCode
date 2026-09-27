#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class MSNOI_BruteForce {
public:
	vector<int> best;
	vector<vector<int>> a;
	long long bestScore = 0;

	bool better(const vector<int>& x, const vector<int>& y) {
		if (x.size() != y.size()) return x.size() < y.size();
		return x < y;
	}

	void dfs(int pos, int lastEnd, int used, long long score, vector<int>& chosen) {
		if (score > bestScore ||
			(score == bestScore && better(chosen, best))) {
			bestScore = score;
			best = chosen;
		}
		if (used == 4) return;
		for (int i = pos; i < (int)a.size(); i++) {
			if (a[i][0] <= lastEnd) continue;
			chosen.push_back(a[i][3]);
			dfs(i + 1, a[i][1], used + 1, score + a[i][2], chosen);
			chosen.pop_back();
		}
	}

	vector<int> maximumWeight(vector<vector<int>>& intervals) {
		a.clear(); best.clear();
		for (int i = 0; i < (int)intervals.size(); i++)
			a.push_back({intervals[i][0], intervals[i][1], intervals[i][2], i});
		sort(a.begin(), a.end());
		a.insert(a.begin(), {0, 0, 0, -1});
		bestScore = 0;
		dfs(1, -1, 0, 0, best);
		return best;
	}
};

class MSNOI_Better {
public:
	vector<int> maximumWeight(vector<vector<int>>& intervals) {
		int n = intervals.size();
		vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(5));
		vector<vector<long long>> score(n + 1, vector<long long>(5));
		for (int i = 1; i <= n; i++) {
			dp[i] = dp[i - 1]; score[i] = score[i - 1];
			int previous = 0;
			for (int j = 0; j < i - 1; j++)
				if (intervals[j][1] < intervals[i - 1][0]) previous = j + 1;
			for (int used = 1; used <= 4; used++) {
				long long candidate = score[previous][used - 1] + intervals[i - 1][2];
				if (candidate > score[i][used]) {
					score[i][used] = candidate;
					dp[i][used] = dp[previous][used - 1];
					dp[i][used].push_back(i - 1);
				}
			}
		}
		return dp[n][4];
	}
};

class MSNOI_Optimal {
public:
	vector<int> maximumWeight(vector<vector<int>>& intervals) {
		sort(intervals.begin(), intervals.end(), [](auto& x, auto& y) {
			return x[1] < y[1];
		});
		int n = intervals.size();
		vector<vector<long long>> dp(n + 1, vector<long long>(5));
		vector<vector<vector<int>>> chosen(n + 1, vector<vector<int>>(5));
		for (int i = 1; i <= n; i++) {
			dp[i] = dp[i - 1]; chosen[i] = chosen[i - 1];
			int previous = 0;
			for (int j = i - 1; j > 0; j--)
				if (intervals[j - 1][1] < intervals[i - 1][0]) { previous = j; break; }
			for (int used = 1; used <= 4; used++) {
				long long candidate = dp[previous][used - 1] + intervals[i - 1][2];
				if (candidate > dp[i][used]) {
					dp[i][used] = candidate;
					chosen[i][used] = chosen[previous][used - 1];
					chosen[i][used].push_back(i - 1);
				}
			}
		}
		return chosen[n][4];
	}
};

int main() {
	vector<vector<int>> intervals = {{1, 3, 2}, {4, 5, 2}, {2, 4, 3}};
	MSNOI_Better solver; vector<int> answer = solver.maximumWeight(intervals);
	for (int index : answer) cout << index << ' ';
	cout << endl;
}
