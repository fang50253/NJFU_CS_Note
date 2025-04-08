import time
from functools import lru_cache

start_time = time.time()
def fibonacci(n):
    if n <= 1:
        return n
    return fibonacci(n-1) + fibonacci(n-2)

n = 40
print(f"斐波那契数列前{n+1}位：")
for i in range(n + 1):
    print(f"fib({i}) = {fibonacci(i)}")
end_time = time.time()

print(f"Time taken: {end_time - start_time:.6f} seconds")