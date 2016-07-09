// https://www.algospot.com/judge/problem/read/BOARDCOVER
#include <iostream>
using namespace std;
int H, W;
char board[20][20];
int dx[4][3] = {
  {0, 0, 1},
  {0, 0, 1},
  {0, 1, 1},
  {0, 1, 1}
};
int dy[4][3] = {
  {0, 1, 0},
  {0, 1, 1},
  {0, 0, -1},
  {0, 0, 1}
};

bool isPossibleBlock(int x, int y) {
  if (x < 0 || x >= H || y < 0 || y >= W) return false;
  return board[x][y] == '.';
}

int solve() {
  int x = -1, y = -1;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++)
      if (board[i][j] == '.') {
        x = i;
        y = j;
        break;
      }
    if (x != -1) break;
  }
  if (x == -1) return 1;
  int sum = 0;
  for (int typeIdx = 0; typeIdx < 4; typeIdx++) {
    bool isPossible = true;
    for (int bIdx = 0; bIdx < 3; bIdx++) {
      if (!isPossibleBlock(x + dx[typeIdx][bIdx], y + dy[typeIdx][bIdx])) {
        isPossible = false;
        break;
      }
    }

    if (isPossible) {
      for (int bIdx = 0; bIdx < 3; bIdx++) board[x + dx[typeIdx][bIdx]][y + dy[typeIdx][bIdx]] = '#';
      sum += solve();
      for (int bIdx = 0; bIdx < 3; bIdx++) board[x + dx[typeIdx][bIdx]][y + dy[typeIdx][bIdx]] = '.';
    }
  }

  return sum;
}

int main() {
  int C;
  cin >> C;
  for (int pItr = 0; pItr < C; pItr++) {
    cin >> H >> W;
    for (int i = 0; i < H; i++)
      for (int j = 0; j < W; j++)
        cin >> board[i][j];
    cout << solve() << endl;
  }
  return 0;
}
