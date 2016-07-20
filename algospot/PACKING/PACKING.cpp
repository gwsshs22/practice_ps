#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 100
#define MAX_W 1001
using namespace std;
int N, W, weights[MAX_N], values[MAX_N], cache[MAX_N][MAX_W];
bool used[MAX_N][MAX_W];
string inputs[MAX_N];

int dp(int n, int w) {
  if (n == N || w == 0) return 0;
  int& ret = cache[n][w];
  if (ret != -1) return ret;
  int curV = values[n];
  int curW = weights[n];

  int valueWhenNotUsed = dp(n + 1, w);
  int valueWhenUsed = -1;
  if (curW <= w) {
    valueWhenUsed = curV + dp(n + 1, w - curW);
  }

  if (valueWhenNotUsed > valueWhenUsed) {
    ret = valueWhenNotUsed;
    used[n][w] = false;
  } else {
    ret = valueWhenUsed;
    used[n][w] = true;
  }

  return ret;
}

void construct(int n, int w, vector<string>& v) {
  if (n == N || w == 0) return;
  if (used[n][w]) {
    v.push_back(inputs[n]);
    construct(n + 1, w - weights[n], v);
  } else {
    construct(n + 1, w, v);
  }
}

int main() {
  int C; cin >> C;
  while (C--) {
    fill(weights, weights + MAX_N, 0);
    fill(values, values + MAX_N, 0);
    fill(cache[0], cache[0] + MAX_N * MAX_W, -1);
    fill(used[0], used[0] + MAX_N * MAX_W, false);
    cin >> N >> W;
    for (int i = 0; i < N ; i++) {
      cin >> inputs[i] >> weights[i] >> values[i];
    }

    cout << dp(0, W) << ' ';
    vector<string> sol;
    construct(0, W, sol);
    cout << sol.size() << endl;
    for (int i = 0; i < sol.size(); i++) {
      cout << sol[i] << endl;
    }
  }
  return 0;
}
