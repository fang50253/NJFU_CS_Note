#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <fstream>

using namespace std;

// 单词类型枚举
enum TokenType {
    KEYWORD = 1,    // 保留字
    IDENTIFIER = 2, // 标识符
    CONSTANT = 3,   // 常数
    OPERATOR = 4,   // 运算符
    DELIMITER = 5   // 分隔符
};

// 单词结构
struct Token {
    TokenType type;
    string value;
    int line;
    
    Token(TokenType t, const string& v, int l) : type(t), value(v), line(l) {}
};

class Lexer {
private:
    string source;           // 源代码
    int position;           // 当前位置
    int line;               // 当前行号
    vector<Token> tokens;   // 识别的单词列表
    
    // 关键字表
    unordered_map<string, bool> keywords = {
        {"main", true}, {"printf", true}, {"if", true}, {"int", true},
        {"for", true}, {"while", true}, {"do", true}, {"return", true},
        {"break", true}, {"continue", true}, {"else", true}, {"char", true},
        {"float", true}, {"long", true}, {"short", true}
    };
    
    // 运算符表
    unordered_map<string, bool> operators = {
        {"+", true}, {"-", true}, {"*", true}, {"/", true}, {"=", true},
        {">", true}, {"<", true}, {">=", true}, {"<=", true}, {"!=", true},
        {"+=", true}, {"-=", true}, {"*=", true}, {"/=", true}, {"==", true},
        {"&&", true}, {"||", true}, {"!", true}, {"&", true}, {"|", true},
        {"++", true}, {"--", true}
    };
    
    // 分隔符表
    unordered_map<string, bool> delimiters = {
        {",", true}, {";", true}, {"{", true}, {"}", true}, 
        {"(", true}, {")", true}, {"[", true}, {"]", true}
    };

public:
    Lexer(const string& code) : source(code), position(0), line(1) {}
    
    // 词法分析主函数
    vector<Token> analyze() {
        tokens.clear();
        
        while (position < source.length()) {
            // 跳过空白字符
            if (isspace(source[position])) {
                skipWhitespace();
                continue;
            }
            
            // 跳过注释
            if (source[position] == '/' && position + 1 < source.length()) {
                if (source[position + 1] == '/') {
                    skipLineComment();
                    continue;
                } else if (source[position + 1] == '*') {
                    skipBlockComment();
                    continue;
                }
            }
            
            // 处理字符串字面量
            if (source[position] == '"') {
                processString();
                continue;
            }
            
            // 处理字符字面量
            if (source[position] == '\'') {
                processChar();
                continue;
            }
            
            // 处理数字
            if (isdigit(source[position])) {
                processNumber();
                continue;
            }
            
            // 处理标识符和关键字
            if (isalpha(source[position]) || source[position] == '_') {
                processIdentifier();
                continue;
            }
            
            // 处理运算符和分隔符
            processSymbol();
        }
        
        return tokens;
    }
    
private:
    // 跳过空白字符
    void skipWhitespace() {
        while (position < source.length() && isspace(source[position])) {
            if (source[position] == '\n') {
                line++;
            }
            position++;
        }
    }
    
    // 跳过多行注释
    void skipBlockComment() {
        position += 2; // 跳过 "/*"
        while (position < source.length() - 1) {
            if (source[position] == '\n') {
                line++;
            }
            if (source[position] == '*' && source[position + 1] == '/') {
                position += 2;
                return;
            }
            position++;
        }
    }
    
    // 跳过单行注释
    void skipLineComment() {
        while (position < source.length() && source[position] != '\n') {
            position++;
        }
    }
    
    // 处理字符串字面量
    void processString() {
        int start = position;
        position++; // 跳过开头的 "
        
        while (position < source.length() && source[position] != '"') {
            if (source[position] == '\\') {
                position++; // 处理转义字符
            }
            if (source[position] == '\n') {
                line++;
            }
            position++;
        }
        
        if (position < source.length()) {
            position++; // 跳过结尾的 "
            string str = source.substr(start, position - start);
            tokens.emplace_back(CONSTANT, str, line);
        }
    }
    
    // 处理字符字面量
    void processChar() {
        int start = position;
        position++; // 跳过开头的 '
        
        if (position < source.length() && source[position] == '\\') {
            position++; // 处理转义字符
        }
        
        if (position < source.length()) {
            position++; // 跳过字符内容
        }
        
        if (position < source.length() && source[position] == '\'') {
            position++; // 跳过结尾的 '
            string chr = source.substr(start, position - start);
            tokens.emplace_back(CONSTANT, chr, line);
        }
    }
    
    // 处理数字
    void processNumber() {
        int start = position;
        
        // 处理整数部分
        while (position < source.length() && isdigit(source[position])) {
            position++;
        }
        
        // 处理浮点数的小数部分
        if (position < source.length() && source[position] == '.') {
            position++;
            while (position < source.length() && isdigit(source[position])) {
                position++;
            }
        }
        
        string num = source.substr(start, position - start);
        tokens.emplace_back(CONSTANT, num, line);
    }
    
    // 处理标识符和关键字
    void processIdentifier() {
        int start = position;
        
        while (position < source.length() && 
               (isalnum(source[position]) || source[position] == '_')) {
            position++;
        }
        
        string id = source.substr(start, position - start);
        
        // 检查是否是关键字
        if (keywords.find(id) != keywords.end()) {
            tokens.emplace_back(KEYWORD, id, line);
        } else {
            tokens.emplace_back(IDENTIFIER, id, line);
        }
    }
    
    // 处理运算符和分隔符
    void processSymbol() {
        string symbol(1, source[position]);
        
        // 检查双字符运算符
        if (position + 1 < source.length()) {
            string twoChar = source.substr(position, 2);
            if (operators.find(twoChar) != operators.end() || 
                twoChar == ">=" || twoChar == "<=" || twoChar == "==" || 
                twoChar == "!=" || twoChar == "+=" || twoChar == "-=" ||
                twoChar == "*=" || twoChar == "/=" || twoChar == "++" ||
                twoChar == "--" || twoChar == "&&" || twoChar == "||") {
                tokens.emplace_back(OPERATOR, twoChar, line);
                position += 2;
                return;
            }
        }
        
        // 单字符运算符或分隔符
        if (operators.find(symbol) != operators.end()) {
            tokens.emplace_back(OPERATOR, symbol, line);
        } else if (delimiters.find(symbol) != delimiters.end()) {
            tokens.emplace_back(DELIMITER, symbol, line);
        } else {
            // 未知字符，跳过
            tokens.emplace_back(DELIMITER, symbol, line);
        }
        
        position++;
    }
};

// 打印分析结果
void printTokens(const vector<Token>& tokens) {
    cout << "词法分析结果：" << endl;
    cout << "（种别码，单词值）" << endl;
    cout << "-------------------" << endl;
    
    for (const auto& token : tokens) {
        cout << "（" << token.type << "，\"" << token.value << "\"）" << endl;
    }
}

// 测试函数
int main() {
    // 测试代码
    string testCode = R"(
main()
{
    int i,j,m,n;
    printf("please input data to i,j");
    i=1;
    j=4;
    m=i+j;
    n=i-j;
    printf("m=%d,n=%d",m,n);
}
)";

    cout << "源代码：" << endl;
    cout << testCode << endl;
    cout << "====================" << endl;

    Lexer lexer(testCode);
    vector<Token> tokens = lexer.analyze();
    printTokens(tokens);

    // 从文件读取测试
    cout << endl << "====================" << endl;
    cout << "是否从文件测试？(y/n): ";
    char choice;
    cin >> choice;
    
    if (choice == 'y' || choice == 'Y') {
        string filename;
        cout << "请输入文件名: ";
        cin >> filename;
        
        ifstream file(filename);
        if (file.is_open()) {
            string fileContent((istreambuf_iterator<char>(file)), 
                              istreambuf_iterator<char>());
            file.close();
            
            Lexer fileLexer(fileContent);
            vector<Token> fileTokens = fileLexer.analyze();
            printTokens(fileTokens);
        } else {
            cout << "无法打开文件: " << filename << endl;
        }
    }

    return 0;
}