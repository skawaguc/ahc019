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
#include <cstdlib>
#include <iostream>
#include <tuple>
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

  // 乱数シードを固定
  srand(0);

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
  constexpr int K = 6;
  const int dx[K] = {-1, 1, 0, 0, 0, 0};
  const int dy[K] = {0, 0, -1, 1, 0, 0};
  const int dz[K] = {0, 0, 0, 0, -1, 1};
  constexpr int SEARCH_CNT = 1000;
  bool is_placeble_pos[2][D][D][D];
  for (int i = 0; i < 2; i++) {
    for (int x = 0; x < D; x++) {
      for (int y = 0; y < D; y++) {
        for (int z = 0; z < D; z++) {
          if (f[i][z][x] == '1' && r[i][z][y] == '1') {
            is_placeble_pos[i][x][y][z] = true;
          } else {
            is_placeble_pos[i][x][y][z] = false;
          }
        }
      }
    }
  }
  int n = 0;
  vector b(2, vector(D * D * D, 0));
  while (true) {
    vector placeable_pos(2, vector<tuple<int, int, int>>());
    for (int i = 0; i < 2; i++) {
      for (int x = 0; x < D; x++) {
        for (int y = 0; y < D; y++) {
          for (int z = 0; z < D; z++) {
            if (is_placeble_pos[i][x][y][z]) {
              placeable_pos[i].push_back(make_tuple(x, y, z));
            }
          }
        }
      }
    }
    // どちらかのシルエットについて、配置可能な場所が存在しない
    bool has_placeable_pos = true;
    for (int i = 0; i < 2; i++) {
      if (placeable_pos[i].size() == 0) has_placeable_pos = false;
    }
    if (!has_placeable_pos) break;
    // （乱択）貪欲法
    vector max_blocks(2, vector<tuple<int, int, int>>());
    for (int search_cnt = 0; search_cnt < SEARCH_CNT; search_cnt++) {
      // ランダムに配置可能場所を選び、ランダムな一方向にそれぞれ伸ばしていく
      vector blocks(2, vector<tuple<int, int, int>>());
      vector k(2, 0);
      for (int i = 0; i < 2; i++) {
        blocks[i].push_back(placeable_pos[i][rand() % placeable_pos[i].size()]);
        k[i] = rand() % K;
      }
      while (true) {
        vector next_block(2, tuple<int, int, int>());
        bool can_go = true;
        for (int i = 0; i < 2; i++) {
          int x, y, z;
          tie(x, y, z) = *blocks[i].rbegin();
          const int nx = x + dx[k[i]], ny = y + dy[k[i]], nz = z + dz[k[i]];
          if (nx < 0 || D <= nx || ny < 0 || D <= ny || nz < 0 || D <= nz) {
            can_go = false;
            break;
          }
          if (!is_placeble_pos[i][nx][ny][nz]) {
            can_go = false;
            break;
          }
          next_block[i] = make_tuple(nx, ny, nz);
        }
        if (!can_go) break;
        for (int i = 0; i < 2; i++) blocks[i].push_back(next_block[i]);
      }
      for (int i = 0; i < 2; i++) {
        if (max_blocks[i].size() < blocks[i].size()) max_blocks[i] = blocks[i];
      }
    }
    n++;
    for (int i = 0; i < 2; i++) {
      for (const tuple<int, int, int> xyz : max_blocks[i]) {
        int x, y, z;
        tie(x, y, z) = xyz;
        b[i][x * D * D + y * D + z] = n;
        is_placeble_pos[i][x][y][z] = false;
      }
    }
  }
  // 残りの配置可能場所について、配置必要であれば配置
  for (int i = 0; i < 2; i++) {
    for (int x = 0; x < D; x++) {
      for (int y = 0; y < D; y++) {
        for (int z = 0; z < D; z++) {
          if (!is_placeble_pos[i][x][y][z]) continue;
          bool needed1 = true;
          for (int ny = 0; ny < D; ny++) {
            if (b[i][x * D * D + ny * D + z] > 0) needed1 = false;
          }
          bool needed2 = true;
          for (int nx = 0; nx < D; nx++) {
            if (b[i][nx * D * D + y * D + z] > 0) needed2 = false;
          }
          if (!needed1 && !needed2) continue;
          n++;
          b[i][x * D * D + y * D + z] = n;
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
