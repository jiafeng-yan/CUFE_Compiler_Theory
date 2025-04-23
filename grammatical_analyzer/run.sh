## analyzer.c
cd ./grammatical_analyzer
gcc ./analyzer.c

## self test c
echo "Result of an example should be passed:"
./a.out  ../data/grammar_pass_example.txt

echo
echo "Result of an example should not be passed:"
./a.out ../data/grammar_unpass_example.txt


# ## 实验3  Example
# cd ./experiments/GrammarAnalyzer
# gcc YFFX.C
# ...