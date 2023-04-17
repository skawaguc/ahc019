from __future__ import annotations
import itertools


def get_input() -> tuple[int, list[list[int]], list[list[int]]]:
    """標準入力を取得する.

    Returns:
        tuple[int, list[list[int]], list[list[int]]]: シルエット画像の大きさ、i番目のシルエット画像の組であり正面/右側から見たシルエット
    """
    # シルエット画像の大きさ
    D = int(input())
    # 正面から見たシルエット
    f = [[] for i in range(2)]
    # 右側から見たシルエット
    r = [[] for i in range(2)]
    for i in range(2):
        for _ in range(D):
            f[i].append(input())
        for _ in range(D):
            r[i].append(input())
    return D, f, r


def solve() -> None:
    """求解処理
    """
    b = [[0 for _ in range(D * D * D)] for _ in range(2)]
    n = 0
    for i in range(2):
        for x, y, z in itertools.product(range(D), repeat=3):
            if f[i][z][x] == "1" and r[i][z][y] == "1":
                n += 1
                b[i][x * D * D + y * D + z] = n

    # 結果出力
    print(n)
    print(" ".join(map(str, b[0])))
    print(" ".join(map(str, b[1])))


if __name__ == "__main__":
    # 入力
    D, f, r = get_input()

    # 求解
    solve()
