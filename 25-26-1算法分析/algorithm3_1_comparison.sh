#!/bin/bash

# 编译两个程序
g++ -std=c++11 -O2 -o algorithm3_1_greedy algorithm3_1_greedy.cpp
g++ -std=c++11 -O2 -o algorithm3_1_dp algorithm3_1_dp.cpp

# 运行并保存结果
./algorithm3_1_greedy > greedy_output.txt
./algorithm3_1_dp > dp_output.txt

# 输出结果到终端
echo "=== Greedy 输出 ==="
cat greedy_output.txt
echo
echo "=== DP 输出 ==="
cat dp_output.txt
echo

# 比对两个输出
echo "=== 输出比对 (diff) ==="
diff greedy_output.txt dp_output.txt