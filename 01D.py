n = int(input())
a = [None] * n
for i in range(n):
    a[i] = int(input())

min_val = a[0]
max = -10**9


for i in range(1, n):
    diff = a[i] - min_val
    if diff > max:
        max = diff
    if a[i] < min_val:
        min_val = a[i]

print(max)
