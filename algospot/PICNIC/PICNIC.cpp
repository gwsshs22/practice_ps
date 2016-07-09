// https://www.algospot.com/judge/problem/read/PICNIC
#include <iostream>
#include <algorithm>
using namespace std;
bool areFriends[10][10];
int N, M;

int getNumberOfPairs(bool matched[10]) {
  int notMatched = -1;
  for (int i = 0; i < N; i++) {
    if (!matched[i]) {
      notMatched = i;
      break;
    }
  }

  if (notMatched == -1) return 1;
  int num = 0;
  for (int i = notMatched + 1; i < N; i++) {
    if (!matched[i] && areFriends[notMatched][i]) {
      matched[notMatched] = matched[i] = true;
      num += getNumberOfPairs(matched);
      matched[notMatched] = matched[i] = false;
    }
  }

  return num;
}

int main() {
  int C;
  cin >> C;
  for (int pItr = 0; pItr < C; pItr++) {
    cin >> N >> M;
    fill(&areFriends[0][0], &areFriends[0][0] + sizeof(areFriends), false);
    for (int i = 0; i < M; i++) {
      int s, e;
      cin >> s >> e;
      areFriends[e][s] = areFriends[s][e] = true;
    }
    bool matched[10];
    fill(&matched[0], &matched[0] + sizeof(matched), false);
    cout << getNumberOfPairs(matched) << endl;
  }
  return 0;
}
