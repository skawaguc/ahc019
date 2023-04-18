/**
 * @file main.cpp
 * @author skawaguc
 * @brief https://atcoder.jp/contests/ahc019
 * @version 0.1
 * @date 2023-04-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <vector>
using namespace std;

int D;
vector<vector<string>> f, r;

void get_input();
void solve();

/**
 * @brief メイン処理.
 *
 * @return int 0
 */
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  // 標準入力を取得
  get_input();

  // 求解処理
  solve();

  return 0;
}

/**
 * @brief 標準入力を取得する.
 *
 */
void get_input() {
  cin >> D;
  f.resize(2, vector<string>(D));
  r.resize(2, vector<string>(D));
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < D; j++) cin >> f[i][j];
    for (int j = 0; j < D; j++) cin >> r[i][j];
  }
}

/**
 * @brief 求解処理.
 *
 */
void solve() {
  int n = 0;
  vector b(2, vector(D * D * D, 0));
  for (int i = 0; i < 2; i++) {
    for (int x = 0; x < D; x++) {
      for (int y = 0; y < D; y++) {
        for (int z = 0; z < D; z++) {
          if (f[i][z][x] == '1' && r[i][z][y] == '1') {
            n++;
            b[i][x * D * D + y * D + z] = n;
          }
        }
      }
    }
  }

  // 結果出力
  cout << n << endl;
  for (int i = 0; i < D * D * D; i++) {
    if (i) cout << " ";
    cout << b[0][i];
  }
  cout << endl;
  for (int i = 0; i < D * D * D; i++) {
    if (i) cout << " ";
    cout << b[1][i];
  }
  cout << endl;
}
