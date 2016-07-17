#include <iostream>
#include <algorithm>
#include <vector>
#define MAX_N 50
#define MAX_D 101
using namespace std;
int N, D;
double prob[MAX_D][MAX_N];
vector<int> edge[MAX_N];
void cal() {
  for (int day = 1; day <= D; day++) {
    for (int town = 0; town < N; town++) {
      int adjNum = edge[town].size();
      double p = prob[day - 1][town];
      if (adjNum != 0) p /= adjNum;
      for (int i = 0; i < adjNum; i++) {
        prob[day][edge[town][i]] += p;
      }
    }
  }
}
int main() {
  int C; cin >> C;
  cout.precision(12);
  while (C--) {
    int p;
    cin >> N >> D >> p;
    fill(prob[0], prob[0] + MAX_N * MAX_D, 0.0);
    for (int i = 0; i < N; i++) edge[i].clear();
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++) {
        bool connected;
        cin >> connected;
        if (connected)
          edge[i].push_back(j);
      }
    prob[0][p] = 1.0;
    cal();
    int t, q;
    cin >> t;
    for (int i = 0; i < t; i++) {
      cin >> q;
      cout << fixed << prob[D][q];
      if (i < t - 1) cout << ' ';
      else cout << endl;
    }
  }
  return 0;
}
