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
                printf("( %d, '%s' )\n", syn, token);
            }
            else
            {
                printf("(  %d, %s )\n", syn, token);
            }
        }
        else if (is_digit(ch))
        {
            int sum = 0;
            while (is_digit(ch))
            {
                sum = sum * 10 + (ch - '0');
                ch = fgetc(file);
            }
            printf("( 11,  %d )\n", sum);
        }
        else
        {
            switch (ch)
            {
            case '+':
                printf("( 13,  +  )\n");
                ch = fgetc(file);
                break;
            case '-':
                printf("( 14,  -  )\n");
                ch = fgetc(file);
                break;
            case '*':
                printf("( 15,  *  )\n");
                ch = fgetc(file);
                break;
            case '/':
                printf("( 16,  /  )\n");
                ch = fgetc(file);
                break;
            case ':':
            {
                ch = fgetc(file);
                if (ch == '=')
                {
                    printf("( 18, := )\n");
                    ch = fgetc(file);
                }
                else
                {
                    printf("( 17, :  )\n");
                }
                break;
            }
            case '<':
            {
                ch = fgetc(file);
                if (ch == '>')
                {
                    printf("( 21, <> )\n");
                    ch = fgetc(file);
                }
                else if (ch == '=')
                {
                    printf("( 22, <= )\n");
                    ch = fgetc(file);
                }
                else
                {
                    printf("( 20, <  )\n");
                }
                break;
            }
            case '>':
            {
                ch = fgetc(file);
                if (ch == '=')
                {
                    printf("( 24, >= )\n");
                    ch = fgetc(file);
                }
                else
                {
                    printf("( 23, >  )\n");
                }
                break;
            }
            case '=':
                printf("( 25, =  )\n");
                ch = fgetc(file);
                break;
            case ';':
                printf("( 26, ;  )\n");
                ch = fgetc(file);
                break;
            case '(':
                printf("( 27, (  )\n");
                ch = fgetc(file);
                break;
            case ')':
                printf("( 28, )  )\n");
                ch = fgetc(file);
                break;
            case '#':
                printf("( 0 , #  )\n");
                ch = fgetc(file);
                break;
            default:
                printf("(unknown, %c", ch);
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