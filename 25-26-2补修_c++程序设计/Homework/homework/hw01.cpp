// assignment:
// 设计一个四则运算器程序，要求：
// 1.用随机数控制产生的四则运算表达式
// 2.让用户定时计算结果并计算正确率

#include<time.h>
#include<iostream>
#include<unordered_map>
#include<chrono>
#include<thread>
#include<ctime>
#include<cstdlib>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>

using std::cin;
using std::cout;
using std::endl;
using std::unordered_map;

unordered_map<int,char> op;

int get_random(int l, int r){
    return rand() % (r - l + 1) + l;
}

// 修正：ans 必须使用引用传递，否则无法返回正确答案
int get_test(int &a, int &b, int &_op, int &ans){
    // 生成两个操作数 (1-100)
    a = get_random(1, 100);
    b = get_random(1, 100);
    _op = get_random(0, 3);
    
    switch(_op) {
        case 0: // 加法
            ans = a + b;
            break;
        case 1: // 减法，不允许出现负数
            if (a < b) {
                std::swap(a, b);
            }
            ans = a - b;
            break;
        case 2: // 乘法
            if (a * b > 1000) {
                a = get_random(1, 30);
                b = get_random(1, 30);
            }
            ans = a * b;
            break;
        case 3: { // 除法，必须能整除
            b = get_random(1, 20);
            int multiplier = get_random(1, 10);
            a = b * multiplier;
            if (a > 100) {
                multiplier = get_random(1, 100 / b);
                a = b * multiplier;
            }
            ans = a / b;
            break;
        }
    }
    return 1;
}

// 检测是否有输入（非阻塞）
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

void test(){
    int total_questions = 10;
    int correct_count = 0;
    int user_answer;
    int a, b, op_type, correct_ans;
    
    cout << "\n========== 四则运算测试 ==========" << endl;
    cout << "您将有 " << total_questions << " 道题目" << endl;
    cout << "每道题限时5秒，输入答案后按回车立即判断" << endl;
    cout << "按回车键开始..." << endl;
    cin.get();
    
    auto start_time = std::chrono::steady_clock::now();
    
    for(int i = 1; i <= total_questions; i++) {
        // 生成题目（传递 correct_ans 的引用）
        get_test(a, b, op_type, correct_ans);
        
        // 显示题目
        cout << "\n第 " << i << " 题: " << a << " " << op[op_type] << " " << b << " = ?" << endl;
        
        auto question_start = std::chrono::steady_clock::now();
        user_answer = 0;
        bool has_answer = false;
        
        // 等待用户输入，但有5秒超时
        while(true) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - question_start).count();
            
            if(elapsed >= 5) {
                cout << "\n时间到！超时了..." << endl;
                // 清空输入缓冲区
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
            
            // 检测是否有输入
            if(kbhit()) {
                cin >> user_answer;
                has_answer = true;
                break;
            }
            
            // 避免CPU占用过高
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        // 如果用户回答了，立即判断
        if(has_answer) {
            if(user_answer == correct_ans) {
                cout << "✓ 正确！" << endl;
                correct_count++;
            } else {
                cout << "✗ 错误！正确答案是: " << correct_ans << endl;
            }
        }
    }
    
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    
    double accuracy = (double)correct_count / total_questions * 100;
    
    cout << "\n========== 测试结果 ==========" << endl;
    cout << "总题数: " << total_questions << endl;
    cout << "正确数: " << correct_count << endl;
    cout << "错误数: " << total_questions - correct_count << endl;
    cout << "正确率: " << accuracy << "%" << endl;
    cout << "总用时: " << duration.count() << " 秒" << endl;
    
    if(accuracy >= 90) {
        cout << "评价: 优秀！继续保持！" << endl;
    } else if(accuracy >= 70) {
        cout << "评价: 良好！再努力一下！" << endl;
    } else if(accuracy >= 60) {
        cout << "评价: 及格！需要加强练习！" << endl;
    } else {
        cout << "评价: 不及格！请多加练习！" << endl;
    }
    cout << "==============================" << endl;
}

int main(){
    op[0] = '+';
    op[1] = '-';
    op[2] = '*';
    op[3] = '/';
    
    srand(time(NULL));
    
    cout << "欢迎使用四则运算练习程序！" << endl;
    
    char choice;
    do {
        test();
        cout << "\n是否继续练习？(y/n): ";
        cin >> choice;
        cin.ignore(); // 清除缓冲区
    } while(choice == 'y' || choice == 'Y');
    
    cout << "感谢使用，再见！" << endl;
    
    return 0;
}