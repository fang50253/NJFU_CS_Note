#include <iostream>
#include <string>
#include <vector>
#include <cctype>

class RecursiveDescentParser {
private:
    std::string input;
    int position;
    char current_char;
    bool error;
    std::vector<std::string> steps;
    std::string current_expr;  // 当前推导结果

public:
    RecursiveDescentParser(const std::string& str) 
        : input(str), position(0), error(false), current_expr("E") {
        if (!input.empty()) {
            current_char = input[0];
        }
    }

    void nextChar() {
        position++;
        if (position < input.length()) {
            current_char = input[position];
        } else {
            current_char = '\0';
        }
    }

    void skipWhitespace() {
        while (current_char == ' ' || current_char == '\t' || current_char == '\n') {
            nextChar();
        }
    }

    bool match(char expected) {
        skipWhitespace();
        if (current_char == expected) {
            nextChar();
            return true;
        }
        return false;
    }

    void reportError(const std::string& message) {
        error = true;
        std::cout << "错误: " << message << std::endl;
    }

    // 替换最左边的非终结符
    void replaceLeftmost(char from, const std::string& to) {
        size_t pos = current_expr.find(from);
        if (pos != std::string::npos) {
            current_expr.replace(pos, 1, to);
        }
    }

    void printStep(const std::string& production) {
        std::cout << "使用产生式: " << production <<"     ";
        std::cout << "推导结果: " << current_expr << std::endl;
        steps.push_back(production + " -> " + current_expr);
    }

    // E -> T G
    void E() {
        replaceLeftmost('E', "TG");
        printStep("E -> T G");
        T();
        if (!error) G();
    }

    // G -> + T G | - T G | ε
    void G() {
        skipWhitespace();
        if (current_char == '+') {
            replaceLeftmost('G', "+TG");
            printStep("G -> + T G");
            if (!match('+')) {
                reportError("期望 '+'");
                return;
            }
            T();
            if (!error) G();
        } else if (current_char == '-') {
            replaceLeftmost('G', "-TG");
            printStep("G -> - T G");
            if (!match('-')) {
                reportError("期望 '-'");
                return;
            }
            T();
            if (!error) G();
        } else {
            replaceLeftmost('G', "");
            printStep("G -> ε");
        }
    }

    // T -> F S
    void T() {
        replaceLeftmost('T', "FS");
        printStep("T -> F S");
        F();
        if (!error) S();
    }

    // S -> * F S | / F S | ε
    void S() {
        skipWhitespace();
        if (current_char == '*') {
            replaceLeftmost('S', "*FS");
            printStep("S -> * F S");
            if (!match('*')) {
                reportError("期望 '*'");
                return;
            }
            F();
            if (!error) S();
        } else if (current_char == '/') {
            replaceLeftmost('S', "/FS");
            printStep("S -> / F S");
            if (!match('/')) {
                reportError("期望 '/'");
                return;
            }
            F();
            if (!error) S();
        } else {
            replaceLeftmost('S', "");
            printStep("S -> ε");
        }
    }

    // F -> ( E ) | i
    void F() {
        skipWhitespace();
        if (current_char == '(') {
            replaceLeftmost('F', "(E)");
            printStep("F -> ( E )");
            if (!match('(')) {
                reportError("期望 '('");
                return;
            }
            E();
            if (!error) {
                if (!match(')')) {
                    reportError("期望 ')'");
                }
            }
        } else if (current_char == 'i') {
            replaceLeftmost('F', "i");
            printStep("F -> i");
            if (!match('i')) {
                reportError("期望 'i'");
                return;
            }
        } else {
            reportError("期望 '(', 'i' 或标识符");
        }
    }

    bool parse() {
        std::cout << "========================================" << std::endl;
        std::cout << "递归下降分析程序" << std::endl;
        std::cout << "编制人：方泽宇，2351610105，23508014" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "输入符号串: " << input << std::endl;
        std::cout << "========================================" << std::endl;
        
        steps.clear();
        error = false;
        current_expr = "E";
        
        std::cout << "开始语法分析..." << std::endl;
        std::cout << "初始状态: " << current_expr << std::endl;
        
        E();
        
        if (!error) {
            skipWhitespace();
            if (current_char != '#' && current_char != '\0') {
                reportError("期望结束符 '#' 或字符串结束");
            } else if (current_char == '#') {
                match('#');
            }
        }
        
        std::cout << "\n========================================" << std::endl;
        if (!error) {
            std::cout << "✓ 分析成功: " << input << " 为合法符号串" << std::endl;
            return true;
        } else {
            std::cout << "✗ 分析失败: " << input << " 为非法符号串" << std::endl;
            return false;
        }
    }
};

int main() {
    std::string input;
    std::cout << "请输入要分析的符号串 (以#结束): ";
    std::getline(std::cin, input);
    
    if (!input.empty() && input.back() != '#') {
        input += '#';
    }
    
    RecursiveDescentParser parser(input);
    parser.parse();
    
    return 0;
}