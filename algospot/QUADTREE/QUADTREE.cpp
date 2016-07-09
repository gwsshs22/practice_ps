// https://www.algospot.com/judge/problem/read/QUADTREE
#include <iostream>
using namespace std;
string flip(string::iterator& it) {
  char head = *it;
  ++it;
  if (head != 'x')
    return string(1, head);

  string subtree[4];
  for (int i = 0; i < 4; i++)
    subtree[i] = flip(it);
  return "x" + subtree[2] + subtree[3] + subtree[0] + subtree[1];
}

int main() {
  int C; cin >> C;
  while (C--) {
    string tree;
    cin >> tree;
    string::iterator it = tree.begin();
    cout << flip(it) << endl;
  }
  return 0;
}
