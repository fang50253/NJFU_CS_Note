#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <windows.h>

using namespace std;

// 单词类型枚举
enum TokenType {
    KEYWORD = 1,
    IDENTIFIER = 2,
    CONSTANT = 3,
    OPERATOR = 4,
    DELIMITER = 5
};

// 单词结构
struct Token {
    TokenType type;
    string value;
    int line;
    int position;
    
    Token(TokenType t, const string& v, int l, int p) : type(t), value(v), line(l), position(p) {}
};

class Lexer {
private:
    string source;
    int pos;
    int line;
    int column;
    vector<Token> tokens;
    
    unordered_map<string, bool> keywords = {
        {"main", true}, {"printf", true}, {"if", true}, {"int", true},
        {"for", true}, {"while", true}, {"do", true}, {"return", true},
        {"break", true}, {"continue", true}, {"else", true}, {"char", true},
        {"float", true}, {"long", true}, {"short", true}, {"scanf", true},
        {"void", true}, {"switch", true}, {"case", true}, {"default", true}
    };
    
    unordered_map<string, bool> operators = {
        {"+", true}, {"-", true}, {"*", true}, {"/", true}, {"=", true},
        {">", true}, {"<", true}, {">=", true}, {"<=", true}, {"!=", true},
        {"+=", true}, {"-=", true}, {"*=", true}, {"/=", true}, {"==", true},
        {"&&", true}, {"||", true}, {"!", true}, {"&", true}, {"|", true},
        {"++", true}, {"--", true}, {"%", true}
    };
    
    unordered_map<string, bool> delimiters = {
        {",", true}, {";", true}, {"{", true}, {"}", true}, 
        {"(", true}, {")", true}, {"[", true}, {"]", true}
    };

public:
    Lexer() : pos(0), line(1), column(1) {}
    
    vector<Token> analyze(const string& code) {
        source = code;
        pos = 0;
        line = 1;
        column = 1;
        tokens.clear();
        
        while (pos < source.length()) {
            int startColumn = column;
            
            if (isspace(source[pos])) {
                skipWhitespace();
                continue;
            }
            
            if (source[pos] == '/' && pos + 1 < source.length()) {
                if (source[pos + 1] == '/') {
                    skipLineComment();
                    continue;
                } else if (source[pos + 1] == '*') {
                    skipBlockComment();
                    continue;
                }
            }
            
            if (source[pos] == '"') {
                processString(startColumn);
                continue;
            }
            
            if (source[pos] == '\'') {
                processChar(startColumn);
                continue;
            }
            
            if (isdigit(source[pos])) {
                processNumber(startColumn);
                continue;
            }
            
            if (isalpha(source[pos]) || source[pos] == '_') {
                processIdentifier(startColumn);
                continue;
            }
            
            processSymbol(startColumn);
        }
        
        return tokens;
    }
    
    void clearResults() {
        tokens.clear();
    }

private:
    void skipWhitespace() {
        while (pos < source.length() && isspace(source[pos])) {
            if (source[pos] == '\n') {
                line++;
                column = 1;
            } else {
                column++;
            }
            pos++;
        }
    }
    
    void skipBlockComment() {
        int startLine = line;
        int startColumn = column;
        pos += 2;
        column += 2;
        
        while (pos < source.length() - 1) {
            if (source[pos] == '\n') {
                line++;
                column = 1;
            } else {
                column++;
            }
            
            if (source[pos] == '*' && source[pos + 1] == '/') {
                pos += 2;
                column += 2;
                return;
            }
            pos++;
        }
    }
    
    void skipLineComment() {
        while (pos < source.length() && source[pos] != '\n') {
            pos++;
            column++;
        }
    }
    
    void processString(int startColumn) {
        int start = pos;
        pos++;
        column++;
        
        while (pos < source.length() && source[pos] != '"') {
            if (source[pos] == '\\') {
                pos++;
                column++;
            }
            if (source[pos] == '\n') {
                line++;
                column = 1;
            } else {
                column++;
            }
            pos++;
        }
        
        if (pos < source.length()) {
            pos++;
            column++;
            string str = source.substr(start, pos - start);
            tokens.emplace_back(CONSTANT, str, line, startColumn);
        }
    }
    
    void processChar(int startColumn) {
        int start = pos;
        pos++;
        column++;
        
        if (pos < source.length() && source[pos] == '\\') {
            pos++;
            column++;
        }
        
        if (pos < source.length()) {
            pos++;
            column++;
        }
        
        if (pos < source.length() && source[pos] == '\'') {
            pos++;
            column++;
            string chr = source.substr(start, pos - start);
            tokens.emplace_back(CONSTANT, chr, line, startColumn);
        }
    }
    
    void processNumber(int startColumn) {
        int start = pos;
        
        while (pos < source.length() && isdigit(source[pos])) {
            pos++;
            column++;
        }
        
        if (pos < source.length() && source[pos] == '.') {
            pos++;
            column++;
            while (pos < source.length() && isdigit(source[pos])) {
                pos++;
                column++;
            }
        }
        
        string num = source.substr(start, pos - start);
        tokens.emplace_back(CONSTANT, num, line, startColumn);
    }
    
    void processIdentifier(int startColumn) {
        int start = pos;
        
        while (pos < source.length() && 
               (isalnum(source[pos]) || source[pos] == '_')) {
            pos++;
            column++;
        }
        
        string id = source.substr(start, pos - start);
        
        if (keywords.find(id) != keywords.end()) {
            tokens.emplace_back(KEYWORD, id, line, startColumn);
        } else {
            tokens.emplace_back(IDENTIFIER, id, line, startColumn);
        }
    }
    
    void processSymbol(int startColumn) {
        string symbol(1, source[pos]);
        
        if (pos + 1 < source.length()) {
            string twoChar = source.substr(pos, 2);
            if (operators.find(twoChar) != operators.end()) {
                tokens.emplace_back(OPERATOR, twoChar, line, startColumn);
                pos += 2;
                column += 2;
                return;
            }
        }
        
        if (operators.find(symbol) != operators.end()) {
            tokens.emplace_back(OPERATOR, symbol, line, startColumn);
        } else if (delimiters.find(symbol) != delimiters.end()) {
            tokens.emplace_back(DELIMITER, symbol, line, startColumn);
        } else {
            tokens.emplace_back(DELIMITER, symbol, line, startColumn);
        }
        
        pos++;
        column++;
    }
};

// 界面控制类
class LexerUI {
private:
    Lexer lexer;
    string currentFile;
    
public:
    void showMenu() {
        while (true) {
            system("cls");
            cout << "==========================================" << endl;
            cout << "       词法分析器 - 前端界面" << endl;
            cout << "==========================================" << endl;
            cout << "1. 输入源代码" << endl;
            cout << "2. 从文件加载" << endl;
            cout << "3. 执行词法分析" << endl;
            cout << "4. 显示分析结果" << endl;
            cout << "5. 保存结果到文件" << endl;
            cout << "6. 显示符号表" << endl;
            cout << "0. 退出" << endl;
            cout << "==========================================" << endl;
            cout << "请选择操作: ";
            
            int choice;
            cin >> choice;
            cin.ignore(); // 清除输入缓冲区
            
            switch (choice) {
                case 1:
                    inputSourceCode();
                    break;
                case 2:
                    loadFromFile();
                    break;
                case 3:
                    performAnalysis();
                    break;
                case 4:
                    displayResults();
                    break;
                case 5:
                    saveResults();
                    break;
                case 6:
                    showSymbolTable();
                    break;
                case 0:
                    return;
                default:
                    cout << "无效选择，请重新输入！" << endl;
                    waitForKey();
            }
        }
    }

private:
    void inputSourceCode() {
        system("cls");
        cout << "请输入源代码（输入'END'单独一行结束）:" << endl;
        cout << "==========================================" << endl;
        
        stringstream code;
        string line;
        
        while (true) {
            getline(cin, line);
            if (line == "END") break;
            code << line << "\n";
        }
        
        currentFile = "手动输入";
        lexer.analyze(code.str());
        
        cout << "源代码已输入完成！" << endl;
        waitForKey();
    }
    
    void loadFromFile() {
        system("cls");
        cout << "请输入文件名: ";
        string filename;
        cin >> filename;
        
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "无法打开文件: " << filename << endl;
            waitForKey();
            return;
        }
        
        stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        
        currentFile = filename;
        lexer.analyze(buffer.str());
        
        cout << "文件加载成功！" << endl;
        waitForKey();
    }
    
    void performAnalysis() {
        system("cls");
        cout << "执行词法分析..." << endl;
        // 分析已经在加载时执行
        cout << "分析完成！" << endl;
        waitForKey();
    }
    
    void displayResults() {
        system("cls");
        auto tokens = lexer.analyze(""); // 重新分析当前代码
        
        cout << "词法分析结果 - " << currentFile << endl;
        cout << "==========================================" << endl;
        cout << setw(8) << "行号" << setw(8) << "位置" << setw(12) << "种别码" 
             << setw(20) << "单词值" << setw(15) << "类型" << endl;
        cout << "------------------------------------------" << endl;
        
        for (const auto& token : tokens) {
            cout << setw(8) << token.line 
                 << setw(8) << token.position
                 << setw(12) << token.type
                 << setw(20) << "\"" + token.value + "\""
                 << setw(15) << getTypeName(token.type) << endl;
        }
        
        cout << "==========================================" << endl;
        cout << "总计: " << tokens.size() << " 个单词" << endl;
        waitForKey();
    }
    
    void saveResults() {
        cout << "请输入输出文件名: ";
        string filename;
        cin >> filename;
        
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "无法创建文件: " << filename << endl;
            waitForKey();
            return;
        }
        
        auto tokens = lexer.analyze("");
        
        file << "词法分析结果 - " << currentFile << endl;
        file << "==========================================" << endl;
        file << "行号\t位置\t种别码\t单词值\t\t类型" << endl;
        
        for (const auto& token : tokens) {
            file << token.line << "\t" 
                 << token.position << "\t"
                 << token.type << "\t"
                 << "\"" << token.value << "\"\t\t"
                 << getTypeName(token.type) << endl;
        }
        
        file.close();
        cout << "结果已保存到: " << filename << endl;
        waitForKey();
    }
    
    void showSymbolTable() {
        system("cls");
        auto tokens = lexer.analyze("");
        
        cout << "符号表 - " << currentFile << endl;
        cout << "==========================================" << endl;
        
        // 统计各类单词数量
        int keywordCount = 0, identifierCount = 0, constantCount = 0;
        int operatorCount = 0, delimiterCount = 0;
        
        unordered_map<string, int> identifierMap;
        
        for (const auto& token : tokens) {
            switch (token.type) {
                case KEYWORD: keywordCount++; break;
                case IDENTIFIER: 
                    identifierCount++;
                    identifierMap[token.value]++;
                    break;
                case CONSTANT: constantCount++; break;
                case OPERATOR: operatorCount++; break;
                case DELIMITER: delimiterCount++; break;
            }
        }
        
        cout << "单词类型统计:" << endl;
        cout << "------------------------------------------" << endl;
        cout << "关键字: " << keywordCount << " 个" << endl;
        cout << "标识符: " << identifierCount << " 个" << endl;
        cout << "常数: " << constantCount << " 个" << endl;
        cout << "运算符: " << operatorCount << " 个" << endl;
        cout << "分隔符: " << delimiterCount << " 个" << endl;
        cout << "总计: " << tokens.size() << " 个单词" << endl;
        
        cout << endl << "标识符详情:" << endl;
        cout << "------------------------------------------" << endl;
        for (const auto& entry : identifierMap) {
            cout << entry.first << ": " << entry.second << " 次" << endl;
        }
        
        waitForKey();
    }
    
    string getTypeName(TokenType type) {
        switch (type) {
            case KEYWORD: return "关键字";
            case IDENTIFIER: return "标识符";
            case CONSTANT: return "常数";
            case OPERATOR: return "运算符";
            case DELIMITER: return "分隔符";
            default: return "未知";
        }
    }
    
    void waitForKey() {
        cout << endl << "按任意键继续..." << endl;
        _getch();
    }
};

// 主函数
int main() {
    // 设置控制台编码为UTF-8以支持中文
    SetConsoleOutputCP(65001);
    
    LexerUI ui;
    ui.showMenu();
    
    return 0;
}