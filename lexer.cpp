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

//Scanner class that can be initialised with a .c+++ file
//has only one public constructor, Scanner(string programFile)
//has one public member function, tuple<int, string, int> getToken() which returns a token
class Scanner {
    //current program line number
    int line;
    //is bufferChar loaded?
    bool bufferCharLoaded;
    //the buffer character
    char bufferChar;
    //input stream for program
    ifstream program;
    //table for keyword lookup
    vector<pair<string, int>> v;
    //peek the next character without consuming it
    char peekChar()
    {
        if(!bufferCharLoaded)
        {
            bufferCharLoaded = true;
            program >> noskipws >> bufferChar;
        }
        return bufferChar;
    }
    //peek the next character and consume it
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
    //skip a line in program file, used to handle comments
    void skipLine()
    {
        while(!program.eof() && getChar() != '\n')
            ;
    }
    //used to identify seperator characters
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
    //the DFA representing the lexer
    //0 is the initial state
    //1 is the state for integer literals
    //2 is the state for identifiers and keywords
    //once a identifier/keyword is generated, it is matched against the keyword table
    //a string error is thrown in case the token generated is invalid or a bad symbol occurs
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
                while(!program.eof() && !isSeparator(c))
                    c = getChar(), token += c, c = peekChar();
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
                while(!program.eof() && !isSeparator(c))
                    c = getChar(), token += c, c = peekChar();
                throw "Error, " + token + " is not a valid identifier!!!";
            }
        }
    }
    public:
    //constructor for Scanner
    Scanner(string programFile)
    : line(1)
    , bufferCharLoaded(false)
    , program(programFile)
    , v
        {
            {"int", 100},
            {"if", 101},
            {"else", 102},
            {"while", 103},
            {"print", 104}
        }
    {}
    //used to get the next token
    tuple<int, string, int> getToken()
    {
        string token;
        int id = DFA(0, token);
        if(id == END)
            token = "FILE_END_REACHED";
        return {id, token, line};
    }
};

int32_t main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    Scanner scanner(argv[1]);
    while(true)
    {
        try {
            tuple<int, string, int> token = scanner.getToken();
            int id, line;
            string s;
            tie(id, s, line) = token;
            if(id == END)
                break;
            cout << "Token: " << id << " , String: " << s << " , Line number: " << line << "\n";
        }
        catch(string error) {
            cout << error << "\n";
        }
    }
}
