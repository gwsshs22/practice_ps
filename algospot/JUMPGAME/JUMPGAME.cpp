// https://www.algospot.com/judge/problem/read/JUMPGAME
#include <iostream>
#include <algorithm>
using namespace std;
bool canTouch[100][100];
int N, board[100][100];

void set(int x, int y) {
  if (0 <= x && x < N && 0 <= y && y < N) {
    canTouch[x][y] = true;
  }
}

void solve() {
  canTouch[0][0] = true;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (canTouch[i][j]) {
        set(i + board[i][j], j);
        set(i, j + board[i][j]);
      }
    }
  }
  if (canTouch[N-1][N-1]) cout << "YES" << endl;
  else cout << "NO" << endl;
}
int main() {
  cin.sync_with_stdio(false);
  int C; cin >> C;
  while (C--) {
    cin >> N;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        cin >> board[i][j];
    fill(canTouch[0], canTouch[0] + 100 * 100, false);
    solve();
  }
  return 0;
}
