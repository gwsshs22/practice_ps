// https://www.algospot.com/judge/problem/read/WILDCARD
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
string pattern, word;
int cache[101][101];
int pSize, wSize;
bool matched(int pIdx, int wIdx) {
  if (pIdx == pSize) {
    return wIdx == wSize;
  }

  int& ret = cache[pIdx][wIdx];
  if (ret != -1) return ret;

  if (pattern[pIdx] == '*') {
    ret = matched(pIdx + 1, wIdx) || ((wIdx <= wSize) && matched(pIdx, wIdx + 1));
    return ret;
  } else if (pattern[pIdx] == '?') {
    ret = matched(pIdx + 1, wIdx + 1);
    return ret;
  } else {
    ret = pattern[pIdx] == word[wIdx] && matched(pIdx + 1, wIdx + 1);
    return ret;
  }
}

int main() {
  int C, N; cin >> C;
  while (C--) {
    cin >> pattern >> N;
    pSize = pattern.size();
    set<string> wordSet;
    for (int i = 0; i < N; i++) {
      cin >> word;
      wSize = word.size();
      fill(cache[0], cache[0] + 101 * 101, -1);
      if (matched(0, 0))
        wordSet.insert(word);
    }
    for (auto word : wordSet) {
      cout << word << endl;
    }
  }
  return 0;
}
