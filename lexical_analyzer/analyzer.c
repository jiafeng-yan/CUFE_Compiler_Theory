#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 1000
char token[MAX_LEN];
char keys[6][5] = {"begin", "if", "then", "while", "do", "then"};

bool is_little(char c)
{
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

void analyzer(char *file_path)
{
    FILE *file; // 文件指针

    file_path[strcspn(file_path, "\n")] = 0;

    file = fopen(file_path, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file: %s\n", file_path);
        return;
    }

    char ch = fgetc(file);

    while (ch != EOF)
    {
        // process
        if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r')
        {
            ch = fgetc(file);
            continue;
        }

        if (is_alpha(ch))
        {
            int index = 0;
            while (is_alpha(ch) || is_digit(ch))
            {
                token[index++] = ch;
                ch = fgetc(file);
            }
            token[index] = '\0';
            int syn = 10;
            for (int i = 0; i < 6; ++i)
            { // 比对是否为 保留字
                if (strcmp(token, keys[i]) == 0)
                {
                    syn = i + 1;
                    break;
                }
            }
            if (syn == 10)
            {
                printf("(    %d   ,    '%s' \t)\n", syn, token);
            }
            else
            {
                printf("(     %d   ,    %s \t\t)\n", syn, token);
            }
        }
        else if (is_digit(ch) || ch == '.')
        {
            int index = 0;
            bool decimal = false;
            while(is_digit(ch) || ch == '.') {
                if(ch == '.') {
                    if(decimal) {
                        printf("\n Error: Decimal with two dot!\n");
                        return;
                    }
                    decimal = true;
                }
                token[index++] = ch;
                ch = fgetc(file);
            }
            token[index] = '\0';
            printf("(    11   ,     %s \t)\n", token);
        }
        else
        {
            switch (ch)
            {
            case '+':
                printf("(    13   ,     +  \t)\n");
                ch = fgetc(file);
                break;
            case '-':
                printf("(    14   ,     -  \t)\n");
                ch = fgetc(file);
                break;
            case '*':
                printf("(    15   ,     *  \t)\n");
                ch = fgetc(file);
                break;
            case '/':
                printf("(    16   ,     /  \t)\n");
                ch = fgetc(file);
                break;
            case ':':
            {
                ch = fgetc(file);
                if (ch == '=')
                {
                    printf("(    18   ,    := \t)\n");
                    ch = fgetc(file);
                }
                else
                {
                    printf("(    17   ,    :  \t)\n");
                }
                break;
            }
            case '<':
            {
                ch = fgetc(file);
                if (ch == '>')
                {
                    printf("(    21   ,    <> \t)\n");
                    ch = fgetc(file);
                }
                else if (ch == '=')
                {
                    printf("(    22   ,    <= \t)\n");
                    ch = fgetc(file);
                }
                else
                {
                    printf("(    20   ,    <  \t)\n");
                }
                break;
            }
            case '>':
            {
                ch = fgetc(file);
                if (ch == '=')
                {
                    printf("(    24   ,    >= \t)\n");
                    ch = fgetc(file);
                }
                else
                {
                    printf("(    23   ,    >  \t)\n");
                }
                break;
            }
            case '=':
                printf("(    25   ,    =  \t)\n");
                ch = fgetc(file);
                break;
            case ';':
                printf("(    26   ,    ;  \t)\n");
                ch = fgetc(file);
                break;
            case '(':
                printf("(    27   ,    (  \t)\n");
                ch = fgetc(file);
                break;
            case ')':
                printf("(    28   ,    )  \t)\n");
                ch = fgetc(file);
                break;
            case '#':
                printf("(    0    ,    #  \t)\n");
                ch = fgetc(file);
                break;
            default:
                printf("(   unknown   ,    %c \t)\n", ch);
                ch = fgetc(file);
                break;
            }
        }
    }

    fclose(file);
    return;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }
    char *file_path = argv[1];

    analyzer(file_path);

    return 0;
}