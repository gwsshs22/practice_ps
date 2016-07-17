#include <iostream>
#include <algorithm>
#define DIV_VAL 1000000007
using namespace std;
int cache[101];
int all(int n) {
  int& ret = cache[n];
  if (ret != -1) return ret;
  ret = (all(n - 1) + all(n - 2)) % DIV_VAL;
  return ret;
}

int main() {
  int C, n; cin >> C;
  fill(cache, cache + 101, -1);
  cache[0] = 1, cache[1] = 1;
  while (C--) {
    cin >> n;
    cout << all(n) << endl;
  }
  return 0;
}
