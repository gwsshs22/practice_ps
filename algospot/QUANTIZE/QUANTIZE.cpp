#include <iostream>
#include <algorithm>
#define MAX_NUM 1002
using namespace std;
int arr[MAX_NUM], S, N, MIN_V, MAX_V, cache[11][MAX_NUM];
int rightSquareSum[MAX_NUM][MAX_NUM];

int dp(int s, int n) {
  int& ret = cache[s][n];
  if (ret != -1) return ret;
  int minV = 2000000000;
  for (int prevPoint = MIN_V; prevPoint <= n; prevPoint++) {
    int mid = (prevPoint + n) / 2;
    int squareSum = dp(s - 1, prevPoint);
    squareSum -= rightSquareSum[prevPoint][mid + 1];
    squareSum += rightSquareSum[n][mid + 1];
    if (squareSum < minV) minV = squareSum;
  }
  ret = minV;
  return ret;
}

int solve() {
  for (int pivot = MIN_V; pivot <= MAX_V; pivot++) {
    int squareSum = 0;
    for (int right = MAX_V; right >= MIN_V; right--) {
      squareSum += arr[right] * (right - pivot) * (right - pivot);
      rightSquareSum[pivot][right] = squareSum;
    }

    cache[1][pivot] = squareSum;
  }

  int minV = 2000000000;
  for (int i = MIN_V; i <= MAX_V; i++) {
    int t = dp(S, i);
    if (t < minV) minV = t;
  }

  return minV;
}

int main() {
  int C, t; cin >> C;
  while (C--) {
    cin >> N >> S;
    MIN_V = 1001, MAX_V = -1;
    fill(arr, arr + MAX_NUM, 0);
    fill(rightSquareSum[0], rightSquareSum[0] + MAX_NUM * MAX_NUM, 0);
    fill(cache[0], cache[0] + 11 * MAX_NUM, -1);
    for (int i = 0; i < N; i++) {
      cin >> t;
      arr[t]++;
      if (t < MIN_V) MIN_V = t;
      if (t > MAX_V) MAX_V = t;
    }
    cout << solve() << endl;
  }
  return 0;
}
