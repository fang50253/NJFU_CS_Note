def f(x):
    """将数字各位相乘"""
    res = 1
    for c in str(x):
        res *= int(c)
    return res

def g(x):
    """计算x最终变成不变数需要的次数"""
    cnt = 0
    while True:
        fx = f(x)
        if fx == x:
            break
        x = fx
        cnt += 1
    return cnt

# 打表小范围
MAX = 10**5 # 可以尝试10000以内的数
table = []
for x in range(1, MAX):
    table.append((x, g(x), f(x)))

# 按 g(x) 降序
table.sort(key=lambda t: t[1], reverse=True)

# 找两个 f(x) 不同的数，使 g(a)+g(b) 最大
best_sum = -1
best_pair = None
for i in range(len(table)):
    for j in range(i+1, len(table)):
        if table[i][2] != table[j][2]:
            s = table[i][1] + table[j][1]
            if s > best_sum:
                best_sum = s
                best_pair = (table[i][0], table[j][0])
print("Best pair:", best_pair)
print("g(a)+g(b) =", best_sum)