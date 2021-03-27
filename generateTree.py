from nltk import Tree
import traceback

TreeFileName = "tree.txt"

try:
    with open("./" + TreeFileName) as treeFile:
        print("success")
        next(treeFile)
        for line in treeFile:
            print(line)
            t = Tree.fromstring(line)
            t.pretty_print()
except Exception:
    traceback.print_exc()