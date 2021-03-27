import sys
import os.path

dict = {
    'int' : 100,
    'if' : 101,
    'else' : 102,
    'while' : 103,
    '(' : 110,
    ')' : 111,
    '{' : 112,
    '}' : 113,
    ';' : 114,
    ',' : 115,
    '+' : 120,
    '*' : 121,
    '<' : 122,
    '!' : 123,
    '=' : 124,
    'identifier' : 130,
    'integerLiteral' : 131,
    '$' : 132,
    'assignmentStatement' : 201,
    'blockStatement' : 202,
    'conditionalStatement' : 203,
    'declarationStatement' : 204,
    'expression' : 205,
    'function' : 206,
    'loopStatement' : 207,
    'parameterList' : 208,
    'program' : 209,
    'program\'' : 210,
    'statement' : 211
}

BNF = "BNF.txt"
t = []

try:
    with open("./" + BNF) as bnfFile:
        for line in bnfFile:
            # print(line)
            values = line.split()
            if values[2] == '\'\'':
                t.append([dict[values[0]] , 0])
            else:
                t.append([dict[values[0]] ,len(values) - 2])

except:
    print("BNF file doesn't exist!")
    exit(0)

print(len(t))
for move in t:
    print(move[0], move[1])