// https://algospot.com/judge/problem/read/JLIS
#include <iostream>
#include <limits>
#include <algorithm>
#define MAX_N 102
using namespace std;
long long a[MAX_N], b[MAX_N];
int aLen, bLen, dp[MAX_N][MAX_N];
int jlis(int x, int y) {
  int& ret = dp[x][y];
  if (ret != -1) return ret;
  long long currentV = max(a[x], b[y]);
  int maxVX = -1;
  for (int i = 0; i < x; i++)
    if (a[i] < currentV) {
      maxVX = max(maxVX, jlis(i, y));
    }

  int maxVY = -1;
  for (int i = 0; i < y; i++)
    if (b[i] < currentV) {
      maxVY = max(maxVY, jlis(x, i));
    }

  if (a[x] == b[y]) ret = max(maxVX, maxVY);
  else if (a[x] > b[y]) ret = maxVX + 1;
  else ret = maxVY + 1;
  return ret;
}
int main() {
  int C; cin >> C;
  a[0] = b[0] = numeric_limits<long long>::min();
  while (C--) {
    cin >> aLen >> bLen;
    for (int i = 1; i <= aLen; i++) cin >> a[i];
    for (int i = 1; i <= bLen; i++) cin >> b[i];
    fill(dp[0], dp[0] + MAX_N * MAX_N, -1);
    dp[0][0] = 0;
    a[aLen + 1] = b[bLen + 1] = numeric_limits<long long>::max();
    cout << jlis(aLen + 1, bLen + 1) - 1 << endl;
  }
  return 0;
}
