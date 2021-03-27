#copy from site to raw
#run script, generate table
#run python file, generate parseTable.txt
#run python file, generate reduceTable.txt

#if necessary, update the dict

cd ./parsing
cut -f 2- -d$'\t' raw.txt > table.txt
python3 generateParseTable.py >../parseTable.txt
python3 generateReduceTable.py >../reduceTable.txt
# cat ../feed2.txrt | tr ' ' '\n' | sort | uniq