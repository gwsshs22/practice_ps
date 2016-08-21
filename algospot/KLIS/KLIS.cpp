#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 501
using namespace std;
vector<int> nextIndices[MAX_N];
int N, arr[MAX_N], dp[MAX_N];
long long numLISs[MAX_N];
int solve(int index) {
  int& ret = dp[index];
  if (ret != -1) return ret;
  int maxV = 1;
  vector<int>& nextList = nextIndices[index];
  for (int next = index + 1; next <= N; next++) {
    int nextElement = arr[next];
    if (arr[index] < nextElement) {
      int tmp = solve(next) + 1;
      if (maxV < tmp) {
        maxV = tmp;
        nextList.clear();
        numLISs[index] = 0;
      }

      if (maxV == tmp) {
        nextList.push_back(next);
        numLISs[index] += numLISs[next];
        numLISs[index] %= 20000000000000;
      }
    }
  }

  ret = maxV;
  return ret;
}

void count(int index, int k, vector<int>& solution) {
  vector<int>& nextList = nextIndices[index];
  if (nextList.size() == 0) return;
  sort(nextList.begin(), nextList.end(),
    [](const int& a, const int& b) {
      return arr[a] < arr[b];
    });
  int nextIndex;
  for (int i = 0 ; i < nextList.size(); i++) {
    nextIndex = nextList[i];
    if (k <= numLISs[nextIndex])
      break;
    else
      k -= numLISs[nextIndex];
  }

  solution.push_back(arr[nextIndex]);
  count(nextIndex, k, solution);
}

int main() {
  int C; cin >> C;
  while (C--) {
    int k;
    cin >> N >> k;
    nextIndices[0].clear();
    for (int i = 1; i <= N; i++) {
      cin >> arr[i];
      nextIndices[i].clear();
    }
    fill(dp, dp + MAX_N, -1);
    fill(numLISs, numLISs + MAX_N, 1);
    cout << solve(0) - 1 << endl;
    vector<int> solution;
    count(0, k, solution);
    cout << solution[0];
    for (int i = 1; i < solution.size(); i++)
      cout << ' ' << solution[i];
    cout << endl;
  }
}
