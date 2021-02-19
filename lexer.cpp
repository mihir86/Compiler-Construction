#include <bits/stdc++.h>
using namespace std;

#define LPAREN 110
#define RPAREN 111
#define LBRACE 112
#define RBRACE 113
#define SEMICOL 114
#define COMMA 115
#define OP_ADD 120
#define OP_MUL 121
#define LESS 122
#define NOT 123
#define ASSIGN 124
#define IDENTIFIER 130
#define INTEGER_LITERAL 131
#define END 132

class Scanner {
    int line;
    bool bufferCharLoaded;
    char bufferChar;
    ifstream program;
    vector<pair<string, int>> v;
    char peekChar()
    {
        if(!bufferCharLoaded)
        {
            bufferCharLoaded = true;
            program >> noskipws >> bufferChar;
        }
        return bufferChar;
    }
    char getChar()
    {
        if(!bufferCharLoaded)
        {
            bufferCharLoaded = true;
            program >> noskipws >> bufferChar;
        }
        bufferCharLoaded = false;
        if(bufferChar == '\n')
            line++;
        return bufferChar;
    }
    void skipLine()
    {
        while(!program.eof() && getChar() != '\n')
            ;
    }
    bool isSeparator(char c)
    {
        if(c == '(' || c == ')' || c == '{' || c == '}' || c == ';' || c == ',')
            return true;
        if(c == '+' || c == '*' || c == '<' || c == '!' || c == '=')
            return true;
        if(c == ' ' || c == '\n')
            return true;
        return false;
    }
    int DFA(int state, string &token)
    {
        if(state == 0)
        {
            char c = getChar();
            if(program.eof())
                return END;
            if(c == '#')
            {
                skipLine();
                return DFA(state, token);
            }
            if(c == ' ' || c == '\n')
                return DFA(state, token);
            token += c;
            if(c == '(')
                return LPAREN;
            if(c == ')')
                return RPAREN;
            if(c == '{')
                return LBRACE;
            if(c == '}')
                return RBRACE;
            if(c == ';')
                return SEMICOL;
            if(c == ',')
                return COMMA;
            if(c == '+')
                return OP_ADD;
            if(c == '*')
                return OP_MUL;
            if(c == '<')
                return LESS;
            if(c == '!')
                return NOT;
            if(c == '=')
                return ASSIGN;
            if(c >= '0' && c <= '9')
                return DFA(1, token);
            if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                return DFA(2, token);
            throw "Error, cannot process " + string(1, c) + " as beggining of a token!!!";
        }
        else if(state == 1)
        {
            char c = peekChar();
            if(program.eof())
                return INTEGER_LITERAL;
            if(c >= '0' && c <= '9')
            {
                c = getChar();
                token += c;
                return DFA(1, token);
            }
            else if(isSeparator(c))
                return INTEGER_LITERAL;
            else
            {
                c = getChar();
                while(!program.eof() && !isSeparator(c))
                    token += c, c = getChar();
                throw "Error, " + token + " is not a valid identifier!!!";
            }
        }
        else
        {
            char c = peekChar();
            if(program.eof())
            {
                for(auto &k: v)
                    if(k.first == token)
                        return k.second;
                return IDENTIFIER;
            }
            if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            {
                c = getChar();
                token += c;
                return DFA(2, token);
            }
            else if(isSeparator(c))
            {
                for(auto &k: v)
                    if(k.first == token)
                        return k.second;
                return IDENTIFIER;
            }
            else
            {
                c = getChar();
                while(!program.eof() && !isSeparator(c))
                    token += c, c = getChar();
                throw "Error, " + token + " is not a valid identifier!!!";
            }
        }
    }
    public:
    Scanner(string programFile)
    : line(1)
    , bufferCharLoaded(false)
    , program(programFile)
    , v
        {
            {"int", 100},
            {"if", 101},
            {"else", 102},
            {"while", 103}
        }
    {}
    tuple<int, string, int> getToken()
    {
        string token;
        int id = DFA(0, token);
        if(id == END)
            token = "FILE_END_REACHED";
        return {id, token, line};
    }
};

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    Scanner scanner("program.c++++");
    while(true)
    {
        try {
            tuple<int, string, int> token = scanner.getToken();
            int id, line;
            string s;
            tie(id, s, line) = token;
            cout << id << " " << s << " " << line << "\n";
            if(id == END)
                break;
        }
        catch(string error) {
            cout << error << "\n";
        }
    }
}
