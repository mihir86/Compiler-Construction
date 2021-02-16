#include <bits/stdc++.h>
using namespace std;

vector<pair<string, int>> v{
    {"int", 100},
    {"if", 101},
    {"else", 102},
    {"while", 103},
    {"return", 104},
    {"main", 105},
    {"(", 110},
    {")", 111},
    {"{", 112},
    {"}", 113},
    {"[", 114},
    {"]", 115},
    {";", 116},
    {",", 117},
    {"+", 120},
    {"*", 121},
    {"<", 122},
    {"!", 123},
    {"=", 124},
};
//130 -> identifier
//131 -> integer literal

int DFA(string &s, int index, int state)
{
    if(state == 0)
    {
        if((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z'))
            return DFA(s, index+1, 1);
        else if((s[0] >= '0' && s[0] <= '9') || s[0] == '+' || s[0] == '-')
            return DFA(s, index+1, 2);
        else
            throw "Invalid Token: " + s;
    }
    else if(state == 1)
    {
        if(index == (int)s.size())
            return 130;
        else if((s[index] >= 'a' && s[index] <= 'z') || (s[index] >= 'A' && s[index] <= 'Z') || (s[index] >= '0' && s[index] <= '9') || s[index] == '_')
            return DFA(s, index+1, 1);
        else
            throw "Invalid Token: " + s;
    }
    else if(state == 2)
    {
        if(index == (int)s.size())
            return 131;
        else if(s[index] >= '0' && s[index] <= '9')
            return DFA(s, index+1, 2);
        else
            throw "Invalid Token: " + s;
    }
    throw "Invalid Token: " + s;
}

void tokenize(string s, int line)
{
    string t = "";
    for(auto &k: v)
        if(k.first == s)
            t = to_string(k.second);
    if(t == "")
        t = to_string(DFA(s, 0, 0));
    cout << "Token " << t << ", string " << s << ", line number " << line << "\n";
}

void process(string &s, int line)
{
    if(s != "")
        tokenize(s, line);
    s = "";
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    ifstream program("program.xyz");
    int line = 1;
    char c;
    string s = "";
    try {
        while(program >> noskipws >> c)
        {
            //handle + seperately
            if(c == '#')
            {
                while((program >> noskipws >> c))
                    if(c == '\n')
                        break;
            }
            else if(c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ';' || c == ',')
            {
                process(s, line);
                s += c;
                process(s, line);
            }
            else if(c == '+' || c == '*' || c == '<' || c == '!' || c == '=')
            {
                process(s, line);
                s += c;
                process(s, line);
            }
            else if(c == ' ' || c == '\n')
                process(s, line);
            else
                s += c;
            if(c == '\n')
                line++;
        }
        process(s, line);
    }
    catch(string err)
    {
        cout << err << "\n";
    }
}