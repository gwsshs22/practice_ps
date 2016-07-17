#include <iostream>
#include <algorithm>
#define MAX_N 1001
using namespace std;
double cache[MAX_N][MAX_N];
double dp(int n, int m) {
  if (n <= m) return 1.0;
  if (n > 2 * m) return 0.0;
  double& ret = cache[n][m];
  if (ret >= 0) return ret;

  ret = 0.25 * dp(n - 1, m - 1) + 0.75 * dp(n - 2, m - 1);
  return ret;
}
int main() {
  int C; cin >> C;
  cout.precision(12);
  fill(cache[0], cache[0] + MAX_N * MAX_N, -1.0);
  while (C--) {
    int n, m;
    cin >> n >> m;
    cout << fixed << dp(n, m) << endl;
  }
  return 0;
}
