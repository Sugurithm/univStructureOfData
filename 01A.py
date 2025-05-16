N = int(input())
A = list(map(int, input().split()))

def insertionSort(A, N):
    print(" ".join(map(str, A)))    
    for i in range(1, N):
        key = A[i]
        j = i - 1
        while j >= 0 and key < A[j]:
            A[j + 1] = A[j]
            j -= 1
        A[j + 1] = key
        print(" ".join(map(str, A)))
    return A

insertionSort(A, N)

