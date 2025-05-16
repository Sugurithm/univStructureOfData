def counting_sort(OriginArray):
    max_val = max(OriginArray)
    countArray = [0] * (max_val + 1)
    for num in OriginArray:
        countArray[num] += 1
    
    # print(*countArray)
    sorted_arr = []
    for num in range(len(countArray)):
        for _ in range(countArray[num]):
            sorted_arr.append(num)
    return sorted_arr

if __name__ == "__main__":
    n = int(input())
    li = list(map(int, input().split()))
    li = counting_sort(li)
    print(*li)
