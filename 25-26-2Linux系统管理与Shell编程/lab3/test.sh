#!/bin/bash
# test.sh

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# 创建答案目录
mkdir -p answer

echo "========================================="
echo "Running tests for Lab 3"
echo "========================================="

# 测试每个任务
for task in {1..7}; do
    input_file="./test_cases/task${task}.in"
    output_file="./answer/task${task}.out"
    expected_file="./answer/task${task}.expected"  # 如果有预期输出文件
    
    echo -e "\n${YELLOW}Testing Task ${task}...${NC}"
    
    # 检查输入文件是否存在
    if [ ! -f "$input_file" ]; then
        echo -e "${RED}  ✗ Input file not found: $input_file${NC}"
        continue
    fi
    
    # 检查任务脚本是否存在
    if [ ! -f "task${task}.sh" ]; then
        echo -e "${RED}  ✗ Script not found: task${task}.sh${NC}"
        continue
    fi
    
    # 运行脚本生成输出
    bash "task${task}.sh" < "$input_file" > "$output_file"
    
    # 检查是否成功生成输出
    if [ -f "$output_file" ]; then
        echo -e "${GREEN}  ✓ Output generated: $output_file${NC}"
        
        # 显示输出内容（前5行）
        echo "  --- Output content ---"
        head -5 "$output_file" | sed 's/^/    /'
        if [ $(wc -l < "$output_file") -gt 5 ]; then
            echo "    ... (truncated)"
        fi
        echo "  ----------------------"
    else
        echo -e "${RED}  ✗ Failed to generate output${NC}"
    fi
done

echo -e "\n========================================="
echo -e "${GREEN}Test completed!${NC}"
echo "Output files saved in ./answer/"
echo "========================================="

# 显示生成的文件列表
echo -e "\nGenerated output files:"
ls -la ./answer/