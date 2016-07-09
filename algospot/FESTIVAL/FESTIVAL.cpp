// https://www.algospot.com/judge/problem/read/FESTIVAL
#include <iostream>
#include <algorithm>
using namespace std;
int N, L, arr[1000];
double acc[1000];
double solve() {
  double lo = 0.0, hi = 100.0;
  int t = 100;
  while (hi - lo >= 1e-8) {
    double x = (lo + hi) / 2;
    acc[0] = arr[0] - x;
    for (int i = 0; i < N; i++)
      acc[i] = acc[i - 1] + arr[i] - x;

    double prevMaxSum = 0.0;
    double minSum = 200.0 * 1000.0;
    for (int i = L - 1; i < N; i++) {
      minSum = min(minSum, acc[i] - prevMaxSum);
      prevMaxSum = max(prevMaxSum, acc[i - L + 1]);
    }

    if (minSum < 0) {
      hi = x;
    } else {
      lo = x;
    }
  }

  return lo;
}

int main() {
  int C;
  cin >> C;
  cout.precision(16);
  for (int pItr = 0; pItr < C; pItr++) {
    cin >> N >> L;
    for (int i = 0; i < N; i++) {
      cin >> arr[i];
    }
    cout << fixed << solve() << endl;
  }
}
