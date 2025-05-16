n = int(input())
A = list(map(int, input().split()))
q = int(input())
M = list(map(int, input().split()))

MAX_SUM = 2000

dp = [False] * (MAX_SUM + 1)
dp[0] = True

for a in A:
    for i in range(MAX_SUM, -1, -1):
        if dp[i] and i + a <= MAX_SUM:
            dp[i + a] = True

for m in M:
    if dp[m]:
        print("yes")
    else:
        print("no")