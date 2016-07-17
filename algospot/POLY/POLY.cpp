#include <iostream>
#include <algorithm>
#define DIV_N 10000000
#define MAX_N 101
using namespace std;
int cache[MAX_N][MAX_N];
int dp(int n, int m) {
  if (n == m) return 1;
  int& ret = cache[n][m];
  if (ret != -1) return ret;
  int sum = 0;
  for (int i = 1; i <= n - m; i++) {
    if (m != 0) sum += (i + m - 1) * dp(n - m, i);
    else sum += dp(n - m, i);
    sum %= DIV_N;
  }
  ret = sum;
  return ret;
}
int main() {
  int C, n; cin >> C;
  fill(cache[0], cache[0] + MAX_N * MAX_N, -1);
  while (C--) {
    cin >> n;
    cout << dp(n, 0) << endl;
  }
  return 0;
}
