#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define MAX_LEN 1000
// char token[MAX_LEN];
// char keys[6][5] = {"begin", "if", "then", "while", "do", "then"};
// bool error = false;

bool is_little(char c) {
    return 'a' <= c && c <= 'z';
}

bool is_alpha(char c)
{
    return is_little(c) || 'A' <= c && c <= 'Z';
}

bool is_digit(char c)
{
    return '0' <= c && c <= '9';
}

char ignore_blank(char ch, FILE *file) {
    while (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r')
    {
        ch = fgetc(file);
    }
    return ch;
}

char parse_ID(char ch, FILE *file) {
    ch = ignore_blank(ch, file);
    if (!is_alpha(ch)) return EOF;
    
    // Print or store the identifier if needed
    printf("ID:  %c", ch);
    
    // Continue reading valid ID characters (alphabets and digits)
    ch = fgetc(file);
    while (is_alpha(ch) || is_digit(ch) || ch == '_') {
        printf("%c", ch); // Print or store the rest of the identifier
        ch = fgetc(file);
    }
    printf("\n");
    
    return ch; // Return the first character not part of the ID
}

char parse_NUM(char ch, FILE *file) {
    ch = ignore_blank(ch, file);

    // Check for negative number
    bool negative = false;
    bool decimal = false;
    if (ch == '-') {
        negative = true;
        printf("NUM: -");

        ch = fgetc(file);
        if(ch == '.') {
            decimal = true;
            printf("0."); 
        } else if(is_digit(ch)) {
            printf("%c", ch);
        } else {
            return EOF;
        }
    } else if (is_digit(ch)) {
        printf("NUM: %c", ch);
    } else if(ch == '.') {
        printf("NUM: 0.");
        decimal = true;
    } else {
        return EOF;
    }
    
    ch = fgetc(file);
    while(is_digit(ch) || ch == '.') {
        if(ch == '.') {
            if(decimal) return EOF;
            decimal = true;
        }
        printf("%c", ch);
        ch = fgetc(file);
    }
    
    printf("\n");
    
    return ch; // Return the first character not part of the NUM
}

char parse_X(char ch, FILE *file);

char parse_Z(char ch, FILE *file) {
    ch = ignore_blank(ch, file);

    if(ch == '(') {                         //  (
        printf("\t( \n");
        ch = parse_X(fgetc(file), file);    //  X
        if(ch != ')') return EOF;           //  )
        printf("\t) \n");
        ch = fgetc(file);
    } else if(is_alpha(ch)) {               
        ch = parse_ID(ch, file);            //  ID
    } else {
        ch = parse_NUM(ch, file);           //  NUM
    }
    return ch;
}


char parse_Y(char ch, FILE *file) {
    ch = parse_Z(ch, file);                 //  Z

    ch = ignore_blank(ch, file);            //  {
    while(ch == '*' || ch == '/') {         //      [* | /]
        printf("\t%c \n", ch);
        ch = parse_Z(fgetc(file), file);    //      Z
        ch = ignore_blank(ch, file);        //  }
    }
    return ch;

}

char parse_X(char ch, FILE *file) {
    ch = parse_Y(ch, file);                 //  Y

    ch = ignore_blank(ch, file);            //  {
    while(ch == '+' || ch == '-') {         //      [+ | -]
        printf("\t%c \n", ch);
        ch = parse_Y(fgetc(file), file);    //      Y
        ch = ignore_blank(ch, file);        //  }
    }
    return ch;

}

char parse_C(char ch, FILE *file) {
    ch = parse_ID(ch, file);                //  ID

    ch = ignore_blank(ch, file);
    if(ch != ':') return EOF;               //  :=
    if(fgetc(file) != '=') return EOF;
    printf("\t:= \n");

    ch = ignore_blank(fgetc(file), file);     //  X
    ch = parse_X(ch, file);
    return ch;
}

char parse_B(char ch, FILE *file) {
    ch = parse_C(ch, file);                 //  C

    ch = ignore_blank(ch, file);            //  {
    while(ch == ';') {                      //      ;
        printf("\t; \n");
        ch = parse_C(fgetc(file), file);    //      C
        ch = ignore_blank(ch, file);        //  }
    }
    return ch;
}


bool analyzer(char* file_path) {
    FILE *file;

    file_path[strcspn(file_path, "\n")] = 0;

    file = fopen(file_path, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file: %s\n", file_path);
        return false;
    }

    char ch = fgetc(file);

    while(ch != EOF) {
        ch = ignore_blank(ch, file);

        if(ch != 'b') return false;                 //  begin
        if(fgetc(file) != 'e') return false;
        if(fgetc(file) != 'g') return false;
        if(fgetc(file) != 'i') return false;
        if(fgetc(file) != 'n') return false;
        printf(" begin \n");

        ch = parse_B(fgetc(file), file);            //  B

        if(ch != 'e') return false;
        if(fgetc(file) != 'n') return false;        //  end
        if(fgetc(file) != 'd') return false;
        printf(" end \n");

        return ignore_blank(fgetc(file), file) == '#';      //  #
    }

}



int main(int argc, char* argv[]) {
    if (argc != 2)
    {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }
    char *file_path = argv[1];

    if(analyzer(file_path)) {
        printf(" # \n");
        printf("Success!\n");
    } else {
        printf("Error!\n");
    }

    return 0;
}


/*
    用扩充的BNF表示如下:
    (1)<程序> → begin<语句串>end
    (2)<语句串> → <语句>{;<语句>}
    (3)<语句> → <赋值语句>
    (4)<赋值语句> → ID：＝<表达式>
    (5)<表达式> → <项>｛＋<项> | —项>｝
    (6)<项> → <因子>{*<因子> | /<因子>}
    (7)<因子> → ID | NUM | (<表达式>)

    solve:
    <程序>    ->   A
    <语句串>  ->   B 
    <语句>    ->   C
    <赋值>    ->   D
    <表达式>  ->   X 
    <项>      ->   Y
    <因子>    ->   Z

    A  ->  begin B end #
    B  ->  C {; C}
    C  ->  ID := X
    X  ->  Y {[+ | -] Y}
    Y  ->  Z {[* | /] Z}
    Z  ->  ID | NUM | [( X )]
*/



// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>

// #define MAX_LEN 1000
// char token[MAX_LEN];
// char keys[6][5] = {"begin", "if", "then", "while", "do", "then"};

// bool is_little(char c)
// {
//     return 'a' <= c && c <= 'z';
// }

// bool is_alpha(char c)
// {
//     return is_little(c) || 'A' <= c && c <= 'Z';
// }

// bool is_digit(char c)
// {
//     return '0' <= c && c <= '9';
// }

// void analyzer(char *file_path)
// {
//     FILE *file; // 文件指针

//     file_path[strcspn(file_path, "\n")] = 0;

//     file = fopen(file_path, "r");
//     if (file == NULL)
//     {
//         printf("Error: Could not open file: %s\n", file_path);
//         return;
//     }

//     char ch = fgetc(file);

//     while (ch != EOF)
//     {
//         // process
//         if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r')
//         {
//             ch = fgetc(file);
//             continue;
//         }

//         if (is_alpha(ch))
//         {
//             int index = 0;
//             while (is_alpha(ch) || is_digit(ch))
//             {
//                 token[index++] = ch;
//                 ch = fgetc(file);
//             }
//             token[index] = '\0';
//             int syn = 10;
//             for (int i = 0; i < 6; ++i)
//             { // 比对是否为 保留字
//                 if (strcmp(token, keys[i]) == 0)
//                 {
//                     syn = i + 1;
//                     break;
//                 }
//             }
//             if (syn == 10)
//             {
//                 printf("( %d, '%s' )\n", syn, token);
//             }
//             else
//             {
//                 printf("(  %d, %s )\n", syn, token);
//             }
//         }
//         else if (is_digit(ch))
//         {
//             int sum = 0;
//             while (is_digit(ch))
//             {
//                 sum = sum * 10 + (ch - '0');
//                 ch = fgetc(file);
//             }
//             printf("( 11,  %d )\n", sum);
//         }
//         else
//         {
//             switch (ch)
//             {
//             case '+':
//                 printf("( 13,  +  )\n");
//                 ch = fgetc(file);
//                 break;
//             case '-':
//                 printf("( 14,  -  )\n");
//                 ch = fgetc(file);
//                 break;
//             case '*':
//                 printf("( 15,  *  )\n");
//                 ch = fgetc(file);
//                 break;
//             case '/':
//                 printf("( 16,  /  )\n");
//                 ch = fgetc(file);
//                 break;
//             case ':':
//             {
//                 ch = fgetc(file);
//                 if (ch == '=')
//                 {
//                     printf("( 18, := )\n");
//                     ch = fgetc(file);
//                 }
//                 else
//                 {
//                     printf("( 17, :  )\n");
//                 }
//                 break;
//             }
//             case '<':
//             {
//                 ch = fgetc(file);
//                 if (ch == '>')
//                 {
//                     printf("( 21, <> )\n");
//                     ch = fgetc(file);
//                 }
//                 else if (ch == '=')
//                 {
//                     printf("( 22, <= )\n");
//                     ch = fgetc(file);
//                 }
//                 else
//                 {
//                     printf("( 20, <  )\n");
//                 }
//                 break;
//             }
//             case '>':
//             {
//                 ch = fgetc(file);
//                 if (ch == '=')
//                 {
//                     printf("( 24, >= )\n");
//                     ch = fgetc(file);
//                 }
//                 else
//                 {
//                     printf("( 23, >  )\n");
//                 }
//                 break;
//             }
//             case '=':
//                 printf("( 25, =  )\n");
//                 ch = fgetc(file);
//                 break;
//             case ';':
//                 printf("( 26, ;  )\n");
//                 ch = fgetc(file);
//                 break;
//             case '(':
//                 printf("( 27, (  )\n");
//                 ch = fgetc(file);
//                 break;
//             case ')':
//                 printf("( 28, )  )\n");
//                 ch = fgetc(file);
//                 break;
//             case '#':
//                 printf("( 0 , #  )\n");
//                 ch = fgetc(file);
//                 break;
//             default:
//                 printf("(unknown, %c", ch);
//                 ch = fgetc(file);
//                 break;
//             }
//         }
//     }

//     fclose(file);
//     return;
// }

// int main(int argc, char *argv[])
// {
//     if (argc != 2)
//     {
//         printf("Usage: %s <file_path>\n", argv[0]);
//         return 1;
//     }
//     char *file_path = argv[1];

//     analyzer(file_path);

//     return 0;
// }