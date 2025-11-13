#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <iomanip>
#include <cctype>

class PredictiveParser {
private:
    // 文法符号定义
    enum Symbol {
        E, G, T, S, F,   // 非终结符
        PLUS, MINUS, MULTIPLY, DIVIDE, // 运算符
        LPAREN, RPAREN,   // 括号
        ID,               // 标识符 i
        END,              // 结束符 #
        EMPTY,            // 空串 ε
        ERROR             // 错误
    };

    // 分析表类型
    typedef std::map<Symbol, std::map<Symbol, std::vector<Symbol>>> ParsingTable;

    ParsingTable table;
    std::stack<Symbol> analysis_stack;
    std::vector<Symbol> input_symbols;
    int step;

    // 符号到字符串的映射
    std::string symbolToString(Symbol s) {
        switch(s) {
            case E: return "E";
            case G: return "G";
            case T: return "T";
            case S: return "S";
            case F: return "F";
            case PLUS: return "+";
            case MINUS: return "-";
            case MULTIPLY: return "*";
            case DIVIDE: return "/";
            case LPAREN: return "(";
            case RPAREN: return ")";
            case ID: return "i";
            case END: return "#";
            case EMPTY: return "ε";
            default: return "?";
        }
    }

    // 字符到符号的映射
    Symbol charToSymbol(char c) {
        switch(c) {
            case '+': return PLUS;
            case '-': return MINUS;
            case '*': return MULTIPLY;
            case '/': return DIVIDE;
            case '(': return LPAREN;
            case ')': return RPAREN;
            case 'i': return ID;
            case '#': return END;
            default: return ERROR;
        }
    }

    // 初始化分析表
    void initializeParsingTable() {
        // E -> T G
        table[E][ID] = {T, G};
        table[E][LPAREN] = {T, G};

        // G -> + T G
        table[G][PLUS] = {PLUS, T, G};
        // G -> - T G
        table[G][MINUS] = {MINUS, T, G};
        // G -> ε
        table[G][RPAREN] = {EMPTY};
        table[G][END] = {EMPTY};

        // T -> F S
        table[T][ID] = {F, S};
        table[T][LPAREN] = {F, S};

        // S -> * F S
        table[S][MULTIPLY] = {MULTIPLY, F, S};
        // S -> / F S
        table[S][DIVIDE] = {DIVIDE, F, S};
        // S -> ε
        table[S][PLUS] = {EMPTY};
        table[S][MINUS] = {EMPTY};
        table[S][RPAREN] = {EMPTY};
        table[S][END] = {EMPTY};

        // F -> ( E )
        table[F][LPAREN] = {LPAREN, E, RPAREN};
        // F -> i
        table[F][ID] = {ID};
    }

    // 获取产生式字符串
    std::string getProductionString(Symbol non_terminal, const std::vector<Symbol>& production) {
        std::string result = symbolToString(non_terminal) + " -> ";
        if (production.empty() || production[0] == EMPTY) {
            result += "ε";
        } else {
            for (size_t i = 0; i < production.size(); i++) {
                result += symbolToString(production[i]);
                if (i < production.size() - 1) {
                    result += " ";
                }
            }
        }
        return result;
    }

    // 打印分析步骤
    void printStep(const std::string& action) {
        std::cout << std::setw(4) << step++ << " | ";
        
        // 打印分析栈
        std::stack<Symbol> temp_stack = analysis_stack;
        std::vector<std::string> stack_contents;
        while (!temp_stack.empty()) {
            stack_contents.push_back(symbolToString(temp_stack.top()));
            temp_stack.pop();
        }
        for (int i = stack_contents.size() - 1; i >= 0; i--) {
            std::cout << stack_contents[i];
        }
        std::cout << std::setw(20 - stack_contents.size()) << " | ";
        
        // 打印剩余输入串
        for (size_t i = 0; i < input_symbols.size(); i++) {
            std::cout << symbolToString(input_symbols[i]);
        }
        std::cout << std::setw(15 - input_symbols.size()) << " | ";
        
        // 打印动作
        std::cout << action << std::endl;
    }

public:
    PredictiveParser() : step(1) {
        initializeParsingTable();
    }

    bool parse(const std::string& input_str) {
        std::cout << "========================================" << std::endl;
        std::cout << "LL(1)分析程序" << std::endl;
        std::cout << "编制人：方泽宇，2351610105，23508014" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "输入符号串: " << input_str << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "步骤 | 分析栈           | 剩余输入串     | 所用产生式" << std::endl;
        std::cout << "----|------------------|---------------|-------------------" << std::endl;

        // 初始化
        step = 1;
        while (!analysis_stack.empty()) analysis_stack.pop();
        input_symbols.clear();

        // 初始化栈
        analysis_stack.push(END);
        analysis_stack.push(E);

        // 初始化输入符号串
        for (char c : input_str) {
            if (c != ' ' && c != '\t' && c != '\n') {
                Symbol s = charToSymbol(c);
                if (s == ERROR) {
                    std::cout << "错误: 非法字符 '" << c << "'" << std::endl;
                    return false;
                }
                input_symbols.push_back(s);
            }
        }

        // 开始分析
        while (!analysis_stack.empty() && !input_symbols.empty()) {
            Symbol stack_top = analysis_stack.top();
            Symbol current_input = input_symbols[0];

            if (stack_top == current_input) {
                // 匹配终结符
                if (stack_top == END) {
                    printStep("分析成功");
                    break;
                }
                std::string action = "匹配 " + symbolToString(stack_top);
                printStep(action);
                analysis_stack.pop();
                input_symbols.erase(input_symbols.begin());
            }
            else if (stack_top == EMPTY) {
                // 空产生式
                printStep("ε");
                analysis_stack.pop();
            }
            else if (table[stack_top].find(current_input) != table[stack_top].end()) {
                // 查表得到产生式
                std::vector<Symbol> production = table[stack_top][current_input];
                std::string production_str = getProductionString(stack_top, production);
                printStep(production_str);

                analysis_stack.pop();
                // 将产生式右部逆序入栈
                for (int i = production.size() - 1; i >= 0; i--) {
                    if (production[i] != EMPTY) {
                        analysis_stack.push(production[i]);
                    }
                }
            }
            else {
                // 分析错误
                std::cout << "错误: 分析表[" << symbolToString(stack_top) 
                         << "][" << symbolToString(current_input) << "] 无定义" << std::endl;
                return false;
            }
        }

        std::cout << "========================================" << std::endl;
        if (analysis_stack.empty() && input_symbols.empty()) {
            std::cout << "✓ 分析成功: " << input_str << " 为合法符号串" << std::endl;
            return true;
        } else {
            std::cout << "✗ 分析失败: " << input_str << " 为非法符号串" << std::endl;
            return false;
        }
    }
};

// 测试函数
void runTests() {
    PredictiveParser parser;
    
    std::vector<std::string> test_cases = {
        "i+i*i#",
        "i*i+i#",
        "(i+i)*i#",
        "i#",
        "i+i*i+i#",
        "i+*i#",      // 非法的
        "i+i#",       // 缺少结束符，但我们会自动添加
        "(i+i#",      // 非法的 - 括号不匹配
    };

    for (const auto& test_case : test_cases) {
        std::cout << std::endl;
        std::cout << "测试用例: " << test_case << std::endl;
        std::cout << "========================================" << std::endl;
        parser.parse(test_case);
        std::cout << "========================================" << std::endl;
    }
}

int main() {
    std::cout << "预测分析法 (LL(1)分析器)" << std::endl;
    std::cout << "文法规则:" << std::endl;
    std::cout << "E -> T G" << std::endl;
    std::cout << "G -> + T G | - T G | ε" << std::endl;
    std::cout << "T -> F S" << std::endl;
    std::cout << "S -> * F S | / F S | ε" << std::endl;
    std::cout << "F -> ( E ) | i" << std::endl;
    std::cout << std::endl;

    while (true) {
        std::cout << "选择模式:" << std::endl;
        std::cout << "1. 交互式分析" << std::endl;
        std::cout << "2. 运行测试用例" << std::endl;
        std::cout << "3. 退出" << std::endl;
        std::cout << "请输入选择 (1-3): ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore(); // 清除换行符
        
        if (choice == 1) {
            std::string input;
            std::cout << "请输入要分析的符号串 (以#结束): ";
            std::getline(std::cin, input);
            
            // 如果输入没有以#结束，自动添加
            if (!input.empty() && input.back() != '#') {
                input += '#';
            }
            
            PredictiveParser parser;
            parser.parse(input);
        }
        else if (choice == 2) {
            runTests();
        }
        else if (choice == 3) {
            std::cout << "再见!" << std::endl;
            break;
        }
        else {
            std::cout << "无效选择，请重新输入!" << std::endl;
        }
        
        std::cout << std::endl;
    }

    return 0;
}