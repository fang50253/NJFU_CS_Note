// assignment
// 编写一个程序，其功能要求如下：
// 1.能够一屏一屏简单浏览指定文本文件
// 2.将两个文本文件合并成一个文本文件
// 3.给一个文本文件每一行加上行号存储到另一个文本文件中
// 4.将一个文件中的所有小写字母转换成大写字母后存储到另一个文本文件中
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;

class FileProcessor {
public:
    // 一屏一屏浏览指定文本文件
    static void BrowseFile(const string& filename) {
        ifstream file(filename);
        if(!file.is_open()) {
            cout << "无法打开文件: " << filename << endl;
            return;
        }
        
        string line;
        int lineCount = 0;
        const int LINES_PER_PAGE = 20;
        
        cout << "\n正在浏览文件: " << filename << endl;
        cout << "按回车键继续浏览，输入 q 退出" << endl;
        
        while(getline(file, line)) {
            cout << line << endl;
            lineCount++;
            
            if(lineCount % LINES_PER_PAGE == 0) {
                cout << "已显示 " << lineCount << " 行，按回车继续...";
                char ch = cin.get();
                if(ch == 'q' || ch == 'Q') {
                    break;
                }
                cout << endl;
            }
        }
        
        cout << "文件浏览结束，共 " << lineCount << " 行" << endl;
        file.close();
    }
    
    // 将两个文本文件合并成一个文本文件
    static bool MergeFiles(const string& file1, const string& file2, const string& outputFile) {
        ifstream in1(file1);
        ifstream in2(file2);
        ofstream out(outputFile);
        
        if(!in1.is_open()) {
            cout << "无法打开文件: " << file1 << endl;
            return false;
        }
        if(!in2.is_open()) {
            cout << "无法打开文件: " << file2 << endl;
            return false;
        }
        if(!out.is_open()) {
            cout << "无法创建输出文件: " << outputFile << endl;
            return false;
        }
        
        string line;
        
        // 写入第一个文件的内容
        while(getline(in1, line)) {
            out << line << endl;
        }
        
        // 写入第二个文件的内容
        while(getline(in2, line)) {
            out << line << endl;
        }
        
        in1.close();
        in2.close();
        out.close();
        
        cout << "文件合并成功！" << endl;
        cout << file1 << " + " << file2 << " -> " << outputFile << endl;
        return true;
    }
    
    // 给文本文件每一行加上行号存储到另一个文本文件中
    static bool AddLineNumbers(const string& inputFile, const string& outputFile) {
        ifstream in(inputFile);
        ofstream out(outputFile);
        
        if(!in.is_open()) {
            cout << "无法打开文件: " << inputFile << endl;
            return false;
        }
        if(!out.is_open()) {
            cout << "无法创建输出文件: " << outputFile << endl;
            return false;
        }
        
        string line;
        int lineNum = 1;
        
        while(getline(in, line)) {
            out << lineNum++ << ". " << line << endl;
        }
        
        in.close();
        out.close();
        
        cout << "添加行号成功！共处理 " << (lineNum - 1) << " 行" << endl;
        cout << inputFile << " -> " << outputFile << " (已加行号)" << endl;
        return true;
    }
    
    // 将文件中的所有小写字母转换成大写字母后存储到另一个文本文件中
    static bool ConvertToUpper(const string& inputFile, const string& outputFile) {
        ifstream in(inputFile);
        ofstream out(outputFile);
        
        if(!in.is_open()) {
            cout << "无法打开文件: " << inputFile << endl;
            return false;
        }
        if(!out.is_open()) {
            cout << "无法创建输出文件: " << outputFile << endl;
            return false;
        }
        
        string line;
        int charCount = 0;
        
        while(getline(in, line)) {
            for(char& ch : line) {
                if(islower(ch)) {
                    ch = toupper(ch);
                    charCount++;
                }
            }
            out << line << endl;
        }
        
        in.close();
        out.close();
        
        cout << "小写转大写成功！共转换 " << charCount << " 个字符" << endl;
        cout << inputFile << " -> " << outputFile << " (已转大写)" << endl;
        return true;
    }
    
    // 创建测试文件
    static void CreateTestFiles() {
        // 创建文件1
        ofstream file1("file1.txt");
        if(file1.is_open()) {
            file1 << "这是第一个测试文件" << endl;
            file1 << "This is the first test file" << endl;
            file1 << "1234567890" << endl;
            file1 << "Hello World!" << endl;
            file1 << "文件合并测试" << endl;
            file1.close();
        }
        
        // 创建文件2
        ofstream file2("file2.txt");
        if(file2.is_open()) {
            file2 << "这是第二个测试文件" << endl;
            file2 << "This is the second test file" << endl;
            file2 << "Line 3 of file 2" << endl;
            file2 << "Line 4 of file 2" << endl;
            file2 << "文件合并完成" << endl;
            file2.close();
        }
        
        // 创建用于添加行号的测试文件
        ofstream file3("input.txt");
        if(file3.is_open()) {
            file3 << "第一行内容" << endl;
            file3 << "第二行内容" << endl;
            file3 << "第三行内容" << endl;
            file3 << "第四行内容" << endl;
            file3 << "第五行内容" << endl;
            file3.close();
        }
        
        // 创建用于大小写转换的测试文件
        ofstream file4("mixed.txt");
        if(file4.is_open()) {
            file4 << "Hello World! 你好世界！" << endl;
            file4 << "This is a Mixed CASE string." << endl;
            file4 << "ALL UPPERCASE" << endl;
            file4 << "all lowercase" << endl;
            file4 << "AbCdEfG HiJkLmN" << endl;
            file4.close();
        }
        
        cout << "测试文件已创建" << endl;
    }
    
    // 显示菜单
    static void ShowMenu() {
        cout << "\n文件处理程序" << endl;
        cout << "1. 一屏一屏浏览指定文本文件" << endl;
        cout << "2. 将两个文本文件合并成一个文本文件" << endl;
        cout << "3. 给文本文件每一行加上行号" << endl;
        cout << "4. 将文件中小写字母转换成大写字母" << endl;
        cout << "5. 创建测试文件" << endl;
        cout << "0. 退出程序" << endl;
        cout << "请选择功能: ";
    }
};

int main() {
    int choice;
    string filename, file1, file2, outputFile;
    
    cout << "文件处理程序" << endl;
    
    while(true) {
        FileProcessor::ShowMenu();
        cin >> choice;
        cin.ignore(); // 清除缓冲区
        
        switch(choice) {
            case 1:
                cout << "请输入要浏览的文件名: ";
                getline(cin, filename);
                FileProcessor::BrowseFile(filename);
                break;
                
            case 2:
                cout << "请输入第一个文件名: ";
                getline(cin, file1);
                cout << "请输入第二个文件名: ";
                getline(cin, file2);
                cout << "请输入合并后的文件名: ";
                getline(cin, outputFile);
                FileProcessor::MergeFiles(file1, file2, outputFile);
                break;
                
            case 3:
                cout << "请输入源文件名: ";
                getline(cin, file1);
                cout << "请输入输出文件名: ";
                getline(cin, outputFile);
                FileProcessor::AddLineNumbers(file1, outputFile);
                break;
                
            case 4:
                cout << "请输入源文件名: ";
                getline(cin, file1);
                cout << "请输入输出文件名: ";
                getline(cin, outputFile);
                FileProcessor::ConvertToUpper(file1, outputFile);
                break;
                
            case 5:
                FileProcessor::CreateTestFiles();
                break;
                
            case 0:
                cout << "感谢使用，再见！" << endl;
                return 0;
                
            default:
                cout << "无效选择，请重新输入！" << endl;
                break;
        }
    }
    
    return 0;
}