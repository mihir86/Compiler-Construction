from nltk import Tree
import traceback

TreeFileName = "tree.txt"

try:
    with open("./" + TreeFileName) as treeFile:
        for line in treeFile:
            print(line)
            t = Tree.fromstring(line, brackets='[]', remove_empty_top_bracketing=True)
            t.pretty_print()
except Exception:
    traceback.print_exc()