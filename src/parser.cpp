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

        is = ifstream("actionTable.txt");
        is >> n;
        for(int i = 0; i < n; i++) {
            int id, length;
            is >> id >> length;
            reduceTable[i] = {id, length};
            // cout << id << " " << length << "\n";
        }
        is.close();

        getString[130] = "identifier";
        getString[131] = "integerLiteral";
        getString[132] = "$";
        getString[201] = "assignmentStatement";
        getString[202] = "blockStatement";
        getString[203] = "conditionalStatement";
        getString[204] = "declarationStatement";
        getString[205] = "expression";
        getString[206] = "function";
        getString[207] = "loopStatement";
        getString[208] = "parameterList";
        getString[209] = "program";
        getString[210] = "program\'";
        getString[211] = "statement";
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
    s.push({END, 0, new parseTreeNode("program\'")});
    int id, line;
    string str;
    tie(id, str, line) = getToken();
    // int i = 0;
    int flag = 1;
    int _1, _2;
    parseTreeNode* _3;
    while(true) {
        tie(_1, _2, _3) = s.top();
        int currentState = _2;
        if(parseTable.find({currentState, id}) != parseTable.end()) {
            string move = parseTable[{currentState, id}];
            if(move == "acc") {
                if(flag)
                    cerr << "ACCEPTED\n";
                else
                    cerr << "REJECTED\n";
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
                s.push({id, newStateMove, new parseTreeNode(str)});
                tie(id, str, line) = getToken();
            }
            else if(move[0] == 'r') {
                int id2, length2;
                tie(id2, length2) = reduceTable[newStateMove];
                parseTreeNode *newNode = new parseTreeNode(getString[id2]);
                // cout << id2 << " " << length2 << "\n";
                // break;
                while(length2--) {
                    tie(_1, _2, _3) = s.top();
                    newNode->addNode(_3);
                    _3->correctOrder();
                    s.pop();
                }
                tie(_1, _2, _3) = s.top();
                int newState = stoi(parseTable[{_2, id2}]);
                s.push({id2, newState, newNode});
            }
        }
        else {
            flag = 0;
            tie(_1, _2, _3) = s.top();
            cerr << "Parser could not parse Line #" << line << "\n";
            if(parseTable.find({_2, RBRACE}) != parseTable.end()) {
                cerr << "Performing Syntactical Error Recovery for }\n";
                errorStack.push({id, str, line});
                id = RBRACE; str = "$DUMMY_}$";
                continue;
            }
            if(parseTable.find({_2, RPAREN}) != parseTable.end()) {
                cerr << "Performing Syntactical Error Recovery for )\n";
                errorStack.push({id, str, line});
                id = RPAREN; str = "$DUMMY_)$";
                continue;
            }
            if(parseTable.find({_2, SEMICOL}) != parseTable.end()) {
                cerr << "Performing Syntactical Error Recovery for ;\n";
                errorStack.push({id, str, line});
                id = SEMICOL; str = "$DUMMY_;$";
                continue;
            }
            cerr << "Entering Panic Recovery Mode\n";
            int currentTop = _1;
            // cout << currentTop << " " << id << "\n";
            while(!(currentTop == 201 
                    || currentTop == 202
                    || currentTop == 203
                    || currentTop == 204
                    || currentTop == 206
                    || currentTop == 207
                    || currentTop == 209
                    || currentTop == 210
                    || currentTop == 211
                    || currentTop == END)) {
                // cout << s.top().first << "\n";
                s.pop();
                // cout << _1 << "\n";
                tie(_1, _2, _3) = s.top();
                currentTop = _1;
            }
            // cout << "\n";
            // break;

            while(true) {
                if(id == END || parseTable.find({_2, id}) != parseTable.end())
                    break;
                tie(id, str, line) = getToken();
            }

            if(id == END) {
                while(!s.empty() && parseTable.find({_2, id}) == parseTable.end()) {
                    s.pop();
                    tie(_1, _2, _3) = s.top();
                }
                // if(s.empty()) {
                //     s.push({END, 0, new parseTreeNode("program\'")});
                // }
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
    tie(_1, _2, _3) = s.top();
    _3->correctOrder();
    _3->printTree();
}