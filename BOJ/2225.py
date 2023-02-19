n, k = map(int, input().split())

# 2차원 k*n 배열 생성
dp = [[0 for _ in range(n+1)] for _ in range(k+1)]

# 1행 1로 초기화
for i in range(1, n+1):
    dp[1][i] = 1

# 1열 12345---로 초기화
for j in range(1, k+1):
    dp[j][1] = j

# dp 배열 값 생성
for l in range(2, k+1):
    for m in range(2, n+1):
        dp[l][m] = dp[l][m-1] + dp[l-1][m]

print(dp[k][n] % 1_000_000_000)
