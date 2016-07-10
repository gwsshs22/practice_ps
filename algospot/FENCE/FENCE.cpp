// https://www.algospot.com/judge/problem/read/FENCE
// Using divede and conquer.
#include <iostream>
#include <algorithm>
using namespace std;
int heights[20000], N;
int solve(int s, int e) {
  if (s == e) return heights[s];
  int mid = (s + e) / 2;
  int lItr = mid, rItr = mid + 1;
  int minHeight = 10001;
  int maxArea = -1;
  while (s <= lItr && rItr <= e) {
    minHeight = min(min(minHeight, heights[lItr]), heights[rItr]);
    maxArea = max(maxArea, minHeight * (rItr - lItr + 1));
    if (lItr == s) rItr++;
    else if (rItr == e) lItr--;
    else {
      if (heights[rItr + 1] > heights[lItr - 1]) rItr++;
      else lItr--;
    }
  }
  maxArea = max(solve(s, mid) ,maxArea);
  maxArea = max(solve(mid + 1, e), maxArea);
  return maxArea;
}
int main() {
  int C; cin >> C;
  while (C--) {
    cin >> N;
    for (int i = 0; i < N; i++)
      cin >> heights[i];
    cout << solve(0, N - 1) << endl;
  }
  return 0;
}
