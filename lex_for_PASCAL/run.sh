## pascal.l
cd lex_for_PASCAL
flex pascal.l
tcc lex.yy.c
./a.out < ../data/pascal.txt

