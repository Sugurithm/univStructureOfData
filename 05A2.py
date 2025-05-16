n = int(input())
A = list(map(int, input().split()))
q = int(input())
M = list(map(int, input().split()))

# bit 全探索
makeableNum = set()

for bit in range(1 << n):
    total = 0
    for i in range(n):
        if bit & (1 << i):
            total += A[i]
    makeableNum.add(total)

for m in M:
    if m in makeableNum:
        print("yes")
    else:
        print("no")
