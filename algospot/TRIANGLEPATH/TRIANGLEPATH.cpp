// https://www.algospot.com/judge/problem/read/TRIANGLEPATH
#include <iostream>
#include <algorithm>
using namespace std;
int triangle[101][101], N, cache[101][101];
int getMaxPath(int r, int c) {
  if (c < 0 || r < c) return 0;
  int& ret = cache[r][c];
  if (ret != -1) return ret;
  ret = triangle[r][c] + max(getMaxPath(r - 1, c), getMaxPath(r - 1, c - 1));
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
    int maxV = 0;
    for (int i = 0; i < N; i++)
      maxV = max(maxV, getMaxPath(N - 1, i));
    cout << maxV << endl;
  }
  return 0;
}
