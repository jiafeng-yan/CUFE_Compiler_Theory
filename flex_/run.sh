## count.l
cd flex_
flex count.l
tcc lex.yy.c
./a.out < ../data/test1.txt

