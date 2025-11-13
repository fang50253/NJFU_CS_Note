#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>

class ReversePolishNotation {
private:
    // 运算符优先级
    std::map<char, int> priority = {
        {'#', 0},
        {'(', 1},
        {'+', 2}, {'-', 2},
        {'*', 3}, {'/', 3},
        {')', 4}
    };

    // 检查字符是否为运算符
    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '#';
    }

    // 比较运算符优先级
    bool higherPriority(char op1, char op2) {
        return priority[op1] > priority[op2];
    }

public:
    // 中缀表达式转逆波兰式
    std::string infixToPostfix(const std::string& infix) {
        std::stack<char> op_stack;
        std::string postfix;
        std::string number_buffer;
        
        // 在表达式末尾添加#
        std::string expression = infix + "#";
        
        for (size_t i = 0; i < expression.length(); i++) {
            char c = expression[i];
            
            if (std::isdigit(c)) {
                // 处理数字
                number_buffer += c;
            } else {
                // 数字缓冲区非空，输出数字
                if (!number_buffer.empty()) {
                    if (!postfix.empty() && std::isdigit(postfix.back())) {
                        postfix += "&"; // 数字分隔符
                    }
                    postfix += number_buffer;
                    number_buffer.clear();
                }
                
                if (isOperator(c)) {
                    if (c == '(') {
                        op_stack.push(c);
                    } else if (c == ')') {
                        // 弹出直到遇到左括号
                        while (!op_stack.empty() && op_stack.top() != '(') {
                            postfix += op_stack.top();
                            op_stack.pop();
                        }
                        if (!op_stack.empty() && op_stack.top() == '(') {
                            op_stack.pop(); // 弹出左括号
                        }
                    } else if (c == '#') {
                        // 弹出所有运算符
                        while (!op_stack.empty()) {
                            postfix += op_stack.top();
                            op_stack.pop();
                        }
                    } else {
                        // 普通运算符
                        while (!op_stack.empty() && op_stack.top() != '(' && 
                               !higherPriority(c, op_stack.top())) {
                            postfix += op_stack.top();
                            op_stack.pop();
                        }
                        op_stack.push(c);
                    }
                }
            }
        }
        
        return postfix;
    }

    // 计算逆波兰式
    double calculatePostfix(const std::string& postfix) {
        std::stack<double> num_stack;
        std::string number_buffer;
        
        for (size_t i = 0; i < postfix.length(); i++) {
            char c = postfix[i];
            
            if (std::isdigit(c)) {
                // 处理数字
                number_buffer += c;
            } else if (c == '&') {
                // 数字分隔符，将缓冲区数字入栈
                if (!number_buffer.empty()) {
                    num_stack.push(std::stod(number_buffer));
                    number_buffer.clear();
                }
            } else if (isOperator(c) && c != '(' && c != ')' && c != '#') {
                // 处理运算符
                if (!number_buffer.empty()) {
                    num_stack.push(std::stod(number_buffer));
                    number_buffer.clear();
                }
                
                if (num_stack.size() < 2) {
                    throw std::runtime_error("表达式错误：运算对象不足");
                }
                
                double b = num_stack.top(); num_stack.pop();
                double a = num_stack.top(); num_stack.pop();
                double result;
                
                switch (c) {
                    case '+': result = a + b; break;
                    case '-': result = a - b; break;
                    case '*': result = a * b; break;
                    case '/': 
                        if (b == 0) throw std::runtime_error("数学错误：除零错误");
                        result = a / b; 
                        break;
                    default: throw std::runtime_error("未知运算符");
                }
                
                num_stack.push(result);
            }
        }
        
        // 处理最后一个数字
        if (!number_buffer.empty()) {
            num_stack.push(std::stod(number_buffer));
        }
        
        if (num_stack.size() != 1) {
            throw std::runtime_error("表达式错误：结果不唯一");
        }
        
        return num_stack.top();
    }

    // 验证中缀表达式
    bool validateInfix(const std::string& infix) {
        std::stack<char> paren_stack;
        bool last_was_operator = true; // 开始时期望数字或左括号
        
        for (size_t i = 0; i < infix.length(); i++) {
            char c = infix[i];
            
            if (std::isdigit(c)) {
                last_was_operator = false;
            } else if (c == '(') {
                paren_stack.push(c);
                last_was_operator = true;
            } else if (c == ')') {
                if (paren_stack.empty() || paren_stack.top() != '(') {
                    return false; // 括号不匹配
                }
                paren_stack.pop();
                last_was_operator = false;
            } else if (isOperator(c) && c != '#' && c != '(' && c != ')') {
                if (last_was_operator) {
                    return false; // 连续运算符
                }
                last_was_operator = true;
            } else if (!std::isdigit(c) && !isOperator(c)) {
                return false; // 非法字符
            }
        }
        
        return paren_stack.empty() && !last_was_operator;
    }

    // 显示转换过程
    void displayConversionProcess(const std::string& infix) {
        std::stack<char> op_stack;
        std::string postfix;
        std::string number_buffer;
        std::string expression = infix + "#";
        
        std::cout << "转换过程:" << std::endl;
        std::cout << std::setw(10) << "步骤" << std::setw(15) << "当前字符" 
                  << std::setw(20) << "运算符栈" << std::setw(20) << "输出" << std::endl;
        std::cout << std::string(65, '-') << std::endl;
        
        int step = 1;
        
        for (size_t i = 0; i < expression.length(); i++) {
            char c = expression[i];
            std::string stack_content = getStackContent(op_stack);
            std::string current_output = postfix;
            
            if (std::isdigit(c)) {
                number_buffer += c;
                std::cout << std::setw(10) << step++ 
                          << std::setw(15) << c 
                          << std::setw(20) << stack_content 
                          << std::setw(20) << current_output << " (读取数字)" << std::endl;
            } else {
                if (!number_buffer.empty()) {
                    if (!postfix.empty() && std::isdigit(postfix.back())) {
                        postfix += "&";
                    }
                    postfix += number_buffer;
                    number_buffer.clear();
                    current_output = postfix;
                }
                
                if (isOperator(c)) {
                    std::string action;
                    
                    if (c == '(') {
                        op_stack.push(c);
                        action = "压入 (";
                    } else if (c == ')') {
                        action = "弹出直到 (";
                        while (!op_stack.empty() && op_stack.top() != '(') {
                            postfix += op_stack.top();
                            op_stack.pop();
                        }
                        if (!op_stack.empty() && op_stack.top() == '(') {
                            op_stack.pop();
                        }
                    } else if (c == '#') {
                        action = "结束处理";
                        while (!op_stack.empty()) {
                            postfix += op_stack.top();
                            op_stack.pop();
                        }
                    } else {
                        action = "比较优先级";
                        while (!op_stack.empty() && op_stack.top() != '(' && 
                               !higherPriority(c, op_stack.top())) {
                            postfix += op_stack.top();
                            op_stack.pop();
                        }
                        op_stack.push(c);
                    }
                    
                    std::cout << std::setw(10) << step++ 
                              << std::setw(15) << c 
                              << std::setw(20) << stack_content 
                              << std::setw(20) << current_output 
                              << " (" << action << ")" << std::endl;
                }
            }
        }
    }

private:
    // 获取栈内容字符串
    std::string getStackContent(std::stack<char> stack) {
        std::string content;
        while (!stack.empty()) {
            content = stack.top() + content;
            stack.pop();
        }
        return content.empty() ? "空" : content;
    }
};

// 测试函数
void runTests() {
    ReversePolishNotation rpn;
    
    std::vector<std::string> test_cases = {
        "28+68*2",
        "(28+68)*2",
        "10+20*30",
        "100/5+50",
        "((2+3)*4)/5",
        "1+2+3+4+5",
        "10*(2+3)-4/2"
    };
    
    std::cout << "运行测试用例..." << std::endl;
    std::cout << "========================================" << std::endl;
    
    for (const auto& test_case : test_cases) {
        std::cout << "\n测试用例: " << test_case << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        
        try {
            if (!rpn.validateInfix(test_case)) {
                std::cout << "error表达式验证失败" << std::endl;
                continue;
            }
            
            std::string postfix = rpn.infixToPostfix(test_case);
            double result = rpn.calculatePostfix(postfix);
            
            std::cout << "逆波兰式: " << postfix << std::endl;
            std::cout << "计算结果: " << result << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "error错误: " << e.what() << std::endl;
        }
    }
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "逆波兰式的生成及计算程序" << std::endl;
    std::cout << "编制人：姓名，学号，班级" << std::endl;
    std::cout << "========================================" << std::endl;
    
    ReversePolishNotation rpn;
    
    while (true) {
        std::cout << "\n选择模式:" << std::endl;
        std::cout << "1. 交互式转换" << std::endl;
        std::cout << "2. 显示详细转换过程" << std::endl;
        std::cout << "3. 运行测试用例" << std::endl;
        std::cout << "4. 退出" << std::endl;
        std::cout << "请输入选择 (1-4): ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        if (choice == 1 || choice == 2) {
            std::string input;
            std::cout << "请输入中缀表达式 (以#结束): ";
            std::getline(std::cin, input);
            
            // 移除输入中的#
            if (!input.empty() && input.back() == '#') {
                input.pop_back();
            }
            
            try {
                if (!rpn.validateInfix(input)) {
                    std::cout << "error表达式格式错误" << std::endl;
                    continue;
                }
                
                std::string postfix = rpn.infixToPostfix(input);
                
                if (choice == 2) {
                    rpn.displayConversionProcess(input);
                    std::cout << "\n----------------------------------------" << std::endl;
                }
                
                std::cout << "逆波兰式: " << postfix << std::endl;
                
                double result = rpn.calculatePostfix(postfix);
                std::cout << "计算结果: " << result << std::endl;
                
            } catch (const std::exception& e) {
                std::cout << "error！错误: " << e.what() << std::endl;
            }
            
        } else if (choice == 3) {
            runTests();
        } else if (choice == 4) {
            std::cout << "再见!" << std::endl;
            break;
        } else {
            std::cout << "无效选择，请重新输入!" << std::endl;
        }
    }
    
    return 0;
}