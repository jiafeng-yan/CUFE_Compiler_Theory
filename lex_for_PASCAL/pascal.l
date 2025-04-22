%{
    #include<math.h>
%}
/* same as: [#include<math.h>] with indent */

DIGIT [0-9]
ID [A-Za-z][A-Za-z0-9]*

%%
{DIGIT}+    {
    printf("整数:  \t\t %s (%d)\n", yytext, atoi(yytext));
}
{DIGIT}+"."{DIGIT}*     {
    printf("浮点数:  \t %s (%g)\n", yytext, atof(yytext));
}
if|then|begin|end.|procedure|function|program|var|to|do    {
    printf("关键字:  \t %s\n", yytext);
}
{ID}    {
    printf("标识符:  \t %s\n", yytext);
}
"+"|"-"|"*"|"/"|"^"|":="     {
    printf("运算符 r:  \t %s\n", yytext);
}
":"|"("|")"     {
    printf("辅助符号 r:  \t %s\n", yytext);
}
'[^']*'     {
    printf("字符串： \t %s\n", yytext);
}

"{"[^}\n]*"}"   /* 忽略注释 */
[ \t\n\r;,]+         /* 忽略空白字符 */
.       printf("不能识别字符： \t %s\n", yytext);

%%
main(argc, argv)
int argc;
char **argv;
{
    ++argv, --argc;     /* 跳过执行文件名到第一个参数 */
    if(argc > 0) {
        yyin = fopen(argv[0], "r");
    } else {
        yyin = stdin;
        yylex();
    }
}

int yywrap() {
    return 1;
}