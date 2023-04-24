from __future__ import annotations
import itertools
import random

# 乱数シードを固定
random.seed(0)


def get_input() -> tuple[int, list[list[int]], list[list[int]]]:
    """標準入力を取得する.

    Returns:
        tuple[int, list[list[int]], list[list[int]]]: シルエット画像の大きさ、i番目のシルエット画像の組であり正面/右側から見たシルエット
    """
    # シルエット画像の大きさ
    D = int(input())
    # 正面から見たシルエット
    f = [[] for _ in range(2)]
    # 右側から見たシルエット
    r = [[] for _ in range(2)]
    for i in range(2):
        for _ in range(D):
            f[i].append(input())
        for _ in range(D):
            r[i].append(input())
    return D, f, r


def solve() -> None:
    """求解処理
    """
    XYZ = list(itertools.product(range(D), repeat=3))
    K = 6
    DX = [-1, 1, 0, 0, 0, 0]
    DY = [0, 0, -1, 1, 0, 0]
    DZ = [0, 0, 0, 0, -1, 1]
    SEARCH_CNT = 1000
    is_placeable_pos = [{(x, y, z): f[i][z][x] == "1" and r[i][z][y] == "1" for x, y, z in XYZ}
                        for i in range(2)]
    n = 0
    b = [[0 for _ in range(D * D * D)] for _ in range(2)]
    while True:
        placeable_pos = [[(x, y, z) for x, y, z in filter(lambda xyz: is_placeable_pos[i][xyz], XYZ)]
                         for i in range(2)]
        if any(len(placeable_pos[i]) == 0 for i in range(2)):
            # どちらかのシルエットについて、配置可能場所が存在しない
            break
        # （乱択）貪欲法
        max_blocks = [[] for _ in range(2)]
        for _ in range(SEARCH_CNT):
            # ランダムに配置可能場所を選び、ランダムな一方向にそれぞれ伸ばしていく
            blocks = [[random.choice(placeable_pos[i])] for i in range(2)]
            k = [random.randrange(0, K) for _ in range(2)]
            while True:
                next_block = [(blocks[i][-1][0]+DX[k[i]], blocks[i][-1][1]+DY[k[i]], blocks[i][-1][2]+DZ[k[i]])
                              for i in range(2)]
                if any(next_block[i] not in is_placeable_pos[i].keys() for i in range(2)):
                    break
                if any(not is_placeable_pos[i][next_block[i]] for i in range(2)):
                    break
                for i in range(2):
                    blocks[i].append(next_block[i])
            for i in range(2):
                max_blocks[i] = max(max_blocks[i], blocks[i], key=len)
        n += 1
        for i in range(2):
            for x, y, z in max_blocks[i]:
                b[i][x * D * D + y * D + z] = n
                is_placeable_pos[i][x, y, z] = False
    # 残りの配置可能場所について、配置必要であれば配置
    for i in range(2):
        for x, y, z in itertools.product(range(D), repeat=3):
            if not is_placeable_pos[i][x, y, z]:
                continue
            if any(b[i][x * D * D + ny * D + z] > 0 for ny in range(D)) and any(b[i][nx * D * D + y * D + z] > 0 for nx in range(D)):
                continue
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
