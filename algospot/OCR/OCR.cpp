#include <iostream>
#include <cmath>
#include <map>
#include <limits>
#define MAX_M 501
#define MAX_N 101
using namespace std;
map<string, int> wordMap;
map<int, string> reverseWordMap;
int M, N;
double pNear[MAX_M][MAX_M], pClassify[MAX_M][MAX_M], MIN_DOUBLE = -numeric_limits<double>::max() / 4;

double prob[MAX_N][MAX_M];
int input[MAX_N], output[MAX_N], prevSelect[MAX_N][MAX_M];

void solve() {
  for (int i = 0; i <= N; i++) for (int j = 0; j <= M; j++) prob[i][j] = 0.0;
  for (int word = 1; word <= M; word++) {
    prob[1][word] = pNear[0][word] + pClassify[word][input[1]];
  }

  for (int wordIdx = 2; wordIdx <= N; wordIdx++) {
    for (int word = 1; word <= M; word++) {
      double pc = pClassify[word][input[wordIdx]];
      double maxV = MIN_DOUBLE;
      for (int prevWord = 1; prevWord <= M; prevWord++) {
        double pn = pNear[prevWord][word];
        double prevP = prob[wordIdx - 1][prevWord];
        double p = pn + pc + prevP;
        if (maxV < p) {
          maxV = p;
          prevSelect[wordIdx][word] = prevWord;
        }
      }

      prob[wordIdx][word] = maxV;
    }
  }

  double maxV = MIN_DOUBLE;
  int maxWord = -1;
  for (int word = 1; word <= M; word++) {
    double p = prob[N][word];
    if (p != 1 && p > maxV) {
      maxWord = word;
      maxV = p;
    }
  }

  output[N] = maxWord;
  for (int i = N - 1; i >= 1; i--) {
    output[i] = prevSelect[i + 1][output[i + 1]];
  }
}

double toLogP(double p) {
  if (p == 0) return MIN_DOUBLE;
  else return log(p);
}

int main() {
  int q; cin >> M >> q;
  string word;
  for (int i = 1; i <= M; i++) {
    cin >> word;
    wordMap[word] = i;
    reverseWordMap[i] = word;
  }
  for (int i = 1; i <= M; i++) {
    double p;
    cin >> p;
    pNear[0][i] = toLogP(p);
  }
  for (int i = 1; i <= M; i++)
    for (int j = 1; j <= M; j++) {
      double p;
      cin >> p;
      pNear[i][j] = toLogP(p);
    }
  for (int i = 1; i <= M; i++)
    for (int j = 1; j <= M; j++) {
      double p;
      cin >> p;
      pClassify[i][j] = toLogP(p);
    }

  for (int i = 0; i < q; i++) {
    cin >> N;
    string word;
    for (int j = 1; j <= N; j++) {
      cin >> word;
      input[j] = wordMap[word];
    }

    solve();
    cout << reverseWordMap[output[1]];
    for (int j = 2; j <= N; j++)
      cout << ' ' << reverseWordMap[output[j]];
    cout << endl;
  }
  return 0;
}
