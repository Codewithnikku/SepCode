#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class MMTCTC_BruteForce {
public:

    int m, n, energyCap, full, best;
    vector<string> g; vector<vector<int>> bit;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    void dfs(int r, int c, int e, int mask, int moves) {
        if(moves >= best) return;
        if(mask == full) { best = min(best, moves); return; }

        for(int d=0; d<4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if(nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
            if(g[nr][nc] == 'X') continue;
            if(e == 0) continue;

            int ne = e - 1;
            if(ne < 0) continue;

            int nmask = mask;
            if(bit[nr][nc] != -1) nmask |= (1 << bit[nr][nc]);

            dfs(nr, nc, ne, nmask, moves + 1);
        }
    }

    int minMoves(vector<string>& classroom, int energy) {
        g = classroom; m = g.size(); n = g[0].size();
        energyCap = energy; bit.assign(m, vector<int>(n, -1));

        int sr = 0, sc = 0, cnt = 0;
        for(int i=0; i<m; i++) 
            for(int j=0; j<n; j++) {
                if(g[i][j] == 'S') { sr = i; sc = j; }
                else if(g[i][j] == 'L') bit[i][j] = cnt++;
            }

            if(cnt == 0) return 0;
            full = (1 << cnt) - 1; best = INT_MAX;
        
        dfs(sr, sc, energy, 0, 0);
        return best == INT_MAX ? -1 : best;

        
    }
};

class MMTCTC_better {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        vector<vector<int>> bit(m, vector<int>(n, -1));

        int sr = 0, sc = 0, cnt = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } else if (classroom[i][j] == 'L') {
                    bit[i][j] = cnt++;
                }
            }
        }

        if (cnt == 0)
            return 0;

        int full = (1 << cnt) - 1;

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        vector<vector<vector<vector<bool>>>> vis(
            m,
            vector<vector<vector<bool>>>(
                n,
                vector<vector<bool>>(
                    energy + 1,
                    vector<bool>(1 << cnt, false)
                )
            )
        );

        queue<array<int, 4>> q;
        q.push({sr, sc, energy, 0});
        vis[sr][sc][energy][0] = true;

        int moves = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto [r, c, e, mask] = q.front();
                q.pop();

                if (mask == full)
                    return moves;

                if (e == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    if (classroom[nr][nc] == 'X')
                        continue;

                    int ne = e - 1;
                    int nmask = mask;

                    if (bit[nr][nc] != -1)
                        nmask |= (1 << bit[nr][nc]);

                    if (classroom[nr][nc] == 'R')
                        ne = energy;

                    if (!vis[nr][nc][ne][nmask]) {
                        vis[nr][nc][ne][nmask] = true;
                        q.push({nr, nc, ne, nmask});
                    }
                }
            }

            moves++;
        }

        return -1;
    }
};

class MMTCTC_optimal {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size(), n = classroom[0].size();
        vector<int> bitOf(m * n, -1);        
        int sr = 0, sc = 0, cnt = 0;
        
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') { sr = i; sc = j; }
                else if (classroom[i][j] == 'L') bitOf[i * n + j] = cnt++;
            }

        if (cnt == 0) return 0;
        int full = (1 << cnt) - 1;
        int E = energy + 1, MASK = 1 << cnt;

        long long total = (long long)m * n * E * MASK;
        vector<char> vis(total, 0); 

        auto encode = [&](int r, int c, int e, int mask) {
            return ((r * n + c) * E + e) * MASK + mask;
        };

        vector<int> cur = {encode(sr, sc, energy, 0)};
        vis[cur[0]] = 1;
        int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1}; int moves = 0;

        while (!cur.empty()) {
            vector<int> nxt;
            nxt.reserve(cur.size() * 3);
            for (int code : cur) {

                int mask = code % MASK; int t = code / MASK;
                int e = t % E; int pos = t / E;
                int r = pos / n, c = pos % n;
                if (e == 0) continue; 
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];

                    if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                    if (classroom[nr][nc] == 'X') continue;

                    int ne = e - 1; int nmask = mask;
                    int b = bitOf[nr * n + nc];

                    if (b != -1) nmask |= (1 << b);
                    if (classroom[nr][nc] == 'R') ne = energy;
                    if (nmask == full) return moves + 1; 

                    int code2 = encode(nr, nc, ne, nmask);
                    if (!vis[code2]) { vis[code2] = 1; nxt.push_back(code2); }
                }
            }
            cur.swap(nxt);
            moves++;
        }
        return -1;
    }
};


int main(){
    vector<string> classroom = { "LS", "RL"};
    int energy = 4;
    MMTCTC_BruteForce solver_bf;
    MMTCTC_better solver_btr;
    MMTCTC_optimal solver_opt;
    cout<< "Minimum moves to clean the classroom (Brute Force): " << solver_bf.minMoves(classroom, energy) << endl;
    cout<< "Minimum moves to clean the classroom (Better): " << solver_btr.minMoves(classroom, energy) << endl;
    cout<< "Minimum moves to clean the classroom (Optimal): " << solver_opt.minMoves(classroom, energy) << endl;
    return 0;
}