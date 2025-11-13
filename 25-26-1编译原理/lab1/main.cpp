#include<stdio.h>
#include<iostream>
#include<string.h>
#include<unordered_map>
#include<vector>
#include <fstream> 
struct Result{
    int line;
    int column;
    std::string token;
    int token_type;
};
class Lexical{
private:
    std::string str;
    int index;
    std::vector<Result>results;
    enum TokenType {
        KEYWORD = 1,
        IDENTIFIER = 2,
        CONSTANT = 3,
        OPERATOR = 4,
        DELIMITER = 5
    };
    std::unordered_map<std::string, bool> keywords = {
        {"main", true}, {"printf", true}, {"if", true}, {"int", true},
        {"for", true}, {"while", true}, {"do", true}, {"return", true},
        {"break", true}, {"continue", true}, {"else", true}, {"char", true},
        {"float", true}, {"long", true}, {"short", true}
    };
    std::unordered_map<std::string, bool> operators = {
        {"+", true}, {"-", true}, {"*", true}, {"/", true}, {"=", true},
        {">", true}, {"<", true}, {">=", true}, {"<=", true}, {"!=", true},
        {"+=", true}, {"-=", true}, {"*=", true}, {"/=", true}, {"==", true},
        {"&&", true}, {"||", true}, {"!", true}, {"&", true}, {"|", true},
        {"++", true}, {"--", true}
    };
    std::unordered_map<std::string, bool> delimiters = {
        {",", true}, {";", true}, {"{", true}, {"}", true}, 
        {"(", true}, {")", true}, {"[", true}, {"]", true}
    };
    void read_line(){
        std::getline(std::cin,str);
    }
    void trim_space(){
        str.erase(std::remove_if(str.begin(),str.end(),::isspace),str.end());
    }
    void analyze_line(){
        std::string next_token="";
        while(1){
            if(index<str.length()) next_token+=str[index++];
            else break;
            if(keywords.find(next_token)!=keywords.end()){
                Result res;
                res.line = index;
                res.column = index + static_cast<int>(next_token.length());
                res.token = next_token;
                res.token_type = KEYWORD;
                results.push_back(res);
            }
            else if(operators.find(next_token)!=operators.end()){
                Result res;
                res.line = index;
                res.column = index + static_cast<int>(next_token.length());
                res.token = next_token;
                res.token_type = KEYWORD;
                results.push_back(res);
            }
            else if(delimiters.find(next_token)!=delimiters.end()){
                Result res;
                res.line = index;
                res.column = index + static_cast<int>(next_token.length());
                res.token = next_token;
                res.token_type = KEYWORD;
                results.push_back(res);
            }
        }

    }
    void open(std::string filename){
        std::ifstream file(filename);
        if(file.is_open()){
            std::string line;
            while(std::getline(file,line)){
                str+=line;
            }
            file.close();
        }
        else{
            std::cout<<"Error opening file"<<std::endl;
        }
    }
    void save(std::string filename){
        std::ofstream file(filename);
        if(file.is_open()){
            for(auto result:results){
                file<<result.line<<" "<<result.column<<" "<<result.token<<" "<<result.token_type<<std::endl;
            }
            file.close();
        }
        else{
            std::cout<<"Error opening file"<<std::endl;
        }
    }
public:
    Lexical(){
        index=0;
        results.clear();

    }
    void run(std::string filename){
        open(filename);        
        while(1){
            read_line();
            if(str=="") break;
            trim_space();
            analyze_line();
        }
        save("example.out");
    }
};
int main(){
    Lexical lexical;
    lexical.run("example.c");
    return 0;
}