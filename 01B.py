a, b = map(int, input().split())

# 最大公約数 再帰関数
def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)

print(gcd(a, b))
