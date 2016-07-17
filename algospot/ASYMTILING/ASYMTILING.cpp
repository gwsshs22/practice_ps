#include <iostream>
#include <algorithm>
#define DIV_VAL 1000000007
using namespace std;
int cache[101], cache1[101];
int all(int n) {
  int& ret = cache[n];
  if (ret != -1) return ret;
  ret = (all(n - 1) + all(n - 2)) % DIV_VAL;
  return ret;
}

int sym(int n) {
  int& ret = cache1[n];
  if (ret != -1) return ret;
  ret = (sym(n - 2) + sym(n - 4)) % DIV_VAL;
  return ret;
}

int main() {
  int C, n; cin >> C;
  fill(cache, cache + 101, -1);
  fill(cache1, cache1 + 101, -1);
  cache[0] = 1, cache[1] = 1;
  cache1[0] = 1, cache1[1] = 2; cache1[2] = 2; cache1[3] = 1;
  while (C--) {
    cin >> n;
    int sol = all(n) - sym(n);
    if (sol < 0) sol += DIV_VAL;
    cout << sol << endl;
  }
  return 0;
}
