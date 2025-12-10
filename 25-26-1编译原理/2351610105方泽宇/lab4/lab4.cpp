#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <iomanip>
#include <cctype>

class LR1Parser {
private:
    // 文法符号定义
    enum Symbol {
        E, T, F,           // 非终结符
        PLUS, MINUS,       // + -
        MULTIPLY, DIVIDE,  // * /
        LPAREN, RPAREN,    // ( )
        ID,                // i
        END,               // #
        DOLLAR             // 文法开始符号的结束标记
    };

    // 动作类型
    enum ActionType {
        SHIFT,    // 移进
        REDUCE,   // 归约
        ACCEPT,   // 接受
        ERROR     // 错误
    };

    // 动作结构
    struct Action {
        ActionType type;
        int value;  // 对于SHIFT是状态号，对于REDUCE是产生式编号
        
        Action(ActionType t = ERROR, int v = -1) : type(t), value(v) {}
    };

    // 产生式结构
    struct Production {
        Symbol left;  // 左部
        std::vector<Symbol> right; // 右部
        int length;   // 右部长度
        
        Production(Symbol l, const std::vector<Symbol>& r) : left(l), right(r), length(r.size()) {}
    };

    // LR(1)分析表
    std::vector<std::map<Symbol, Action>> action_table;
    std::vector<std::map<Symbol, int>> goto_table;
    std::vector<Production> productions;
    
    int step;

    // 符号到字符串的映射
    std::string symbolToString(Symbol s) {
        switch(s) {
            case E: return "E";
            case T: return "T";
            case F: return "F";
            case PLUS: return "+";
            case MINUS: return "-";
            case MULTIPLY: return "*";
            case DIVIDE: return "/";
            case LPAREN: return "(";
            case RPAREN: return ")";
            case ID: return "i";
            case END: return "#";
            case DOLLAR: return "$";
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
            default: return END; // 默认返回END
        }
    }

    // 初始化文法和分析表
    void initializeGrammar() {
        // 产生式列表 (从1开始编号)
        productions.push_back(Production(E, {E, PLUS, T}));     // 0: E -> E + T
        productions.push_back(Production(E, {E, MINUS, T}));    // 1: E -> E - T
        productions.push_back(Production(E, {T}));              // 2: E -> T
        productions.push_back(Production(T, {T, MULTIPLY, F})); // 3: T -> T * F
        productions.push_back(Production(T, {T, DIVIDE, F}));   // 4: T -> T / F
        productions.push_back(Production(T, {F}));              // 5: T -> F
        productions.push_back(Production(F, {LPAREN, E, RPAREN})); // 6: F -> ( E )
        productions.push_back(Production(F, {ID}));             // 7: F -> i
    }

    // 初始化LR(1)分析表 (简化版本)
    void initializeParsingTable() {
        // 扩展状态表大小
        action_table.resize(20);
        goto_table.resize(20);

        // 状态0
        action_table[0][ID] = Action(SHIFT, 5);
        action_table[0][LPAREN] = Action(SHIFT, 4);
        goto_table[0][E] = 1;
        goto_table[0][T] = 2;
        goto_table[0][F] = 3;

        // 状态1
        action_table[1][PLUS] = Action(SHIFT, 6);
        action_table[1][MINUS] = Action(SHIFT, 7);
        action_table[1][END] = Action(ACCEPT, 0);

        // 状态2
        action_table[2][PLUS] = Action(REDUCE, 2);
        action_table[2][MINUS] = Action(REDUCE, 2);
        action_table[2][MULTIPLY] = Action(SHIFT, 8);
        action_table[2][DIVIDE] = Action(SHIFT, 9);
        action_table[2][RPAREN] = Action(REDUCE, 2);
        action_table[2][END] = Action(REDUCE, 2);

        // 状态3
        action_table[3][PLUS] = Action(REDUCE, 5);
        action_table[3][MINUS] = Action(REDUCE, 5);
        action_table[3][MULTIPLY] = Action(REDUCE, 5);
        action_table[3][DIVIDE] = Action(REDUCE, 5);
        action_table[3][RPAREN] = Action(REDUCE, 5);
        action_table[3][END] = Action(REDUCE, 5);

        // 状态4
        action_table[4][ID] = Action(SHIFT, 5);
        action_table[4][LPAREN] = Action(SHIFT, 4);
        goto_table[4][E] = 10;
        goto_table[4][T] = 2;
        goto_table[4][F] = 3;

        // 状态5
        action_table[5][PLUS] = Action(REDUCE, 7);
        action_table[5][MINUS] = Action(REDUCE, 7);
        action_table[5][MULTIPLY] = Action(REDUCE, 7);
        action_table[5][DIVIDE] = Action(REDUCE, 7);
        action_table[5][RPAREN] = Action(REDUCE, 7);
        action_table[5][END] = Action(REDUCE, 7);

        // 状态6
        action_table[6][ID] = Action(SHIFT, 5);
        action_table[6][LPAREN] = Action(SHIFT, 4);
        goto_table[6][T] = 11;
        goto_table[6][F] = 3;

        // 状态7
        action_table[7][ID] = Action(SHIFT, 5);
        action_table[7][LPAREN] = Action(SHIFT, 4);
        goto_table[7][T] = 12;
        goto_table[7][F] = 3;

        // 状态8
        action_table[8][ID] = Action(SHIFT, 5);
        action_table[8][LPAREN] = Action(SHIFT, 4);
        goto_table[8][F] = 13;

        // 状态9
        action_table[9][ID] = Action(SHIFT, 5);
        action_table[9][LPAREN] = Action(SHIFT, 4);
        goto_table[9][F] = 14;

        // 状态10
        action_table[10][PLUS] = Action(SHIFT, 6);
        action_table[10][MINUS] = Action(SHIFT, 7);
        action_table[10][RPAREN] = Action(SHIFT, 15);

        // 状态11
        action_table[11][PLUS] = Action(REDUCE, 0);
        action_table[11][MINUS] = Action(REDUCE, 0);
        action_table[11][MULTIPLY] = Action(SHIFT, 8);
        action_table[11][DIVIDE] = Action(SHIFT, 9);
        action_table[11][RPAREN] = Action(REDUCE, 0);
        action_table[11][END] = Action(REDUCE, 0);

        // 状态12
        action_table[12][PLUS] = Action(REDUCE, 1);
        action_table[12][MINUS] = Action(REDUCE, 1);
        action_table[12][MULTIPLY] = Action(SHIFT, 8);
        action_table[12][DIVIDE] = Action(SHIFT, 9);
        action_table[12][RPAREN] = Action(REDUCE, 1);
        action_table[12][END] = Action(REDUCE, 1);

        // 状态13
        action_table[13][PLUS] = Action(REDUCE, 3);
        action_table[13][MINUS] = Action(REDUCE, 3);
        action_table[13][MULTIPLY] = Action(REDUCE, 3);
        action_table[13][DIVIDE] = Action(REDUCE, 3);
        action_table[13][RPAREN] = Action(REDUCE, 3);
        action_table[13][END] = Action(REDUCE, 3);

        // 状态14
        action_table[14][PLUS] = Action(REDUCE, 4);
        action_table[14][MINUS] = Action(REDUCE, 4);
        action_table[14][MULTIPLY] = Action(REDUCE, 4);
        action_table[14][DIVIDE] = Action(REDUCE, 4);
        action_table[14][RPAREN] = Action(REDUCE, 4);
        action_table[14][END] = Action(REDUCE, 4);

        // 状态15
        action_table[15][PLUS] = Action(REDUCE, 6);
        action_table[15][MINUS] = Action(REDUCE, 6);
        action_table[15][MULTIPLY] = Action(REDUCE, 6);
        action_table[15][DIVIDE] = Action(REDUCE, 6);
        action_table[15][RPAREN] = Action(REDUCE, 6);
        action_table[15][END] = Action(REDUCE, 6);
    }

    // 获取动作描述字符串
    std::string getActionDescription(const Action& action, int production_index = -1) {
        switch(action.type) {
            case SHIFT:
                return "移进 s" + std::to_string(action.value);
            case REDUCE:
                return "归约 r" + std::to_string(action.value) + " (" + getProductionString(productions[action.value]) + ")";
            case ACCEPT:
                return "接受";
            case ERROR:
                return "错误";
            default:
                return "未知";
        }
    }

    // 获取产生式字符串
    std::string getProductionString(const Production& prod) {
        std::string result = symbolToString(prod.left) + " -> ";
        for (Symbol s : prod.right) {
            result += symbolToString(s);
        }
        return result;
    }

    // 打印分析步骤
    void printStep(int step_num, const std::stack<int>& state_stack, 
                   const std::stack<Symbol>& symbol_stack, 
                   const std::vector<Symbol>& remaining_input,
                   const std::string& action) {
        std::cout << std::setw(4) << step_num << " | ";
        
        // 打印状态栈
        std::stack<int> temp_state = state_stack;
        std::vector<int> state_contents;
        while (!temp_state.empty()) {
            state_contents.push_back(temp_state.top());
            temp_state.pop();
        }
        for (int i = state_contents.size() - 1; i >= 0; i--) {
            std::cout << state_contents[i] << " ";
        }
        std::cout << std::setw(15 - state_contents.size() * 2) << " | ";
        
        // 打印符号栈
        std::stack<Symbol> temp_symbol = symbol_stack;
        std::vector<std::string> symbol_contents;
        while (!temp_symbol.empty()) {
            symbol_contents.push_back(symbolToString(temp_symbol.top()));
            temp_symbol.pop();
        }
        for (int i = symbol_contents.size() - 1; i >= 0; i--) {
            std::cout << symbol_contents[i];
        }
        std::cout << std::setw(10 - symbol_contents.size()) << " | ";
        
        // 打印剩余输入串
        for (Symbol s : remaining_input) {
            std::cout << symbolToString(s);
        }
        std::cout << std::setw(15 - remaining_input.size()) << " | ";
        
        // 打印动作
        std::cout << action << std::endl;
    }

public:
    LR1Parser() : step(1) {
        initializeGrammar();
        initializeParsingTable();
    }

    bool parse(const std::string& input_str) {
        std::cout << "========================================" << std::endl;
        std::cout << "LR(1)分析程序" << std::endl;
        std::cout << "编制人：方泽宇，2351610105，23508014" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "输入符号串: " << input_str << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "步骤 | 状态栈         | 符号栈   | 剩余输入串     | 动作" << std::endl;
        std::cout << "----|----------------|----------|---------------|-------------------" << std::endl;

        // 初始化
        step = 1;
        std::stack<int> state_stack;
        std::stack<Symbol> symbol_stack;
        std::vector<Symbol> input_symbols;

        // 初始化栈
        state_stack.push(0);
        symbol_stack.push(DOLLAR);

        // 初始化输入符号串
        for (char c : input_str) {
            if (c != ' ' && c != '\t' && c != '\n') {
                Symbol s = charToSymbol(c);
                input_symbols.push_back(s);
            }
        }

        // 开始分析
        while (!state_stack.empty() && !input_symbols.empty()) {
            int current_state = state_stack.top();
            Symbol current_input = input_symbols[0];

            // 查找动作表
            if (action_table[current_state].find(current_input) != action_table[current_state].end()) {
                Action action = action_table[current_state][current_input];
                std::string action_desc = getActionDescription(action);

                // 打印当前步骤
                printStep(step++, state_stack, symbol_stack, input_symbols, action_desc);

                switch(action.type) {
                    case SHIFT: {
                        // 移进动作
                        state_stack.push(action.value);
                        symbol_stack.push(current_input);
                        input_symbols.erase(input_symbols.begin());
                        break;
                    }
                    case REDUCE: {
                        // 归约动作
                        Production prod = productions[action.value];
                        
                        // 弹出右部长度的符号
                        for (int i = 0; i < prod.length; i++) {
                            state_stack.pop();
                            symbol_stack.pop();
                        }
                        
                        // 压入左部符号
                        symbol_stack.push(prod.left);
                        
                        // 查找GOTO表
                        int new_state = state_stack.top();
                        if (goto_table[new_state].find(prod.left) != goto_table[new_state].end()) {
                            state_stack.push(goto_table[new_state][prod.left]);
                        } else {
                            std::cout << "错误: GOTO表[" << new_state << "][" 
                                     << symbolToString(prod.left) << "] 无定义" << std::endl;
                            return false;
                        }
                        break;
                    }
                    case ACCEPT: {
                        std::cout << "========================================" << std::endl;
                        std::cout << "✓ 分析成功: " << input_str << " 为合法符号串" << std::endl;
                        return true;
                    }
                    case ERROR: {
                        std::cout << "错误: 在状态 " << current_state 
                                 << " 遇到符号 " << symbolToString(current_input) << std::endl;
                        return false;
                    }
                }
            } else {
                std::cout << "错误: ACTION表[" << current_state << "][" 
                         << symbolToString(current_input) << "] 无定义" << std::endl;
                return false;
            }
        }

        std::cout << "========================================" << std::endl;
        std::cout << "✗ 分析失败: " << input_str << " 为非法符号串" << std::endl;
        return false;
    }
};

// 测试函数
void runTests() {
    LR1Parser parser;
    
    std::vector<std::string> test_cases = {
        "i+i*i#",
        "i*i+i#",
        "(i+i)*i#",
        "i#",
        "i+i*i+i#",
        "i+*i#",      // 非法的
        "(i+i#",      // 非法的 - 括号不匹配
    };

    for (const auto& test_case : test_cases) {
        std::cout << std::endl;
        std::cout << "测试用例: " << test_case << std::endl;
        parser.parse(test_case);
        std::cout << "========================================" << std::endl;
    }
}

int main() {
    std::cout << "LR(1)语法分析程序" << std::endl;
    std::cout << "文法规则:" << std::endl;
    std::cout << "E -> E + T" << std::endl;
    std::cout << "E -> E - T" << std::endl;
    std::cout << "E -> T" << std::endl;
    std::cout << "T -> T * F" << std::endl;
    std::cout << "T -> T / F" << std::endl;
    std::cout << "T -> F" << std::endl;
    std::cout << "F -> ( E )" << std::endl;
    std::cout << "F -> i" << std::endl;
    std::cout << std::endl;

    while (true) {
        std::cout << "选择模式:" << std::endl;
        std::cout << "1. 交互式分析" << std::endl;
        std::cout << "2. 运行测试用例" << std::endl;
        std::cout << "3. 退出" << std::endl;
        std::cout << "请输入选择 (1-3): ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        if (choice == 1) {
            std::string input;
            std::cout << "请输入要分析的符号串 (以#结束): ";
            std::getline(std::cin, input);
            
            if (!input.empty() && input.back() != '#') {
                input += '#';
            }
            
            LR1Parser parser;
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