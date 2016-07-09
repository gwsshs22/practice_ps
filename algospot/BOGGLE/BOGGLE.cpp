// https://www.algospot.com/judge/problem/read/BOGGLE
#include <iostream>

using namespace std;

int m[11][5][5];
char board[5][5];
const int dx[8] = {-1, -1, -1, 1, 1, 1, 0, 0};
const int dy[8] = {-1, 0, 1, -1, 0, 1, -1, 1};

bool hasWord(int x, int y, const string& word) {
  if (x < 0 || x > 4 || y < 0 || y > 4) return false;
  if (m[word.size()][x][y] != -1) {
    return m[word.size()][x][y];
  }

  bool result;
  if (board[x][y] != word[0]) {
    result = false;
  } else if (word.size() == 1) {
    result = true;
  } else {
    result = false;
    for (int direction = 0; direction < 8; direction++) {
      int nextX = x + dx[direction];
      int nextY = y + dy[direction];
      if (hasWord(nextX, nextY, word.substr(1))) {
        result = true;
        break;
      }
    }
  }
  m[word.size()][x][y] = result;
  return result;
}

bool hasWord(string& word) {
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      if (hasWord(i, j, word))
        return true;
  return false;
}

int main() {
  int C, N;
  string word;
  cin >> C;
  for (int iter = 0; iter < C; iter++) {
    for (int i = 0; i < 5; i++)
      for (int j = 0; j < 5; j++)
        cin >> board[i][j];

    cin >> N;
    for (int wordItr = 0; wordItr < N; wordItr++) {
      for (int i = 0; i < 11; i++)
        for (int j = 0; j < 5; j++)
          for (int k = 0; k < 5; k++) m[i][j][k] = -1;
      cin >> word;
      cout << word << " ";
      if (hasWord(word)) {
        cout << "YES" <<endl;
      } else {
        cout << "NO" << endl;
      }
    }
  }
  return 0;
}
