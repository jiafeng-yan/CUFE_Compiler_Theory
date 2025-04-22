
#include "wordscan.h"
char prog[80];
int syn,kk;
char ch;
void lrparser();
void yucu();
void statement();
void expression();
void term();
void factor();
int kk=0;

void lrparser()
{
if (syn==1)
{
   scaner();
   yucu();
   if (syn==6)
   {
    scaner();
    if (syn==0 && kk==0) printf("success \n");
   }
   else
   {
    if(kk!=1) printf("error,lose 'end' ! \n");
    kk=1;
   }
}
else
{
   printf("error,lose 'begin' ! \n");
   kk=1;
}
    return;
}

void yucu()
{
statement();
while(syn==26)
{
   scaner();
   statement();
}
return;
}

void statement()
{
if (syn==10)
{
   scaner();
   if (syn==18)
      {
    scaner();
    expression();
   }
   else
   {
    printf("error!");
    kk=1;
   }
}
else
{
   printf("error!");
   kk=1;
}
return;
}


void expression()
{
term();
while(syn==13 || syn==14)
{
   scaner();
   term();
}
return;
}


void term()
{
factor();
while(syn==15 || syn==16)
{
   scaner();
   factor();
}
return;
}


void factor()
{
if(syn==10 || syn==11)   scaner();
else if(syn==27)
{
   scaner();
   expression();
   if(syn==28)   scaner();
	else {printf(" ')' output error!"); kk=1;}
}
    else { printf("output expression error!"); kk=1;}
return;
}


void main()
{
p=0;
printf(" ****************** A Grammar Parser ******************\n");
printf("Please input your source code!\n");
do
{
   scanf("%c",&ch);
   prog[p++]=ch;
}while(ch!='#');
p=0;
scaner();
    lrparser();
printf("The end of Parsing\n");
}
