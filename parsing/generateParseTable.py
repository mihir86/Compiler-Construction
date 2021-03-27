import pandas as pd

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

df = pd.read_csv("table.txt", sep='\t')

parseTable = []
for row in df.index:
    for col in df:
        val = df.iloc[row][col]
        if val == ' ':
            continue
        val = val.split(' ', 1)[0]
        col = dict[col]
        parseTable.append([row, col, val])

print(len(parseTable))
for entry in parseTable:
    print(entry[0], entry[1], entry[2])