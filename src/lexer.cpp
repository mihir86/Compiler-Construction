#include <lexer.hpp>

char Scanner::peekChar()
{
    if(!bufferCharLoaded)
    {
        bufferCharLoaded = true;
        program >> noskipws >> bufferChar;
    }
    return bufferChar;
}
char Scanner::getChar()
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
void Scanner::skipLine()
{
    while(!program.eof() && getChar() != '\n')
        ;
}
bool Scanner::isSeparator(char c)
{
    if(c == '(' || c == ')' || c == '{' || c == '}' || c == ';' || c == ',')
        return true;
    if(c == '+' || c == '*' || c == '<' || c == '!' || c == '=')
        return true;
    if(c == ' ' || c == '\n')
        return true;
    return false;
}
int Scanner::DFA(int state, string &token)
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
Scanner::Scanner(string programFile)
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
tuple<int, string, int> Scanner::getToken()
{
    string token;
    int id = DFA(0, token);
    if(id == END)
        token = "FILE_END_REACHED";
    return {id, token, line};
}