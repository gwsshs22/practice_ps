// https://algospot.com/judge/problem/read/FANMEETING
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// a += b * 2 ^ k
void add(vector<int>& a, const vector<int>& b, int k) {
  int aSize = a.size(), bSize = b.size();
  for (int i = 0; i < (bSize + k) - aSize; i++) {
    a.push_back(0);
  }
  for (int i = 0; i < bSize; i++) a[i + k] += b[i];
}

// a -= b
void subtract(vector<int>& a, const vector<int>& b) {
  for (int i = 0; i < b.size(); i++) a[i] -= b[i];
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
  int aSize = a.size(), bSize = b.size();
  vector<int> ret;
  vector<int> tmp(aSize);
  for (int i = 0; i < bSize; i++) {
    for (int j = 0; j < aSize; j++) {
      tmp[j] = b[i] * a[j];
    }
    add(ret, tmp, i);
  }
  return ret;
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
  int aSize = a.size(), bSize = b.size(), half = aSize / 2;
  if (aSize < bSize) return karatsuba(b, a);
  if (bSize == 0) return vector<int>();
  if (aSize <= 100) return multiply(a, b);
  vector<int> a0 = vector<int>(a.begin(), a.begin() + half);
  vector<int> a1 = vector<int>(a.begin() + half, a.end());
  vector<int> b0 = vector<int>(b.begin(), b.begin() + min(half, (int)b.size()));
  vector<int> b1 = vector<int>(b.begin() + min(half, (int)b.size()), b.end());
  vector<int> z0 = karatsuba(a0, b0);
  vector<int> z1 = karatsuba(a1, b1);

  add(a0, a1, 0);
  add(b0, b1, 0);
  vector<int> z2 = karatsuba(a0, b0); // (a1 + a0) * (b1 * b0)
  subtract(z2, z0);
  subtract(z2, z1);

  add(z0, z1, 2 * half);
  add(z0, z2, half);
  return z0;
}

int main() {
  int C; cin >> C;
  while (C--) {
    string m, f;
    cin >> m >> f;
    int aSize = m.size(), bSize = f.size(), ans = 0;
    vector<int> a(aSize), b(bSize);
    for (int i = 0; i < aSize; i++) a[i] = (m[i] == 'M');
    for (int i = 0; i < bSize; i++) b[i] = (f[bSize - 1 - i] == 'M');
    vector<int> result = karatsuba(b, a);
    for (int i = aSize - 1; i < bSize; i++)
      if (result[i] == 0) ans++;
    cout << ans << endl;
  }
  return 0;
}
