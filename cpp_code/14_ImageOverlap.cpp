#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class ImageOverlap_BruteForce {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size(), answer = 0;
        for (int dr = -n + 1; dr < n; dr++)
            for (int dc = -n + 1; dc < n; dc++) {
                int overlap = 0;
                for (int r = 0; r < n; r++)
                    for (int c = 0; c < n; c++) {
                        int nr = r + dr, nc = c + dc;
                        if (nr >= 0 && nr < n && nc >= 0 && nc < n)
                            overlap += img1[r][c] && img2[nr][nc];
                    }
                answer = max(answer, overlap);
            }
        return answer;
    }
};

class ImageOverlap_Better {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size(), answer = 0;
        vector<pair<int, int>> first, second;
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++) {
                if (img1[r][c]) first.push_back({r, c});
                if (img2[r][c]) second.push_back({r, c});
            }
        for (auto a : first)
            for (auto b : second) {
                int overlap = 0;
                for (auto x : first)
                    for (auto y : second)
                        if (x.first - a.first == y.first - b.first && x.second - a.second == y.second - b.second) overlap++;
                answer = max(answer, overlap);
            }
        return answer;
    }
};

class ImageOverlap_Optimal {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size(), answer = 0;
        vector<pair<int, int>> first, second;
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++) {
                if (img1[r][c]) first.push_back({r, c});
                if (img2[r][c]) second.push_back({r, c});
            }
        vector<int> count((2 * n - 1) * (2 * n - 1));
        for (auto a : first)
            for (auto b : second) {
                int dr = a.first - b.first + n - 1;
                int dc = a.second - b.second + n - 1;
                answer = max(answer, ++count[dr * (2 * n - 1) + dc]);
            }
        return answer;
    }
};

int main() {
    vector<vector<int>> img1 = {{1, 1, 0}, {0, 1, 0}, {0, 0, 0}};
    vector<vector<int>> img2 = {{0, 0, 0}, {0, 1, 1}, {0, 0, 1}};
    ImageOverlap_BruteForce bf; cout << bf.largestOverlap(img1, img2) << endl;
    ImageOverlap_Better btr; cout << btr.largestOverlap(img1, img2) << endl;
    ImageOverlap_Optimal opt; cout << opt.largestOverlap(img1, img2) << endl;
    return 0;
}
