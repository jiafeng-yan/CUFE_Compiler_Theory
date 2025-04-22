## pascal.l
cd lex_for_PASCAL
flex pascal.l
tcc lex.yy.c

## self test text
# ./a.out < ../data/pascal.txt

## 实验1.2
./a.out < ../experiments/LEX/pascal.txt