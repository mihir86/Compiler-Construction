#include <parser.hpp>

Parser::Parser(char* fileName)
    : scanner(fileName)
    {
        int n;

        ifstream is("parseTable.txt");
        is >> n;
        while(n--) {
            int state, token;
            string move;
            is >> state >> token >> move;
            parseTable[{state, token}] = move;
        }
        is.close();

        is = ifstream("reduceTable.txt");
        is >> n;
        for(int i = 0; i < n; i++) {
            int id, length;
            is >> id >> length;
            reduceTable[i] = {id, length};
            // cout << id << " " << length << "\n";
        }
        is.close();
    }

void Parser::printTokens() {
    while(true)
    {
        try {
            tuple<int, string, int> token = scanner.getToken();
            int id, line;
            string str;
            tie(id, str, line) = token;
            if(id == END)
                break;
            cout << "Token: " << id << " , String: " << str << " , Line number: " << line << "\n";
        }
        catch(string error) {
            cout << error << "\n";
        }
    }
}

tuple<int, string, int> Parser::getToken() {
    if(!errorStack.empty()) {
        tuple<int, string, int> t = errorStack.top();
        errorStack.pop();
        return t;
    }
    return scanner.getToken();
}

void Parser::LR1() {
    s.push({END, 0});
    int id, line;
    string str;
    tie(id, str, line) = getToken();
    // int i = 0;
    int flag = 1;
    while(true) {
        int currentState = s.top().second;
        if(parseTable.find({currentState, id}) != parseTable.end()) {
            string move = parseTable[{currentState, id}];
            if(move == "acc") {
                if(flag)
                    cout << "ACCEPTED\n";
                else
                    cout << "REJECTED\n";
                break;
            }

            // if(i == 4) {
            //     cout << currentState << " " << move << "\n";
            //     break;
            // }

            string submove = string(move.begin()+1, move.end());
            int newStateMove = stoi(submove);
            // cout << currentState << " " << move << " " << newStateMove << "\n";

            if(move[0] == 's') {
                s.push({id, newStateMove});
                tie(id, str, line) = getToken();
            }
            else if(move[0] == 'r') {
                int id2, length2;
                tie(id2, length2) = reduceTable[newStateMove];
                // cout << id2 << " " << length2 << "\n";
                // break;
                while(length2--)
                    s.pop();
                int newState = stoi(parseTable[{s.top().second, id2}]);
                s.push({id2, newState});
            }
        }
        else {
            flag = 0;
            int currentTop = s.top().first;
            cout << "Parser could not parse Line #" << line << "\n";
            // cout << currentTop << " " << id << "\n";
            while(!(currentTop == 202 
                    || currentTop == 211
                    || currentTop == 209
                    || currentTop == 210
                    || currentTop == 206
                    || currentTop == END
                    || currentTop == LBRACE)) {
                // cout << s.top().first << "\n";
                s.pop();
                currentTop = s.top().first;
            }
                // s.pop();
            while(true) {
                if(id == END)
                    break;
                if(id == SEMICOL || id == RBRACE) {
                    tie(id, str, line) = getToken();
                    // cout << line << " " << id << "###\n";
                    break;
                }
                tie(id, str, line) = getToken();
            }
            // cout << s.size() << " " << id << "\n";
            // break;
            // if(id == RPAREN) {
            //     if(s.top().first == LPAREN) {
            //         cout << "Line " << line << " has a missing expression in ()\n";
            //         errorStack.push({id, str, line});
            //         id = IDENTIFIER, str = "$DUMMY_ID$";
            //     }
            //     else {
            //         cout << "Line " << line << " has a imbalanced )\n";
            //         tie(id, str, line) = getToken();
            //     }
            // }
            // else if(id == RBRACE) {
            //     cout << "Line " << line << " has a imbalanced }\n";
            //     tie(id, str, line) = getToken();
            // }
            // else if(id == IDENTIFIER) {
            //     cout << "Line " << line << " has a missing operator\n";
            //     errorStack.push({id, str, line});
            //     id = OP_ADD, str = "$DUMMY_OP$";
            // }
            // else if(id == OP_ADD || id == OP_MUL || id == LESS) {
            //     cout << "Line " << line << " has a missing identifier/literal\n";
            //     errorStack.push({id, str, line});
            //     id = IDENTIFIER, str = "$DUMMY_ID$";
            // }
            // else if(id == ASSIGN) {
            //     cout << "Line " << line << " has a missing LHS identifier\n";
            //     errorStack.push({id, str, line});
            //     id = IDENTIFIER, str = "$DUMMY_ID$";
            // }
            // else {
            //     cout << "Line " << line << " has a missing semicolon\n";
            //     errorStack.push({id, str, line});
            //     id = SEMICOL, str = "$DUMMY_;$";
            // }
            // break;
        }
        // i++;
    }
}