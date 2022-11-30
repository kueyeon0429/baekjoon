import sys
input = sys.stdin.readline

def solutions(N, B):
    dp = [[0 for _ in range(N)] for _ in range(N)]
    dp[0][0] = 1
    for i in range(N):
        for j in range(N):
            if i == N-1 and j == N-1:
                return dp[i][j]
            d = B[i][j]
            if j + d < N:
                dp[i][j+d] += dp[i][j]
            if i + d < N:
                dp[i+d][j] += dp[i][j]

n = int(input())
board = []
for _ in range(n):
    board.append(list(map(int, input().split())))

print(solutions(n, board))
