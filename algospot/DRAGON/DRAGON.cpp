#include <iostream>
#include <algorithm>

using namespace std;
long long lenCurves[51];
string curves[7];
string getCurveStr(int n, int p, int l, char midOp) {
  if (l == 0) return "";
  if (n <= 6) {
    if (n != 0)
      curves[n][lenCurves[n] / 2] = midOp;
    return curves[n].substr(p - 1, l);
  }

  long long halfLen = lenCurves[n] / 2;
  if (p + l - 1 <= halfLen)
    return getCurveStr(n - 1, p, l, '+');
  else if (p >= halfLen + 2)
    return getCurveStr(n - 1, p - (halfLen + 1), l, '-');
  else {
    int leftLen = halfLen + 1 - p;
    int rightLen = l - leftLen - 1;
    return getCurveStr(n - 1, p, leftLen, '+') + midOp + getCurveStr(n - 1, 1, rightLen, '-');
  }
}

int main() {
  int C; cin >> C;
  curves[0] = "FX";
  for (int i = 1; i < 7; i++) {
    curves[i] = "";
    string& prevCurve = curves[i - 1];
    for (int j = 0; j < prevCurve.size(); j++) {
      if (prevCurve[j] == 'X') curves[i] += "X+YF";
      else if (prevCurve[j] == 'Y') curves[i] += "FX-Y";
      else curves[i] += prevCurve[j];
    }
  }
  lenCurves[0] = 2;
  for (int i = 1; i < 51; i++) lenCurves[i] = 2 * lenCurves[i - 1] + 1;
  while (C--) {
    int n, p, l;
    cin >> n >> p >> l;
    cout << getCurveStr(n, p, l, '+') << endl;
  }
  return 0;
}
