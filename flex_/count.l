/* 何炎祥编《编译原理》 例13.1 (P217) */
    int num_chars = 0, num_lines = 0;   
    /* C 语言全局变量，must with indent (任何非顶行文字将被直接拷贝到输出文件中, same as %{ ... %}) */
%%
\n  ++num_chars, ++num_lines;    /* no indent */
.   ++num_chars;

%%
main() {
    yylex();
    printf("本文件的行数为：%d，字符数为：%d\n", num_lines, num_chars);
}
int yywrap() {  /* 文件结束处理函数，yylex读到EOF时调用该函数，用户必须提供该函数，否在在编译连接时会出错 */
    return 1;   /* 返回 1 表示文件扫描结束，不必再扫描别的文件 */
}