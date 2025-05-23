n , q = map(int, input().split())

buffer_size = n + 1 # head = tail　の時必ず空である保証
queue = [None] * buffer_size
head = 0
tail = 0
process_time = 0
ans = []

# 入力
for _ in range(n):
    name, time = input().split()
    queue[tail] = (name, int(time))
    tail = (tail + 1) % buffer_size

# 処理
while head != tail: # head = tail の時，キューは空
    name, time = queue[head]
    head = (head + 1) % buffer_size

    if time > q: # さらに処理が必要な場合
        process_time += q
        queue[tail] = (name, time - q)
        tail = (tail + 1) % buffer_size
    else:
        process_time += time
        ans.append((name, process_time))

# 出力
for name, time in ans:
    print(name, time)
