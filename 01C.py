n = int(input())
A = [None] * n
for i in range(n):
    A[i] = int(input())

# 試し割り法
def is_prime(n):
    if n < 2:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True

def count_primes(arr):
    count = 0
    for num in arr:
        if is_prime(num):
            count += 1
    return count

print(count_primes(A))
