n = int(input())
box = [0] + list(map(int, input().split()))
dp = [0 for _ in range(n+1)]

for i in range(1, n+1):
    # current box보다 전에 있는 박스들 중에서
    max_dp = dp[i]
    for j in range(i):
        if box[i] > box[j]: # current box보다 크기가 작고
            if dp[j] > max_dp: # dp값이 최대인걸로 갱신
                max_dp = dp[j]
    dp[i] = max_dp + 1

print(max(dp))
