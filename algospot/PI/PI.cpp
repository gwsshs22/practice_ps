#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int dp[10001], MAX_VAL = 100000000;
char input[10001];
int eval(int s, int e) {
  if (s < 0) return 0;
  char t = input[s]; bool allSame = true;
  for (int i = s + 1; i <= e; i++)
    if (t != input[i]) {
      allSame = false;
      break;
    }
  if (allSame) return 1;

  int diff = input[s + 1] - input[s]; bool diffSame = true;
  for (int i = s + 1; i < e; i++)
    if ((input[i + 1] - input[i]) != diff) {
      diffSame = false;
      break;
    }
  if (diffSame) {
    if (diff == 1 || diff == -1) return 2;
    return 5;
  }

  char arr[2]; bool twoNumbers = true;
  arr[0] = input[s]; arr[1] = input[s + 1];
  for (int i = s + 2, idx = 0; i <= e; i++, idx++) {
    if (input[i] != arr[idx % 2]) {
      twoNumbers = false;
      break;
    }
  }
  if (twoNumbers) return 4;

  return 10;
}
int solve(int x) {
  if (x == -1) return 0;
  if (x < 2) return MAX_VAL;
  int& ret = dp[x];
  if (ret != -1) return ret;
  int minV = solve(x - 3) + eval(x - 2, x);
  minV = min(minV, solve(x - 4) + eval(x - 3, x));
  minV = min(minV, solve(x - 5) + eval(x - 4, x));
  ret = minV;
  return ret;
}
int main() {
  int C; cin >> C;
  while (C--) {
    cin >> input;
    int inputSize = strlen(input);
    fill(dp, dp + inputSize, -1);
    cout << solve(inputSize - 1) << endl;
  }
  return 0;
}
