#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;
class Parser
{
public:
    int lookhead; // 下一个要处理的字符
    Parser()
    {
        getNext();
    }
    // 处理表达式
    void expr()
    {
        term();
        if (lookhead == '+')
        {
            match('+');
            term();
        }
        else if (lookhead == '-')
        {

            match('-');
            term();
        }
    }
    // 处理项
    void term()
    {
        factor();
        if (lookhead == '*')
        {
            match('*');
            factor();
        }
        else if (lookhead == '/')
        {

            match('/');
            factor();
        }
    }
    // 处理因子
    void factor()
    {
        if (isalpha(lookhead))
            id();
        else if (isdigit(lookhead) ||
                 lookhead == '+' ||
                 lookhead == '-')
            num();
        else if (lookhead == '(')
        {
            match('(');
            expr();
            match(')');
        }
        else
            error();
    }
    // 处理标识符
    void id()
    {
        matchAlpha();
        while (isalpha(lookhead) || isdigit(lookhead))
        {
            if (isalpha(lookhead))
                matchAlpha();
            else
                matchDigit();
        }
    }
    // 处理数字
    void num()
    {
        if (lookhead == '+')
            match('+');
        else if (lookhead == '-')
            match('-');
        matchDigit();
        while (isdigit(lookhead))
            matchDigit();
        if (lookhead == '.')
        {
            match('.');
            matchDigit();
            while (isdigit(lookhead))
                matchDigit();
        }
        if (lookhead == 'e')
        {
            match('e');
            if (lookhead == '+')
                match('+');
            else if (lookhead == '-')
                match('-');
            matchDigit();
            while (isdigit(lookhead))
                matchDigit();
        }
    }
    // 匹配单个字符，成功则读取下一个字符
    void match(int t)
    {
        if (lookhead == t)
            getNext();
        else
            error();
    }
    // 匹配字母
    void matchAlpha()
    {
        if (isalpha(lookhead))
            getNext();
        else
            error();
    }
    // 匹配数字
    void matchDigit()
    {
        if (isdigit(lookhead))
            getNext();
        else
            error();
    }
    // 读取下一个字符
    void getNext()
    {
        char tmp;
        if (!(cin >> tmp))
            success();
        lookhead = tmp;
        cout << tmp;
    }
    // 出错处理
    void error()
    {
        puts("\nerror!");
        exit(1);
    }
    // 成功后的响应
    void success()
    {
        printf("\nsuccess!");
        exit(0);
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    Parser a = Parser();
    a.expr();
    system("pause");
    return 0;
}
