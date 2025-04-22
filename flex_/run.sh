## count.l
cd flex_
flex count.l
tcc lex.yy.c

## self test text
# ./a.out < ../data/test1.txt

## 实验1.1
./a.out < ../experiments/LEX/test.txt