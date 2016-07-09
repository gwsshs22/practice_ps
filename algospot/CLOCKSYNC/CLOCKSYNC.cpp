// https://www.algospot.com/judge/problem/read/CLOCKSYNC
#include <iostream>
#include <vector>
using namespace std;
bool finish;
int answer;
vector<vector<int>> buttonToClock({
    vector<int>({ 0, 1, 2 }),
    vector<int>({ 3, 7, 9, 11 }),
    vector<int>({ 4, 10, 14, 15 }),
    vector<int>({ 0, 4, 5, 6, 7 }),
    vector<int>({ 6, 7, 8, 10, 12 }),
    vector<int>({ 0, 2, 14, 15 }),
    vector<int>({ 3, 14, 15 }),
    vector<int>({ 4, 5, 7, 14, 15 }),
    vector<int>({ 1, 2, 3, 4, 5 }),
    vector<int>({ 3, 4, 5, 9, 13 })
});

vector<vector<int>> clockToButton({});

void click(vector<int>& clockStates, vector<int>& buttons, vector<int>& nums, bool restore) {
  for (int i = 0; i < buttons.size(); i++) {
    vector<int>& button = buttonToClock[buttons[i]];
    for (int j = 0; j < button.size(); j++) {
      if (!restore) {
        clockStates[button[j]] += nums[i];
      } else {
        clockStates[button[j]] += (4 - nums[i]);
      }
      if (clockStates[button[j]] >= 5)
        clockStates[button[j]] -= 4;
    }
  }
}

void generateClicks(int remained, vector<int>& container, vector<vector<int>>& acc, int numToClick) {
  if (remained == 0) {
    if (numToClick == 0) {
      vector<int> copied = container;
      acc.push_back(copied);
    }
    return;
  }

  for (int i = 0; i < 4; i++) {
    if (numToClick >= i) {
      container.push_back(i);
      generateClicks(remained - 1, container, acc, numToClick - i);
      container.pop_back();
    }
  }
}

void solve(int clockIdx, vector<int>& clockStates, bool usedButtons[10], int numClicks) {
  if (finish) return;
  if (clockIdx == 16) {
    finish = true;
    answer = numClicks;
    return;
  }
  int currentClockState = clockStates[clockIdx];
  vector<int> possibleButtons;
  for (int i = 0; i < clockToButton[clockIdx].size(); i++) {
    int buttonIdx = clockToButton[clockIdx][i];
    if (!usedButtons[buttonIdx]) {
      possibleButtons.push_back(buttonIdx);
    }
  }

  if (currentClockState != 4 && possibleButtons.size() == 0) {
    return;
  }

  for (int i = 0; i < possibleButtons.size(); i++) {
    usedButtons[possibleButtons[i]] = true;
  }

  int numToClick = 4 - currentClockState;
  while (numToClick  <= possibleButtons.size() * 3) {
    vector<vector<int>> possibleClicks;
    vector<int> emptyContainer;
    generateClicks(possibleButtons.size(), emptyContainer, possibleClicks, numToClick);
    for (int i = 0; i < possibleClicks.size(); i++) {
      click(clockStates, possibleButtons, possibleClicks[i], false);
      solve(clockIdx + 1, clockStates, usedButtons, numClicks + numToClick);
      click(clockStates, possibleButtons, possibleClicks[i], true);
    }
    numToClick += 4;
  }

  for (int i = 0; i < possibleButtons.size(); i++) {
    usedButtons[possibleButtons[i]] = false;
  }
}

int main() {
  for (int i = 0; i < 16; i++) clockToButton.push_back(vector<int>({}));
  for (int i = 0; i < buttonToClock.size(); i++) {
    for (int j = 0; j < buttonToClock[i].size(); j++) {
      clockToButton[buttonToClock[i][j]].push_back(i);
    }
  }

  int C;
  cin >> C;
  for (int pItr = 0; pItr < C; pItr++) {
    finish = false;
    answer = -1;
    vector<int> clockStates;
    for (int i = 0; i < 16; i++) {
      int state;
      cin >> state;
      clockStates.push_back(state / 3);
    }

    bool usedButtons[10] = {false, };
    solve(0, clockStates, usedButtons, 0);

    cout << answer << endl;
  }

  return 0;
}
