S = input().split()

"""
スタックを使って逆ポーランド記法を計算する．
与えられた数字をスタックしていき，演算子が来た時点で演算をしてスタックに入れる.
"""

stack = []
for i in range(len(S)):
    if S[i] == "+":
        b, a = stack.pop(), stack.pop()
        stack.append(a + b)
    elif S[i] == "-":
        b, a = stack.pop(), stack.pop()
        stack.append(a - b)
    elif S[i] == "*":
        b, a = stack.pop(), stack.pop()
        stack.append(a * b)
    elif S[i] == "/":
        b, a = stack.pop(), stack.pop()
        stack.append(a / b)
    else:
        stack.append(int(S[i]))

print(stack[0])
