#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

class U3DEN_BruteForce {
public:
	int totalNumbers(vector<int>& digits) {
		set<int> numbers;
		int n = digits.size();
		for (int i = 0; i < n; i++) {
			if (digits[i] == 0) continue;
			for (int j = 0; j < n; j++) {
				if (j == i) continue;
				for (int k = 0; k < n; k++) {
					if (k == i || k == j || digits[k] % 2 != 0) continue;
					numbers.insert(digits[i] * 100 + digits[j] * 10 + digits[k]);
				}
			}
		}
		return numbers.size();
	}
};

class U3DEN_Better {
public:
	int totalNumbers(vector<int>& digits) {
		set<int> numbers;
		int n = digits.size();
		for (int i = 0; i < n; i++) {
			if (digits[i] == 0) continue;
			for (int j = 0; j < n; j++) {
				if (j == i) continue;
				for (int k = 0; k < n; k++) {
					if (k == i || k == j || digits[k] % 2 != 0) continue;
					numbers.insert(digits[i] * 100 + digits[j] * 10 + digits[k]);
				}
			}
		}
		return numbers.size();
	}
};

class U3DEN_Optimal {
public:
	int totalNumbers(vector<int>& digits) {
		int count[10] = {};
		for (int x : digits) count[x]++;
		int answer = 0;
		for (int first = 1; first <= 9; first++) {
			if (!count[first]) continue;
			count[first]--;
			for (int second = 0; second <= 9; second++) {
				if (!count[second]) continue;
				count[second]--;
				for (int last = 0; last <= 8; last += 2)
					if (count[last]) answer++;
				count[second]++;
			}
			count[first]++;
		}
		return answer;
	}
};

int main() {
	vector<int> digits = {2, 1, 3, 0};
	U3DEN_BruteForce bf; cout << bf.totalNumbers(digits) << endl;
	U3DEN_Better btr; cout << btr.totalNumbers(digits) << endl;
	U3DEN_Optimal opt; cout << opt.totalNumbers(digits) << endl;
	return 0;
}
