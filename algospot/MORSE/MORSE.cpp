#include <iostream>
#include <algorithm>

using namespace std;
long long c[201][201];
void solve(int n, int m, int k) {
  if (n >= 1 && k <= c[n+m-1][n-1]) {
    cout << '-';
    solve(n-1, m, k);
  } else if (m >= 1) {
    cout << 'o';
    int left = n == 0 ? 0 : c[n+m-1][n-1];
    solve(n, m-1, k-left);
  }
}

int main() {
  int C; cin >> C;
  for (int i = 0; i < 201; i++)
    c[i][0] = c[i][i] = 1;
  for (int i = 1; i < 201; i++)
    for (int j = 1; j < i; j++) {
      c[i][j] = c[i-1][j] + c[i-1][j-1];
      c[i][j] %= 1000000000000000000;
    }

  while (C--) {
    int n, m, k;
    cin >> n >> m >> k;
    solve(n, m, k);
    cout << endl;
  }
  return 0;
}
