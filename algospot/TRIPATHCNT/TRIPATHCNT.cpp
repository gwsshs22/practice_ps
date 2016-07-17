// https://www.algospot.com/judge/problem/read/TRIPATHCNT
#include <iostream>
#include <algorithm>
using namespace std;
int triangle[101][101], N, cache[101][101], cnt[101][101];
int getCnt(int r, int c) {
  if (c < 0 || r < c) return 0;
  return cnt[r][c];
}
int getMaxPath(int r, int c) {
  if (c < 0 || r < c) return 0;
  int& ret = cache[r][c];
  if (ret != -1) return ret;
  int fromLeft = triangle[r][c] + getMaxPath(r - 1, c - 1);
  int fromUp = triangle[r][c] + getMaxPath(r - 1, c);
  if (fromLeft == fromUp) {
    ret = fromLeft;
    cnt[r][c] = getCnt(r - 1, c) + getCnt(r - 1, c - 1);
  } else if (fromLeft > fromUp) {
    ret = fromLeft;
    cnt[r][c] = getCnt(r - 1, c - 1);
  } else {
    ret = fromUp;
    cnt[r][c] = getCnt(r - 1, c);
  }
  return ret;
}
int main() {
  int C; cin >> C;
  while (C--) {
    cin >> N;
    for (int i = 0; i < N; i++)
      for (int j = 0; j <= i; j++)
        cin >> triangle[i][j];
    fill(cache[0], cache[0] + 101 * 101, -1);
    cnt[0][0] = 1;
    cache[0][0] = triangle[0][0];
    int maxV = 0, sol = 0;
    for (int i = 0; i < N; i++) {
      int t = getMaxPath(N - 1, i);
      if (t > maxV) {
        maxV = t;
        sol = 0;
      }

      if (t == maxV) sol += getCnt(N - 1, i);
    }

    cout << sol << endl;
  }
  return 0;
}
