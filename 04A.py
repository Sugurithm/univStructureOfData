n = int(input())
S = input().split()
q = int(input())
T = input().split()

S = set(S)

ans = 0
for i in range(q):
    if T[i] in S:
        ans += 1

print(ans)