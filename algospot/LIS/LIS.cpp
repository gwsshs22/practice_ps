// https://www.algospot.com/judge/problem/read/LIS
#include <iostream>
using namespace std;
int N, best[501], bestIdx;

int bSearch(int s, int e, int v) {
  int mid = (s + e) / 2;
  if (best[mid - 1] < v && v <= best[mid]) return mid;
  else if (best[mid - 1] < v) return bSearch(mid + 1, e, v);
  return bSearch(s, mid - 1, v);
}

int main() {
  int C, t, s, e; cin >> C;
  while (C--) {
    cin >> N;
    bestIdx = 0;
    best[0] = -1;
    for (int i = 0; i < N; i++) {
      cin >> t;
      if (best[bestIdx] < t) best[++bestIdx] = t;
      else best[bSearch(1, bestIdx, t)] = t;
    }
    cout << bestIdx << endl;
  }
  return 0;
}
