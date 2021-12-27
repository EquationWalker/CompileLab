#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>
using namespace std;
unordered_map<string, int> Tag = {{"begin", 1}, {"if", 2}, {"then", 3},
    {"while", 4}, {"do", 5}, {"end", 6}, 
    {"id", 10}, {"num", 11}, {"+", 13}, {"-", 14},
     {"*", 15}, {"/", 16}, {":", 17}, {":=", 18},
    {"<", 20}, {"<>", 21}, {"<=", 22}, {">", 23}, 
    {">=", 24}, {"=", 25}, {";", 26}, 
    {"(", 27}, {")", 28}, {"#", 0}};
typedef pair<int, string> PIS;
const PIS ERROR = {-1, "error"};

class Lexer
{
public:
    int line = 1;
    PIS scan()
    {
        // 跳过空格，制表符和换行
        for (; !isError; readch())
        {
            if (peak == ' ' || peak == '\t')
                continue;
            else if (peak == '\n')
                line++;
            else
                break;
        }
        if (isError)
            return ERROR;
        // 处理基本运算符
        switch (peak)
        {
        case '<':
            if (readch('='))
                return {Tag["<="], "<="};
            else if (peak == '>')
                return {Tag["<>"], "<>"};
            else
                return {Tag["<"], "<"};
        case ':':
            if (readch('='))
                return {Tag[":="], ":="};
            else
                return {Tag[":"], ":"};
        case '>':
            if (readch('='))
                return {Tag[">="], ">="};
            else
                return {Tag[">"], ">"};
        case '=':
            peak = ' ';
            return {Tag["="], "="};
        case '+':
            peak = ' ';
            return {Tag["+"], "+"};
        case '-':
            peak = ' ';
            return {Tag["-"], "-"};
        case '*':
            peak = ' ';
            return {Tag["*"], "*"};
        case '/':
            peak = ' ';
            return {Tag["/"], "/"};
        case ';':
            peak = ' ';
            return {Tag[";"], ";"};
        case '(':
            peak = ' ';
            return {Tag["("], "("};
        case ')':
            peak = ' ';
            return {Tag[")"], ")"};
        case '#':
            peak = ' ';
            return {Tag["#"], "#"};
        }
        // 处理数字
        if (isdigit(peak))
        {
            int v = 0;
            do
            {
                v = 10 * v + peak - '0';
                readch();
            } while (isdigit(peak));

            return {Tag["num"], to_string(v)};
        }
        // 处理关键字和标识符
        if (isalpha(peak))
        {
            string buffer;
            do
            {
                buffer.push_back(peak);
                readch();
            } while (isalpha(peak) || isdigit(peak));

            if (Tag.count(buffer) > 0)
                return {Tag[buffer], buffer};
            return {Tag["id"], buffer};
        }
        return ERROR;
    }

private:
    char peak = ' ';
    bool isError = false;
    void readch()
    {
        if (!cin.get(peak))
            peak = ' ', isError = true;
    }
    bool readch(char c)
    {
        readch();
        if (c != peak)
            return false;
        peak = ' ';
        return true;
    }
};

int main()
{
    Lexer lex;
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    PIS curToken;
    while ((curToken = lex.scan()) != ERROR)
        cout << "(" + to_string(curToken.first) + 
            "," + curToken.second + ")";
    return 0;
}